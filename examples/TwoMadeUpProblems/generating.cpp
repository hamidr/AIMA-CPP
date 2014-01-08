#include "generating.h"

Generating::Generating()
: Problem(0)
{ }

Generating::leafs_list 
Generating::successors( const node_ptr &state) const
{
    leafs_list eles;

    static int k = 0, j = 0;

    ++k;
    ++j;

    if ( k >= 15 ) 
        return eles;

    for(int i = j; i < j+2; ++i)
        eles.push_back(makeNode(state->getState()+i, state));

    return eles;
}

bool Generating::isGoal (const int & value) const 
{
    return ( value == 104 );
}


