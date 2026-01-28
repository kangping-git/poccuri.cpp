#pragma once

#include <cstddef>
#include <memory>
#include <vector>
#include <iostream>
#include <concepts>
#include <array>

using namespace std;

template <size_t... N>
constexpr size_t getSize()
{
    size_t size = 1;
    if constexpr (sizeof...(N) > 0)
    {
        size = (N * ...);
    }
    return size;
}
template <size_t... N>
constexpr array<size_t, sizeof...(N)> getMultiplies()
{
    if constexpr (sizeof...(N) == 0)
    {
        return {};
    }
    array<size_t, sizeof...(N)> multiplies;
    size_t sizes[] = {N...};
    multiplies[sizeof...(N) - 1] = 1;
    for (size_t i = (sizeof...(N)) - 1; i > 0; --i)
    {
        multiplies[i - 1] = multiplies[i] * sizes[i];
    }
    return multiplies;
}

template <typename T, size_t... N>
class Tensor
{
private:
    shared_ptr<vector<T>> data;
    static constexpr size_t total_size = getSize<N...>();
    static constexpr size_t sizes[] = {N...};
    static constexpr array<size_t, sizeof...(N)> multiplies = getMultiplies<N...>();

public:
    Tensor() : data(make_shared<vector<T>>(total_size))
    {
    }

    T &operator()(convertible_to<size_t> auto... idx)
        requires(sizeof...(idx) == sizeof...(N))
    {
        size_t p = 0;
        size_t indices[] = {static_cast<size_t>(idx)...};
        size_t sizes[] = {N...};
        for (size_t i = 0; i < sizeof...(N); ++i)
        {
            if (indices[i] >= sizes[i])
            {
                throw runtime_error("out of index");
            }
            p += indices[i] * multiplies[i];
        }
        return (*data)[p];
    };
    const T &operator()(convertible_to<size_t> auto... idx) const
        requires(sizeof...(idx) == sizeof...(N))
    {
        size_t p = 0;
        size_t indices[] = {static_cast<size_t>(idx)...};
        for (size_t i = 0; i < sizeof...(N); ++i)
        {
            p += indices[i] * multiplies[i];
        }
        return (*data)[p];
    };
    T &operator[](convertible_to<size_t> auto idx)
    {
        return (*data)[idx];
    }
    const T &operator[](convertible_to<size_t> auto idx) const
    {
        return (*data)[idx];
    }
};