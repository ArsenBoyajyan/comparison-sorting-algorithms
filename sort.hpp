#ifndef SORT_HPP
#define SORT_HPP

#include <vector>
#include <stdlib.h>
#include <functional>

template<typename T, typename Compare>
void bubble_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    int size = int(vector.size());
    T temp = vector[0];

    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            if (comp(vector[j+1], vector[j])) {
                temp = vector[j];
                vector[j] = vector[j+1];
                vector[j + 1] = temp;
            }
        }
    }
}

template<typename T, typename Compare>
void insertion_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    int size = int(vector.size());
    T temp = vector[0];

    for (int i = 1, j; i < size; i ++) {
        j = i;
        while (j > 0 && comp(vector[j], vector[j - 1])) {
            temp = vector[j];
            vector[j] = vector[j - 1];
            vector[j - 1] = temp;
            j--;
        }
    }
}

template<typename T, typename Compare>
void selection_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    int size = int(vector.size());
    T min = vector[0], temp = vector[0];
    int min_index = 0;

    for (int i = 0; i < size - 1; i++) {
        min = vector[i];
        min_index = i;

        for (int j = i + 1; j < size; j++) {
            if (comp(vector[j], min)) {
                min = vector[j];
                min_index = j;
            }
        }

        temp = vector[i];
        vector[i] = vector[min_index];
        vector[min_index] = temp;
    }
}

template<typename T, typename Compare>
void merge(std::vector<T> &vector, int left, int mid, int right, Compare comp) {
    int left_size = mid - left + 1;
    int right_size = right - mid;

    std::vector<T> leftArr(left_size);
    std::vector<T> rightArr(right_size);

    for (int i = 0; i < left_size; i++)
        leftArr[i] = vector[left + i];
    for (int j = 0; j < right_size; j++)
        rightArr[j] = vector[mid + 1 + j];

    int i = 0, j = 0, k = left;
    
    while (i < left_size && j < right_size) {
        if (comp(leftArr[i], rightArr[j])) {
            vector[k] = leftArr[i];
            i++;
        } else {
            vector[k] = rightArr[j];
            j++;
        }
        k++;
    }

    while (i < left_size) {
        vector[k] = leftArr[i];
        i++;
        k++;
    }

    while (j < right_size) {
        vector[k] = rightArr[j];
        j++;
        k++;
    }
}

template<typename T, typename Compare = std::less<T>>
void merge_sort_helper(std::vector<T> &vector, int left, int right, Compare comp = Compare()) {
    if (left >= right) return;
    
    int mid = left + (right - left) / 2;

    merge_sort_helper(vector, left, mid, comp);
    merge_sort_helper(vector, mid + 1, right, comp);

    merge(vector, left, mid, right, comp);
}

template<typename T, typename Compare>
void merge_sort(std::vector<T> &vector, Compare comp = std::less<T>()) {
    int size = int(vector.size());
    merge_sort_helper(vector, 0, size - 1, comp);
} 

template<typename T, typename Compare>
void quick_sort_extra(std::vector<T> &vector, Compare comp = std::less<T>()) {
    if (int(vector.size()) <= 1) return;

    T pivot = vector[vector.size() / 2];
    std::vector<T> left, right;

    for (const T &element : vector) {
        if (comp(element, pivot)) {
            left.push_back(element);
        } else if (comp(pivot, element)) {
            right.push_back(element);
        }
    }

    quick_sort_extra(left, comp);
    quick_sort_extra(right, comp);

    vector.clear();
    vector.insert(vector.end(), left.begin(), left.end());
    vector.push_back(pivot);
    vector.insert(vector.end(), right.begin(), right.end());
}

template<typename T, typename Compare>
int partition(std::vector<T> &vector, int left, int right, Compare comp) {
    T pivot = vector[right], temp = vector[0];
    int i = left - 1;

    for (int j = left; j < right; j++) {
        if (comp(vector[j], pivot)) {
            i++;
            temp = vector[i];
            vector[i] = vector[j];
            vector[j] = temp;
        }
    }
    temp = vector[i + 1];
    vector[i + 1] = vector[right];
    vector[right] = temp;
    return i + 1;
}

template<typename T, typename Compare>
void quick_sort_helper(std::vector<T> &vector, int left, int right, Compare comp) {
    if (left < right) {
        int pivotIndex = partition(vector, left, right, comp);

        quick_sort_helper(vector, left, pivotIndex - 1, comp);
        quick_sort_helper(vector, pivotIndex + 1, right, comp);
    }
}

template<typename T, typename Compare = std::less<T>>
void quick_sort_inplace(std::vector<T> &vector, Compare comp = Compare()) {
    quick_sort_helper(vector, 0, int(vector.size()) - 1, comp);
}

#endif //SORT_HPP
