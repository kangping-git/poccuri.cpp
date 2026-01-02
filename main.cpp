#include "variable.cpp"
#include "functions.cpp"
#include "composite.cpp"
#include <iostream>

using namespace std;

int main()
{
    auto compositeC = composite();
    auto a = VectorVariable<7>({0.0, 0.6, 0.4, 2, 3.6, 0.1, -0.7});
    auto b = VectorVariable<7>(0.7);
    auto c = VectorVariable<7>({0.6, -0.2, 0.8, 0.2, -0.5, 0.2, -0.1});
    compositeC.subscribeVariable(a);
    compositeC.subscribeVariable(b);
    compositeC.subscribeVariable(c);
    cout << compositeC << endl;
}