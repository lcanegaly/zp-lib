project(zp)

add_subdirectory(${PROJECT_SOURCE_DIR}/orifice)
include_directories(${PROJECT_SOURCE_DIR}/orifice)
link_directories(${PROJECT_SOURCE_DIR}/orifice/lib)

link_libraries(flowplate)

add_library(zp leak.cpp zone.cpp)
