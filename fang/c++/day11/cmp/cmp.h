#ifndef _CMP_H
#define _CMP_H
//通用模板
template <typename T>
class Comparator{
    public:
        Comparator(T x, T y);
        T min (void) const;
        T max (void) const;
    private:
        T m_x;
        T m_y;
};
#include "cmp.cpp"
#endif //_CMP_H

