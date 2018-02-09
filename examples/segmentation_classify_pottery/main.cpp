/*

PICCANTE Examples
The hottest examples of Piccante:
http://vcg.isti.cnr.it/piccante

Copyright (C) 2014
Visual Computing Laboratory - ISTI CNR
http://vcg.isti.cnr.it
First author: Francesco Banterle

This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3.0 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    See the GNU Lesser General Public License
    ( http://www.gnu.org/licenses/lgpl-3.0.html ) for more details.
*/

//This means that OpenGL acceleration layer is disabled
#define PIC_DISABLE_OPENGL

#include "../common_code/image_qimage_interop.hpp"

#include "piccante.hpp"

#include "data_pottery.hpp"

int main(int argc, char *argv[])
{
    std::string img_str;

    if(argc == 2) {
        img_str = argv[1];
    } else {
        img_str = "../data/input/features/checker_board_photo_2.png";
    }

    printf("Reading an image...");
    pic::Image img;
    ImageRead(img_str, &img, pic::LT_NOR);

    printf("Ok\n");

    if(img.isValid()) {
        pic::RadialBasisFunction rbf;
        rbf.update(colors, 177, 3, var_distance);

        pic::FilterRadialBasisFunction flt_rbf;
        flt_rbf.update(&rbf);

        float *white_pixel = img(82, 126);
        pic::FilterWhiteBalance flt_wb;
        flt_wb.update(white_pixel, img.channels, true);

        pic::Image *img_wb = flt_wb.ProcessP(Single(&img), NULL);

        ImageWrite(img_wb, "../data/output/s_input_wb.png");

        pic::Image *out = flt_rbf.ProcessP(pic::Single(img_wb), NULL);

        out->clamp(0.0f, 1.0f);

        ImageWrite(out, "../data/output/s_radial_basis_function.png");
    }

    return 0;
}
