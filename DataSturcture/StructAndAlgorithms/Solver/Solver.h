#ifndef _SOLVER_H_
#define _SOLVER_H_

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



#endif //_SOLVER_H_