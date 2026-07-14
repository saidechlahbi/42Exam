#include "vect2.hpp"
#include <stdexcept>

vect2::vect2() : x(0), y(0) {}
vect2::vect2(int a, int b) : x(a), y(b) {}
vect2::vect2(const vect2& other) : x(other.x), y(other.y) {}
vect2& vect2::operator=(const vect2& other) { if (this != &other) { x = other.x; y = other.y; } return *this; }
vect2::~vect2() {}



vect2  vect2::operator++(int)
{
    vect2 tmp = *this;;
    x += 1;
    y += 1;
    return tmp;
}
vect2& vect2::operator++()
{
     x += 1;
    y += 1;
    return *this;   
}
vect2  vect2::operator--(int)
{
    vect2 tmp = *this;;
    x -= 1;
    y -= 1;
    return tmp;
}
vect2& vect2::operator--()
{
    x -= 1;
    y -= 1;
    return *this;  
}

vect2& vect2::operator+=(const vect2& obj)
{
    x +=obj.x;
    y += obj.y;
    return *this;
}
vect2& vect2::operator-=(const vect2& obj)
{
    x -=obj.x;
    y -= obj.y;
    return *this;
}


vect2  vect2::operator+(const vect2& obj) const
{
    vect2 tmp;
    tmp[0] = x + obj.x;
    tmp[1] = y + obj.y;
    return tmp;
}
vect2  vect2::operator-(const vect2& obj) const
{
    vect2 tmp;
    tmp[0] = x - obj.x;
    tmp[1] = y - obj.y;
    return tmp;
}

vect2  vect2::operator*(int value) const
{
    vect2 tmp;
    tmp[0] = x * value;
    tmp[1] = y * value;
    return tmp;
}
vect2& vect2::operator*=(int value)
{
    x *= value;
    y *= value;
    return *this;
}


bool   vect2::operator==(const vect2 &obj) const
{
    if (x == obj.x && y == obj.y)
        return true;
    return false;
}
bool   vect2::operator!=(const vect2 &obj) const
{
    if (x == obj.x && y == obj.y)
        return false;
    return true;
}

vect2  vect2::operator-() const
{
    vect2 tmp = *this;
    tmp[0] *= - 1;
    tmp[1] *= - 1;
    return tmp;
}
int    vect2::operator[](std::size_t index) const
{
    if (index == 0)
        return x;
    if (index == 1)
        return y;
    return 0;
}
int&   vect2::operator[](std::size_t index)
{
    if (index == 0)
        return x;
    if (index == 1)
        return y;
    return x;
}



std::ostream &operator<<(std::ostream& out, const vect2& F) {
    out << "{" << F[0] << ", " << F[1] << "}";
    return out;
}

vect2 operator*(int num, const vect2& v) {
    return v * num;
}