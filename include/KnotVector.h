
#ifndef KnotVectorClass_H
#define KnotVectorClass_H

#include <vector>

namespace cad {

  template <typename T>
  class KnotVector
  {
  public:
    KnotVector() : m_values({ T(0), T(1) }), m_order(1) {}
    KnotVector(T start, T stop, unsigned int order);

    T getStart() const { return m_values[0]; }
    T getStop() const { return m_values[m_values.size() - 1]; }

    void insert(T value);
    unsigned int getOrder() const { return m_order; }

    int size() const { return m_values.size(); }

    T operator[] (int i) const { return m_values[i]; }
  private:
    std::vector<T> m_values;
    unsigned int m_order;
  };

  template <typename T>
  KnotVector<T>::KnotVector(T start, T stop, unsigned int order) : m_order(order)
  {
    m_values.insert(m_values.end(), m_order, start);
    m_values.insert(m_values.end(), m_order, stop);
  }

  template <typename T>
  void KnotVector<T>::insert(T value)
  {
    if ((value > getStart()) && (value < getStop()))
    {
      auto it = std::upper_bound(m_values.begin(), m_values.end(), value);

      m_values.insert(it, value);
    }
    else
    {

    }

  }

}


#endif // KnotVectorClass_H
