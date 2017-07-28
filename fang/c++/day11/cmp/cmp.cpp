#include "cmp.h"
#include <cstring>
//通用模板
template <typename T>
Comparator<T>::Comparator(T x, T y):
    m_x(x), m_y(y){}
template <typename T>
T Comparator<T>:: min (void) const{
    return m_x < m_y ? m_x : m_y;
}
template <typename T>
T Comparator<T>::max (void) const{
    return m_x > m_y ? m_x : m_y;
}
//针对char*的成员函数特化
template<>
char* Comparator<char*>::min(void) const{
    return strcmp(m_x, m_y) < 0 ? m_x : m_y;
}
template<>
char* Comparator<char*>::max(void) const{
    return strcmp(m_x, m_y) > 0 ? m_x : m_y;
}

