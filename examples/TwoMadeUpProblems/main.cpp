#include "treenumber.h"
#include "generating.h"

#include "search.hpp"

int main()
{
    cout << endl<< "Made-up test problem using class (Generating on the air):" << endl ;
    auto testNum = depthFirstGS(Generating());
    showRoute(testNum);


    cout << endl << "Tree number problem: " << endl ;
    auto num = iterativeDeepeningSearch(TreeNumbers());
    showRoute(num);

    return 0;
}
