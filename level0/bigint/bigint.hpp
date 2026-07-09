#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <deque>
class bigint 
{
    private:
        std::deque<int> container;

    public:
        bigint();
        bigint(int value);
        bigint(const bigint &other);
        bigint &operator=(const bigint &other);
        ~bigint();

        void addition(const bigint& obj);

        /* helper functions*/
        void print()const;
        bigint operator+(const bigint &obj) const; // a + b
        bigint& operator+=(const bigint &obj); // a+= b

        bigint& operator++(); // ++i
        bigint operator++(int); // i++

        bigint &operator<<(int bitshifted); // b << 10
        bigint &operator<<=(int bitshifted); // d <<= 4
        bigint &operator>>=(const bigint data);  // d >>= (const bigint) 2


        bool operator<(const bigint obj) const;
        bool operator>(const bigint obj) const;
        bool operator==(const bigint obj) const;
        bool operator!=(const bigint obj) const;
        bool operator<=(const bigint obj) const;
        bool operator>=(const bigint obj) const;

        bigint& operator<<(const bigint &obj);
        bigint& operator>>(const bigint &obj);


    // comparison
    // digitshift
};

std::ostream& operator<<(std::ostream &out, const bigint& F);
#endif /*BIGINT_HPP*/
