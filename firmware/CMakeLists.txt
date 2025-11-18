cmake_minimum_required(VERSION 3.16)

# Tell ESP-IDF where to find extra components (our repo-level components/)
set(EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}/../components")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(ccm_esp32_vision_node)
