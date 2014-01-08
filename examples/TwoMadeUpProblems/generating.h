
#include "problem.hpp"

using namespace AI;

DefClassProblem(Generating, int)
{
    Generating();

    leafs_list successors( const node_ptr &state) const;

    bool isGoal (const int & value) const;
};

