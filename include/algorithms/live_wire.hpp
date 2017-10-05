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
    Image *img_L, *img_G, *fZ, *g, *e, *pointers;

    /**
     * @brief getCost
     * @param x
     * @param y
     * @return
     */
    float getCost(Vec<2, int> &p, Vec<2, int> &q)
    {
        float out;
        float *tmp;

        //fZ cost
        tmp = (*fZ)(q[0], q[1]);
        out  = 0.43f * tmp[0];

        tmp = (*img_G)(q[0], q[1]);

        //fG cost
        float dist_qp = sqrtf(q.distanceSq(p));
        out += 0.14f * tmp[2] / dist_qp;

        //fD cost

        return out;
    }

    /**
     * @brief release
     */
    void release()
    {
        if(img_L != NULL) {
            delete img_L;
        }

        if(img_G != NULL) {
            delete img_G;
        }

        if(fZ != NULL) {
            delete fZ;
        }

        if(g != NULL) {
            delete g;
        }

        if(e != NULL) {
            delete e;
        }
    }

public:

    LiveWire(Image *img)
    {
        img_L = NULL;
        img_G = NULL;
        fZ = NULL;
        g = NULL;
        e = NULL;
        pointers = NULL;

        set(img);
    }

    ~LiveWire()
    {
        release();
    }

    /**
     * @brief set
     * @param img
     */
    void set(Image *img)
    {
        release();

        img_L = FilterLuminance::Execute(img, img_L);

        img_G = FilterGradient::Execute(img, img_G);

        //compute fZ
        fZ = FilterLoG2D::Execute(img_L, fZ, 1.0f);

        Image tmp(img_L->width, img_L->height, 1);
        tmp = 1.0f;
        *fZ = tmp - *fZ;

        //aux buffers
        g = img_L->allocateSimilarOne();
        e = img_L->allocateSimilarOne();

        pointers = new Image(img_L->width, img_L->height, 2);
    }

    /**
     * @brief execute
     * @param pS
     * @param pE
     */
    void execute(Vec<2, int> pS, Vec<2, int> pE, std::vector< Vec<2, int> > &out)
    {
        float *tmp;

        std::vector< Vec<2, int> > list;

        *g = FLT_MAX;
        e->setZero();

        int nx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
        int ny[] = {1, 1, 1, 0, 0, -1, -1, -1};

        tmp = (*g)(pS[0], pS[1]);
        tmp[0] = 0.0f;

        list.push_back(pS);

        while(!list.empty()) {
            //get the best
            std::vector< Vec<2, int> >::iterator index;
            Vec<2, int> q;

            float g_q = FLT_MAX;
            for(auto it = list.begin(); it != list.end(); it++) {
                float g_it = (*g)((*it)[0], (*it)[1])[0];
                if(g_it < g_q) {
                    g_q = g_it;
                    index = it;
                }
            }

            q[0] = (*index)[0];
            q[1] = (*index)[1];

            list.erase(index);

            //update
            tmp = (*e)(q[0], q[1]);
            tmp[0] = 1.0f;

            for(int i = 0; i < 8; i++) {
                Vec<2, int> r = q;
                r[0] += nx[i];
                r[1] += ny[i];

                if(r[0] > -1 && r[0] < img_L->width &&
                   r[1] > -1 && r[1] < img_L->height) {
                    tmp = (*e)(r[0], r[1]);
                    if(tmp[0] < 0.5f) {
                        float g_tmp = g_q + getCost(q, r);

                        //check list
                        bool bFlag = false;
                        for(auto it = list.begin(); it != list.end(); it++) {
                            if((*it)[0] == r[0] && (*it)[1] == r[1]) {
                                index = it;
                                bFlag = true;
                            }
                        }

                        if(bFlag && g_tmp < g_q) {
                            list.erase(index);
                        }

                        if(!bFlag) {
                            tmp = (*g)(r[0], r[1]);
                            tmp[0] = g_tmp;

                            tmp = (*pointers)(r[0], r[1]);
                            tmp[0] = float(q[0]);
                            tmp[1] = float(q[1]);
                            list.push_back(r);
                        }

                    }

                }

            }

        }

        //tracking
        out.clear();

        out.push_back(pE);
        Vec<2, int> m = pE;

        printf("tracking");
        while(true) {
            if(m[0] == pS[0] && m[1] == pS[1]) {
                break;
            }

            tmp = (*pointers)(m[0], m[1]);
            Vec<2, int> t(tmp[0], tmp[1]);

            out.push_back(t);
            m = t;
        }

    }
};

} // end namespace pic

#endif /* PIC_ALGORITHMS_LIVE_WIRE_HPP */

