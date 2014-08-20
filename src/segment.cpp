/*
Copyright (C) 2006 Pedro Felzenszwalb

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
*/

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include "segment/SegmentFH.h"
#include <segment/image.h>
#include <segment/misc.h>
#include <segment/pnmfile.h>
#include "segment/segment-image.h"

// Test C++ wrapper
extern int testSegmentFH();

int main(int argc, char **argv)
{
    if ( (argc > 1) && !strcmp(argv[1],"test") )
    {
        int err = testSegmentFH();
        if ( !err ) std::cout << "[" << __func__ << "]: " << "C++ wrapper test PASSED" << std::endl;
        else        std::cerr << "[" << __func__ << "]: " << "C++ wrapper test FAILED" << std::endl;
        return err;
    }
    else
    {
        std::cout << "[" << __func__ << "]: " << "Usage: call \t\"" << argv[0] << " test\"\tto test the C++ wrapper" << std::endl;
    }


    if ( argc != 6 )
    {
        fprintf(stderr, "usage: %s sigma k min input(ppm) output(ppm)\n", argv[0]);
        return 1;
    }

    float   sigma    = atof(argv[1]);
    float   k        = atof(argv[2]);
    int     min_size = atoi(argv[3]);

    printf("loading input image.\n");
    fh::image<fh::rgb> *input = fh::loadPPM(argv[4]);

    printf("processing\n");
    int num_ccs;
    fh::image<fh::rgb> *seg = segment_image(input, sigma, k, min_size, &num_ccs);
    fh::savePPM(seg, argv[5]);

    printf("got %d components\n", num_ccs);
    printf("done! uff...thats hard work.\n");

    return 0;
}

