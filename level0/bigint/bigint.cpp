#include "bigint.hpp"

bigint::bigint(){
    container.push_front(0);
}

bigint::bigint(int value)
{
    if (value == 0)
    {
        container.push_front(0);
    }
    if (value > 0)
    {
        while (value)
        {
            container.push_front(value%10);
            value = value / 10;
        }
    }
}

bigint::bigint(const bigint &other):container(other.container)
{}
bigint& bigint::operator=(const bigint &other)
{
    if (this != &other)
    {
        container = other.container;
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
    std::deque<int> new_result;
    std::deque<int> first_container = this->container;
    std::deque<int> second_container = obj.container;
    if (this->container.size() == 0 && this->container[0] == 0)
    {
        this->container = obj.container;
        return;
    }
    if (obj.container.size() == 0 && obj.container[0] == 0)
    {
        return;
    }
    if (first_container.size() > second_container.size())
    {
        for (int i = second_container.size(); i < first_container.size(); i++)
            second_container.push_back(0);        
    }
    if (second_container.size() > first_container.size())
    {
        for (int i = first_container.size(); i < second_container.size(); i++)
            first_container.push_back(0);        
    }
    int data = 0;
    for (int i = first_container.size() - 1; i >= 0; i--)
    {
        data = first_container[i] + second_container[i];
        new_result.push_front(data%10);
        if (data >= 10)
            data = data - 10;
        else 
            data = 0;
    }
    if (data > 0)
        new_result.push_front(data);
    this->container = new_result;
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