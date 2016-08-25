/**
 * @file point.tcc
 * Implementation of the point class.
 *
 * @author Shahzad Bhatti
 * @date Summer 2015
 */

#include "point.h"

template <int Dim>
point<Dim>::point()
{
    for (int i = 0; i < Dim; ++i)
        vals_[i] = 0;
}

template <int Dim>
point<Dim>::point(double arr[Dim])
{
    for (int i = 0; i < Dim; ++i)
        vals_[i] = arr[i];
}

template <int Dim>
template <class... Ts>
point<Dim>::point(Ts... args)
    : vals_{static_cast<double>(args)...}
{
    static_assert(sizeof...(Ts) == Dim, "must specify all elements of the point");
}

template <int Dim>
double point<Dim>::operator[](int index) const
{
    if (index >= Dim)
        throw std::out_of_range{"point index out of range"};
    return vals_[index];
}

template <int Dim>
double& point<Dim>::operator[](int index)
{
    if (index >= Dim)
        throw std::out_of_range{"point index out of range"};
    return vals_[index];
}

template <int Dim>
bool operator==(const point<Dim>& lhs, const point<Dim>& rhs)
{
    for (int i = 0; i < Dim; ++i)
    {
        if (lhs[i] != rhs[i])
            return false;
    }
    return true;
}

template <int Dim>
bool operator!=(const point<Dim>& lhs, const point<Dim>& rhs)
{
    return !(lhs == rhs);
}

template <int Dim>
bool operator<(const point<Dim>& lhs, const point<Dim>& rhs)
{
    for (int i = 0; i < Dim; ++i)
    {
        if (lhs[i] != rhs[i])
            return lhs[i] < rhs[i];
    }
    return false;
}

template <int Dim>
bool operator>(const point<Dim>& lhs, const point<Dim>& rhs)
{
    return rhs < lhs;
}

template <int Dim>
bool operator<=(const point<Dim>& lhs, const point<Dim>& rhs)
{
    return lhs < rhs || lhs == rhs;
}

template <int Dim>
bool operator>=(const point<Dim>& lhs, const point<Dim>& rhs)
{
    return lhs > rhs || lhs == rhs;
}
