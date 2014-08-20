SET(PROJECT_NAME felzenTest)
PROJECT(${PROJECT_NAME})
CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

INCLUDE_DIRECTORIES( include )

SET( H_LIST
    include/segment/segment-image.h
    include/segment/segment-graph.h
    include/segment/convolve.h
    include/segment/disjoint-set.h
    include/segment/filter.h
    include/segment/image.h
    include/segment/imconv.h
    include/segment/imutil.h
    include/segment/misc.h
    include/segment/pnmfile.h
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
