#ifndef NODE_TEST_HPP
#define NODE_TEST_HPP

#include <string>

#include <stdio.h>
#include "search.hpp"

using namespace AI;

DefClassProblem(IntProblem, int)
{
    IntProblem()
    : Problem(10) 
    {
        auto &_40 = getRoot().addLeaf(40,50);
        _40.addLeaf(22);
        _40.addLeaf(23);
        auto &_12 = getRoot().addLeaf(12);
        _12.addLeaf(6);
        _12.addLeaf(8).addLeaf(7,4);
        _12.addLeaf(20);
        auto &_11 = getRoot().addLeaf(11,12);
        _11.addLeaf(9);
        _11.addLeaf(25).addLeaf(26);


        //
        //             ___10__
        //           /    |   \ 
        //         40    12_   11 ___
        //       / |    / | \    \  \
        //    22  23   6  8  20   9  25
        //                |           |
        //                7           26
        // 
        //  

    }

    bool isGoal (const int & value) const {
        if ( value == 7 )
            return true;
        return false;
    }
};



DefClassProblem(TestProblem, int)
{
    TestProblem()
    : Problem(0)
    { }

    leafs_list successors( const node_ptr &state) const
    {
        leafs_list eles;

        static int k = 0, j = 0;

        ++k;
        ++j;

        if ( k >= 15 ) 
            return eles;
            

        for(int i = j; i < j+2; ++i)
            eles.push_back(makeNode(state->getState()+i, state, state->pathCost() + 1));

        return eles;

    }

    bool isGoal (const int & value) const {
        if( value == 104 )
            return true;
        return false;
    }
};


DefClassProblem(AlphabetProblem, char)
{
    AlphabetProblem()
    : Problem('A') 
    {
        auto &b = getRoot().addLeaf('B');
            auto &d = b.addLeaf('D');
                auto &h = d.addLeaf('H');
                auto &i = d.addLeaf('I');
            auto &e = b.addLeaf('E');
                auto &j = e.addLeaf('J');
                auto &k = e.addLeaf('K');

        auto &c = getRoot().addLeaf('C');
            auto &f = c.addLeaf('F');
                auto &l = f.addLeaf('L');
                auto &m = f.addLeaf('M');
            auto &g = c.addLeaf('G');
                auto &n = g.addLeaf('N');
                auto &o = g.addLeaf('O');
    }

    bool isGoal (const char & n) const {
        if ( n == 'M' )
            return true;
        return false;
    }
};

#endif
