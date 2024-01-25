include(FetchContent)

FetchContent_Declare(
  boost
  GIT_REPOSITORY    https://github.com/boostorg/boost.git # 指定git仓库地址
  GIT_TAG           boost-1.79.0 # 指定版本
  SOURCE_DIR        ${CMAKE_SOURCE_DIR}/third-party/boost   # 源码下载到此目录下
)

FetchContent_MakeAvailable(boost)