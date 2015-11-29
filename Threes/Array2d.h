// Threes Clone App
// Array2d.h
// 2次元配列を扱うための利便用クラス。
// @author Okumura Hiroaki

#include "constants.h"

template <class T>
class Array2d
{
public:
    Array2d()
    {
        m_elems = NULL;
    }
    ~Array2d()
    {
        SAFE_DELETE_ARRAY(m_elems);
    }
    void setSize(int size_x, int size_y)
    {
        m_x = size_x;
        m_y = size_y;
        m_elems = new T[m_x * m_y];
    }

    T& operator()(int x, int y)
    {
        _ASSERT(0 <= x && x <= m_x);
        _ASSERT(0 <= y && y <= m_y);
        return m_elems[y * m_x + x];
    }

    const T& operator()(int x, int y) const
    {
        _ASSERT(0 <= x && x <= m_x);
        _ASSERT(0 <= y && y <= m_y);
        return m_elems[y * m_x + x];
    }

private:
    T*  m_elems;
    int m_x;
    int m_y;
};