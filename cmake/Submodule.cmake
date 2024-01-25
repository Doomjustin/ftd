function(update_submodule)
    find_package(Git REQUIRED)
    include(CMakePrintHelpers)
    cmake_print_variables(GIT_VERSION_STRING)

    if (EXISTS ${PROJECT_SOURCE_DIR}/.git)
        message(STATUS "Executing: git submodule update --init --recursive")
        execute_process(COMMAND ${GIT_EXECUTABLE} submodule update --init --recursive
                WORKING_DIRECTORY ${${PROJECT_NAME}_SOURCE_DIR}
                RESULT_VARIABLE RESULT)

        if(NOT RESULT EQUAL "0")
            message(FATAL_ERROR "git submodule update --init --recursive failed with ${RESULT}")
        endif()
    endif ()
endfunction()
