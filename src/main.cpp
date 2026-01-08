#include <iostream>
#include "tensor/tensor.cpp"

using namespace std;

int main()
{
    Tensor<float, 2, 5> tensor;
    tensor(1, 4) = 1.0;
    tensor(1, 3) = 2.0;
    tensor(1, 1) = 5.0;
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            cout << tensor(i, j) << " ";
        }
        cout << endl;
    }
    return 0;
}