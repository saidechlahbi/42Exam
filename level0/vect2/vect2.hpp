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


        vect2 operator++(int);
        vect2& operator++();
        vect2 operator--(int);
        vect2& operator--();

        vect2& operator+=(const vect2& obj);
        vect2& operator-=(const vect2& obj);


        vect2 operator+(const vect2& obj) const;
        vect2 operator-(const vect2& obj) const;

        vect2 operator*(int value) const;
        vect2& operator*=(int value);


        bool operator==(const vect2 &obj) const;
        bool operator!=(const vect2 &obj) const;

        vect2 operator-() const;
        int operator[](std::size_t index) const;
        int& operator[](std::size_t index);
};

std::ostream &operator<<(std::ostream& out, const vect2& F);
vect2 operator*(int num, const vect2& v);
#endif /*VECT2_HPP*/

