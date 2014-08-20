SET(PROJECT_NAME felzenTest)
PROJECT(${PROJECT_NAME})
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

INCLUDE_DIRECTORIES( include )

SET( H_LIST
    include/segment_fh/segment-image.h
    include/segment_fh/segment-graph.h
    include/segment_fh/convolve.h
    include/segment_fh/disjoint-set.h
    include/segment_fh/filter.h
    include/segment_fh/image.h
    include/segment_fh/imconv.h
    include/segment_fh/imutil.h
    include/segment_fh/misc.h
    include/segment_fh/pnmfile.h
    include/segment_fh/wrapper/segmentFH.hpp
)
SET( SRC_LIST
    src/segment.cpp
    src/testSegmentFH.cpp
)
ADD_EXECUTABLE( ${PROJECT_NAME}
	${SRC_LIST}
    ${H_LIST}
)

#TARGET_LINK_LIBRARIES( ${PROJECT_NAME} ${PROJECT_LIBS} )
