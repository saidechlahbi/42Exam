#pragma once

#include "searchable_bag.hpp"
class set
{
    private:
        searchable_bag *bag;
    public:

        set(){}
        set(searchable_bag &obj)
        {
            bag = &obj;
        }
        set(const set& other):bag(other.bag){}
        set  &operator=(const set& other)
        {
            if (this != &other)
                bag = other.bag;
            return *this;
        }
        ~set(){}

        void insert (int value)
        {
            if (bag->has(value) == false)
                bag->insert(value);
        }
        void insert (int *data, int size)
        {
            for (int i = 0; i < size; i ++)
            {
                if (!data || size <= 0)
                    return;
                if (bag->has(data[i]) ==false)
                    bag->insert(data[i]);
            }
        }
        void print() const
        {
            bag->print();
        }
        void clear()
        {
            bag->clear();
        }

        bool has(int value) const
        {
            return bag->has(value);
        }
        searchable_bag& get_bag()
        {
            return *bag;
        }
};