#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric>

void sort_radix_base256(std::vector<int>& vect) {
    std::vector<int> aux(vect.size()), digits_base256(256, 0);
    for(int shift=0; shift<4; ++shift) {
        std::vector<int>::reverse_iterator r_it;
        unsigned short index;

        for(r_it = vect.rbegin(); r_it != vect.rend(); ++r_it) {
            index = (*r_it >> (shift << 3)) & 255;
            index ^= (1 << 7);
            ++digits_base256.at(index);
        }

        std::partial_sum(digits_base256.begin(), digits_base256.end(), digits_base256.begin());

        for(r_it = vect.rbegin(); r_it != vect.rend(); ++r_it) {
            index = (*r_it >> (shift << 3)) & 255;
            index ^= (1 << 7);
            aux.at(--digits_base256.at(index)) = *r_it;
        }

        std::copy(aux.begin(), aux.end(), vect.begin());
        std::fill(digits_base256.begin(), digits_base256.end(), 0);
    }
}

int main()
{
    std::default_random_engine engine;
    engine.seed(std::random_device{}());

    int arr_size = 20;
    int range_min = INT_MIN, range_max = INT_MAX;
    std::vector<int> arr(arr_size);
    std::uniform_int_distribution<int> distribution(range_min, range_max);
    for(int& ele : arr)
        ele = distribution(engine);

    auto printElement = [](const int& ele){std::cout << " " << ele;};
    std::cout << "Array elements before sorting =";
    std::for_each(arr.begin(), arr.end(), printElement);

    sort_radix_base256(arr);

    std::cout << std::endl << "Array elements after sorting =";
    std::for_each(arr.begin(), arr.end(), printElement);
    return 0;
}
