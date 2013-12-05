#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include "node.hpp"

namespace AI 
{

using std::shared_ptr;
using std::make_shared;

template <typename T>
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
        this->watch(val);
        return this->isGoal(val);
    }

    virtual bool isGoal(const T &value) const = 0;

    virtual leafs_list successors( const node_ptr &state) const
    { return state->expand(); }

    virtual void watch(const T & n) const {
        std::cout << n << std::endl;
    }

protected:
    using daddy_type = Problem<T>;

private:
    const node_ptr mTree;
};


namespace Private 
{

template<typename T, typename G >
struct ProblemMaker : public Problem<T>
{

    ProblemMaker(T root, T goal, const G &gen )
    : Problem<T>(forward<T>(root)), mGoal(forward<T>(goal)), mGenerator(gen)
    { }

    ProblemMaker(typename Problem<T>::node_ptr node, T goal, const G &gen )
    : Problem<T>(move(node)), mGoal(forward<T>(goal)), mGenerator(gen)
    { }

    bool isGoal (const T & value) const override {
        if ( value == mGoal )
            return true;
        return false;
    }

    virtual typename Problem<T>::leafs_list 
    successors(const typename Problem<T>::node_ptr &state) const override 
    {
        return mGenerator(state);
    }

private:
    const T mGoal;
    const G &mGenerator;
};

template<typename T>
struct DefaultExpander
{
    typename Problem<T>::leafs_list 
    operator()(const typename Problem<T>::node_ptr &state) const 
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
ProblemMaker<T,G> makeProblem(const typename Problem<T>::node_ptr &graph, T goal)
{
    G gen;
    return ProblemMaker<T,G>(graph, forward<T>(goal), gen);
}


#define MAKE_PROBLEM(ROOT, GOAL, NODE, STATE, GEN) makeProblem(ROOT, GOAL, [&]( \
            const Node<decltype(ROOT)>::node_ptr & NODE) { \
        typename Problem<decltype(ROOT)>::leafs_list GEN; \
        auto STATE = NODE ->getState();

#define END_PROBLEM })


}

#endif
