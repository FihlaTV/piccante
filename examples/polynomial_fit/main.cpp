/*

PICCANTE
The hottest HDR imaging library!
http://piccantelib.net

Copyright (C) 2014-2016
Visual Computing Laboratory - ISTI CNR
http://vcg.isti.cnr.it
First author: Francesco Banterle

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.

*/

#include <QCoreApplication>

//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "piccante.hpp"

int main(int argc, char *argv[])
{
    Q_UNUSED(argc);
    Q_UNUSED(argv);

    std::vector<float> x, y;

    for(int i=0;i<10;i++) {
        x.push_back(i);
        y.push_back(i * i);
    }

    std::vector< float > tmp = pic::polynomialFit(x, y, 2);

    for(int i=0;i<3;i++) {
        printf("%f ", tmp[i]);
    }

    float y_2 = pic::polynomialVal(tmp, 4.0f);
    printf("\n %f\n", y_2);

    return 0;
}
