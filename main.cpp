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
    auto t2 = GetFromIdx<7, 2>(a);
    auto t2_result = t2.get();
    auto t3 = FloatMulFloat(t_result, t2_result);
    auto t3_result = t3.get();
    auto t4 = Scalar(c, t3_result);
    auto t4_backward = t4.backward(1.0);
    auto t3_backward = t3.backward(get<1>(t4_backward));
    auto c_backward = get<0>(t4_backward);
    auto t2_backward = t2.backward(get<1>(t3_backward));
    auto t_backward = t.backward(get<0>(t3_backward));
    auto a_backward = get<0>(t2_backward);
    a_backward = a_backward + get<0>(t_backward);
    auto b_backward = get<1>(t_backward);
    cout << "t_4 = " << t4.get() << endl;
    cout << "δt_4/δa = " << a_backward << endl;
    cout << "δt_4/δb = " << b_backward << endl;
    cout << "δt_4/δc = " << c_backward << endl;
}