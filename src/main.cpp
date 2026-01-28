#include <iostream>
#include "tensor/tensor.cpp"
#include "function/add.cpp"

using namespace std;

int main()
{
    Tensor<float, 2, 5> tensor;
    tensor(1, 4) = 1.0;
    tensor(1, 3) = 2.0;
    tensor(1, 1) = 5.0;
    Tensor<float, 2, 5> tensor2;
    tensor2(1, 4) = 3.0;
    tensor2(1, 3) = 5.0;
    tensor2(1, 1) = 6.0;
    auto add_func = add(tensor, tensor2);
    Tensor<float, 2, 5>
        tensor3 = add_func.forward();
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << tensor(i, j) << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << tensor2(i, j) << " ";
        }
        cout << endl;
    }
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << tensor3(i, j) << " ";
        }
        cout << endl;
    }
    return 0;
}