#ifndef CMN_MATRIX_HEADER
#define CMN_MATRIX_HEADER

#include <vector>
#include <stdexcept>


namespace CmnClass
{

  // Modified from:
  //  http://www.parashift.com/c%2B%2B-faq-lite/freestore-mgmt.html#faq-16.17
  template<typename T>
  class Matrix {
  public:
    Matrix(unsigned nrows, unsigned ncols)
      throw(std::invalid_argument);

    // Access methods to get the (i,j) element:
    T& operator() (unsigned i, unsigned j)
      throw(std::invalid_argument);

    const T& operator() (unsigned i, unsigned j) const
      throw(std::invalid_argument);

    std::vector<T>& operator[] (unsigned int i)
      throw(std::invalid_argument);



    unsigned nrows() const;  // #rows in this matrix
    unsigned ncols() const;  // #columns in this matrix

  private:
    std::vector<std::vector<T> > data_;
  };



  template<typename T>
  Matrix<T>::Matrix(unsigned nrows, unsigned ncols)
    throw(std::invalid_argument)  : data_ (nrows)
  {
    if (nrows == 0 || ncols == 0)
      throw std::invalid_argument("matrix :: error with row and/or col.");

    for (unsigned i = 0; i < nrows; ++i)
      data_[i].resize(ncols);
  }


  template<typename T>
  inline unsigned Matrix<T>::nrows() const
  {
    return data_.size();
  }

  template<typename T>
  inline unsigned Matrix<T>::ncols() const
  {
    return data_[0].size();
  }


  template<typename T>
  inline T& Matrix<T>::operator() (unsigned row, unsigned col)
    throw(std::invalid_argument)
  {
    if (row >= nrows() || col >= ncols())
      throw std::invalid_argument("matrix :: error with row and/or col.");
    return data_[row][col];
  }

  template<typename T>
  inline const T& Matrix<T>::operator() (unsigned row, unsigned col) const
    throw(std::invalid_argument)
  {
    if (row >= nrows() || col >= ncols())
      throw std::invalid_argument("matrix :: error with row and/or col.");
    return data_[row][col];
  }


  template<typename T>
  inline std::vector<T>& Matrix<T>::operator[] (unsigned int row)
    throw(std::invalid_argument)
  {
    if (row >= nrows()) {
      throw std::invalid_argument("matrix :: error with row.");
    }
    return data_[row];
  }
}


#endif
