#include "missiocanib.h"
#include "search.hpp"

int main()
{
    cout << endl<< "Missionaries and cannibals problem:" << endl ;

    auto resMCB = bestFirstGS(MiCaBo());

    showRoute(resMCB);

    return 0;
}
