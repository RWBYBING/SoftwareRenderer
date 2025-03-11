#ifndef MATRIX_H
#define MATRIX_H

#include <cmath>
#include <iostream>

#include <core/math/vector.h>

namespace Core
{
    namespace Math
    {
        struct Matrix4x4
        {
        public:
            float operator()(int i, int j);                             // get element Mat[i][j]
            void set(int x, int y, double value);                       // set element Mat[i][j]

            Matrix4x4();
            Matrix4x4(const Matrix4x4& mat);

        };
    }
}

#endif // MATRIX