#include <CL/sycl.hpp>
#include <iostream>
#include <chrono>

int main() {
    sycl::queue q;

    int N;
    std::cout << "Enter number of elements: ";
    std::cin >> N;

    int *data = new int[N];
    std::cout << "Enter " << N << " elements: ";
    for (int i = 0; i < N; i++) {
        std::cin >> data[i];
    }

    int result = 0;

    auto start = std::chrono::high_resolution_clock::now(); // Start time

    {
        sycl::buffer<int> data_buf(data, sycl::range<1>(N));
        sycl::buffer<int> result_buf(&result, sycl::range<1>(1));

        q.submit([&](sycl::handler& h) {
            auto acc = data_buf.get_access<sycl::access::mode::read>(h);
            auto sum = sycl::reduction(result_buf, h, sycl::plus<int>());

            h.parallel_for(N, sum, [=](sycl::id<1> i, auto& temp) {
                temp += acc[i];
            });
        }).wait(); // Ensure execution completes
    }

    auto end = std::chrono::high_resolution_clock::now(); // End time
    std::chrono::duration<double, std::milli> elapsed = end - start; // Compute elapsed time

    std::cout << "Sum: " << result << std::endl;
    std::cout << "Time taken: " << elapsed.count() << " ms" << std::endl;

    delete[] data;
    return 0;
}
