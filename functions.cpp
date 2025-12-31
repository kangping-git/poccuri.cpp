#pragma once

#include <tuple>
#include <variant>
#include <type_traits>
#include "variable.cpp"

using namespace std;

// 関数

template <typename T>
struct is_vector : false_type
{
};
template <size_t N>
struct is_vector<VectorVariable<N>> : true_type
{
};

template <typename T>
inline constexpr bool is_vector_v = is_vector<T>::value;

template <typename T>
concept AllowedType = is_same_v<T, floatVariable> || is_vector_v<T>;

template <AllowedType T>
class add
{

private:
    T A;
    T B;
    T val;

public:
    add(T &a, T &b)
    {
        a.freeze();
        b.freeze();
        A = a;
        B = b;
        val = a + b;
    }
    T get()
    {
        return val;
    }
    tuple<T, T> backward(T r)
    {
        return {r, r};
    }
};

class FloatMulFloat
{
private:
    floatVariable A;
    floatVariable B;
    floatVariable val;

public:
    FloatMulFloat(floatVariable &a, floatVariable &b)
    {
        a.freeze();
        b.freeze();
        A = a;
        B = b;
        val = a.get() * b.get();
    }
    floatVariable get()
    {
        return val;
    }
    tuple<floatVariable, floatVariable> backward(floatVariable v)
    {
        floatVariable A_res = B.get() * v.get();
        floatVariable B_res = A.get() * v.get();
        A_res.freeze();
        B_res.freeze();
        return {A_res, B_res};
    }
};

template <size_t N>
class DotProduct
{
private:
    VectorVariable<N> A;
    VectorVariable<N> B;
    floatVariable val;

public:
    DotProduct(VectorVariable<N> &a, VectorVariable<N> &b)
    {
        a.freeze();
        b.freeze();
        A = a;
        B = b;
        double ans = 0;
        for (int i = 0; i < N; ++i)
        {
            ans += a[i] * b[i];
        }
        val = ans;
    }
    floatVariable get()
    {
        return val;
    }
    tuple<VectorVariable<N>, VectorVariable<N>> backward(floatVariable v)
    {
        VectorVariable<N> A_res(0.0);
        for (int i = 0; i < N; ++i)
        {
            A_res[i] = v.get() * B[i];
        }
        VectorVariable<N> B_res(0.0);
        for (int i = 0; i < N; ++i)
        {
            B_res[i] = v.get() * A[i];
        }
        A_res.freeze();
        B_res.freeze();
        return {A_res, B_res};
    }
};

template <size_t N>
class Scalar
{
private:
    VectorVariable<N> A;
    floatVariable B;
    VectorVariable<N> val;

public:
    Scalar(VectorVariable<N> &a, floatVariable &b)
    {
        a.freeze();
        b.freeze();
        A = a;
        B = b;

        for (int i = 0; i < N; ++i)
        {
            val[i] = A[i] * B.get();
        }
    }

    VectorVariable<N> get()
    {
        return val;
    }

    tuple<VectorVariable<N>, floatVariable> backward(VectorVariable<N> v)
    {
        float grad_B_val = 0;
        for (int i = 0; i < N; ++i)
        {
            grad_B_val += v[i] * A[i];
        }
        floatVariable grad_B = grad_B_val;

        VectorVariable<N> grad_A;
        for (int i = 0; i < N; ++i)
        {
            grad_A[i] = B.get() * v[i];
        }

        grad_A.freeze();
        grad_B.freeze();

        return {grad_A, grad_B};
    }
};

template <size_t N, size_t A, size_t B>
    requires(A <= B && B <= N)
class Slice
{
private:
    VectorVariable<N> value;
    VectorVariable<B - A> output;

public:
    Slice(VectorVariable<N> &from)
    {
        from.freeze();
        value = from;
        for (int i = A; i < B; ++i)
        {
            output[i - A] = from[i];
        }
    }
    VectorVariable<B - A> get()
    {
        return output;
    }
    tuple<VectorVariable<N>> backward(VectorVariable<B - A> v)
    {
        VectorVariable<N> b(0.0);
        for (int i = A; i < B; ++i)
        {
            b[i] = v[i - A];
        }
        b.freeze();
        return b;
    }
};

template <size_t N, size_t idx>
    requires(idx < N)
class GetFromIdx
{
private:
    floatVariable output;

public:
    GetFromIdx(VectorVariable<N> from)
    {
        output = floatVariable(from[idx]);
    }
    floatVariable get()
    {
        return output;
    }
    tuple<VectorVariable<N>> backward(floatVariable v)
    {
        VectorVariable<N> res(0.0);
        res[idx] = static_cast<double>(v.get());
        res.freeze();
        return {res};
    }
};