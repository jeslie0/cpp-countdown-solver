#pragma once
#include <vector>
#include <algorithm>

auto factorial(unsigned int n) -> unsigned int;

template<typename T>
auto choices(std::vector<T> vec) -> std::vector<std::vector<T>>{
    std::vector<std::vector<T>> permutations(factorial(vec.size()));

    for (int i = 0; i < factorial(vec.size()); i++) {
        permutations.push_back(std::next_permutation(vec));
    }
    return permutations;
}
template<typename T>
auto split_at(int n, const std::vector<T>& vec) -> std::pair<std::vector<T>, std::vector<T>>{
    std::vector<T> fst(vec.begin(), vec.begin() + n);
    std::vector<T> snd(vec.begin() + n, vec.end());
    return std::pair<std::vector<T>, std::vector<T>>(fst, snd);
}

template<typename T>
auto split(const std::vector<T>& vec) -> std::vector<std::pair<std::vector<T>, std::vector<T>>>{
    if (vec.size() == 1) {
        std::vector<std::pair<std::vector<T>, std::vector<T>>> foo = {{vec, {}}};
        return foo;
    }
    std::vector<std::pair<std::vector<T>, std::vector<T>>> result;
    for (int indx = 1; indx < vec.size(); indx++) {
        result.push_back(split_at<T>(indx,vec));
    }
    return result;
}

template<typename T>
auto flatten(const std::vector<std::vector<T>>& vec) -> std::vector<T> {
    std::vector<T> result;
    for (auto subvec : vec) {
        for (auto elem : subvec) {
            result.push_back(elem);
        }
    }
    return result;
}
