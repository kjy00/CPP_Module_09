#include <iostream>
#include <iomanip>
#include "PmergeMe.hpp"

bool isValidNumber(const char* end, int number)
{
	if (*end != '\0')
	{
		return false;
	}

	if (number < INT_MIN || number > INT_MAX)
	{
		return false;
	}

	if (number <= 0)
	{
		return false;
	}

	return true;
}

void addNumbersToContainers(int argc, char* argv[], std::vector<int>& vectorNumbers, std::list<int>& listNumbers)
{
	for (int i = 1; i < argc; i++)
	{
		char *end;
		long number = strtol(argv[i], &end, 10);

		if (isValidNumber(end, number))
		{
			vectorNumbers.push_back(number);
			listNumbers.push_back(number);
		}
		else
		{
			std::cout << "Error: Invalid number" << std::endl;
			exit(1);
		}
	}
}

template <typename T>
void display(const T& container, const std::string& label)
{
	std::cout << label << ": ";
	typename T::const_iterator it;
	for (it = container.begin() ; it != container.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

int main(int argc, char* argv[])
{
	if (argc < 3)
	{
		std::cout << "Please input at least two parameters." << std::endl;
		return 1;
	}

	PmergeMe pMergeMe;
	std::vector<int> vectorNumbers;
	std::list<int> listNumbers;

	addNumbersToContainers(argc, argv, vectorNumbers, listNumbers);

	display(listNumbers, "Before");

	clock_t vectorStart = clock();
	pMergeMe.mergeInsertionSort(vectorNumbers, 0, vectorNumbers.size() - 1);
	clock_t vectorEnd = clock();

	clock_t listStart = clock();
	pMergeMe.mergeInsertionSort(listNumbers, listNumbers.begin(), listNumbers.end());
	clock_t listEnd = clock();

	display(vectorNumbers, "After");

	double vectorTime = static_cast<double>(vectorEnd - vectorStart) / CLOCKS_PER_SEC;
	double listTime = static_cast<double>(listEnd - listStart) / CLOCKS_PER_SEC;

	std::cout << "Time to process a range of " << vectorNumbers.size() << " elements with std::vector: " << std::fixed << std::setprecision(6) << vectorTime << " us" << std::endl;
	std::cout << "Time to process a range of " << listNumbers.size() << " elements with std::list: " << std::fixed << std::setprecision(6) << listTime << " us" << std::endl;

	return 0;
}
