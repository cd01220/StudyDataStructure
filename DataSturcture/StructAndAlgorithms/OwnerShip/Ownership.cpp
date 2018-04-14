#include "Ownership.h" 

Ownership::Ownership () : isOwner (true)
{}

Ownership::Ownership (Ownership& arg) : isOwner (arg.isOwner)
{ 
    arg.isOwner = false; 
}

void Ownership::AssertOwnership ()
{ 
    isOwner = true; 
}

void Ownership::RescindOwnership ()
{ 
    isOwner = false; 
}

bool Ownership::IsOwner () const
{ 
    return isOwner; 
}

