#include "arraygenerator.h"

class SortTester {
private:
    ArrayGenerator generator;

    // Insertion Sort для небольших массивов
    void insertionSort(std::vector<int>& arr, int left, int right) {
        for (int i = left + 1; i <= right; i++) {
            int key = arr[i];
            int j = i - 1;

            while (j >= left && arr[j] > key) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // Гибридный Merge Sort
    void hybridMergeSort(std::vector<int>& arr, int left, int right, int threshold) {
        if (left >= right) return;

        // Если размер подмассива меньше порога, используем Insertion Sort
        if (right - left + 1 <= threshold) {
            insertionSort(arr, left, right);
            return;
        }

        int mid = left + (right - left) / 2;
        hybridMergeSort(arr, left, mid, threshold);
        hybridMergeSort(arr, mid + 1, right, threshold);
        merge(arr, left, mid, right);
    }

    void merge(std::vector<int>& arr, int left, int mid, int right) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<int> L(n1), R(n2);

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) {
            if (L[i] <= R[j]) {
                arr[k] = L[i];
                i++;
            } else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

public:
    SortTester() {}

    // Тестирование гибридного алгоритма с заданным порогом
    long long testHybridSort(const std::vector<int>& originalArray, int threshold) {
        std::vector<int> arr = originalArray; // Копируем массив
        auto start = std::chrono::high_resolution_clock::now();

        if (!arr.empty()) {
            hybridMergeSort(arr, 0, arr.size() - 1, threshold);
        }

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    }

    // Тестирование стандартного Merge Sort для сравнения
    long long testStandardMergeSort(const std::vector<int>& originalArray) {
        std::vector<int> arr = originalArray;
        auto start = std::chrono::high_resolution_clock::now();

        if (!arr.empty()) {
            standardMergeSort(arr, 0, arr.size() - 1);
        }

        auto elapsed = std::chrono::high_resolution_clock::now() - start;
        return std::chrono::duration_cast<std::chrono::microseconds>(elapsed).count();
    }

private:
    void standardMergeSort(std::vector<int>& arr, int left, int right) {
        if (left >= right) return;

        int mid = left + (right - left) / 2;
        standardMergeSort(arr, left, mid);
        standardMergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
};
