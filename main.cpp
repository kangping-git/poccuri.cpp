#include "variable.cpp"
#include "functions.cpp"
#include "composite.cpp"
#include <iostream>

using namespace std;

int main()
{
    auto a = VectorVariable<7>({0.0, 0.6, 0.4, 2, 3.6, 0.1, -0.7});
    auto b = VectorVariable<7>(0.7);
    auto c = VectorVariable<7>({0.6, -0.2, 0.8, 0.2, -0.5, 0.2, -0.1});
    auto t = DotProduct(a, b);
    auto t_result = t.get();
    auto t2 = Scalar<7>(c, t_result);
    auto t2_backward = t2.backward(1.0);
}