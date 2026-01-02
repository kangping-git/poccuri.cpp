#pragma once

#include <any>
#include <memory>
#include "variable.cpp"
using namespace std;

// 関数を組み合わせてグラフを作ってやるやつ

enum VariableType
{
    FloatVariableType,
    VectorVariableType,
};
class Variable
{
private:
    VariableType v_t;
    size_t l;
    vector<double> value;

public:
    Variable(floatVariable input)
    {
        value.push_back(input.get());
        v_t = VariableType::FloatVariableType;
    };
    template <size_t N>
    Variable(VectorVariable<N> input)
    {
        v_t = VariableType::VectorVariableType;
        l = N;
        for (size_t i = 0; i < N; ++i)
        {
            value.push_back(input[i]);
        }
    };
    floatVariable getAsFloatVariable()
    {
        if (v_t != VariableType::FloatVariableType)
        {
            throw runtime_error("The value is not FloatVariable");
        }
        return floatVariable(value[0]);
    };
    template <size_t N>
    VectorVariable<N> getAsVectorVariable()
    {
        if (v_t != VariableType::VectorVariableType || l != N)
        {
            throw runtime_error("The value is not VectorVariable<N>");
        }
        return VectorVariable<N>(value);
    };
    vector<double> getAsVector()
    {
        if (v_t != VariableType::VectorVariableType)
        {
            throw runtime_error("The value is not VectorVariable");
        }
        return value;
    }
    VariableType getType()
    {
        return v_t;
    }
    size_t getSize()
    {
        return l;
    }
};

template <typename Target, typename... T>
constexpr bool contains()
{
    return (std::is_same_v<Target, T> || ...);
};

class composite
{
private:
    vector<Variable> variables;

public:
    composite() = default;

    void subscribeVariable(floatVariable v)
    {
        variables.push_back(v);
    }
    template <size_t N>
    void subscribeVariable(VectorVariable<N> v)
    {
        variables.push_back(v);
    }

    friend ostream &operator<<(ostream &os, composite val)
    {
        cout << "Composite(";
        cout << "variables={";
        bool f = false;
        for (Variable v : val.variables)
        {
            if (f)
                cout << ", ";
            if (v.getType() == FloatVariableType)
            {
                cout << v.getAsFloatVariable();
            }
            if (v.getType() == VectorVariableType)
            {
                vector<double> vec = v.getAsVector();
                os << "Vector(";
                for (int i = 0; i < vec.size(); ++i)
                {
                    if (i == 0)
                    {
                        os << vec[i];
                    }
                    else
                    {
                        os << ", " << vec[i];
                    }
                }
                os << ")";
            }
            f = true;
        };
        cout << "})";
        return os;
    }
};