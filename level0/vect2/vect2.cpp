#include "vect2.hpp"
#include <stdexcept>

vect2::vect2() : x(0), y(0) {}
vect2::vect2(int a, int b) : x(a), y(b) {}
vect2::vect2(const vect2& other) : x(other.x), y(other.y) {}
vect2& vect2::operator=(const vect2& other) { if (this != &other) { x = other.x; y = other.y; } return *this; }
vect2::~vect2() {}

int vect2::getX() const { return x; }
int vect2::getY() const { return y; }
void vect2::setX(int a) { x = a; }
void vect2::setY(int b) { y = b; }

bool vect2::operator==(const vect2& obj) const { return x == obj.x && y == obj.y; }
bool vect2::operator!=(const vect2& obj) const { return !(*this == obj); }

vect2& vect2::operator+=(const vect2& obj) { x += obj.x; y += obj.y; return *this; }
vect2& vect2::operator-=(const vect2& obj) { x -= obj.x; y -= obj.y; return *this; }
vect2& vect2::operator*=(const vect2& obj) { x *= obj.x; y *= obj.y; return *this; }

vect2& vect2::operator++() { ++x; ++y; return *this; }
vect2& vect2::operator--() { --x; --y; return *this; }
vect2 vect2::operator++(int) { vect2 tmp(*this); ++(*this); return tmp; }
vect2 vect2::operator--(int) { vect2 tmp(*this); --(*this); return tmp; }

vect2& vect2::operator*=(int num) { x *= num; y *= num; return *this; }

vect2 vect2::operator-(const vect2 &obj) const { return vect2(x - obj.x, y - obj.y); }
vect2 vect2::operator+(const vect2 &obj) const { return vect2(x + obj.x, y + obj.y); }
vect2 vect2::operator*(const vect2 &obj) const { return vect2(x * obj.x, y * obj.y); }

vect2 vect2::operator-() const { return vect2(-x, -y); }
vect2 vect2::operator*(int num) const { return vect2(x * num, y * num); }
vect2& vect2::operator=(int num) { x = num; y = num; return *this; }

int& vect2::operator[](std::size_t idx) {
    if (idx == 0) return x;
    if (idx == 1) return y;
    throw std::out_of_range("vect2::operator[] index out of range");
}
int vect2::operator[](std::size_t idx) const {
    if (idx == 0) return x;
    if (idx == 1) return y;
    throw std::out_of_range("vect2::operator[] index out of range");
}

std::ostream &operator<<(std::ostream& out, const vect2& F) {
    out << "{" << F.getX() << ", " << F.getY() << "}";
    return out;
}

vect2 operator*(int num, const vect2& v) {
    return v * num;
}