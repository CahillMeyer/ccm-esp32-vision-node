cmake_minimum_required(VERSION 3.10)
project(ccm_vision_sim)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)
include_directories(../components/cv_pipeline)
include_directories(../components/utils)

# Source files (Real Logic + Simulation Wrapper)
add_executable(vision_sim 
    SimMain.cpp
    ../components/cv_pipeline/CvPipeline.cpp
)