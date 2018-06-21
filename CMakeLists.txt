# CMAKE_CURRENT_LIST_DIR 当前文件所在路径
#1.cmake verson，指定cmake版本 
cmake_minimum_required(VERSION 2.8)

PROJECT(messi)
# The version number.
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 0)

ADD_EXECUTABLE(messi
    common/StringUtil.cc
    common/test/StringUtilTest.cc
    common/IpAddr.cc
    common/GlobalConst.cc
    common/test/testMain.cc)
#add_definitions("-Wall -lpthread -g")
#include_directories()
link_directories(/usr/lib64)
target_link_libraries(${PROJECT_NAME} gtest pthread)

#2.project name，指定项目的名称，一般和项目的文件夹名称对应.
# 可以用${PROJECT_NAME}应用

#3. 依赖包
#find_package(catkin REQUIRED)

#4.head file path，头文件目录
INCLUDE_DIRECTORIES(
common
)

#5.source directory，源文件目录
#AUX_SOURCE_DIRECTORY(
#common
#common/test
#)

set(CMAKE_CXX_FLAGS "-fPIC -std=c++11 -g")

#6.set environment variable，设置环境变量
# 编译用到的源文件全部都要放到这里，否则编译能够通过，但是执行的时候会出现各种问题，比如"symbol lookup error xxxxx , undefined symbol"
#SET(MESSI
#${DIR_SRCS}
#)
#SET(LIBRARIES
#)

#7.add executable file，添加要编译的可执行文件

#8.add link library，添加可执行文件所需要的库，比如我们用到了libm.so（命名规则：lib+name+.so），就添加该库的名称
#TARGET_LINK_LIBRARIES(${PROJECT_NAME} m)

# add the install targets
#install (TARGETS Tutorial DESTINATION bin)
#install (FILES "${PROJECT_BINARY_DIR}/TutorialConfig.h"        
#    DESTINATION include)

