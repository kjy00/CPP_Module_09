#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <vector>
#include <list>
#include <iterator>

class PmergeMe
{
	public:
		PmergeMe();
		PmergeMe(PmergeMe const &ref);
		~PmergeMe();
		PmergeMe& operator=(PmergeMe const &ref);

		void mergeInsertionSort(std::vector<int> &numbers, int left, int right);
		void mergeInsertionSort(std::list<int> &numbers, std::list<int>::iterator left, std::list<int>::iterator right);

private:
		void insertionSort(std::vector<int> &numbers, int left, int right);
		void mergeSort(std::vector<int> &numbers, int left, int mid, int right);
		void insertionSort(std::list<int>::iterator left, std::list<int>::iterator right);
		void mergeSort(std::list<int>::iterator left, std::list<int>::iterator mid, std::list<int>::iterator right);
};

#endif
