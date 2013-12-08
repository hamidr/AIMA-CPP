
#include "test.hpp"

#include <string>
using std::string;

int main()
{

        auto _10 = makeNode(10);
        auto &_40 = _10->addLeaf(40,4);
        _40.addLeaf(22, 1);
        _40.addLeaf(23);
        auto &_12 = _10->addLeaf(12);
        _12.addLeaf(6);
        _12.addLeaf(8).addLeaf(7);
        _12.addLeaf(20);
        auto &_11 = _10->addLeaf(11);
        _11.addLeaf(9);
        _11.addLeaf(25).addLeaf(26);

//        auto foo = WTH( makeProblem(_10, 7) );


/*
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



    BFTS(IntProblem());
    auto ar = WTH(IntProblem());
    DFGS(AlphabetProblem());
    

    WTH(AlphabetProblem());

    auto bar = WTH(AlphabetProblem());
*/
    
    //mapToRoot(foo, [](const Node<int>::node_ptr &n) { std::cout << " -> " << n->getState(); });
    
    auto arad       = makeNode<string>("Arad");
    auto zerind     = makeNode<string>("Zerind");
    auto oradea     = makeNode<string>("Oradea");
    auto sibiu      = makeNode<string>("Sibiu");
    auto fagaras    = makeNode<string>("Fagaras");
    auto bucharest  = makeNode<string>("Bucharest");
    auto rimincu    = makeNode<string>("Rimnicu Vilcea");
    auto pitesi     = makeNode<string>("Pitesti");
    auto giurgiu    = makeNode<string>("Giurgiu");
    auto craiova    = makeNode<string>("Craiova");
    auto drobeta    = makeNode<string>("Drobeta");
    auto mehadia    = makeNode<string>("Mehadia");
    auto lugoj      = makeNode<string>("Lugoj");
    auto timisoara  = makeNode<string>("Timisoara");
    auto urziceni   = makeNode<string>("Urziceni");
    auto hirsova    = makeNode<string>("Hirsova");
    auto valsui     = makeNode<string>("Valsui");
    auto iasi       = makeNode<string>("Iasi");
    auto neamt      = makeNode<string>("Neamt");
    auto eforie     = makeNode<string>("Eforie");

    arad->connect(zerind,75).connect(oradea,71).connect(sibiu,151);
    arad->connect(sibiu, 140).connect(fagaras,99).connect(bucharest, 211);
    sibiu->connect(rimincu, 80);
    rimincu->connect(pitesi, 97);
    pitesi->connect(bucharest, 101).connect(giurgiu, 90);
    pitesi->connect(craiova, 138);
    rimincu->connect(craiova, 146).connect(drobeta, 120).connect(mehadia,75).connect(lugoj,70).connect(timisoara,111).connect(arad, 118);
    bucharest->connect(urziceni, 85);
    urziceni->connect(hirsova,98).connect(eforie, 86);
    urziceni->connect(valsui, 142).connect(iasi, 92).connect(neamt, 87);
    
    auto romania = UCS(makeProblem(timisoara, string("Pitesti")));

    mapToRoot(romania, [](const Node<string>::node_ptr &n) { std::cout << " -> " << n->getState(); });

    std::cout << std::endl;


    return 0;
}

