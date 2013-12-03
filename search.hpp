#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <set>
#include <memory>
#include <deque>
#include <stack>


namespace AI 
{

template <typename T>
struct Problem
{
	using value_type = T;

  	Problem(T head)
	: mTree(new member_type(head)) 
	{ }

	Node<T> & getRoot() const
	{ return *mTree; }

	typename Node<T>::leafs_list expand(const Node<T> *node)
	{ return node->getLeafs(); }

	Node<T> * initial() const 
	{ return mTree.get(); }

	bool testGoal(const Node<T> *node) const 
	{
		T && val = node->getValue();
		this->watch(val);
		return this->isGoal(val);
	}

	virtual bool isGoal(const T &n) const = 0; 
	virtual void watch(const T & n) const = 0; 

	using member_type = Node<T>;
	using daddy_type = Problem<T>;

private:
	std::unique_ptr<member_type> mTree;
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

template < typename C, typename P, typename E = typename C::value_type >
E graphSearch(C fringe, P &problem)
{
	set<E> explored;

	fringe.push(problem.initial());
	while(! fringe.empty())
	{
		E node = fringe.pop();

		if (explored.insert(node).second == false)
			continue;

		if ( problem.testGoal(node) )
			return node;

		auto nodes = problem.expand(node);
		for(const E e : nodes)
			fringe.push(e);
	}

	return problem.initial();
}

}

using namespace Private;

template <typename P>
void BFTS(P p)
{
	treeSearch(MyQueue<Node<typename P::value_type>*>(), p );
}

template <typename P>
void DFTS(P p)
{
	treeSearch(MyStack<Node<typename P::value_type>*>(), p );
}



template <typename P>
void DFGS(P p)
{
	graphSearch(MyStack<Node<typename P::value_type>*>(), p);
}

template <typename P>
void BFGS(P p)
{
	graphSearch(MyQueue<Node<typename P::value_type>*>(), p );
}


}
#endif
