cmake_minimum_required(VERSION 3.16)

# 1. Configuration: Single Source of Truth for Version
set(PROJECT_VER "0.2.1")

# Tell ESP-IDF where to find extra components
set(EXTRA_COMPONENT_DIRS "${CMAKE_CURRENT_LIST_DIR}/../components")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)

project(ccm_esp32_vision_node)