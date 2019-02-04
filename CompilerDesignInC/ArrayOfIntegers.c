#include "ArrayOfIntegers.h"

int index_of(const int arr[], const int n, const int element)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == element)
			return i;
	}

	return -1;
}

void sort(int arr[], const int n)
{
	int swapped = 0;

	for (int i = 0; i < n - 1; i++)
	{
		swapped = 0;

		for (int j = 0; j < n - 1; j++)
		{
			if (arr[j] > arr[j + 1])
			{
				const int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				swapped = 1;
			}
		}

		if (swapped == 0)
			break;
	}
}

int remove_duplicates_from_sorted_array(int arr[], const int n)
{
	if (n == 0 || n == 1)
		return n;

	int j = 0;

	for (int i = 0; i < n - 1; i++)
		if (arr[i] != arr[i + 1])
			arr[j++] = arr[i];

	arr[j++] = arr[n - 1];

	return j;
}