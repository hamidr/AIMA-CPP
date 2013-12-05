#ifndef PROBLEM_HPP
#define PROBLEM_HPP

#include "node.hpp"

namespace AI 
{

using std::shared_ptr;
using std::make_shared;

template <typename T>
struct Problem
{
	using state_type = T;
	using node_type = Node<state_type>;
	using node_ptr = typename node_type::node_ptr;
	using leafs_list = typename node_type::leafs_list;

	Problem(const Problem&) = delete;
	Problem(Problem&&) = default;

	Problem(T head)
	: mTree(make_shared<node_type>(head)) 
	{ }

	inline node_type & getRoot() const
	{ return *mTree; }

	inline node_ptr initial() const 
	{ return mTree->shared_from_this(); }

	bool testGoal(const node_ptr &node) const 
	{
		T && val = node->getState();
		this->watch(val);
		return this->isGoal(val);
	}

	virtual bool isGoal(const T &value) const = 0;

	virtual leafs_list successors( const node_ptr &state) const
	{ return state->expand(); }

	virtual void pathCost(const node_ptr &state1) const {} 

	virtual void watch(const T & n) const {
		std::cout << n << std::endl;
	}

protected:
	using daddy_type = Problem<T>;

private:
	const node_ptr mTree;
};


namespace Private 
{

template<typename T, typename G >
struct ProblemMaker : public Problem<T>
{

	ProblemMaker(T root, T goal, const G &gen )
	: Problem<T>(forward<T>(root)), mGoal(forward<T>(goal)), mGenerator(gen)
	{ }

  	bool isGoal (const T & value) const override {
		if ( value == mGoal )
			return true;
		return false;
	}

	virtual typename Problem<T>::leafs_list 
	successors(const typename Problem<T>::node_ptr &state) const override 
	{
		return mGenerator(state);
	}

private:
	const T mGoal;
	const G &mGenerator;
};

}

using namespace Private;

template <typename T, typename G>
ProblemMaker<T,G> makeProblem(T root, T goal, G gen)
{
	return ProblemMaker<T,G>(root, goal, gen);
}

#define MAKE_PROBLEM(ROOT, GOAL, STATE, GEN) makeProblem(ROOT, GOAL, [&]( \
			const Node<decltype(ROOT)>::node_ptr & STATE) { \
				typename Problem<decltype(ROOT)>::leafs_list GEN;

#define END_PROBLEM })


}

#endif
