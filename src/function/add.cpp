#include <cstddef>
#include "../tensor/tensor.cpp"

template <typename T, size_t... N>
class add
{
private:
    Tensor<T, N...> A;
    Tensor<T, N...> B;

public:
    add(Tensor<T, N...> a, Tensor<T, N...> b)
    {
        A = a;
        B = b;
    }
    Tensor<T, N...> forward()
    {
        Tensor<T, N...> C;
        for (int i = 0; i < getSize<N...>(); ++i)
        {
            C[i] = A[i] + B[i];
        }
        return C;
    }
    array<Tensor<T, N...>, 2> backward(Tensor<T, N...> b)
    {
        return {b, b};
    }
};