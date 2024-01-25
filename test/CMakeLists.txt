list(APPEND CMAKE_MODULE_PATH ${catch2_SOURCE_DIR}/extras)

# 开启CMake的测试框架
enable_testing()
include(Catch)
include(CTest)

function(add_catch2_test TARGET SOURCE)
   add_executable(${TARGET} ${SOURCE})

   target_link_libraries(${TARGET} PRIVATE
       Catch2::Catch2WithMain
       ftd::ftd
   )
   catch_discover_tests(${TARGET})
endfunction()

function(add_ftd_test TARGET SOURCE)
    add_executable(${TARGET} ${SOURCE})

    target_link_libraries(${TARGET} PRIVATE ftd::ftd)
endfunction()

add_catch2_test(test-endpoint test_endpoint.cpp)

add_ftd_test(test-log test_log.cpp)
add_ftd_test(test-threadpool test_threadpool.cpp)
add_ftd_test(test-timer test_timer.cpp)