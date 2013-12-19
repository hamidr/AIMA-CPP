
#include "test.hpp"

#include <string>

int main()
{

    cout << endl << "City problems: " << endl ;
    auto romania = recursiveBestFirstSearch(RomaniaCities());
    showRoute(romania);

    cout <<  endl << "Int problem: " << endl ;
    auto num = iterativeDeepeningSearch(IntProblem());
    showRoute(num);

    cout <<  endl << "Alphabet problem: " << endl ;
    auto foundNum = breadthFirstGS(AlphabetProblem());
    showRoute(foundNum);

    cout <<  endl << "Made-up test problem using macro (Generating on the air):" << endl ;
    auto mac =
        depthLimitedSearch(
            MAKE_PROBLEM (1, 17, node, state, eles)
                static int k = 0, j = 0;
                ++k; ++j;

                if ( k >= 15 )
                return eles;

                for(int i = j; i < j+2; ++i)
                    eles.push_back(makeNode(state + i, node, 1));

                return eles;
            END_PROBLEM, 10
        );
    showRoute(mac);

    cout << endl<< "Made-up test problem using class (Generating on the air):" << endl ;
    auto testNum = depthFirstGS(TestProblem());
    showRoute(testNum);

    cout << endl<< "Missionaries and cannibals problem:" << endl ;
    auto resMCB = bestFirstGS(MiCaBo());
    showRoute(resMCB);

    cout << endl;
    return 0;
}

