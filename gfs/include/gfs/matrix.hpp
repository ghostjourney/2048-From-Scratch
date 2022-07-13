#pragma once

#include <memory>
#include <array>
#include <algorithm>
#include <concepts>
#include <type_traits>
#include <initializer_list>
#include <cmath>

namespace gfs {
template<typename T, int C>
class RVector {
    public:
        using Type = T;

        inline int GetCols() {
            return C;
        }

        RVector(void) {}
        ~RVector(void) {}
        RVector(std::initializer_list<T> l) {
            std::copy(l.begin(), l.end(), mRVector.begin());
        }

        RVector(RVector& rv) {
            std::copy(rv.mRVector.begin(), rv.mRVector.end(), mRVector.begin());
        }

        RVector(RVector&& rv) {
            mRVector = std::move(rv.mRVector);
        }

        RVector& operator=(const RVector& rv) {
            std::copy(rv.mRVector.begin(), rv.mRVector.end(), mRVector.begin());
            return *this;
        }

        RVector& operator=(const RVector&& rv) {
            mRVector = std::move(rv.mRVector);
        }

        T& operator[](int i) {
            return mRVector[i];
        }

        inline T GetX(void) const noexcept {
            return mRVector[0];
        }

        inline T GetY(void) const noexcept {
            return mRVector[1];
        }

        auto begin() {
            return mRVector.begin();
        }

        auto cend() const {
            return mRVector.cend();
        }
    
        auto cbegin() const {
            return mRVector.cbegin();
        }

        auto end () {
            return mRVector.end();
        }

    private:
        std::array<T, C> mRVector;
};

template<typename T, int R, int C>
class Matrix {
    public:

        using Type = T;

        inline int GetRows(void) const {
            return R;
        }

        inline int GetColumns(void) const {
            return C;
        }

        Matrix(void) { }

        ~Matrix(void) { }

        Matrix(std::initializer_list<T> l) {
            std::copy(l.begin(), l.end(), mMatrix.begin());
        }

        Matrix(const Matrix& m) {
            std::copy(m.mMatrix.begin(), m.mMatrix.end(), mMatrix.begin());
        }

        Matrix(const Matrix&& m) {
            mMatrix = std::move(m.mMatrix);
        }

        T* GetData() noexcept {
            return mMatrix.data();
        }

        Matrix& operator=(const Matrix& m) {
            std::copy(m.mMatrix.begin(), m.mMatrix.end(), mMatrix.begin());
            return *this;
        }

        Matrix& operator=(const Matrix&& m) {
            mMatrix = std::move(m.mMatrix);
            return *this;
        }

        
        T& operator[](int i) {
            return mMatrix[i];
        }

        Matrix& operator+=(const Matrix& rhs) {
            const int length = R * C;
            for(int i = 0; i < length; ++i) {
                this[i] += rhs[i];
            }
            return *this;
        }

        inline void Set(const int row, const int col, const T& val) noexcept {
            mMatrix[row * R + col] = val;
        }


        friend Matrix operator+(Matrix lhs, const Matrix& rhs);

        template<typename H, int A, int B, int D>
        friend Matrix<T, A, D> operator*(const Matrix<T, A, B>& lhs, const Matrix<T, B, D>& rhs);
    
        template<typename Type, int N>
        friend Matrix<Type, N, N> CreateIdentity(Type identity);

    private:
        std::array<T,R*C> mMatrix;
};

template<typename T, int R, int C> 
Matrix<T, R, C> operator+(Matrix<T, R, C> lhs, const Matrix<T, R, C>& rhs) {
    const int length = R * C;
    for(int i = 0; i < length; ++i) {
        lhs[i] += rhs[i];
    }
    return lhs;
}

template<typename T, int A, int B, int C>
Matrix<T, A, C> operator*(const Matrix<T, A, B>& lhs, const Matrix<T, B, C>& rhs) {
    Matrix<T, A, B> out;
    for(int i = 0; i < A; ++i ) {
        for(int j = 0; j < B; ++j) {
            out.mMatrix[i][j] = T();
            for(int k = 0; k < C; ++k) {
                out += lhs.mMatrix[i][j] * rhs.mMatrix[j][k];
            }
        }
    }
}

template<typename T, int N>
Matrix<T, N, N> operator*(const Matrix<T, N, N>& lhs, const Matrix<T, N, N>& rhs) {
    return operator*<T, N, N>(lhs, rhs);
}

template<typename T, int A, int B>
Matrix<T, A, B> operator*(const Matrix<T, A, B>& lhs, const Matrix<T, B, A>& rhs) {
    return operator*<T, A, B, B>(lhs, rhs);
}


template<typename Type, int N>
inline Matrix<Type, N, N> CreateIdentity(const Type identity) {
    Matrix<Type, N, N> out;

    for(int i = 0; i < N*N; ++i) {
        out[i] = Type();
    }
    
    for(int i = 0; i < N; ++i) {
        out[i*N+i] = identity;
    }

    return out;
}

inline Matrix<float, 4, 4> CreateIdentity() {
    return CreateIdentity<float, 4>(1.0f);
}

template<typename T>
inline Matrix<T, 4, 4> TranslationMatrix(const T x, const T y, const T z) {
    Matrix<T, 4, 4> out = CreateIdentity<T, 4>(1);
    out[0 * 4 + 3] = x;
    out[1 * 4 + 3] = y;
    out[2 * 4 + 3] = z;
    return out;
}

template<typename T>
inline Matrix<T, 4, 4> ScaleMatrix(const T x, const T y, const T z) {
    Matrix<T, 4, 4> out = CreateIdentity<T, 4>(1);
    out[0 * 4 + 0] = x;
    out[1 * 4 + 1] = y;
    out[2 * 4 + 2] = z;
    return out;
}

template<class T>
concept FloatingPoint = std::is_floating_point_v<T>;

template<class T>
requires FloatingPoint<T>
inline Matrix<T, 4, 4> RotationMatrix(const T x, const T y, const T z) {
    Matrix<T, 4, 4> rotX = {
        1,           0,            0, 0,
        0, std::cos(x), -std::sin(x), 0,
        0, std::sin(x),  std::cos(x), 0,
        0,           0,            0, 1};

    Matrix<T, 4, 4> rotY = {
        std::cos(x),0,   std::sin(x),  0,
        0, 1, -std::sin(x),  0,
        -std::sin(x), 0, std::cos(x), 0,
        0,           0,            0, 1};

    Matrix<T, 4, 4> rotZ = {
        std::cos(z), -std::sin(z), 0, 0,
        std::sin(z),  std::cos(z), 0, 0,
        0, 0, 1, 0,
        0, 0, 0, 1};

    return rotX * rotY * rotZ;
}

template<class T>
requires FloatingPoint<T>
inline Matrix<T, 4, 4> ProjectionMatrix(const T left, const T right, const T bottom, const T top, const T near, const T far) {

    Matrix<T, 4, 4> out = {
        2.0f / (right - left), 0, 0, -(right+left) / (right - left),
        0, 2.0f / (top - bottom), 0, -(top+bottom) / (top - bottom),
        0, 0, -2.0f/ (far - near), -(far + near) / (far - near),
        0, 0, 0, 1
    };
    return out;
}

template<class T>
requires FloatingPoint<T>
inline void Transpose(Matrix<float, 4, 4>& matrix) {
    for(int i = 0; i < 4; ++i) {
        for(int j = 0; j < i; ++j) {
            
            std::swap(matrix[i*4+j], matrix[j*4+i]);
        }
    }
}

}
