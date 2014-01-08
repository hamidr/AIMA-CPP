#include "problem.hpp"

using namespace AI;

    //
    //             ___10__
    //           /    |   \ 
    //         40    12_   11 ___
    //       / |    / | \    \  \
    //    22  23   6  8  20   9  25
    //                |           |
    //                7           26
    // 

DefClassProblem(TreeNumbers, int)
{
    TreeNumbers();

    bool isGoal (const int & value) const; 

    long F(const node_ptr &n, const long &gn, const long &parent_cost) const;
};

