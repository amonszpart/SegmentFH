#include "segment/SegmentFH.h"

//! \brief Tests the SegmentFH class by providing it graph with one vertical line in the middle.
//! \brief Expects two components as output.
int testSegmentFH()
{
    int W = 10, H = 5;
    fh::SegmentFH<float> segment( W * H );
    // add a vertical edge at W/2
    int split = W / 2;
    for (int y = 0; y != H; ++y )
        for (int x = 0; x != W; ++x )
        {
            if ( x < W-1 )
                segment.addEdge( y * W + x, y * W + x + 1, (x == split ) ? 1.f : 0.1f );
            if ( y < H-1 )
                segment.addEdge( y * W + x, (y+1) * W + x, 0.1f );
        }

    std::vector<std::vector<int> > comps;
    segment.segment( comps, H * W / 4, true );
    for ( int c=  0; c != comps.size(); ++c )
    {
        std::cout << "comps[" << c << "]: ";
        for ( int i = 0; i != comps[c].size(); ++i )
        {
            std::cout << comps[c][i] << ",";
        }
        std::cout << std::endl;
    }

    if ( comps.size() != 2 )
        std::cerr << comps.size() << " components, instead of 2!" << std::endl;
    return !(comps.size() == 2);
}
