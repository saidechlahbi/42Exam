#ifndef SEARCHABLE_TREE_BAG
#define SEARCHABLE_TREE_BAG

#include "tree_bag.hpp"
#include "searchable_bag.hpp"
class searchable_tree_bag: public tree_bag, public searchable_bag
{
    private:
        /* data */
    public:
        searchable_tree_bag(){}
        searchable_tree_bag(const searchable_tree_bag& other):tree_bag(other){}
        searchable_tree_bag& operator=(const searchable_tree_bag& other)
        {
            if (this != &other)
            {
                tree_bag::operator=(other);
            }
            return *this;
        }
        ~searchable_tree_bag(){}
        virtual bool has(int value) const
        {
            node *current = tree;
            while (current)
            {
                if (current->value == value)
                    return true;
                if (current->value > value)
                    current = current->l;
                else
                    current = current->r;
            }
            return false;
        }
    };




#endif /*SEARCHABLE_TREE_BAG*/