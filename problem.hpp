#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include "node.hpp"

namespace AI 
{

using std::shared_ptr;
using std::make_shared;

using std::cout;
using std::endl;


template <typename T, typename Impl>
struct Problem 
{
    using state_type = T;
    using node_type = Node<state_type>;
    using node_ptr = typename node_type::node_ptr;
    using leafs_list = typename node_type::leafs_list;

    Problem(node_ptr head)
        : mTree(move(head)) 
    { }

    Problem(T head)
    : mTree(make_shared<node_type>(head)) 
    { }

    inline node_type & getRoot() const
    { return *mTree; }

    inline node_ptr initial() const 
    { return mTree; }

    bool testGoal(const node_ptr &node) const 
    {
        T && val = node->getState();
        getImpl().watch(node);
        return getImpl().isGoal(val);
    }

    leafs_list successors(const node_ptr &state) const
    { 
        leafs_list leafs;
        const auto edgeBoarder = state->edges();

        for(auto itr = edgeBoarder.first; itr != edgeBoarder.second; ++itr)
        {
            const node_ptr &node = itr->first;
            const long &cost = itr->second;

            leafs.push_back(makeNode(node, state, getImpl().F(node, cost, state->cost())));
        }

        return leafs;
    }

    void watch(const node_ptr &node) const
    {
        cout << "Visited node \"" 
            << node->getState() 
            << "\" with cost of " 
            << node->cost()
            << " and depth of " 
            << node->depth() 
            << endl;
    }

    long F(const node_ptr &n, const long &gn, const long &pcost) const 
    { return gn; }

private:
    const Impl &getImpl() const
    { return *static_cast<const Impl*>(this); }

    const node_ptr mTree;
};



namespace Private 
{

template<typename T, typename G >
struct ProblemMaker : public Problem<T, ProblemMaker<T,G>>
{

    using daddy_type = Problem<T, ProblemMaker<T,G>>;
    using node_ptr = typename daddy_type::node_ptr;

    ProblemMaker(T root, T goal, const G &gen )
    : daddy_type(forward<T>(root)), mGoal(makeNode<T>(forward<T>(goal))), mGenerator(gen)
    { }

    ProblemMaker(const node_ptr &node, T goal, const G &gen )
    : daddy_type(node), mGoal(makeNode<T>(forward<T>(goal))), mGenerator(gen)
    { }

    ProblemMaker(node_ptr node, node_ptr goal, const G &gen )
    : daddy_type(node), mGoal(goal), mGenerator(gen)
    { }

    bool isGoal (const T & value) const 
    { return value == mGoal->getState(); }

    typename Node<T>::leafs_list 
    successors(const node_ptr &state) const 
    { return mGenerator(state); }

private:
    const node_ptr mGoal;
    const G &mGenerator;
};


}

using namespace Private;

template <typename T, typename G>
ProblemMaker<T,G> makeProblem(T root, T goal, G gen )
{
    return ProblemMaker<T,G>(forward<T>(root), forward<T>(goal), gen);
}

template <typename T, typename E = typename T::element_type::state_type , typename G >
ProblemMaker<E,G> makeProblem(const T &graph, const T &goal)
{
    G gen;
    return ProblemMaker<E,G>(graph, goal, gen);
}


#define MAKE_PROBLEM(ROOT, GOAL, NODE, STATE, GEN) makeProblem(ROOT, GOAL, [&]( \
            const Node<decltype(ROOT)>::node_ptr & NODE) { \
        typename Node<decltype(ROOT)>::leafs_list GEN; \
        auto STATE = NODE ->getState();

#define END_PROBLEM })

#define DefClassProblem(name, type) struct name : public Problem<type, name>
#define DefConstructorProblem(p, initial) p::p() : Problem(initial)

}

#endif
