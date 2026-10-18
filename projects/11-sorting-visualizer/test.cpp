#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

void bubble_sort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                std::swap(arr[j], arr[j+1]);
            }
        }
    }
}

int main() {
    std::vector<int> data = {5, 2, 8, 1, 9};
    std::vector<int> expected = {1, 2, 5, 8, 9};
    
    bubble_sort(data);
    assert(data == expected);
    
    // Test empty
    std::vector<int> empty;
    bubble_sort(empty);
    assert(empty.empty());
    
    // Test single
    std::vector<int> single = {42};
    bubble_sort(single);
    assert(single[0] == 42);
    
    std::cout << "All sorting tests passed\n";
    return 0;
}
