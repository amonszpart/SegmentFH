#ifndef FH_SEGMENTFH_H
#define FH_SEGMENTFH_H

/*
 * Library author:          Copyright (C) 2006 Pedro Felzenszwalb
 * Original Source code:    http://cs.brown.edu/~pff/segment/
 *
 * SegmentFH.h author:      Aron Monszpart
 * E-mail:                  a.monszpart@cs.ucl.ac.uk
*/

#include <map>
#include <vector>
#include <iostream>                     // using: cout, endl
#include "segment_fh/segment-graph.h"   // contains the logic

namespace fh
{
    //! \brief          C++ wrapper for super-pixelization by [Felzenszwalb and Huttenlocher 2004]
    //! \tparam _Scalar Edge weight data type
    template <typename _Scalar>
    class SegmentFH
    {
        public:
            typedef _Scalar Scalar; //!< \brief Weight data type.

            //! \brief              Constructor taking predefined vertices size.
            //! \param num_vertices How many nodes will there be in the graph.
            SegmentFH( unsigned num_vertices ) : _num_vertices( num_vertices ) {}

            //! \brief              Adds a weighted edge between two nodes. Use to build the graph.
            //! \param node_a       Id of one of the nodes.
            //! \param node_b       Id of one of the other node.
            //! \param node_weight  Edge weight.
            //! \return             EXIT_SUCCESS
            inline int addEdge( unsigned node_a, unsigned node_b, Scalar weight )
            {
                // create
                fh::edge e; e.a = node_a; e.b = node_b; e.w = weight;
                // add
                _edges.push_back( e );
                std::cout << "[" << __func__ << "]: " << "added " << e.a << " - " << e.b << "(" << e.w << ")" << std::endl;
                // return
                return EXIT_SUCCESS;
            }

            //! \brief                  Performs the superpixelization
            //! \tparam _ComponentsT    Output container type for the results. Needs clear(), resize(int), and operator[]. The inner type needs push_back().
            //! \param c                Algorithm parameter, aka. "K". preferred segment size for the \Tau function.
            //! \param verbose          Enables logging. false by default.
            template <class _ComponentsT>
            inline int segment( _ComponentsT &comps, Scalar c = 500, bool verbose = false )
            {
                /// work
                Universe *u = segment_graph( _num_vertices, _edges.size(), _edges.data(), /* K: */ c );

                /// output
                comps.clear();
                comps.resize( u->num_sets() );
                std::map<int,int> comp_ids;
                if ( verbose ) std::cout << "[" << __func__ << "]: " << "num_sets: " << comps.size() << std::endl;

                for ( unsigned v_id = 0; v_id != _num_vertices; ++v_id )
                {
                    int comp_id = u->find(v_id);
                    std::map<int,int>::iterator it = comp_ids.find( comp_id );
                    if ( it == comp_ids.end() )
                        comp_ids[ comp_id ] = comp_ids.size() - 1;
                    std::cout << "adding v" << v_id << " to comp " << u->find(v_id) << "which is the " << comp_ids[comp_id] << "th component" << std::endl;
                    comps[ comp_ids[comp_id] ].push_back( v_id );
                }

                if ( u ) { delete u; u = NULL; }
                return EXIT_SUCCESS;
            } //...SegmentFH::segment()

        protected:
            std::vector<fh::edge> _edges;        //!< \brief Stores incremental edge structure. Filled from #addEdge()
            unsigned              _num_vertices; //!< \brief Stores the number of vertices in the graph
    }; //...class SegmentFH

} //...namespace fh

#endif // FH_SEGMENTFH_H
