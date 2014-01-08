#include <string>

#include "problem.hpp"

using namespace AI;
using std::string;

DefClassProblem(RomaniaCities, string)
{
    RomaniaCities();

    bool isGoal (const string &city) const ;

    long F(const node_ptr &n, const long &gn, const long &parent_cost) const;

    long H(const node_ptr &n) const;

private:
    node_type::nodeptr_cost_map hTable;
};

