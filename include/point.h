/**
 * @file point.h
 * Definition of a point class for k dimensional points.
 *
 * @author Shahzad Bhatti
 * @date Summer 2015
 */

#ifndef POINT_H__
#define POINT_H__

#include <array>
#include <cstdint>

template <int Dim>
class point
{
    public:
    static_assert(Dim > 0, "Dimension argument must be positive");
 
   /**
     * Creates a default point with zero values.
     */
    point();

    /**
     * Constructs a point from an array.
     * @param arr used to constuct point.
     */
    point(double arr[Dim]);

    /**
     * Constructs a point from a list of arguments.
     *
     * @param args used to constuct point.
     */
    template <class... Ts>
    explicit point(Ts... args);

    /**
     * Gets the value of the point object in the given dimension
     * (index). This function is const so we don't modify points using
     * this function.
     *
     * @param index The dimension of the point to grab.
     * @return The value of the point in the indexth dimension.
     * @throw std::out_of_range if accessing out of bounds
     */
    double operator[](int index) const;

    /**
     * Gets the value of the point object in the given dimension
     * (index). This is the non-const version, so it can be used to
     * modify points like so:
     *
     * \code
     * point<3> a(1, 2, 3);
     * a[0] = 4; // a is now (4, 2, 3)
     * \endcode
     *
     * @param index The dimension of the point to grab.
     * @return The value of the point in the indexth dimension, by
     * reference (so that it may be modified).
     * @throw std::out_of_range if accessing out of bounds
     */
    double& operator[](int index);

    private:
    double vals_[Dim];
};


/**
 * Compares two points for equality.
 * @param lhs The left hand side of the comparison
 * @param rhs The right hand side of the comparison
 * @return a boolean indicating whether lhs and rhs are equivalent points
 */
template <int Dim>
bool operator==(const point<Dim>& lhs, const point<Dim>& rhs);

template <int Dim>
bool operator!=(const point<Dim>& lhs, const point<Dim>& rhs);

/**
 * Compares whether a given point is smaller than another point.
 *
 * @param lhs The left hand side of the comparison
 * @param rhs The right hand side of the comparison
 * @return a boolean indicating whether lhs is less than rhs.
 */
template <int Dim>
bool operator<(const point<Dim>& lhs, const point<Dim>& rhs);

template <int Dim>
bool operator>(const point<Dim>& lhs, const point<Dim>& rhs);

template <int Dim>
bool operator<=(const point<Dim>& lhs, const point<Dim>& rhs);

template <int Dim>
bool operator>=(const point<Dim>& lhs, const point<Dim>& rhs);

#include "point.tcc"

#endif
