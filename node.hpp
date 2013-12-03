#ifndef NODE_HPP
#define NODE_HPP

#include <vector>
#include <memory>

namespace AI 
{

template <typename T>
class Node
{
public:
	using value_type = T;
	using node_type = Node<T>;
	using node_ptr = std::shared_ptr<node_type>;
	using leafs_list = std::vector<node_ptr>;

 	Node(const node_type&n, const node_type *p)
	: mValue(n.mValue), mLeafs(n.mLeafs), mParent(p)
	{ }

	Node(node_type&& t, const node_type * p = nullptr) 
	: mValue(std::move(t.mValue)), mLeafs(std::move(t.mLeafs)), mParent(p) 
	{ }

	inline Node(T value) 
	: mValue(std::forward<T>(value)) { }

	~Node() {
	}

	inline node_ptr getParent() const
	{ return mParent;  }

	inline T getValue() const
	{ return mValue; }

	inline leafs_list getLeafs() const 
	{ return mLeafs; }

	inline node_type &addLeaf(T value)
	{ return this->addLeaf(std::make_shared<node_type>(std::forward<T>(value), this)); }

	inline node_type &addLeaf(node_type &&node) 
	{ return this->addLeaf(std::make_shared<node_type>(std::move(node), this)); }

	inline node_type &addLeaf(const node_type &node)
	{ return this->addLeaf(std::make_shared<node_type>(node,this)); }

	node_type &addLeaf(node_ptr &&nextLeaf ) {
		mLeafs.push_back(nextLeaf);
		return *nextLeaf;
	}


private:
	const T mValue;
	const node_type *mParent = nullptr;

	leafs_list mLeafs;
};

}

#endif
