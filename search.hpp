#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <set>
#include <memory>
#include <deque>
#include <stack>
#include <memory>
#include <iostream>
#include <queue>
#include <limits>
#include <algorithm>


#include "problem.hpp"

namespace AI 
{

namespace Private 
{

using std::set;
using std::stack;
using std::deque;
using std::priority_queue;
using std::sort;
using std::min;
using std::max;
using std::less;

template <typename T>
struct MyQueue : public deque<T>
{
    using deque<T>::deque;

    void push(const T val)
    { this->push_back(val); }

    T pop() 
    {
        auto val = this->front();
        this->pop_front();
        return val;
    }
};

template <typename T>
struct MyStack : public stack<T>
{
    using stack<T>::stack;

    T pop() 
    {
        auto val = this->top();
        stack<T>::pop(); // oops :P watch out the recurisve bug!
        return val;
    }
};


template < typename C, typename P, typename E = typename C::value_type  >
E treeSearch(const P &problem)
{
    C fringe;
    fringe.push(problem.initial());

    while(! fringe.empty())
    {
        E node = fringe.pop();

        if ( problem.testGoal(node) )
            return node;

        auto nodes = problem.successors(node);
        for(const E &e : nodes)
            fringe.push(e);
    }

    return problem.initial();
}

template < typename C, typename P, typename E = typename C::value_type, typename Compare = NodePtrCompare<E> >
E graphSearch(const P &problem)
{
    C fringe;
    fringe.push(problem.initial());

    set<E, Compare> explored;

    while(! fringe.empty())
    {
        E node = fringe.pop();

        if ( explored.insert(node).second == false )
            continue;

        if ( problem.testGoal(node) )
            return node;

        auto nodes = problem.successors(node);
        for( const E &e : nodes)
            fringe.push(e);
    }

    return problem.initial();
}


template<typename T>
struct NodeCostCompare : public less<T>
{
    bool operator()(const T &t1, const T &t2)
    { return t1->cost() > t2->cost(); }
};

template<typename T>
struct NodeDepthCompare : public less<T>
{
    bool operator()(const T &t1, const T &t2)
    { return t1->depth() > t2->depth(); }
};

template <typename T,
         typename Compare = NodeCostCompare<T>,
         typename Parent =  priority_queue<T, typename priority_queue<T>::container_type, Compare> >
struct MyPriorityQueue : public Parent 
{
    using typename Parent::priority_queue;

    T pop()
    {
        T val = this->top();
        Parent::pop();
        return val;
    }
};


template <typename P, typename R = typename P::node_ptr>
R recursiveDLS(const R &node, P &p, int &&limit)
{
    if ( p.testGoal(node) )
        return node;
    else if ( limit == 0 )
        return p.initial();
    else {
        auto nodes = p.successors(node);
        for ( const R &n : nodes ) {
            auto result = recursiveDLS(n, p, limit - 1);
            if ( result != p.initial() )
                return result;
        }
    }
    return p.initial();
}

template <typename P, typename R = typename P::node_ptr>
R RBFS(const R &node, P &p, long limit)
{
    if ( p.testGoal(node) )
        return node;

    auto nodes = p.successors(node);
    if ( !nodes.size() )
        return p.initial();

    for( const auto &s : nodes ) 
        s->setCost(max(s->g() + p.H(s), node->cost()));

    while ( true )
    {
        sort(nodes.begin(), nodes.end(), [](const R& n1, const R &n2) { return n1->cost() < n2->cost(); });

        auto best = nodes.at(0);
        if ( best->cost() > limit )
            return p.initial();

        auto alternative = nodes.at(1);

        auto result = RBFS(best, p, min<long>(limit, alternative->cost()));
        if ( result != p.initial() )
            return result;
    }
}

}

using namespace Private;

template <typename P, typename R = typename P::node_ptr>
R breadthFirstTS(P p)
{
    return treeSearch<MyQueue<R>>( p );
}

template <typename P, typename R = typename P::node_ptr>
R depthFirstTS(P p)
{
    return treeSearch<MyStack<R>>( p );
}

template <typename P, typename R = typename P::node_ptr>
R depthFirstGS(P p)
{
    return graphSearch<MyStack<R>>( p );
}

template <typename P, typename R = typename P::node_ptr>
R breadthFirstGS(P p)
{
    return graphSearch<MyQueue<R>>( p );
}

template <typename P, typename R = typename P::node_ptr>
R bestFirstTS(P p) 
{
    return treeSearch<MyPriorityQueue<R>>( p );
}

template <typename P, typename R = typename P::node_ptr>
R bestFirstGS(P p) // abstract can be everything
{
    return graphSearch<MyPriorityQueue<R>>( p );
}

 /*  Following search strategies have only different f(n) :
  *  UCS:  parent's cost + g(n) 
  *  greedy: g(n)
  *  greedyBestFirst: h(n)
  *  A* : h(n) + g(n)
 */

template <typename P, typename R = typename P::node_ptr>
R depthLimitedSearch(P p, int limit)
{
    return recursiveDLS(p.initial(), p, move(limit));
}

template <typename P, typename R = typename P::node_ptr>
R iterativeDeepeningSearch(P p, const int stop = 100)
{
    int i = 1;
    while ( i != stop ) {
        auto result = depthLimitedSearch(p, i++);
        if ( result != p.initial() )
            return result;
    }

    return p.initial();
}

template <typename P, typename R = typename P::node_ptr>
R recursiveBestFirstSearch(P p)
{
    return RBFS(p.initial(), p, std::numeric_limits<long>::max());
}

}

#endif
