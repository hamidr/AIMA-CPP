#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>

namespace AI 
{

using std::move;
using std::forward;
using std::make_shared;
using std::shared_ptr;

template <typename T>
struct Node : public std::enable_shared_from_this<Node<T>>
{
    using state_type = T;
    using node_type = Node<T>;
    using node_ptr = std::shared_ptr<node_type>;
    using leafs_list = std::vector<node_ptr>;

    template<typename... Args>
    Node( const long &c, Args... args )
    : Node(forward<Args>(args)...) 
    { this->setPathCost(c); }

    Node( const node_ptr &n, const node_ptr &p )
    : mState(n->mState), mLeafs(n->mLeafs), mParent(p)
    { }

    Node( const node_ptr &n )
    : mState(n->mState), mLeafs(n->mLeafs)
    { }
    
    Node( node_ptr &&n )
    : mState(move(n->mState)), mLeafs(move(n->mLeafs))
    { }

    inline Node(T value) 
    : mState(forward<T>(value)) 
    { }

    inline Node(T value, const node_ptr &parent) 
    : mState(forward<T>(value)), mParent(parent) { }

    Node(node_type &&t, node_type &p)
    : Node(move(t.mState), move(t.mLeafs), p) { }

    inline const node_ptr &getParent() const
    { return mParent; }

    inline T getState() const
    { return mState; }

    inline leafs_list expand() const 
    { return mLeafs; }

    void setPathCost( const long &c )
    { mCost = c; }

    long pathCost() const
    { return mCost; }

    inline node_type &addLeaf(T value)
    { return this->addLeaf(make_shared<node_type>(forward<T>(value), *this)); }

    inline node_type &addLeaf(node_type &&node) 
    { return this->addLeaf(make_shared<node_type>(move(node), *this)); }

    inline node_type &addLeaf( node_type &node)
    { return this->addLeaf(node.shared_from_this()); }

    template <typename K> 
    inline node_type &addLeaf(K value, const long &cost)
    { 
        auto &ref = this->addLeaf(forward<K>(value));
        ref.setPathCost(cost);
        return ref;
    }
 
    template<typename N>
    inline node_type &connect(N node, long cost )
    {
        auto &leaf = this->addLeaf(forward<N>(node), cost);
        leaf.addLeaf(this->shared_from_this() , cost);
        return leaf;
    }

    template < typename... Leafs >
    void connect(const std::pair<node_ptr, long> &leaf, Leafs... ls)
    { 
        this->connect(leaf);
        this->connect(forward<Leafs>(ls)...);
    }

    void connect(const std::pair<node_ptr, long> &leaf)
    {
        this->mLeafs.push_back(make_shared<node_type>(leaf.second, leaf.first));
        leaf.first->mLeafs.push_back(make_shared<node_type>(leaf.second, this->shared_from_this()));
    }

    int size() const { return mLeafs.size(); }

    struct Maker {
        inline node_ptr operator()(T t) const
        { return make_shared<Node<T>>(forward<T>(t)); }
    };

    struct Edge {
        inline std::pair<node_ptr, long> 
        operator()(const node_ptr &node, const long &gnlength) const
        { return make_pair(node, gnlength); }
    };

private:
    inline Node(T value, leafs_list leafs, node_type &parent)
    :  mState(forward<T>(value)), mLeafs(move(leafs)), mParent(parent.shared_from_this()) { }
    
    node_type &addLeaf(node_ptr &&nextLeaf ) {
        mLeafs.push_back(nextLeaf);
        return *nextLeaf;
    }

private:
    const T mState;
    const node_ptr mParent;
    long mCost = 0;

    leafs_list mLeafs;
};

template <typename T, typename E = Node<T>, typename R = shared_ptr<E> >
R makeNode(T value)
{
    return make_shared<E>(forward<T>(value));
}

template <typename T, typename E = Node<T>, typename R = shared_ptr<E> >
R makeNode(T value, const R &p, long c = 0)
{
    return make_shared<E>(c, forward<T>(value), p);
}

template <typename T, typename E = Node<T>, typename R = shared_ptr<E> >
R makeNode(const R& value, const R &p, long c = 0)
{
    return make_shared<E>(c, value, p);
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
