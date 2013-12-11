
#include "test.hpp"

#include <string>
using std::string;

int main()
{
    Node<string>::Maker maker;
    auto arad       = maker("Arad");
    auto zerind     = maker("Zerind");
    auto oradea     = maker("Oradea");
    auto sibiu      = maker("Sibiu");
    auto fagaras    = maker("Fagaras");
    auto bucharest  = maker("Bucharest");
    auto rimincu    = maker("Rimnicu Vilcea");
    auto pitesi     = maker("Pitesti");
    auto giurgiu    = maker("Giurgiu");
    auto craiova    = maker("Craiova");
    auto drobeta    = maker("Drobeta");
    auto mehadia    = maker("Mehadia");
    auto lugoj      = maker("Lugoj");
    auto timisoara  = maker("Timisoara");
    auto urziceni   = maker("Urziceni");
    auto hirsova    = maker("Hirsova");
    auto valsui     = maker("Valsui");
    auto iasi       = maker("Iasi");
    auto neamt      = maker("Neamt");
    auto eforie     = maker("Eforie");

    Node<string>::Edge e;

    arad->connect( e(zerind,75), e(sibiu, 140), e(timisoara, 118) );

    std::cout << "Size of arad: " << arad->size() << std::endl;

    oradea->connect( e(zerind,71), e(sibiu,151) );
    sibiu->connect( e(fagaras,99), e(rimincu, 80) );
    rimincu->connect( e(pitesi, 97), e(craiova,146) );
    lugoj->connect( e(timisoara,111), e(mehadia,70) );
    drobeta->connect( e(mehadia,75), e(craiova,120) );
    pitesi->connect( e(craiova,138), e(bucharest,101) );
    bucharest->connect( e(fagaras,211), e(urziceni, 85), e(giurgiu,90));
    hirsova->connect(e(urziceni,98), e(eforie,86));
    valsui->connect( e(urziceni, 142), e(iasi,92));
    neamt->connect( e(iasi,87) );
    

    auto romania = UCS(makeProblem(arad, string("Pitesti")));
    mapToRoot(romania, [](const Node<string>::node_ptr &n) { std::cout << " -> " << n->getState(); });

    std::cout << std::endl;


    return 0;
}

