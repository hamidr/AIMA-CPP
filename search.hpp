#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <set>
#include <memory>
#include <deque>
#include <stack>
#include <memory>
#include "node.hpp"

namespace AI 
{

using std::shared_ptr;
using std::make_shared;

template <typename T>
struct Problem
{
	using value_type = T;
	using node_type = Node<value_type>;
	using node_ptr = typename node_type::node_ptr;
	using leafs_list = typename node_type::leafs_list;

	Problem(const Problem&) = delete;
	Problem(Problem&&) = default;

	Problem(T head)
	: mTree(std::make_shared<node_type>(head)) 
	{ }

	inline node_type & getRoot() const
	{ return *mTree; }

	inline leafs_list expand(const node_ptr &node)
	{ return node->getLeafs(); }

	inline node_ptr initial() const 
	{ return mTree; }

	bool testGoal(const node_ptr &node) const 
	{
		T && val = node->getValue();
		this->watch(val);
		return this->isGoal(val);
	}

	virtual bool isGoal(const T &n) const = 0; 
	virtual void watch(const T & n) const = 0; 

protected:
	using daddy_type = Problem<T>;

private:
	node_ptr mTree;
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
		auto &&val = this->front();
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
		auto &&val = this->top();
		stack<T>::pop(); // oops :P watch out the recurisve bug!
		return val;
	}
};


template < typename C, typename P, typename E = typename C::value_type  >
E treeSearch(C fringe, P &problem)
{
	fringe.push(problem.initial());
	while(! fringe.empty())
	{
		E node = fringe.pop();

		if ( problem.testGoal(node) )
			return node;

		auto nodes = problem.expand(node);
		for(auto &e : nodes)
			fringe.push(e);
	}

	return problem.initial();
}


template<typename T>
struct NodePtrCompare : public std::less<T>
{
	bool operator()(const T &t1, const T &t2)
	{ return t1->getValue() < t2->getValue(); }
};

template < typename C, typename P, typename E = typename C::value_type >
E graphSearch(C fringe, P &problem)
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

		auto nodes = problem.expand(node);
		for(const E &e : nodes)
			fringe.push(e);
	}

	return problem.initial();
}

}

using namespace Private;

template <typename P>
void BFTS(P p)
{
	treeSearch(MyQueue<typename P::node_ptr>(), p );
}

template <typename P>
void DFTS(P p)
{
	treeSearch(MyStack<typename P::node_ptr>(), p );
}

template <typename P>
void DFGS(P p)
{
	graphSearch(MyStack<typename P::node_ptr>(), p);
}

template <typename P>
void BFGS(P p)
{
	graphSearch(MyQueue<typename P::node_ptr>(), p );
}

}
#endif
