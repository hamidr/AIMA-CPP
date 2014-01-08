#include "romaniacities.h"

DefConstructorProblem(RomaniaCities, "Arad")
{
    Node<string>::Maker maker;
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

    initial()->connect( e(zerind,75), e(sibiu, 140), e(timisoara, 118) );
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

    hTable.emplace(initial(), 366);
    hTable.emplace(bucharest, 0);
    hTable.emplace(craiova, 160);
    hTable.emplace(drobeta, 242);
    hTable.emplace(eforie, 161);
    hTable.emplace(fagaras, 176);
    hTable.emplace(giurgiu, 77);
    hTable.emplace(hirsova, 151);
    hTable.emplace(iasi, 226);
    hTable.emplace(lugoj, 244);
    hTable.emplace(mehadia, 241);
    hTable.emplace(neamt, 234);
    hTable.emplace(oradea, 380);
    hTable.emplace(pitesi, 100);
    hTable.emplace(rimincu, 193);
    hTable.emplace(sibiu, 253);
    hTable.emplace(timisoara, 329);
    hTable.emplace(urziceni, 80);
    hTable.emplace(valsui, 199);
    hTable.emplace(zerind, 374);
}


bool RomaniaCities::isGoal (const string &city) const 
{ 
    return city == "Bucharest";
}

long RomaniaCities::F(const node_ptr &n, const long &gn, const long &parent_cost) const 
{
    return H(n) + gn;
}

long RomaniaCities::H(const node_ptr &n) const 
{ 
    return hTable.at(n);
}

