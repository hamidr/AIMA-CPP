
#include "node_test.hpp"

int main()
{
        auto _10 = makeNode(10);
        auto &_40 = _10->addLeaf(40);
        _40.addLeaf(22);
        _40.addLeaf(23);
        auto &_12 = _10->addLeaf(12);
        _12.addLeaf(6);
        _12.addLeaf(8).addLeaf(7);
        _12.addLeaf(20);
        auto &_11 = _10->addLeaf(11);
        _11.addLeaf(9);
        _11.addLeaf(25).addLeaf(26);

        auto foo = WTH( makeProblem(_10, 9) );


    auto bar =
        WTH(
            MAKE_PROBLEM (1, 14, node, state, eles)
                static int k = 0, j = 0;
                ++k; ++j;

                if ( k >= 15 ) 
                    return eles;
                    
                for(int i = j; i < j+2; ++i)
                    eles.push_back(makeNode(state + i, node));

                return eles;
            END_PROBLEM 
            );



/*
    auto bar = WTH(IntProblem());
*/
    //BFTS(IntProblem());
    //DFGS(AlphabetProblem());
    //

//  auto bar = WTH(AlphabetProblem());

    
    mapToRoot(bar, [](const int &n) { std::cout << " -> " << n; });

    std::cout << std::endl;


    return 0;
}

