#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <set>
#include <memory>
#include <deque>
#include <stack>
#include <memory>
#include <iostream>
#include <queue>

#include "problem.hpp"

namespace AI 
{

namespace Private 
{

using std::set;
using std::stack;
using std::deque;
using std::priority_queue;

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
E treeSearch(C fringe, const P &problem)
{
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

template<typename T>
struct NodePtrCompare : public std::less<T>
{
	bool operator()(const T &t1, const T &t2)
	{ return t1->getState() > t2->getState(); }
};

template < typename C, typename P, typename E = typename C::value_type, typename Compair = NodePtrCompare<E> >
E graphSearch(C fringe, const P &problem)
{
	set<E, Compair> explored;

	fringe.push(problem.initial());
	while(! fringe.empty())
	{
		E node = fringe.pop();

		if (explored.insert(node).second == false)
			continue;

		if ( problem.testGoal(node) )
			return node;

		auto nodes = problem.successors(node);
		for( const E &e : nodes)
			fringe.push(e);
	}

	return problem.initial();
}

}

using namespace Private;


template <typename P, typename R = typename P::node_ptr>
R BFTS(P p)
{
	return treeSearch(MyQueue<R>(), p );
}

template <typename P, typename R = typename P::node_ptr>
R DFTS(P p)
{
	return treeSearch(MyStack<R>(), p );
}

template <typename P, typename R = typename P::node_ptr>
R DFGS(P p)
{
	return graphSearch(MyStack<R>(), p);
}

template <typename P, typename R = typename P::node_ptr>
R BFGS(P p)
{
	return graphSearch(MyQueue<R>(), p );
}

template < 	typename T,
		 	typename Compare = NodePtrCompare<T>,
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
R WTH(P p)
{
	return graphSearch(MyPriorityQueue<R>(), p );
}


}
#endif
