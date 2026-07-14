#include "bigint.hpp"

bigint::bigint(){
    container.push_front(0);
}

bigint::bigint(unsigned long long value)
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



bigint bigint::operator+(const bigint &obj) const
{
    bigint result;
    std::deque<int> new_result;
    std::deque<int> first_container = this->container;
    std::deque<int> second_container = obj.container;
    if (this->container.size() == 1 && this->container[0] == 0)
    {
        result.container = obj.container;
        return result;
    }
    if (obj.container.size() == 1 && obj.container[0] == 0)
    {
        result.container = this->container;
        return result;
    }
    if (first_container.size() > second_container.size())
    {
        for (int i = second_container.size(); i < first_container.size(); i++)
            second_container.push_front(0);        
    }
    if (second_container.size() > first_container.size())
    {
        for (int i = first_container.size(); i < second_container.size(); i++)
            first_container.push_front(0);        
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
    result.container = new_result;
    return result;
}

bigint& bigint::operator+=(const bigint &obj)
{
    *this = *this + obj;
    return *this;
}

bigint& bigint::operator++()
{
    *this = *this + bigint(1);
    return *this;
}

bigint bigint::operator++(int)
{
    bigint tmp = *this;
    ++(*this);
    return tmp;
}

bigint bigint::operator<<(int bitshifted)
{
    bigint tmp = *this;
    for (int i = 0; i < bitshifted; i++)
        tmp.container.push_back(0);
    return tmp;
}

bigint& bigint::operator<<=(int bitshifted)
{
    for (int i = 0; i < bitshifted; i++)
        this->container.push_back(0);
    return *this;
}


bigint bigint::operator>>(int bitshifted)
{
    bigint tmp = *this;
    for (int i = 0; i < bitshifted; i++)
        tmp.container.pop_back();
    return tmp;
}

bigint& bigint::operator>>=(int bitshifted)
{
    for (int i = 0; i < bitshifted; i++)
        this->container.pop_back();
    return *this;
}


bigint& bigint::operator>>=(const bigint& data)
{
    unsigned long n = 0;
    for (int i = 0; i < data.container.size(); i++)
    {
        n = n * 10 + data.container[i];
        if (n >=  INT_MAX)
        {
            n = INT_MAX;
            break;
        }
    }
    
    *this = *this >>= n;
     return *this;
}

bigint& bigint::operator<<=(const bigint& data)
{
    unsigned long n = 0;
    for (int i = 0; i < data.container.size(); i++)
    {
        n = n * 10 + data.container[i];
        if (n >=  INT_MAX)
        {
            n = INT_MAX;
            break;
        }
    }
    
    *this = *this <<= n;
     return *this;
}

bigint bigint::operator>>(const bigint& data)
{
    unsigned long n = 0;
    for (int i = 0; i < data.container.size(); i++)
    {
        n = n * 10 + data.container[i];
        if (n >=  INT_MAX)
        {
            n = INT_MAX;
            break;
        }
    }
    
    bigint tmp  = *this >> n;
    return tmp;
}

bigint bigint::operator<<(const bigint& data)
{
    unsigned long n = 0;
    for (int i = 0; i < data.container.size(); i++)
    {
        n = n * 10 + data.container[i];
        if (n >=  INT_MAX)
        {
            n = INT_MAX;
            break;
        }
    }
    
    bigint tmp  = *this << n;
    return tmp;
}


bool bigint::operator<(const bigint obj) const
{
    if (container.size() < obj.container.size())
        return true;
    if (container.size() > obj.container.size())
        return false;
    if (container.size() == obj.container.size())
    {
        int i = 0;
        while (i < container.size() && container[i] == obj.container[i])
            i++;
        if (i == container.size())
            return false;
        else if (container[i] > obj.container[i])
            return false;
        else
            return true;
    }
    return false;
}


bool bigint::operator>(const bigint obj) const
{
    if (container.size() < obj.container.size())
        return false;
    if (container.size() > obj.container.size())
        return true;
    if (container.size() == obj.container.size())
    {
        int i = 0;
        while (i < container.size() && container[i] == obj.container[i])
            i++;
        if (i == container.size())
            return false;
        else if (container[i] > obj.container[i])
            return true;
        else
            return false;
    }
    return false;
}
bool bigint::operator==(const bigint obj) const
{
    if (container.size() < obj.container.size())
        return false;
    if (container.size() > obj.container.size())
        return false;
    if (container.size() == obj.container.size())
    {
        int i = 0;
        while (i < container.size() && container[i] == obj.container[i])
            i++;
        if (i == container.size())
            return true;
        else if (container[i] > obj.container[i])
            return false;
        else
            return false;
    }
    return false;
}

bool bigint::operator!=(const bigint obj) const
{
    if (container.size() < obj.container.size())
        return true;
    if (container.size() > obj.container.size())
        return true;
    if (container.size() == obj.container.size())
    {
        int i = 0;
        while (i < container.size() && container[i] == obj.container[i])
            i++;
        if (i == container.size())
            return false;
        else if (container[i] > obj.container[i])
            return true;
        else
            return true;
    }
    return true;
}

bool bigint::operator<=(const bigint obj) const
{
    if (container.size() < obj.container.size())
        return true;
    if (container.size() > obj.container.size())
        return false;
    if (container.size() == obj.container.size())
    {
        int i = 0;
        while (i < container.size() && container[i] == obj.container[i])
            i++;
        if (i == container.size())
            return true;
        else if (container[i] > obj.container[i])
            return false;
        else
            return true;
    }
    return false;
}
bool bigint::operator>=(const bigint obj) const
{
    if (container.size() < obj.container.size())
        return false;
    if (container.size() > obj.container.size())
        return true;
    if (container.size() == obj.container.size())
    {
        int i = 0;
        while (i < container.size() && container[i] == obj.container[i])
            i++;
        if (i == container.size())
            return true;
        else if (container[i] > obj.container[i])
            return true;
        else
            return false;
    }
    return false;
}


std::ostream &operator<<(std::ostream& out, const bigint &F)
{
    F.print();
    return out;
}