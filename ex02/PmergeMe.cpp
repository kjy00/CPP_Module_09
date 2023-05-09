#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(PmergeMe const &ref)
{
	*this = ref;
}

PmergeMe::~PmergeMe()
{
}

PmergeMe& PmergeMe::operator=(PmergeMe const &ref)
{
	(void)ref;
	return *this;
}

void PmergeMe::insertionSort(std::vector<int> &numbers, int first, int end)
{
	int i, j, key;

	for (i = first + 1; i <= end; i++)
	{
		key = numbers[i];
		j = i - 1;

		while (j >= first && numbers[j] > key)
		{
			numbers[j + 1] = numbers[j];
			j = j - 1;
		}

		numbers[j + 1] = key;
	}
}

void PmergeMe::mergeSort(std::vector<int> &numbers, int left, int mid, int right)
{
	std::vector<int> temp;

	int i = left, j = mid + 1;

	while (i <= mid && j <= right) {
		if (numbers[i] <= numbers[j]) {
			temp.push_back(numbers[i]);
			i++;
		} else {
			temp.push_back(numbers[j]);
			j++;
		}
	}

	while (i <= mid) {
		temp.push_back(numbers[i]);
		i++;
	}

	while (j <= right) {
		temp.push_back(numbers[j]);
		j++;
	}

	for (int k = left; k <= right; k++) {
		numbers[k] = temp[k - left];
	}
}

void PmergeMe::mergeInsertionSort(std::vector<int> &numbers, int left, int right)
{
	if (right - left + 1 <= 15)
	{
		insertionSort(numbers, left, right);
	}
	else
	{
		if (left < right)
		{
			int mid = left + (right - left) / 2;

			mergeInsertionSort(numbers, left, mid);
			mergeInsertionSort(numbers, mid + 1, right);

			mergeSort(numbers, left, mid, right);
		}
	}
}

void PmergeMe::insertionSort(std::list<int>::iterator itFirst, std::list<int>::iterator itEnd)
{
	std::list<int>::iterator itKey = itFirst;

	for (++itKey; itKey != itEnd; ++itKey) {
		int key = *itKey;

		std::list<int>::iterator itNextNumber;
		std::list<int>::iterator itNumber = itKey;
		for (--itNumber; itNumber != itFirst && *itNumber > key; --itNumber)
		{
			itNextNumber = itNumber;
			++itNextNumber;
			*(itNextNumber) = *itNumber;
		}

		if (*itNumber > key)
		{
			itNextNumber = itNumber;
			*(++itNextNumber) = *itNumber;
			*itNumber = key;
		}
		else
		{
			itNextNumber = itNumber;
			*(++itNextNumber) = key;
		}
	}
}


void PmergeMe::mergeSort(std::list<int>::iterator left, std::list<int>::iterator mid, std::list<int>::iterator right)
{
	std::list<int> temp;
	std::list<int>::iterator it1 = left;
	std::list<int>::iterator it2 = mid;

	while (it1 != mid && it2 != right) {
		if (*it1 < *it2) {
			temp.push_back(*it1);
			++it1;
		} else {
			temp.push_back(*it2);
			++it2;
		}
	}
	while (it1 != mid) {
		temp.push_back(*it1);
		++it1;
	}
	while (it2 != right) {
		temp.push_back(*it2);
		++it2;
	}

	std::list<int>::iterator it_out = left;
	std::list<int>::iterator it_temp = temp.begin();
	while (it_out != right) {
		*it_out = *it_temp;
		++it_out;
		++it_temp;
	}
}

void PmergeMe::mergeInsertionSort(std::list<int> &numbers, std::list<int>::iterator left, std::list<int>::iterator right)
{
	if (std::distance(left, right) + 1 <= 15)
	{
		insertionSort(left, right);
	}
	else
	{
		std::list<int>::iterator mid = left;
		std::advance(mid, std::distance(left, right) / 2);

		mergeInsertionSort(numbers, left, mid);
		mergeInsertionSort(numbers, mid, right);

		mergeSort(left, mid, right);
	}
}
