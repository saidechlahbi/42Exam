#include "bigint.hpp"

bigint::bigint(){
    container.push_front(0);
    data = 0;
}

bigint::bigint(int value)
{
    if (value == 0)
    {
        data = value;
        container.push_front(0);
    }
    if (value > 0)
    {
        data = value;
        while (value)
        {
            container.push_front(value%10);
            value = value / 10;
        }
    }
}

bigint::bigint(const bigint &other):container(other.container), data(other.data)
{}

bigint& bigint::operator=(const bigint &other)
{
    if (this != &other)
    {
        container = other.container;
        data = other.data;
    }
    return *this;
}

bigint::~bigint(){}


void bigint::print() const
{
    for (int i = 0; i<container.size();i++)
        std::cout << container[i] ;
}


void bigint::addition(const bigint& obj)
{
    int value1, value2;
    if (container.size() == 1)
        value1 = container[0];
    else
    {
        value1 = container[0];
        for (int i = 1; i < container.size(); i++)
        {
            value1 *= 10;
            value1 += container[i];
        }

    }

    if (obj.container.size() == 1)
        value2 = obj.container[0];
    else
    {
        value2 = obj.container[0];
        for (int i = 1; i < obj.container.size(); i++)
        {
            value2 *= 10;
            value2 += obj.container[i];
        }

    }

    int data = value1 + value2;
    container.clear();
    if (data == 0)
        container.push_front(0);
    if (data > 0)
    {
        while (data)
        {
            container.push_front(data%10);
            data = data / 10;
        }
    }
}

bigint bigint::operator+(const bigint &obj) const
{

}

bigint& bigint::operator+=(const bigint &obj)
{
    return this.addition(obj);
}

std::ostream &operator<<(std::ostream& out, const bigint &F)
{
    F.print();
    return out;
}