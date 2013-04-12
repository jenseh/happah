#ifndef POLYNOM_H
#define POLYNOM_H

#include <stdarg.h>
#include <iostream>
#include <vector>

using namespace std;
/**
 * Polynom class represents a general polynom.
 */
template<class T>
class Polynom
{
    vector<T> m_polynom;
public:
    /**
     * @brief Polynom contructor of a polynom with the degree and a list of degree coefficients of type T.
     * @param degree The degree of the polynom.
     */
    Polynom(int degree, ...){
        va_list coefficients;
        va_start(coefficients, degree);
        m_polynom.resize(degree);
        for(int i = 0; i < degree; ++i )
           m_polynom[i] = va_arg(coefficients, T);
        va_end(coefficients);

    }
    /**
     * @brief evaluateAt evaluates the polynom at value x.
     * @param x the value with which the polynom is evaluated.
     * @return the result of the evaluation.
     */
    T evaluateAt(T x){
        T result = 0;
        T factor = 1.0;
        for( typename vector<T>::iterator it = m_polynom.begin(); it != m_polynom.end(); ++it){
            result += factor * *it;
            factor *= x;
        }
        return result;
    }
    /*
    void print(){
        for(size_t i = 0; i < m_polynom.size(); i++){
            cout<<m_polynom[i]<<"*x^"<<i;
            if( i != m_polynom.size()- 1){
                cout<<" + ";
            }
        }
        cout<<endl;
    }
    */
};

#endif // POLYNOM_H
