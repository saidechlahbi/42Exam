#ifndef VECT2_HPP
#define VECT2_HPP

#include <bits/stdc++.h>


class vect2
{
    private:
        int x;
        int y;
    public:
        vect2();
        vect2(int a, int b);
        vect2(const vect2& other);
        vect2& operator=(const vect2& other);
        ~vect2();

        // getrs and seters
        int getX() const;
        int getY() const;
        void setX(int a);
        void setY(int b);

        bool operator==(const vect2& obj) const; // v1 == v2
        bool operator!=(const vect2& obj) const;  // v1 != v2

        vect2& operator+=(const vect2& obj); // v1 += v2
        vect2& operator-=(const vect2& obj); // v1 -= v2
        vect2& operator*=(const vect2& obj); // v1 *= v2

        vect2& operator++(); // ++i
        vect2& operator--(); // --i
        vect2 operator++(int); // i++
        vect2 operator--(int); // i--

        vect2& operator*=(int num); // v1 *= 33

        vect2 operator-(const vect2 &obj) const; // v1 - v2
        vect2 operator+(const vect2 &obj) const; // v1 + v2
        vect2 operator*(const vect2 &obj) const; // v1 *v2
        
        vect2 operator-() const;
        vect2 operator*(int num) const;
        vect2& operator=(int num);

        int& operator[](std::size_t idx);
        int operator[](std::size_t idx) const;
};
std::ostream &operator<<(std::ostream& out, const vect2& F);
vect2 operator*(int num, const vect2& v);
#endif /*VECT2_HPP*/

