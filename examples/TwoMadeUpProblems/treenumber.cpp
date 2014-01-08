#include "treenumber.h"

TreeNumbers::TreeNumbers()
: Problem(10) 
{
    auto &_40 = getRoot().connect1(40,50);
    _40.connect1(22);
    _40.connect1(23);
    auto &_12 = getRoot().connect1(12);
    _12.connect1(6);
    _12.connect1(8).connect1(7,4);
    _12.connect1(20);
    auto &_11 = getRoot().connect1(11,12);
    _11.connect1(9);
    _11.connect1(25).connect1(26);
}

bool TreeNumbers::isGoal (const int & value) const {
    return ( value == 7 );
}

long TreeNumbers::F(const node_ptr &n, const long &gn, const long &parent_cost) const
{ return parent_cost + gn; }
