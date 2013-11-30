#ifndef SEARCH_HPP
#define SEARCH_HPP

#include <set>
#include <memory>
#include <deque>
#include <stack>

#include <stdio.h>

/*  
template <typename T>
struct Problem
{
  	Problem()
	: mTree(new member_type(0)) 
	{
		mTree->addLeaf(1).addLeaf(2).addLeaf(3);
		mTree->addLeaf(4);
		mTree->addLeaf(*mTree);
	}

	Node<int>::leafs_list expand(const Node<int> *node)
	{ return node->getLeafs(); }

	Node<int> * initial() const 
	{ return mTree.get(); }

	bool isGoal(const Node<int> *node) { 
		printf("%d\n",node->getValue());
		if (node->getValue() == 3)
			return true;
		return false;	
	}

private:
	using member_type = Node<int>; 
	std::unique_ptr<member_type> mTree;
};

*/
struct Problem
{
  	Problem()
	: mTree(new member_type(0)) 
	{
		mTree->addLeaf(1).addLeaf(2).addLeaf(3);
		mTree->addLeaf(4);
		mTree->addLeaf(*mTree);
	}

	Node<int>::leafs_list expand(const Node<int> *node)
	{ return node->getLeafs(); }

	Node<int> * initial() const 
	{ return mTree.get(); }

	bool isGoal(const Node<int> *node) { 
		printf("%d\n",node->getValue());
		if (node->getValue() == 3)
			return true;
		return false;	
	}

private:
	using member_type = Node<int>; 
	std::unique_ptr<member_type> mTree;
};

template <typename T>
struct MyQueue : public std::deque<T>
{
	using std::deque<T>::deque;

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
struct MyStack : public std::stack<T>
{
	using std::stack<T>::stack;

	T pop() 
	{
		auto &&val = this->top();
		std::stack<T>::pop(); // oops :P watch out the recurisve bug!
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

		if ( problem.isGoal(node) )
			return node;

		auto nodes = problem.expand(node);
		for(auto &e : nodes)
			fringe.push(e);
	}

	return problem.initial();
}

template <typename P>
void BFTS(P p)
{
	treeSearch(MyQueue<Node<int>*>(), p );

}

template <typename P>
void DFTS(P p)
{
	treeSearch(MyStack<Node<int>*>(), p );
}

template < typename C, typename P, typename E = typename C::value_type >
E graphSearch(C fringe, P &problem)
{
	std::set<E> explored;

	fringe.push(problem.initial());
	while(! fringe.empty())
	{
		auto node = fringe.pop();

		if (explored.insert(node).second == false)
			continue;

		if ( problem.isGoal(node) )
			return node;

		auto nodes = problem.expand(node);
		for(auto &e : nodes)
			fringe.push(e);
	}

	return problem.initial();
}

template <typename P>
void DFGS(P p)
{
	graphSearch(MyStack<Node<int>*>(), p);
}


#endif
