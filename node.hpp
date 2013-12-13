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


    template<typename... Args>
    Node( const long &c, Args... args )
    : Node(forward<Args>(args)...) 
    { this->setPathCost(c); }

    Node( const node_ptr &node, const node_ptr &p )
        : d_this(node->d_this), mParent(p)
    { }

    inline Node(T value) 
    : d_this(make_shared<NodeData>(forward<T>(value))) 
    { }

    inline Node(T value, const node_ptr &parent) 
    : d_this(make_shared<NodeData>(forward<T>(value))), mParent(parent) 
    { }

    Node(node_type &&t, node_type &p)
    : d_this(move(t.d_this)), mParent(p)
    { }

    inline const node_ptr &getParent() const
    { return mParent; }

    inline T getState() const
    { return d_this->mState; }

    inline leafs_list expand() const 
    { 
        leafs_list leafs;
        for( auto &e : d_this->mEdges ) {
            e.first->setPathCost(e.second);
            leafs.push_back(e.first);
        }
        return leafs;
    }

    void setPathCost( const long &c )
    { mCost = c; }

    long pathCost() const
    { return mCost; }

    template<typename K>
    node_type &addLeaf(K value, const long &cost = 1)
    {
        auto leaf = Maker::makeNode(forward<K>(value));
        d_this->mEdges.insert(make_pair(leaf, cost));
        return *leaf;
    }

    void connect() {}
    template < typename... Leafs >
    void connect(Edge &&leaf, Leafs... ls)
    { 
        this->connect2Way(move(leaf));
        this->connect(forward<Leafs>(ls)...);
    }

    void connect2Way(Edge &&leaf)
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
    long mCost = 0;
    const node_ptr mParent;
    const shared_ptr<NodeData> d_this;
};


template <typename T, typename E = Node<T>, typename R = shared_ptr<E> >
R makeNode(T value)
{
    return E::Maker::makeNode(forward<T>(value));
}

template <typename T, typename R>
R makeNode(T value, const R &p, const long &c = 0)
{
    return Node<T>::Maker::makeNode(c, forward<T>(value), p);
}

template <typename R, typename Node = typename R::element_type>
R makeNode(const R& value, const R &p, const long &c )
{
    return Node::Maker::makeNode(c, value, p);
}

template<typename T, typename Functor>
void mapToRoot(const shared_ptr<Node<T>> &node, Functor f)
{
    if ( !node ) 
        return;

    f( node );
    mapToRoot( node->getParent(), f );
}

}

#endif
