#include "romaniacities.h"
#include "search.hpp"

int main()
{
    cout << endl << "City problems: " << endl ;

    auto romania = recursiveBestFirstSearch(RomaniaCities());

    showRoute(romania);

    return 0;
}
