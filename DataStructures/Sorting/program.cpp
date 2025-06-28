#define _CRT_SECURE_NO_WARNINGS

#include <chrono> 
#include <ctime> 
#include <iostream> 
#include <vector>
#include <random>
#include <fstream>
#include <iomanip>

#include "array.hpp"
#include "isort.hpp"
#include "selection_sort.hpp"

using namespace data_structures;
using std::vector;
using std::cout;

typedef unsigned long long uLong;

void GenerateRandomNumbers(size_t numbers_to_sort[], const size_t& size)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<size_t> dis(0, size);
	for(size_t i = 0; i < size; ++i)
	{
		const size_t random_number = dis(gen);
		numbers_to_sort[i] = random_number;
	}
}

void RunSortForSizeN(const size_t numbers_to_sort[], const size_t& size)
{
	std::ofstream out;
	out.open("sorted_results.txt", std::ios::app);
	if (!out)
	{
		out.clear();
		throw(AdtException("Failed to open file for saving.."));
		exit(1);
	}
	auto timenow =	std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());

	cout << std::endl << ctime(&timenow);

	out << std::endl << ctime(&timenow);
	
	auto my_array = Array<size_t>(size);

	auto vector_container = vector<size_t>(size);

	auto c_array = new size_t[size];

	for (auto i = 0ull; i < size; ++i)
	{
		my_array[i] = vector_container[i] = c_array[i] = numbers_to_sort[i];
	}
	ISort<Array<size_t>>* my_array_sorts[]
	{
		new SelectionSort<Array<size_t>>(),
	};

	cout << "\nAdt arrays at N = " << size << std::endl;

	out << "\nAdt arrays at N = " << size << std::endl;	
	
	for(auto& my_array_sort: my_array_sorts)
	{
		const auto sort_time = my_array_sort->Sort(my_array, my_array.Length());

		cout << std::setw(20) << my_array_sort->SortName() << ": " << std::setw(10) << std::right << sort_time << std::endl;

		out << std::setw(20) << my_array_sort->SortName() << ": " << std::setw(10) << std::right << sort_time << std::endl;

		delete my_array_sort;
	}
	cout << "\nC-Arrays at N = " << size << std::endl;

	out << "\nC-Arrays at N = " << size << std::endl;

	ISort<size_t*>* c_array_sorts[]
	{
		new SelectionSort<size_t*>(),		
	};
	for(auto& c_array_sort:c_array_sorts)
	{
		size_t* c_array_copy = new size_t[size];

		for (auto i = 0u; i < size; ++i) c_array_copy[i] = c_array[i];

		const auto sort_time = c_array_sort->Sort(c_array_copy, size);

		cout << std::setw(20) << c_array_sort->SortName() << ": " << std::setw(10) << std::right << sort_time << std::endl;

		out << std::setw(20) << c_array_sort->SortName() << ": " << std::setw(10) << std::right << sort_time << std::endl;

		delete[] c_array_copy;

		delete c_array_sort;
	}
	cout << "\nVector Arrays at N = " << size << std::endl;

	out << "\nVector Arrays at N = " << size << std::endl;
	
	ISort<vector<size_t>>* vector_sorts[]
	{
		new SelectionSort<vector<size_t>>(),
	};
	for(auto& vector_sort: vector_sorts)
	{
		const auto sort_time = vector_sort->Sort(vector_container, vector_container.size());

		cout << std::setw(20) << vector_sort->SortName() << ": " << std::setw(10) << std::right << sort_time << std::endl;

		out << std::setw(20) << vector_sort->SortName() << ": " << std::setw(10) << std::right << sort_time << std::endl;

		delete vector_sort;
	}
	out.close();
}

int main()
{
	std::ofstream out;

	out.open("sorted_results.txt");

	out.close();
	
	//for(size_t k = 1000; k <= 512000; k += k)
	{
		auto k = 1000ull;
		auto* k_array = new size_t[k];
		GenerateRandomNumbers(k_array, k);
		RunSortForSizeN(k_array, k);
		delete[] k_array;
	}
}