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

    Q_UNUSED(argc);
    Q_UNUSED(argv);

    std::vector< pic::Vec<2, float> > point;
    int n = 1000;

    std::mt19937 m;

    for(int i = 0; i< n; i++) {
        point.push_back(pic::randomPoint<2>(&m));
    }

    std::vector<unsigned int> centers;
    std::vector< std::set<unsigned int> *> labels;

    bool bRet = pic::kMeans(point, 3, 1000, centers, labels);

    if(bRet) {
        printf("K-Means ok!\n");

        pic::Image img(512, 512, 3);

        float colors[] = {1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f};
        for(unsigned int i = 0; i < labels.size(); i++) {

            float r = colors[i * 3    ];
            float g = colors[i * 3 + 1];
            float b = colors[i * 3 + 2];

            printf("Label size: %ld\n", labels[i]->size());

            for (std::set<unsigned int>::iterator it=labels[i]->begin(); it!=labels[i]->end(); it++) {
                unsigned int index = *it;
                int x = point[index][0] * 255 + 256;
                int y = point[index][1] * 255 + 256;
                float *data = img(x, y);
                data[0] = r;
                data[1] = g;
                data[2] = b;
            }
        }

        ImageWrite(&img, "../data/output/kmeans.bmp");
    }

    return 0;
}
