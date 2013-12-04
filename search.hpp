#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <set>
#include <memory>
#include <deque>
#include <stack>
#include <memory>
#include <iostream>

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

	virtual leafs_list successors( node_ptr &state) const
	{ return state->expand(); }

	virtual void pathCost(const node_ptr &state1) const {} 

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

using std::set;
using std::stack;
using std::deque;

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
		E node(fringe.pop());

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
	{ return t1->getState() < t2->getState(); }
};

template < typename C, typename P, typename E = typename C::value_type >
E graphSearch(C fringe, const P &problem)
{
	set<E, NodePtrCompare<E>> explored;

	fringe.push(problem.initial());
	while(! fringe.empty())
	{
		E node = fringe.pop();

		if (explored.insert(node).second == false)
			continue;

		if ( problem.testGoal(node) )
			return node;

		auto &&nodes = problem.successors(node);
		for( const E e : nodes)
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

}
#endif
