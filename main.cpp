﻿#include <iostream>
#include <future>
#include <chrono>
#include <thread>
#include <random>
#include <ctime>

bool flag = true;

void merge(int arr[], int l, int r, int m); //l - начало (слева), m - середина, r - конец (справа);

void mergeSort(int arr[], int l, int r)
{
	int mid{};
	if (flag == true)
	{
		if (l < r)
		{
			mid = (l + r) / 2;
			std::future<void> f1 = std::async(std::launch::async, [&]() {mergeSort(arr, l, mid); });
			f1.get();
			mergeSort(arr, mid + 1, r);
			merge(arr, l, r, mid);
			//Как вариант:
			//mid = (l + r) / 2;
			//std::future<void> f1 = std::async(std::launch::async, [&]() {mergeSort(arr, l, mid); });
			//std::future<void> f2 = std::async(std::launch::async, [&]() {mergeSort(arr, mid+1, r); });
			//f1.get();
			//f2.get();
			//merge(arr, l, r, mid);

		}
	}
	else
	{
		if (l < r)
		{
			mergeSort(arr, l, mid);
			mergeSort(arr, mid + 1, r);
			merge(arr, l, r, mid);
		}
	}
}

void merge(int* arr, int l, int r, int m)
{
	int nl = m - l + 1;
	int nr = r - m;
	int* left = new int[nl];	// создаем временные массивы
	int* right = new int[nr];

	for (int i = 0; i < nl; i++) 	// копируем данные во временные массивы
	{
		left[i] = arr[l + i];
	}
	for (int j = 0; j < nr; j++)
	{
		right[j] = arr[m + 1 + j];
	}

	int i = 0, j = 0;
	int k = l;  // начало левой части

	while (i < nl && j < nr)
	{
		if (left[i] <= right[j]) // записываем минимальные элементы обратно во входной массив
		{
			arr[k] = left[i];
			i++;
		}
		else
		{
			arr[k] = right[j];
			j++;
		}
		k++;
	}
	while (i < nl)// записываем оставшиеся элементы левой части
	{
		arr[k] = left[i];
		i++;
		k++;
	}
	while (j < nr) // записываем оставшиеся элементы правой части
	{
		arr[k] = right[j];
		j++;
		k++;
	}
	delete[] left;
	delete[] right;
}

int main()
{
	setlocale(LC_ALL, "Rus");

	srand(0);
	int arr_size = 20;
	int* arr = new int[arr_size];
	for (long i = 0; i < arr_size; i++) {
		arr[i] = rand() % 100;
	}
	std::cout << "Исходный массив: \n";
	for (int i = 0; i < arr_size; i++)
	{
		std::cout << arr[i] << "  ";
	}
	std::cout << '\n';

	mergeSort(arr, 0, arr_size - 1);
	std::cout << "\n\nМногопоточный отсортированный массив: \n";
	for (int i = 0; i < arr_size; i++)
	{
		std::cout << arr[i] << "  ";
	}
	std::cout << '\n';

	flag == false;
	mergeSort(arr, 0, arr_size - 1);
	std::cout << "\n\nОднопоточный отсортированный массив: \n";
	for (int i = 0; i < arr_size; i++)
	{
		std::cout << arr[i] << "  ";
	}
	std::cout << '\n';
	
	delete[] arr;
	return 0;
}
