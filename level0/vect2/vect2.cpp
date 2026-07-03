#include "vect2.hpp"

vect2::vect2(): x(0), y(0) {}

vect2::vect2(int a, int b): x(a), y(b) {}

vect2::vect2(const vect2 &other): x(other.x), y(other.y) {}

const vect2& vect2::operator=(const vect2& other)
{
    if (this != &other)
    {
        x = other.x;
        y = other.y;
    }
    return *this;
}
vect2::~vect2(){}


int vect2::getX() const
{
    return x;
}
int vect2::getY() const
{
    return y;
}
void vect2::setX(int a)
{
    x = a;
}
void vect2::setY(int b)
{
    y = b;
}

const vect2& vect2::operator[](int a) const
{
    if (a == 0)
        std::cout << this->getX();
    else if (a == 1)
        std::cout << this->getY();
    else
        std::cout << "error";
    return *this;
}


std::ostream& operator<<(std::ostream& out, const vect2& F)
{
    out << "{" << F.getX() << ", " << F.getY() << "}" << std::endl;
    return out;
}
