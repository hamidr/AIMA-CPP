#ifndef NODE_HPP
#define NODE_HPP

#include <list>

namespace AI 
{

template <typename T>
class Node
{
	using value_type = T;
	using node_type = Node<T>;
	using node_ptr = node_type *;


public:
	using leafs_list = std::list<node_ptr>;

 	Node(const node_type&) = delete;
	Node(node_type&& t) = default;

	explicit inline
	Node(const T &value)
		: Node(T(value)) { }

	inline
	Node(T &&value)
		: mValue(std::move(value)) { }

	~Node() {
		for(auto e : mCleanLater)
			delete e;
	}

	inline
	T getValue() const {
		return mValue;	
	}

	inline
	node_type &addLeaf(T &&value) {
		return this->addLeaf(new Node(std::forward<T>(value)), true);
	}

	inline
	node_type &addLeaf(node_type &&node) {
		return this->addLeaf(new node_type(std::move(node)), true);
	}

	inline
	node_type &addLeaf(node_type &node) {
		return this->addLeaf(&node, false);
	}

	node_type &addLeaf(node_ptr nextLeaf, bool gc ) 
	{
		mLeafs.push_back(nextLeaf);
		if (gc)
			mCleanLater.push_back(nextLeaf);
		return *nextLeaf;
	}

	leafs_list getLeafs() const 
	{ return mLeafs; }

private:
	const T mValue;
	leafs_list mLeafs;
	leafs_list mCleanLater;
};

}

#endif
