#ifndef _INC_MY_ARITHMETIC_
#define _INC_MY_ARITHMETIC_

#include "Object.h"
#include <limits>

class Solution : public Object
{
public:
    virtual bool IsFeasible () const = 0;
    virtual bool IsComplete () const = 0;
    virtual int Objective () const = 0;
    virtual int Bound () const = 0;
    virtual Solution& Clone () const = 0;
    virtual Iterator& Successors () const = 0;
};

class Solver
{
protected:
    Solution* bestSolution;
    int bestObjective;
    void UpdateBest (Solution const&);
    virtual void DoSolve (Solution const&) = 0;
public:
    virtual Solution& Solve (Solution const&);
};

Solution& Solver::Solve (Solution const& initial)
{
    bestSolution = 0;
    bestObjective = numeric_limits<int>::max ();
    DoSolve (initial);
    if (bestSolution == 0)
	throw domain_error ("no feasible solution found");
    return *bestSolution;
}

void Solver::UpdateBest (Solution const& solution)
{
    if (solution.IsFeasible() &&
	solution.Objective () < bestObjective)
    {
	delete bestSolution;
	bestSolution = &(solution.Clone ());
	bestObjective = solution.Objective ();
    }
}

class DepthFirstSolver : public Solver
{
    void DoSolve (Solution const&);
};

void DepthFirstSolver::DoSolve (Solution const& solution)
{
    if (solution.IsComplete ())
	UpdateBest (solution);
    else
    {
	Iterator& i = solution.Successors ();
	while (!i.IsDone ()) {
	    Solution& successor = dynamic_cast<Solution&> (*i);
	    DoSolve (successor);
	    delete &successor;
	    ++i;
	}
	delete &i;
    }
}


#endif //_INC_MY_ARITHMETIC_