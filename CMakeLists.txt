# CMakeList.txt: pthreadpool 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。

cmake_minimum_required (VERSION 3.8)

# TODO: 如有需要，请添加测试并安装目标。
# 引入头文件
include_directories("include")

project("pthreadpool")

# 配置自动根据当前是32位还是64位，确定静态库的配置目录
if(CMAKE_CL_64)
	set(platfrom x64)
else()
	set(platform x86)
endif()

link_directories("lib/${platform}")


#CMakeLists.txt 配置宏定义 : 在编译时会出现 " “timespec”:“struct” 类型重定义 " 报错信息 , 需要配置宏定义信息 ;
#处理 “timespec”:“struct” 类型重定义 报错信息
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_STRUCT_TIMESPEC")

# 将源代码添加到此项目的可执行文件。
add_executable (pthreadpool "threadPool/pthreadpool.cpp" "threadPool/pthreadpool.h" "taskqueue/taskqueue.h" "taskqueue/taskqueue.cpp" "test.cpp")

#  CMake 配置链接库 : 链接生成的 005_Thread 和线程动态库 , 线程动态库是 lib/x64 下的 pthreadVC2.lib ;
#链接生成的 005_Thread 和线程动态库名字  
#	动态库是 lib/x64 下的 pthreadVC2.lib 
target_link_libraries(pthreadpool pthreadVC2)