#include <iostream>
#include <chrono>
#include <vector>

int main() {
    int N;
    std::cout << "Enter number of elements: ";
    std::cin >> N;

    std::vector<int> data(N);
    std::cout << "Enter " << N << " elements: ";
    for (int i = 0; i < N; i++) {
        std::cin >> data[i];
    }

    int result = 0;

    auto start = std::chrono::high_resolution_clock::now(); // Start time

    // Compute the sum using a loop
    for (int i = 0; i < N; i++) {
        result += data[i];
    }

    auto end = std::chrono::high_resolution_clock::now(); // End time
    std::chrono::duration<double, std::milli> elapsed = end - start; // Compute elapsed time

    std::cout << "Sum: " << result << std::endl;
    std::cout << "Time taken: " << elapsed.count() << " ms" << std::endl;

    return 0;
}
