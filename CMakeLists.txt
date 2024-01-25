cmake_minimum_required(VERSION 3.21)

project(ftd VERSION 1.0 LANGUAGES C CXX)

# 为了vscode的cmake插件提供智能提示
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
    # Release
endif ()

# option(BUILD_SHARED_LIBS "Build using shared libraries" ON)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(Submodule)
include(CppStandard)

# 更新所有的第三方库: git submodule update
update_submodule()

add_subdirectory(third-party/fmt)
add_subdirectory(third-party/spdlog)
add_subdirectory(third-party/json)

add_subdirectory(examples)
add_subdirectory(src)

# 当且仅当这是主项目时，构建测试
if (CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_subdirectory(third-party/catch2)
    add_subdirectory(test)
endif()
