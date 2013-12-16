#ifndef NODE_TEST_HPP
#define NODE_TEST_HPP

#include <string>

#include <stdio.h>
#include "search.hpp"

using namespace AI;

DefClassProblem(IntProblem, int)
{
    IntProblem()
    : Problem(10) 
    {
        auto &_40 = getRoot().connect1(40,50);
        _40.connect1(22);
        _40.connect1(23);
        auto &_12 = getRoot().connect1(12);
        _12.connect1(6);
        _12.connect1(8).connect1(7,4);
        _12.connect1(20);
        auto &_11 = getRoot().connect1(11,12);
        _11.connect1(9);
        _11.connect1(25).connect1(26);


        //
        //             ___10__
        //           /    |   \ 
        //         40    12_   11 ___
        //       / |    / | \    \  \
        //    22  23   6  8  20   9  25
        //                |           |
        //                7           26
        // 
        //  

    }

    bool isGoal (const int & value) const {
        return ( value == 7 );
    }
};



DefClassProblem(TestProblem, int)
{
    TestProblem()
    : Problem(0)
    { }

    leafs_list successors( const node_ptr &state) const
    {
        leafs_list eles;

        static int k = 0, j = 0;

        ++k;
        ++j;

        if ( k >= 15 ) 
            return eles;
            

        for(int i = j; i < j+2; ++i)
            eles.push_back(makeNode(state->getState()+i, state));

        return eles;

    }

    long f(const node_ptr &n) const
    {
        return n->depth();
    }

    bool isGoal (const int & value) const {
        return ( value == 104 );
    }
};


DefClassProblem(AlphabetProblem, char)
{
    AlphabetProblem()
    : Problem('A') 
    {
        auto &b = getRoot().connect1('B');
            auto &d = b.connect1('D');
                auto &h = d.connect1('H');
                auto &i = d.connect1('I');
            auto &e = b.connect1('E');
                auto &j = e.connect1('J');
                auto &k = e.connect1('K');

        auto &c = getRoot().connect1('C');
            auto &f = c.connect1('F');
                auto &l = f.connect1('L');
                auto &m = f.connect1('M');
            auto &g = c.connect1('G');
                auto &n = g.connect1('N');
                auto &o = g.connect1('O');
    }

    bool isGoal (const char & n) const {
        return ( n == 'M' );
    }
};

#include <unordered_map>
using std::unordered_map;

#define DefConstructorProblem(p, initial) p() : Problem(initial)
DefClassProblem(RomaniaCities, std::string)
{
    DefConstructorProblem(RomaniaCities, "Arad")
    {
        Node<std::string>::Maker maker;
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

        Node<std::string>::Edge e;

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

    leafs_list successors(const node_ptr &state) const
    { 
        leafs_list leafs;
        const auto edgeBoarder = state->edges();

        for(auto itr = edgeBoarder.first; itr != edgeBoarder.second; ++itr)
        {
            const node_ptr &node = itr->first;
            const long &cost = itr->second;

            leafs.push_back(makeNode(node, state, cost, hTable.at(node)));
        }

        return leafs;
    }

    bool isGoal (const std::string &city) const 
    { return city == "Bucharest"; }

    static long F(const node_ptr &n) 
    { return g(n) + h(n); }


private:
    unordered_map<node_ptr, long> hTable;
};


#endif
