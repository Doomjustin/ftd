include(FetchContent)

FetchContent_Declare(
  catch2
  GIT_REPOSITORY    https://github.com/catchorg/Catch2.git # 指定git仓库地址
  GIT_TAG           v3.5.1 # 指定版本
  SOURCE_DIR        ${CMAKE_SOURCE_DIR}/external/catch2   # 源码下载到此目录下
)

FetchContent_MakeAvailable(catch2)

list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)
include(Catch)
