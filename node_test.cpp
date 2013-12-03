#include <string>

#include "node.hpp"
#include "search.hpp"

struct IntProblem : public Problem<int>
{
  	IntProblem()
	: Problem(0) 
	{
		getRoot().addLeaf(1).addLeaf(2).addLeaf(3);
		getRoot().addLeaf(4);
		getRoot().addLeaf(getRoot());
	}

	void watch(const int &n) const override {
		printf("%d\n",n);
	}

  	bool isGoal (const int & n) const override {
		if ( n == 3 )
			return true;
		return false;
	}
};



int main()
{
	DFGS(IntProblem());

	printf("\n");
	
	BFGS(IntProblem());

	return 0;
}

