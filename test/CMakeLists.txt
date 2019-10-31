file(GLOB temp_src_temp ${PROJECT_SOURCE_DIR}/test/*/*test.cpp)

set(BASE_DIR  "{PROJECT_SOURCE_DIR}/base")
include_directories(SYSTEM ${BASE_DIR})


set(GMOCK_DIR  "${PROJECT_SOURCE_DIR}/third_party/gmock")
file(GLOB gmock_srcs  ${GMOCK_DIR}/*.cc)
include_directories(SYSTEM ${GMOCK_DIR})
add_library(gtest EXCLUDE_FROM_ALL ${gmock_srcs})
target_link_libraries(gtest ${CMAKE_THREAD_LIBS_INIT})

foreach(test_src_temp ${temp_src_temp})
    get_filename_component(test_bare_name ${test_src_temp} NAME)
    string(REPLACE ".cpp" "" test_bare_name_without_extension ${test_bare_name})
    string(REPLACE "\"" "" test_name ${test_bare_name_without_extension})

    add_executable(${test_name} ${net_srcs} ${testutils_srcs} ${test_src_temp} )
endforeach(test_src_temp ${temp_src_temp})