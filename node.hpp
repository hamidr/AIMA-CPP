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
	using node_type_ptr = node_type *;
	using node_ptr = std::shared_ptr<node_type>;
	using leafs_list = std::vector<node_ptr>;

	Node(const node_type &) = delete;
	Node(node_type &&) = delete;

	inline Node(T value) 
	: mState(forward<T>(value)) { }

	inline Node(T value, const node_ptr &parent) 
	: mState(forward<T>(value)), mParent(parent->shared_from_this()) { }

 	Node(const node_type &n, const node_type_ptr &p )
	: Node(n.mState, n.mLeafs, p) { }

	Node(node_type &&t, const node_type_ptr &p) 
	: Node(move(t.mState), move(t.mLeafs), p) { }

	inline const node_ptr &getParent() const
	{ return mParent;  }

	inline T getState() const
	{ return mState; }

	inline leafs_list expand() const 
	{ return mLeafs; }

	inline node_type &addLeaf(T value)
	{ return this->addLeaf(make_shared<node_type>(forward<T>(value), this)); }

	inline node_type &addLeaf(node_type &&node) 
	{ return this->addLeaf(make_shared<node_type>(move(node), this)); }

	inline node_type &addLeaf(const node_type &node)
	{ return this->addLeaf(make_shared<node_type>(node, this)); }


private:
	inline Node(T value, leafs_list leafs, const node_type_ptr &parent) 
	: mState(forward<T>(value)), mLeafs(move(leafs)), mParent(parent->shared_from_this()) { }
	
	node_type &addLeaf(node_ptr &&nextLeaf ) {
		mLeafs.push_back(nextLeaf);
		return *nextLeaf;
	}

private:
	const T mState;
	const node_ptr mParent;

	leafs_list mLeafs;
};

template <typename T, typename E = Node<T>, typename R = shared_ptr<E> >
R makeNode(T value)
{
	return make_shared<E>(forward<T>(value));
}

template <typename T, typename E = Node<T>, typename R = shared_ptr<E> >
R makeNode(T value, const R &p)
{
	return make_shared<E>(forward<T>(value), p);
}


}

#endif
