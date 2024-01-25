set(FTD_INCLUDE_DIR "${${PROJECT_NAME}_SOURCE_DIR}/include")
set(FTD_INTERNAL_INCLUDE_DIR "${FTD_INCLUDE_DIR}/ftd")

configure_file(Config.h.in ${PROJECT_SOURCE_DIR}/include/ftd/Config.h)

add_library(ftd INTERFACE 
    ${FTD_INTERNAL_INCLUDE_DIR}/utility/Charset.h
    ${FTD_INTERNAL_INCLUDE_DIR}/utility/Noncopyable.h
    ${FTD_INTERNAL_INCLUDE_DIR}/utility/Singleton.h
    ${FTD_INTERNAL_INCLUDE_DIR}/utility/String.h
    ${FTD_INTERNAL_INCLUDE_DIR}/Config.h
)

add_library(ftd::ftd ALIAS ftd)

target_include_directories(ftd INTERFACE
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include/>
    $<INSTALL_INTERFACE:include/> # 允许使用相对路径，这里是相对于安装路径的相对路径
)

# target_include_directories(ftd INTERFACE ${FTD_INTERNAL_INCLUDE_DIR})

set_target_properties(ftd PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
    CXX_EXTENSIONS OFF
    INTERPROCEDURAL_OPTIMIZATION_DEBUG FALSE
    INTERPROCEDURAL_OPTIMIZATION_RELWITHDEBINFO FALSE
    INTERPROCEDURAL_OPTIMIZATION_RELEASE TRUE
    INTERPROCEDURAL_OPTIMIZATION_MINSIZEREL TRUE
)

target_link_libraries(ftd INTERFACE
    cpp-compiler-flags
    fmt::fmt
    spdlog::spdlog
    nlohmann_json::nlohmann_json
)

target_compile_definitions(ftd INTERFACE
   $<$<CONFIG:Debug>:FTD_DEBUG> # 当有类似于DEBUG宏的东西时，很有用
)
