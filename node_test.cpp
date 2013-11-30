#include <string>

#include "node.hpp"
#include "search.hpp"


int main()
{
	Node<int> nodeInt(1);
	auto &l4 = nodeInt.addLeaf(2);
	l4.addLeaf(3).addLeaf(4);
	auto &tt = nodeInt.addLeaf(5).addLeaf(l4);
	tt.addLeaf(6).addLeaf(7).addLeaf(nodeInt);
	tt.addLeaf(8).addLeaf(l4);

	DFGS(Problem());
	BFTS(Problem());

	/* 
	auto && n = map(nodeInt, [](const int &n){
		printf("%d\n",n);
		return std::to_string(n);
	});

	std::vector<std::string> vec;
	//toSequencial(n, vec);

	std::for_each(vec.begin(), vec.end(), [] (const std::string &str) {
		printf("\"%s\"\n",str.c_str());
		});


 	mapOnce(nodeInt, [](const int &n){
		printf("\"%d\"\n",n);
	});

*/
	return 0;
}

