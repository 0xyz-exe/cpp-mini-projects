#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

void print_array(const std::vector<int>& arr) {
    for (int val : arr) std::cout << val << " ";
    std::cout << "\n";
}

void bubble_sort(std::vector<int> arr, bool visualize) {
    if (visualize) std::cout << "\n=== Bubble Sort ===\n";
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
                if (visualize) {
                    std::cout << "Swap " << arr[j+1] << " and " << arr[j] << ": ";
                    print_array(arr);
                }
            }
        }
    }
}

void insertion_sort(std::vector<int> arr, bool visualize) {
    if (visualize) std::cout << "\n=== Insertion Sort ===\n";
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        if (visualize) {
            std::cout << "Insert " << key << ": ";
            print_array(arr);
        }
    }
}

void merge(std::vector<int>& arr, int left, int mid, int right, bool visualize) {
    std::vector<int> temp(right - left + 1);
    int i = left, j = mid + 1, k = 0;
    
    while (i <= mid && j <= right) {
        if (arr[i] <= arr[j]) temp[k++] = arr[i++];
        else temp[k++] = arr[j++];
    }
    while (i <= mid) temp[k++] = arr[i++];
    while (j <= right) temp[k++] = arr[j++];
    
    for (i = 0; i < k; i++) arr[left + i] = temp[i];
    
    if (visualize) {
        std::cout << "Merge [" << left << ".." << right << "]: ";
        print_array(arr);
    }
}

void merge_sort_helper(std::vector<int>& arr, int left, int right, bool visualize) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        merge_sort_helper(arr, left, mid, visualize);
        merge_sort_helper(arr, mid + 1, right, visualize);
        merge(arr, left, mid, right, visualize);
    }
}

void merge_sort(std::vector<int> arr, bool visualize) {
    if (visualize) std::cout << "\n=== Merge Sort ===\n";
    merge_sort_helper(arr, 0, arr.size() - 1, visualize);
}

int main() {
    std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};
    
    std::cout << "Original: ";
    print_array(data);
    
    int choice;
    std::cout << "\nSelect algorithm:\n1. Bubble Sort\n2. Insertion Sort\n3. Merge Sort\n4. std::sort\n";
    std::cout << "Choice: ";
    std::cin >> choice;
    
    auto start = std::chrono::high_resolution_clock::now();
    
    switch (choice) {
        case 1: bubble_sort(data, true); break;
        case 2: insertion_sort(data, true); break;
        case 3: merge_sort(data, true); break;
        case 4: {
            std::sort(data.begin(), data.end());
            std::cout << "\n=== std::sort (optimized) ===\n";
            std::cout << "Result: ";
            print_array(data);
            break;
        }
        default: std::cout << "Invalid choice\n"; return 1;
    }
    
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
    
    std::cout << "\nTime: " << duration.count() << " microseconds\n";
    std::cout << "Note: Timing includes visualization overhead\n";
    
    return 0;
}
