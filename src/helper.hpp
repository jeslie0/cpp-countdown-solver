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

template<typename T>
auto subVectors(std::vector<T> v) -> std::vector<std::vector<T>>
{
    std::vector<std::vector<T>> res;
    T n = v.size();
    for (T i = 0; i < n; i++)
    {
        for (T j = i; j < n; j++)
        {
            std::vector<T> subv;
            for (T k = i; k <= j; k++)
            {
                subv.push_back(v[k]);
            }
            res.push_back(subv);
        }
    }
    return res;
}
