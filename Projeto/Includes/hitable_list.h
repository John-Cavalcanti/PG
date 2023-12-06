#ifndef HITABLE_LIST_H
#define HITABLE_LIST_H

#include "./hitable.h"
// TODO hitable list deve receber um Vector ou List

class hitable_list: public hitable {
    public:
        hitable_list() {}
        hitable_list(hitable **l, int n) { list = l; list_size = n;}
        virtual bool hit(const ray& r, float t_min, float t_max, hit_record& rec) const;
        hitable **list;
        int list_size;
};


#endif