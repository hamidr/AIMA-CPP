#include "missiocanib.h"

DefConstructorProblem(MiCaBo, mcbVec(3,3,1))
{ }

MiCaBo::leafs_list MiCaBo::successors(const node_ptr &state) const
{ 
    leafs_list leafs;
    for( const auto &act : actions ) {
        const auto next = apply(state, act);
        if ( isValid(next) && isValid(otherSide(next)) )
            leafs.push_back(makeNode(next, state, H(next)));
    }

    return leafs;
}

bool MiCaBo::checkLimit(const int &c) const 
{ 
    return ( c <= 3 && c >= 0 );
}

mcbVec MiCaBo::otherSide(const mcbVec &succ) const
{
    const int &ms = get<0>(succ);
    const int &cs = get<1>(succ);
    const int &b = get<2>(succ);

    return mcbVec(3-ms, 3-cs, 1-b);
}

bool MiCaBo::isValid(const mcbVec &succ) const
{
    const int &ms = get<0>(succ);
    const int &cs = get<1>(succ);
    const int &b = get<2>(succ);

    return checkLimit(ms) && checkLimit(cs) && ( ms == 0 ? true : ms >= cs ) && (b == 0 || b == 1);
}

long MiCaBo::H(const node_ptr &node) const
{
    const auto &state = node ->getState();
    return  H(state);
}


long MiCaBo::H(const mcbVec &state) const
{
    return  get<0>(state) + get<1>(state);
}


mcbVec MiCaBo::apply(const node_ptr &node, const mcbVec &action) const
{
    const auto &state = node->getState();
    return mcbVec( 
            get<0>(state) +  get<0>(action),
            get<1>(state) +  get<1>(action),
            get<2>(state) +  get<2>(action)
        );
}

bool MiCaBo::isGoal(const mcbVec &state) const 
{ 
    return state == mcbVec(0,0,0); 
}


