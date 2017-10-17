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

int main(int argc, char *argv[])
{
    std::string img_str;

    if(argc == 2) {
        img_str = argv[1];
    } else {
        img_str = "../data/input/features/checker_board.png";
    }

    pic::Image img;
    ImageRead(img_str, &img, pic::LT_NOR);

    printf("Ok\n");

    printf("Is the image valid? ");
    if(img.isValid()) {
        printf("OK\n");

        //compute the luminance images
        pic::Image *L = pic::FilterLuminance::Execute(&img, NULL, pic::LT_CIE_LUMINANCE);

        //get corners
        printf("Extracting corners...\n");
        pic::HarrisCornerDetector hcd(2.5f, 5);
        std::vector< Eigen::Vector3f > corners_from_img;
        hcd.execute(L, &corners_from_img);

        pic::GeneralCornerDetector::sortCorners(&corners_from_img);

        printf("[");
        for(unsigned int i = 0; i < corners_from_img.size(); i++) {
            printf("%3.5f %3.5f; ",
                   corners_from_img[i][0],
                   corners_from_img[i][1]);
        }
        printf("]");

        /*
        //compute luminance images
        pic::Image *L_flt = pic::FilterGaussian2D::Execute(L, NULL, 2.5f);

        //compute ORB descriptors for each corner and image
        printf("Computing ORB descriptors...\n");

        pic::ORBDescriptor b_desc(31, 512);

        std::vector< unsigned int *> descs;
        for(unsigned int i=0; i<corners_from_img.size(); i++) {
            int x = corners_from_img[i][0];
            int y = corners_from_img[i][1];
            descs.push_back(b_desc.get(L_flt, x, y));
        }

        */

    } else {
        printf("No there is at least an invalid file!\n");
    }

    return 0;
}
