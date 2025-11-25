cmake_minimum_required(VERSION 3.16)

# Include main project components
set(EXTRA_COMPONENT_DIRS "../../components")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(basic_fps_logger)