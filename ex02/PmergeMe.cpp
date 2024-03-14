#include "PmergeMe.hpp"
#include <iostream>

/*static unsigned int jacobsthal(unsigned int n) {
	if (n == 0)
		return 0;
	else if (n == 1)
		return 1;
	return (jacobSthal(n - 1) + 2 * jacobSthal(n - 2));
}*/

static void createPairs(std::vector<int>& intVec, pair_vec_t& pairs) {
	for (unsigned int i = 0; i < intVec.size(); i += 2) {
		std::pair<int, int> pair(intVec[i], intVec[i + 1]);
		pairs.push_back(pair);
	}
}

static void sortPairs(pair_vec_t& pairs) {
	pair_vec_t::iterator it;

	if (pairs.size() == 1) return;
	for (it = pairs.begin(); it != pairs.end(); it++) {
		if (it->first > it->second) {
			int temp = it->first;
			it->first = it->second;
			it->second = temp;
		}
	}
}

/*static void insert(std::pair<int, int> element, pair_vec_t& pairs, size_t n) {
	if (n < 0) {

	} else if(element.first >= pairs[n].second) {
		if (n == pairs.size() - 1)
			
	}
}

static void insertSortPairs(pair_vec_t& pairs, size_t n) {
	if (n < 1) return;
	insertSortPairs(pairs, n - 1);
	insert(pairs[n], pairs, n - 1);
}*/

static void debugPairs(pair_vec_t& pairs) {
	pair_vec_t::iterator it;
	size_t	idx = 0;
	for (it = pairs.begin(); it != pairs.end(); it++) {
		std::cout << idx << ": [" << it->first << "][" << it->second << "]" << std::endl;
		idx++;
	}
}

void mergeInsertionSort(std::vector<int>& vecInt) {
	int straggler = std::numeric_limits<int>::max();
	pair_vec_t pairs;

	if (vecInt.size() % 2 != 0) {
		straggler = vecInt.back();
		vecInt.pop_back();
	}
	createPairs(vecInt, pairs);
	sortPairs(pairs);
	debugPairs(pairs);
	//insertSortPairs(pairs, pairs.size() - 1);
}