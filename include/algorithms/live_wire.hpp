/*

PICCANTE
The hottest HDR imaging library!
http://vcg.isti.cnr.it/piccante

Copyright (C) 2014
Visual Computing Laboratory - ISTI CNR
http://vcg.isti.cnr.it
First author: Francesco Banterle

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.

*/

#ifndef PIC_ALGORITHMS_LIVE_WIRE_HPP
#define PIC_ALGORITHMS_LIVE_WIRE_HPP

#include <functional>
#include <queue>
#include <vector>

#include "image.hpp"
#include "filtering/filter_luminance.hpp"
#include "filtering/filter_gradient.hpp"
#include "filtering/filter_log_2d.hpp"
#include "util/vec.hpp"

namespace pic {

class LiveWire
{
protected:
    Image *img_L, *img_G, *img_fZ;

public:

    LiveWire(Image *img)
    {
        img_L = NULL;
        img_G = NULL;
        img_fZ = NULL;

        set(img);
    }

    /**
     * @brief set
     * @param img
     */
    void set(Image *img)
    {
        if(img_L != NULL) {
            delete img_L;
        }

        if(img_G != NULL) {
            delete img_G;
        }

        if(img_fZ != NULL) {
            delete img_fZ;
        }

        img_L = FilterLuminance::Execute(img, img_L);

        img_G = FilterGradient::Execute(img, img_G);

        img_fZ = FilterLoG2D::Execute(img_L, img_fZ, 1.0f);

    }

    /**
     * @brief Execute
     * @param pS
     * @param pE
     */
    void Execute(Vec<2, float> pS, Vec<2, float> pE)
    {

        auto cmp = [](Vec<3, float> left, Vec<3, float> right) { return (left[2]) > (right[2]);};
        std::priority_queue< Vec<3, float> , std::vector< Vec<3, float> >, decltype(cmp) > list(cmp);

        //list.push(pS);

        while(~list.empty()) {
            Vec<3, float> q = list.top();
            list.pop();
        }



    }

};

} // end namespace pic

#endif /* PIC_ALGORITHMS_LIVE_WIRE_HPP */

