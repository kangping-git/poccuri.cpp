#include "variable.cpp"
#include "functions.cpp"
#include "composite.cpp"
#include <iostream>

using namespace std;

int main()
{
    auto a = VectorVariable<7>(0.5);
    auto b = VectorVariable<7>(0.7);
    auto t = DotProduct(a, b);
    cout << get<0>(t.backward(1.0)) << endl;
}