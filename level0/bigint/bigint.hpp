#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <deque>
class bigint 
{
    private:
        std::deque<int> container;
        int data;
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
    // comparison
    // digitshift
};

std::ostream& operator<<(std::ostream &out, const bigint& F);
#endif /*BIGINT_HPP*/
