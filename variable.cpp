#pragma once

// 行列、ベクトルとか
#include <vector>
#include <array>
#include <iostream>
using namespace std;

struct FloatProxy
{
    double &ref;
    bool frozen;

    operator double() const
    {
        return ref;
    }
    FloatProxy &operator=(double v)
    {
        if (frozen)
        {
            throw runtime_error("frozen value cannot change");
        }
        ref = v;
        return *this;
    }
};

class floatVariable
{
private:
    double value;
    bool frozen = false;

public:
    floatVariable()
    {
    }
    floatVariable(double val)
    {
        value = val;
    }
    void freeze() { frozen = true; }
    FloatProxy get()
    {
        return FloatProxy{value, frozen};
    }
    floatVariable operator+(floatVariable const other)
    {
        floatVariable res(value + other.value);
        return res;
    }
    friend ostream &operator<<(ostream &os, floatVariable val)
    {
        os << "float(" << val.value << ")";
        return os;
    }
};
template <size_t N>
class VectorVariable
{
private:
    array<double, N> value;
    bool frozen = false;

public:
    VectorVariable()
    {
    }
    VectorVariable(double v)
    {
        value.fill(v);
    }
    VectorVariable(array<double, N> v)
    {
        value = v;
    }
    VectorVariable operator+(VectorVariable other)
    {
        array<double, N> res;
        for (int i = 0; i < N; ++i)
        {
            res[i] = value[i] + other.value[i];
        }
        return VectorVariable(res);
    }
    double operator[](size_t idx) const
    {
        return value[idx];
    }
    FloatProxy operator[](size_t idx)
    {
        return FloatProxy(value[idx], frozen);
    }
    void freeze() { frozen = true; }
    friend ostream &operator<<(ostream &os, VectorVariable val)
    {
        os << "Vector(";
        for (int i = 0; i < N; ++i)
        {
            if (i == 0)
            {
                os << val.value[i];
            }
            else
            {
                os << ", " << val.value[i];
            }
        }
        os << ")";
        return os;
    }
};