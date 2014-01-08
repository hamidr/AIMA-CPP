#ifndef COMMON_HPP
#define COMMON_HPP

#include <iostream>
#include <tuple>

using std::cout;
using std::endl;
using std::get;
using std::tuple;
using std::ostream;


namespace AI 
{

template<typename T, int I>
struct TuplePrint
{
    void operator()(const T& t) const
    {
        TuplePrint<T,I-1>()(t);
        cout <<"," << get<I>(t);
    }
};

template<typename T>
struct TuplePrint<T,0>
{
    void operator()(const T& t) const
    { 
        cout << get<0>(t);
    }
};

template<typename... Args>
ostream& operator<< (ostream& stream, const tuple<Args...>& data)
{
    stream << "<";
    TuplePrint<decltype(data), sizeof...(Args)-1>()(data);
    stream << ">";

    return stream;
}

template<typename R, typename Functor>
void mapToRoot(const R &node, Functor f)
{
    if ( !node ) 
        return;
    f( node );
    mapToRoot( node->parent(), f );
}

template <typename R>
void showRoute(const R & node )
{
    using std::cout;
    using std::endl;

    cout << "Route to root: "<< node->getState();
    mapToRoot(
        node->parent(), 
        [](const R &n) { cout << " -> " << n->getState(); }
    );
    cout << endl;
}


namespace Private
{

template <typename T>
struct NodePtrCompare : std::less<T>
{
     bool operator()(const T &lhs, const T &rhs) const 
    { return lhs->getState() < rhs->getState(); }
};


} // endnamespace Private

} // endnamespace AI

#endif
