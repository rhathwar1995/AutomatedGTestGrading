#ifndef COMPLEX_H
#define COMPLEX_H

/*! @file */

/*! \breif Fraction object and method definitions
 *
 *  A complex object with real and imaginary parts.
 */
typedef struct {
    double real;
    double im;
} Complex;

/*! Add two complex numbers together
 *  \param a The first summand
 *  \param b The second summand
 */
Complex add ( Complex a, Complex b );

/*! Multiply two complex numbers together
 *  \param a The first term
 *  \param b The second term
 */
Complex multiply ( Complex a, Complex b );

/*! Negate a complex number
*   \param a The complex number
*/
Complex negate ( Complex a );

/*! Magnitude of a complex number
*   \param a The complex number
*/
double magnitude ( Complex a );

#endif