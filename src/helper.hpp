#pragma once
#include <vector>
#include <algorithm>

auto factorial(unsigned int n) -> unsigned int;

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
        result.emplace_back(split_at<T>(indx,vec));
    }
    return result;
}

template<typename T>
auto flatten(const std::vector<std::vector<T>>& vec) -> std::vector<T> {
    std::vector<T> result;
    for (const std::vector<T>& subvec : vec) {
        for (const T& elem : subvec) {
            result.emplace_back(elem);
        }
    }
    return result;
}

// Made by ChatGPT - generates the 2^n subsequences from an input
// vector.
// TODO: Check that this does actually work
template<typename T>
auto sub_sequences(std::vector<T> vec) -> std::vector<std::vector<T>>
{
    std::vector<std::vector<T>> res;
    int vec_size = vec.size();
    for (int i = 0; i < vec_size; i++)
    {
        for (int j = i; j < vec_size; j++)
        {
            std::vector<T> subv;
            for (int k = i; k <= j; k++)
            {
                subv.push_back(vec[k]);
            }
            res.push_back(subv);
        }
    }
    return res;
}
