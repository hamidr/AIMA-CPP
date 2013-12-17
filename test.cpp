
#include "test.hpp"

#include <string>
using std::string;

int main()
{

    std::cout << std::endl << "City problems: " << std::endl ;

    auto romania = bestFirstGS(RomaniaCities());
    mapToRoot(romania, [](const Node<string>::node_ptr &n) { std::cout << " -> " << n->getState(); });
    std::cout << std::endl<< std::endl << "Int problem: " << std::endl ;

    auto num = iterativeDeepeningSearch(IntProblem());
    mapToRoot(num, [](const Node<int>::node_ptr &n) { std::cout << " -> " << n->getState(); });

    std::cout << std::endl<< std::endl << "Alphabet problem: " << std::endl ;

    auto foundNum = breadthFirstGS(AlphabetProblem());
    mapToRoot(foundNum, [](const Node<char>::node_ptr &n) { std::cout << " -> " << n->getState(); });


    std::cout << std::endl<< std::endl << "Made-up test problem using macro (Generating on the air):" << std::endl ;

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

    mapToRoot(mac, [](const Node<int>::node_ptr &n) { std::cout << " -> " << n->getState(); });

    std::cout << std::endl << std::endl<< "Made-up test problem using class (Generating on the air):" << std::endl ;

    auto testNum = depthFirstGS(TestProblem());
    mapToRoot(testNum, [](const Node<int>::node_ptr &n) { std::cout << " -> " << n->getState(); });

    std::cout << std::endl;

    return 0;
}

