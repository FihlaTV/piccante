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

#ifndef PIC_FILTERING_FILTER_WHITE_BALANCE_HPP
#define PIC_FILTERING_FILTER_WHITE_BALANCE_HPP

#include "filtering/filter.hpp"

namespace pic {

/**
 * @brief The FilterWhiteBalance class
 */
class FilterWhiteBalance: public Filter
{
protected:

    float *white;
    unsigned int nWhite;

    /**
     * @brief ProcessBBox
     * @param dst
     * @param src
     * @param box
     */
    void ProcessBBox(Image *dst, ImageVec src, BBox *box)
    {
        int width    = src[0]->width;
        int channels = src[0]->channels;
        float *data  = src[0]->data;

        int transformChannels = MIN(channels, nWhite);

        for(int j = box->y0; j < box->y1; j++) {
            int c = j * width;

            for(int i = box->x0; i < box->x1; i++) {
                int indOut = c + i;
                int ind = indOut * channels;

                for(int k = 0; k < transformChannels; k++) {
                    dst->data[ind + k] = data[ind + k] / white[k];
                }
            }
        }
    }

public:

    /**
     * @brief FilterWhiteBalance
     * @param type
     */
    FilterWhiteBalance()
    {
        white = NULL;
        nWhite = -1;
    }

    ~FilterWhiteBalance()
    {
        if(white != NULL) {
            delete[] white;
        }

        nWhite = -1;
    }

    /**
     * @brief update
     * @param type
     */
    void update(float *white, unsigned int nWhite)
    {
        this->nWhite = nWhite;
        memcpy(this->white, white, sizeof(float) * nWhite);

        for(unsigned int i = 0; i < nWhite; i++) {
            if(fabsf(this->white[i]) <= 1e-9f) {
                this->white[i] = 1.0f;
            }
        }
    }
};

} // end namespace pic

#endif /* PIC_FILTERING_FILTER_WHITE_BALANCE_HPP */

