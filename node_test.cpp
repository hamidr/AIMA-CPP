
#include "node_test.hpp"

int main()
{
	auto problem =
		DFGS(
			MAKE_PROBLEM (1, 104, state, eles)
				static int k = 0, j = 0;
				++k; ++j;

				if ( k >= 15 ) 
					return eles;
					
				for(int i = j; i < j+2; ++i)
					eles.push_back(makeNode(state->getState()+i, state));

				return eles;
			END_PROBLEM 
			);


	//DFGS(IntProblem());
	//BFTS(IntProblem());
	//DFGS(AlphabetProblem());
	//
	
	// auto bar = DFGS(AlphabetProblem());

	
	mapToRoot(problem, [](const int &n) {
		std::cout << " ->" << n;
	});
	std::cout << std::endl;


	return 0;
}

