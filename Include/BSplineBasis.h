#ifndef BSplineBasis_H
#define BSplineBasis_H

#include <vector>
#include <algorithm>
#include <KnotVector.h>


namespace cad {

  template<typename T>
  class BSplineBasis
  {
  public:
    BSplineBasis()  { }

    struct Result
    {
      int i;
      std::vector<T> basis;
    };

    //std::size_t operator() (T t, std::vector<T> &basis, const KnotVector<T> &knots) const;

    /**
     * Implementation were put inside class because of strange error due to Result
     */
    Result operator() (T t, const KnotVector<T> &knots) const {
      int m_order = knots.getOrder();

      std::vector<T> coeff(m_order);
      BSplineBasis<T>::Result result;

      result.basis.resize(m_order);
      coeff.resize(m_order);

      // need to find correct i
      result.i = m_order - 1;

      // locate correct index to start from
      for (int k = m_order; k < (knots.size() - m_order); ++k)
      {
        if (t == knots[k])
        {
          result.i = k;
          break;
        }
        if (t > knots[k])
        {
          result.i = k; /*std::max(i, m_order - 1);*/ /*break;*/
        }
      }

      if ((t >= knots[0]) && (t <= knots[knots.size() - 1]))
      {
        result.basis[0] = T(1);
      }
      else
      {
        result.basis[0] = T(0);
      }

      for (int j = 1; j < m_order; ++j)
      {
        // Calculate coefficents
        for (int r = 0; r <= j; ++r)
          coeff[j - r] = (t - knots[result.i - r]) / (knots[result.i - r + j] - knots[result.i - r]);

        // first ledd, special case
        result.basis[j] = coeff[j] * result.basis[j - 1];

        // both elements can be calulated
        for (int r = j - 1; r > 0; --r)
        {
          result.basis[r] = coeff[r] * result.basis[r - 1] + (T(1) - coeff[r + 1]) * result.basis[r];
        }

        // last ledd, special case
        result.basis[0] = (T(1) - coeff[1]) * result.basis[0];
      }

      // returns the index of the first none 0 element
      result.i -= (m_order - 1);

      return result;
    }
  private:

  };



  // template <typename T>
  // std::size_t BSplineBasis<T>::operator() (T t, std::vector<T> &basis, const KnotVector<T> &knots) const
  // {
  //   int m_order = knots.getOrder();

  //   std::vector<T> coeff(m_order);

  //   basis.resize(m_order);
  //   coeff.resize(m_order);

  //   // need to find correct i 
  //   int i = m_order - 1;

  //   // locate correct index to start from
  //   for (int k = m_order; k<(knots.size() - m_order); ++k) {
  //     if (t == knots[k]) { i = k; break;  }
  //     if (t > knots[k]) { i = k; /*std::max(i, m_order - 1);*/ /*break;*/ }
  //   }	

  //   if ((t >= knots[0]) && (t <= knots[knots.size() - 1]))
  //   {
  //     basis[0] = T(1);
  //   }
  //   else
  //   {
  //     basis[0] = T(0);
  //   }

  //   for (int j = 1; j < m_order; ++j)
  //   {
  //     // Calculate coefficents
  //     for (int r = 0; r <= j; ++r)
  //       coeff[j - r] = (t - knots[i - r]) / (knots[i - r + j] - knots[i - r]);

  //     // first ledd, special case
  //     basis[j] = coeff[j] * basis[j - 1];

  //     // both elements can be calulated 
  //     for (int r = j - 1; r>0; --r) {
  //       basis[r] = coeff[r] * basis[r - 1] + (T(1) - coeff[r + 1]) * basis[r];
  //     }

  //     // last ledd, special case
  //     basis[0] = (T(1) - coeff[1])*basis[0];
  //   }

  //   // returns the index of the first none 0 element
  //   return (i - (m_order - 1));
  // }


  /**
   * Could not figure out the compile error regarding cad::BSplineBasis<T>::Result
   * -- move implementation inside class, figure out this later
   */

  // template <typename T>
  // BSplineBasis<T>::Result BSplineBasis<T>::operator() (T t, const KnotVector<T> &knots) const
  // {
  //   int m_order = knots.getOrder();

  //   std::vector<T> coeff(m_order);
  //   BSplineBasis<T>::Result result;

  //   result.basis.resize(m_order);
  //   coeff.resize(m_order);

  //   // need to find correct i 
  //   result.i = m_order - 1;

  //   // locate correct index to start from
  //   for (int k = m_order; k<(knots.size() - m_order); ++k) {
  //     if (t == knots[k]) { result.i = k; break;  }
  //     if (t > knots[k]) { result.i = k; /*std::max(i, m_order - 1);*/ /*break;*/ }
  //   }	

  //   if ((t >= knots[0]) && (t <= knots[knots.size() - 1]))
  //   {
  //     result.basis[0] = T(1);
  //   }
  //   else
  //   {
  //     result.basis[0] = T(0);
  //   }

  //   for (int j = 1; j < m_order; ++j)
  //   {
  //     // Calculate coefficents
  //     for (int r = 0; r <= j; ++r)
  //       coeff[j - r] = (t - knots[result.i - r]) / (knots[result.i - r + j] - knots[result.i - r]);

  //     // first ledd, special case
  //     result.basis[j] = coeff[j] * basis[j - 1];

  //     // both elements can be calulated 
  //     for (int r = j - 1; r>0; --r) {
  //       result.basis[r] = coeff[r] * result.basis[r - 1] + (T(1) - coeff[r + 1]) * result.basis[r];
  //     }

  //     // last ledd, special case
  //     result.basis[0] = (T(1) - coeff[1]) * result.basis[0];
  //   }

  //   // returns the index of the first none 0 element
  //   result.i -= (m_order -1);

  //   return result;
  // }


};

#endif
