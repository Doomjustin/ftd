set(FTD_INCLUDE_DIR "${${PROJECT_NAME}_SOURCE_DIR}/include")
set(FTD_INTERNAL_INCLUDE_DIR "${FTD_INCLUDE_DIR}/ftd")

configure_file(Config.h.in ${PROJECT_SOURCE_DIR}/include/ftd/Config.h)

set(FTD_CONTAINER_SRC
    ${FTD_INTERNAL_INCLUDE_DIR}/container/Heap.h
)

set(FTD_NET_POSIX_SRC
    net/posix/Cast.cpp
    net/posix/Cast.h
    net/posix/Error.cpp
    net/posix/Error.h
    net/posix/PosixSocket.cpp
    net/posix/PosixSocket.h
)

set(FTD_NET_WINDOWS_SRC)

set(FTD_NET_SRC
    ${FTD_INTERNAL_INCLUDE_DIR}/net/Endpoint.h
    ${FTD_INTERNAL_INCLUDE_DIR}/net/Socket.h
    ${FTD_INTERNAL_INCLUDE_DIR}/net/Type.h
    net/Endpoint.cpp
    net/Socket.cpp
    $<$<PLATFORM_ID:Linux>:${FTD_NET_POSIX_SRC}>
    $<$<PLATFORM_ID:Windows>:${FTD_NET_WINDOWS_SRC}>
)

set(FTD_UTILITY_SRC
    ${FTD_INTERNAL_INCLUDE_DIR}/utility/Charset.h
    ${FTD_INTERNAL_INCLUDE_DIR}/utility/EnumOperator.h
    ${FTD_INTERNAL_INCLUDE_DIR}/utility/FunctionWrapper.h
    ${FTD_INTERNAL_INCLUDE_DIR}/utility/Log.h
    ${FTD_INTERNAL_INCLUDE_DIR}/utility/Noncopyable.h
    ${FTD_INTERNAL_INCLUDE_DIR}/utility/Singleton.h
    ${FTD_INTERNAL_INCLUDE_DIR}/utility/String.h
    ${FTD_INTERNAL_INCLUDE_DIR}/utility/ThreadPool.h
    ${FTD_INTERNAL_INCLUDE_DIR}/utility/Timer.h
    ${FTD_INTERNAL_INCLUDE_DIR}/Config.h
    utility/logger/SpdLogger.h
    utility/logger/SpdLogger.cpp
    utility/Log.cpp
    utility/Log.cpp
    utility/ThreadPool.cpp
)

add_library(ftd STATIC 
    ${FTD_CONTAINER_SRC}    
    ${FTD_UTILITY_SRC}
    ${FTD_NET_SRC}
    ${FTD_INTERNAL_INCLUDE_DIR}/Config.h
)

add_library(ftd::ftd ALIAS ftd)

target_include_directories(ftd INTERFACE
    $<BUILD_INTERFACE:${FTD_INCLUDE_DIR}>
    $<INSTALL_INTERFACE:include/> # 允许使用相对路径，这里是相对于安装路径的相对路径
)

target_include_directories(ftd PRIVATE 
    ${FTD_INCLUDE_DIR}
    ${FTD_INTERNAL_INCLUDE_DIR} 
)

set_target_properties(ftd PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    INTERPROCEDURAL_OPTIMIZATION_DEBUG FALSE
    INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO FALSE
    INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
    INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL TRUE
)

target_link_libraries(ftd PRIVATE spdlog::spdlog)

target_link_libraries(ftd PUBLIC
    cpp-compiler-flags
    fmt::fmt
    nlohmann_json::nlohmann_json
)

target_compile_definitions(ftd PUBLIC
   $<$<CONFIG:Debug>:FTD_DEBUG> # 当有类似于DEBUG宏的东西时，很有用
)
