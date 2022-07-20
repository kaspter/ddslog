###############################################################################
# CMake build rules for fastlog
###############################################################################

cmake_minimum_required(VERSION 3.6.0)

project(ddslog VERSION 1.0.0 LANGUAGES C CXX)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Werror -pedantic -Wextra -Wno-unknown-pragmas")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic -Wextra -Wno-unknown-pragmas")


# -rdynamic: 将所有符号都加入到符号表中，便于使用dlopen或者backtrace追踪到符号
# -fPIC: 生成位置无关的代码，便于动态链接
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -rdynamic -fPIC")

# -Wno-unused-function: 不要警告未使用函数
# -Wno-builtin-macro-redefined: 不要警告内置宏重定义，用于重定义内置的__FILE__宏
# -Wno-deprecated: 不要警告过时的特性
# -Wno-deprecated-declarations: 不要警告使用带deprecated属性的变量，类型，函数
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-function -Wno-builtin-macro-redefined -Wno-deprecated -Wno-deprecated-declarations")

set(ddslog_SRCS
    src/Log.cpp
    src/OStreamConsumer
    src/StdoutErrConsumer.cpp
    src/StdoutConsumer.cpp
    src/FileConsumer.cpp
    src/ddslog.cpp
)

add_library(ddslog ${ddslog_SRCS})
target_include_directories(ddslog PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(ddslogTest
    example/main.cpp
    example/example.cpp
)

#target_compile_features(ddslogTest PRIVATE cxx_std_17)
target_include_directories(ddslogTest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(ddslogTest ddslog pthread)


add_executable(ddslogTest_c
    example/main.c
)

target_include_directories(ddslogTest_c PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(ddslogTest_c ddslog pthread)


add_executable(ddslogBenchmark
    example/benchmark.cpp
)

#target_compile_features(ddslogTest PRIVATE cxx_std_17)
target_include_directories(ddslogBenchmark PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(ddslogBenchmark ddslog pthread)
