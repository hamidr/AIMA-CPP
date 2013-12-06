#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include "node.hpp"

namespace AI 
{

using std::shared_ptr;
using std::make_shared;


template <typename T, typename Impl>
struct Problem 
{
    using state_type = T;
    using node_type = Node<state_type>;
    using node_ptr = typename node_type::node_ptr;
    using leafs_list = typename node_type::leafs_list;

    Problem(const Problem&) = delete;
    Problem(Problem&&) = default;

    Problem(node_ptr && head)
        : mTree(move(head)) 
    { }

    Problem(T head)
    : mTree(make_shared<node_type>(head)) 
    { }

    inline node_type & getRoot() const
    { return *mTree; }

    inline node_ptr initial() const 
    { return mTree->shared_from_this(); }

    bool testGoal(const node_ptr &node) const 
    {
        T && val = node->getState();
        getImpl().watch(val);
        return getImpl().isGoal(val);
    }

    leafs_list successors( const node_ptr &state) const
    { return state->expand(); }

    void watch(const T &state) const
    { std::cout << state << std::endl; }

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
    ProblemMaker(T root, T goal, const G &gen )
    : daddy_type(forward<T>(root)), mGoal(forward<T>(goal)), mGenerator(gen)
    { }

    ProblemMaker(typename daddy_type::node_ptr node, T goal, const G &gen )
    : daddy_type(move(node)), mGoal(forward<T>(goal)), mGenerator(gen)
    { }

    bool isGoal (const T & value) const {
        if ( value == mGoal )
            return true;
        return false;
    }

    typename Node<T>::leafs_list 
    successors(const typename daddy_type::node_ptr &state) const 
    { return mGenerator(state); }


private:
    const T mGoal;
    const G &mGenerator;
};

template<typename T>
struct DefaultExpander
{
    typename Node<T>::leafs_list 
    operator()(const typename Node<T>::node_ptr &state) const 
    { return state->expand(); }
};

}

using namespace Private;


template <typename T, typename G>
ProblemMaker<T,G> makeProblem(T root, T goal, G gen )
{
    return ProblemMaker<T,G>(forward<T>(root), forward<T>(goal), gen);
}

template <typename T, typename G = DefaultExpander<T>>
ProblemMaker<T,G> makeProblem(const typename Node<T>::node_ptr &graph, T goal)
{
    G gen;
    return ProblemMaker<T,G>(graph, forward<T>(goal), gen);
}


#define MAKE_PROBLEM(ROOT, GOAL, NODE, STATE, GEN) makeProblem(ROOT, GOAL, [&]( \
            const Node<decltype(ROOT)>::node_ptr & NODE) { \
        typename Node<decltype(ROOT)>::leafs_list GEN; \
        auto STATE = NODE ->getState();

#define END_PROBLEM })

#define DefClassProblem(name, type) struct name : public Problem<type, name>

}

#endif
