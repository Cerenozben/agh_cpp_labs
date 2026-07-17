#pragma once
#include <algorithm>
#include <iterator>
#include <vector>

namespace gdbLab
{
template <typename Vector>
void bubbleSort(Vector &arr)
{
    if (arr.size() <= 1)
    {
        return;
    }
    bool swapped = true;

    while (swapped)
    {
        swapped = false;
        for (auto it = arr.begin(); it != arr.end() - 1; ++it)
        {
            if (*it > *(it + 1))
            {
                std::swap(*it, *(it + 1));
                swapped = true;
            }
        }
    }
}

template <typename RandomAccessIterator>
void quickSort(RandomAccessIterator begin, RandomAccessIterator end)
{
    if (end - begin <= 1)
    {
        return;
    }

    auto pivot = *std::prev(end);
    auto middle1 = std::partition(begin, std::prev(end), [pivot](const auto &em) { return em < pivot; });
    auto middle2 = std::partition(middle1, end, [pivot](const auto &em) { return !(pivot < em); });

    quickSort(begin, middle1);
    quickSort(middle2, end);
}

template <typename Vector>
void quickSort(Vector &vect)
{
    quickSort(vect.begin(), vect.end());
}

template <typename Vector>
void bucketSort(Vector &arr, int noOfBuckets = 5)
{
    if (arr.size() <= 1 || arr.front() == arr.back())
    {
        return;
    }
    double maxElement = *std::max_element(arr.begin(), arr.end());
    double minElement = *std::min_element(arr.begin(), arr.end());

    // range (for buckets)
    double bucketsRange = (maxElement - minElement) / noOfBuckets;

    std::vector<Vector> temp;

    // create empty buckets
    for (int i = 0; i < noOfBuckets; i++)
    {
        temp.push_back(Vector{});
    }

    // scatter the array elements into the correct bucket
    for (auto &elem : arr)
    {
        double diff = ((elem - minElement) / bucketsRange) - int((elem - minElement) / bucketsRange);

        // append the boundary elements to the lower array
        if (diff == 0 && elem != minElement)
        {
            temp[size_t((elem - minElement) / bucketsRange) - 1].push_back(elem);
        }
        else
        {
            temp[size_t((elem - minElement) / bucketsRange)].push_back(elem);
        }
    }

    // Sort each bucket individually
    for (auto &lst : temp)
    {
        if (!lst.empty())
        {
            std::sort(lst.begin(), lst.end());
        }
    }

    // Gather sorted elements to the original array
    size_t k = 0;
    for (auto &lst : temp)
    {
        if (!lst.empty())
        {
            for (auto &elem : lst)
            {
                arr[k] = elem;
                k++;
            }
        }
    }
}
}  // namespace gdbLab
