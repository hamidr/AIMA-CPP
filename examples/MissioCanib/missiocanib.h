#include "common.hpp" 
#include "problem.hpp"

using std::vector;
using namespace AI;

typedef tuple<int, int, int> mcbVec;

DefClassProblem(MiCaBo, mcbVec)
{
    MiCaBo();

    leafs_list successors(const node_ptr &state) const;
    bool isGoal (const mcbVec &state) const;
    long H(const node_ptr &node) const;

private:
    bool checkLimit(const int &c) const;

    bool isValid(const mcbVec &succ) const;
    mcbVec otherSide(const mcbVec &succ) const;

    long H(const mcbVec &state) const;

    mcbVec apply(const node_ptr &node, const mcbVec &action) const;

    const vector<mcbVec> actions = {
        mcbVec(-1,-1,-1), mcbVec(-1,0,-1), mcbVec(0,-1,-1), mcbVec(-2,0,-1), mcbVec(0,-2,-1), 
        mcbVec(1,1,1), mcbVec(1,0,1), mcbVec(0,1,1), mcbVec(2,0,1), mcbVec(0,2,1),
    };
};

