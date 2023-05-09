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

template <typename T>
void addNumbersToContainer(int argc, char* argv[], T& container)
{
	for (int i = 1; i < argc; i++)
	{
		char *end;
		long number = strtol(argv[i], &end, 10);

		if (isValidNumber(end, number))
		{
			container.push_back(number);
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
	std::vector<int> orignal;
	std::vector<int> vectorNumbers;
	std::list<int> listNumbers;

	addNumbersToContainer(argc, argv, orignal);
	display(orignal, "Before");

	clock_t vectorStart = clock();
	addNumbersToContainer(argc, argv, vectorNumbers);
	pMergeMe.mergeInsertionSort(vectorNumbers, 0, vectorNumbers.size() - 1);
	clock_t vectorEnd = clock();

	clock_t listStart = clock();
	addNumbersToContainer(argc, argv, listNumbers);
	pMergeMe.mergeInsertionSort(listNumbers, listNumbers.begin(), listNumbers.end());
	clock_t listEnd = clock();

	double vectorTime = static_cast<double>(vectorEnd - vectorStart) / CLOCKS_PER_SEC;
	double listTime = static_cast<double>(listEnd - listStart) / CLOCKS_PER_SEC;

	display(listNumbers, "After");

	std::cout << "Time to process a range of " << vectorNumbers.size() << " elements with std::vector: " << std::fixed << std::setprecision(6) << vectorTime << " s" << std::endl;
	std::cout << "Time to process a range of " << listNumbers.size() << " elements with std::list: " << std::fixed << std::setprecision(6) << listTime << " s" << std::endl;

	return 0;
}
