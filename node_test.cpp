#include <string>

#include <stdio.h>
#include "search.hpp"

using namespace AI;


struct IntProblem : public Problem<int>
{
  	IntProblem()
	: Problem(0) 
	{
		getRoot().addLeaf(1).addLeaf(2).addLeaf(3);
		getRoot().addLeaf(4);
		getRoot().addLeaf(getRoot());
	}


  	bool isGoal (const int & value) const override {
		if ( value == 3 )
			return true;
		return false;
	}
};

struct TestProblem : public Problem<int>
{
  	TestProblem()
	: Problem(0)
	{}

	virtual leafs_list successors(node_ptr &state) const override 
	{
		static int j = 0;
		++j;
		leafs_list eles;

		static int k = 0;
		++k;

		if ( k >= 15 ) 
			return eles;
			

		for(int i = j; i < j+2; ++i)
			eles.push_back(makeNode(state->getState()+i, state));

		return eles;

	}

  	bool isGoal (const int & value) const override {
		if( value == 104 )
			return true;
		return false;
	}
};

struct AlphabetProblem : public Problem<char>
{
	AlphabetProblem()
	: Problem('A') 
	{
		auto &b = getRoot().addLeaf('B');
			auto &d = b.addLeaf('D');
				auto &h = d.addLeaf('H');
				auto &i = d.addLeaf('I');
			auto &e = b.addLeaf('E');
				auto &j = e.addLeaf('J');
				auto &k = e.addLeaf('K');

		auto &c = getRoot().addLeaf('C');
			auto &f = c.addLeaf('F');
				auto &l = f.addLeaf('L');
				auto &m = f.addLeaf('M');
			auto &g = c.addLeaf('G');
				auto &n = g.addLeaf('N');
				auto &o = g.addLeaf('O');
	}

  	bool isGoal (const char & n) const override {
		if ( n == 'H' )
			return true;
		return false;
	}
};

template<typename T, typename F>
void mapToRoot(const shared_ptr<Node<T>> &n, F f)
{
	if (!n) 
		return;

	mapToRoot(n->getParent(), f);
	f(n->getState());
}


int main()
{
	//DFGS(IntProblem());
	//BFTS(IntProblem());
	//DFGS(AlphabetProblem());
	//
	
	// auto bar = DFGS(AlphabetProblem());

	
	auto ack = DFGS(TestProblem());
	mapToRoot(ack, [](const int &n) {
		std::cout << n << " ";
	});
	std::cout << std::endl;


	return 0;
}

