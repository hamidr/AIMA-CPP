#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>
#include <unordered_map>

namespace AI 
{

using std::move;
using std::forward;
using std::make_shared;
using std::shared_ptr;
using std::unordered_map;

template <typename T>
struct Node : public std::enable_shared_from_this<Node<T>>
{
    using state_type = T;
    using node_type = Node<T>;
    using node_ptr = std::shared_ptr<node_type>;
    using leafs_list = std::vector<node_ptr>;

    struct Maker {
        template<typename... Args>
        inline node_ptr operator()(Args... args) const
        { return makeNode(forward<Args>(args)...); }

        template<typename... Args> inline 
        static node_ptr makeNode(Args... args)
        { return make_shared<Node<T>>(forward<Args>(args)...); }
    };

    struct Edge {

        Edge() {}
        Edge(Edge&&) = default;

        Edge( std::pair<node_ptr, long> &&data ) 
            : mPath(move(data)) { }

        inline Edge 
        operator()(const node_ptr &node, const long &gnlength) const
        { return Edge(make_pair(node, gnlength)); }

        inline long cost() const
        { return mPath.second; }

        inline node_ptr destination() const 
        { return mPath.first; }

        inline const std::pair<node_ptr, long> &getInner() const 
        { return mPath; }

    private:
        const std::pair<node_ptr, long> mPath;
    };


    inline Node(T value) 
     : d_this(make_shared<NodeData>(forward<T>(value))) 
    { }

    inline Node(T value, const node_ptr &parent, const long &c ) 
     : d_this(make_shared<NodeData>(forward<T>(value))), mParent(parent), mCost(c), mDepth(parent->mDepth + 1)
    { }

    Node( const node_ptr &node, const node_ptr &p )
     : Node(node, p, node->pathCost())
    { }

    template <typename N>
    Node( N node, N p, const long &cost, long h = 0 )
     : d_this(node->d_this), mParent(forward<N>(p)), mCost(cost), mDepth(p->depth() + 1), mHeuristicCost(move(h))
    { }

    inline const node_ptr &getParent() const
    { return mParent; }

    inline T getState() const
    { return d_this->mState; }

    inline leafs_list expand() 
    { 
        leafs_list leafs;
        Maker makeLeaf;
        for( auto &e : d_this->mEdges ) 
            leafs.push_back(makeLeaf(e.first, this->shared_from_this(), e.second));
        return leafs;
    }

    auto edges() const
    { return make_pair(d_this->mEdges.begin(), d_this->mEdges.end()); }

    long pathCost() const
    { return mCost; }

    long depth() const
    { return mDepth; }

    long heuristicCost() const
    { return mHeuristicCost; }

    template<typename K>
    node_type &connect1(K value, const long &cost = 1)
    {
        auto leaf = Maker::makeNode(forward<K>(value));
        d_this->mEdges.insert(make_pair(leaf, cost));
        return *leaf;
    }

    void connect() {}
    template < typename... Leafs >
    void connect(Edge &&leaf, Leafs... ls)
    { 
        this->connect2(move(leaf));
        this->connect(forward<Leafs>(ls)...);
    }

    void connect2(Edge &&leaf)
    {
        leaf.destination()->d_this->mEdges.insert(make_pair(this->shared_from_this(), leaf.cost()));
        d_this->mEdges.insert(move(leaf.getInner()));
    }

    int size() const { return d_this->mEdges.size(); }

private:
    struct NodeData { 
        NodeData(T state) 
            : mState(forward<T>(state)) {}

        const T mState;
        unordered_map<node_ptr, long> mEdges;
    };

private:
    const long mHeuristicCost = 0;
    const long mCost = 0;
    const long mDepth = 0;
    const node_ptr mParent;
    const shared_ptr<NodeData> d_this;
};


template <typename T, typename E = Node<T>, typename R = shared_ptr<E> >
R makeNode(T value)
{
    return E::Maker::makeNode(forward<T>(value));
}

template <typename T, typename R>
R makeNode(T node, R parent, const long &c = 1)
{
    return Node<T>::Maker::makeNode(forward<T>(node), forward<R>(parent), c);
}

template <typename R, typename Node = typename R::element_type, typename... Rest>
R makeNode(R node, R parent, Rest...args )
{
    return Node::Maker::makeNode(forward<R>(node), forward<R>(parent), forward<Rest>(args)...);
}

template <typename R, typename Node = typename R::element_type>
long costOfAll(const R &node)
{
    long c = 0;
    R p = node;
    while (p) {
        c += p->pathCost();
        p = p->getParent();
    }
    return c;
}

template<typename T, typename Functor>
void mapToRoot(const shared_ptr<Node<T>> &node, Functor f)
{
    if ( !node ) 
        return;

    f( node );
    mapToRoot( node->getParent(), f );
}

template <typename R, typename Node = typename R::element_type>
long g(const R &node)
{ return node->pathCost(); }

template <typename R, typename Node = typename R::element_type>
long h(const R &node)
{ return node->heuristicCost(); }



}

#endif
