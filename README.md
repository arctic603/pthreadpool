# pthreadpool
### Posix线程池(支持VS环境)

## 需要自行将项目中的DLL库进行配置到Windows的库lib
### POSIX 线程局限性


​1. POSIX 线程局限性 : 在 Android , Linux , UNIX , MAC 中可以直接使用 POSIX , Windows 不可以直接使用 ;​

​2. Windows 配置 POSIX 线程 : 在 Visual Studio 上使用 POSIX 线程 , 需要引入第三方动态库 ;​


POSIX 线程配置文件下载及目录说明


​1. 下载 : POSIX 线程 Windows 配置文件下载地址 :​

​① 下载地址 1 : ftp://sourceware.org/pub/pthreads-win32/pthreads-w32-2-9-1-release.zip ;​

​② 下载地址 2 : https://jaist.dl.sourceforge.net/project/pthreads4w/pthreads-w32-2-9-1-release.zip ( 推荐 ) ;​

***
​2. Pre-built.2 目录下的相关文件说明 :​

![image](https://user-images.githubusercontent.com/87646355/212582965-dafc9d4c-121e-46c8-b052-e232e6b33c03.png)


​① dll 目录 : 存放动态库目录 , 其中包含 64位 和 32位 两种动态库 ;​
![image](https://user-images.githubusercontent.com/87646355/212582974-9c690758-a960-4c7b-98f3-d6adec6d64ea.png)


​下图是 64 位动态库 :​

![image](https://user-images.githubusercontent.com/87646355/212582794-ebb89ed7-eb2d-43aa-9f32-3ee776764a85.png)


​下图是 32 位 动态库 :​

![image](https://user-images.githubusercontent.com/87646355/212582812-a3534dfc-1c09-4f2b-bada-6e5c62774d07.png)


​② lib 目录 ; 存放静态库的目录 , 该目录也是同时包含 64 位 与 32 位 静态库 ;​

![image](https://user-images.githubusercontent.com/87646355/212582826-f85905bf-248e-4b5f-858c-81ceba4fd302.png)


​③ include 目录 : 存放头文件的目录 ;

![image](https://user-images.githubusercontent.com/87646355/212582837-4bbac680-8b17-460c-8724-65c7773be877.png)




***
***

Windows 动态库与静态库


​动态库与静态库文件说明 :​


​① dll 动态库文件说明 : 在 Pre-built.2\dll\x64 目录下 , 是 64 位操作系统的动态库文件 , Windows 上的动态库是 .dll 文件 , 在 Android , Linux 上的动态库是 .so 文件 ;​
​② lib 静态库文件说明 : 在 Windows 上静态库有两种 , 一种只是单纯的起到引导作用 , 引导如何去链接 dll 动态库 ; 另一种是直接定义了所有的静态函数 ;​



***

POSIX 线程配置 ( 项目配置 )


​1. 拷贝文件 : 将 Pre-built.2 目录下的 include 和 lib 两个目录拷贝到 CMakeLists.txt 所在目录中 ;​

![image](https://user-images.githubusercontent.com/87646355/212582882-c216f005-7193-49c6-b479-087614fcac00.png)



​2. CMake 配置 引入头文件 :​
```CMake
#引入头文件
include_directories("include")
```
​3. CMake 配置 静态库 : 用于引导如何链接动态库和静态库 , 这里配置自动根据当前是 32 位还是 64 位程序 , 确定静态库的配置目录 ;​
```CMake
#配置自动根据当前是 32 位还是 64 位程序 , 确定静态库的配置目录
if(CMAKE_CL_64)
    set(platform x64)
else()
    set(platform x86)
endif()

#配置静态库 , 用于引导如何链接动态库和静态库
link_directories("lib/${platform}")

```
​4. CMake 配置链接库 : 链接生成的 005_Thread 和线程动态库 , 线程动态库是 lib/x64 下的 pthreadVC2.lib ;​
```CMake
#链接生成的 005_Thread 和线程动态库名字  
# 动态库是 lib/x64 下的 pthreadVC2.lib 
target_link_libraries(005_Thread pthreadVC2)

```

​5. CMakeLists.txt 配置宏定义 : 在编译时会出现 " “timespec”:“struct” 类型重定义 " 报错信息 , 需要配置宏定义信息 ;​
```CMake
#处理 “timespec”:“struct” 类型重定义 报错信息
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_STRUCT_TIMESPEC")
```
​6. 完整的 CMakeLists.txt 配置 :​
```CMake
# CMakeList.txt: 005_Thread 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

#引入头文件
include_directories("include")



#配置自动根据当前是 32 位还是 64 位程序 , 确定静态库的配置目录
if(CMAKE_CL_64)
    set(platform x64)
else()
    set(platform x86)
endif()
#配置静态库 , 用于引导如何链接动态库和静态库
link_directories("lib/${platform}")

#处理 “timespec”:“struct” 类型重定义 报错信息
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DHAVE_STRUCT_TIMESPEC")

# 将源代码添加到此项目的可执行文件。
add_executable (pthreadpool "xx.cpp" "xx.h")

#链接生成的 project的工程名 
#   动态库是 lib/x64 下的 pthreadVC2.lib 
target_link_libraries(pthreadpool pthreadVC2)

# TODO: 如有需要，请添加测试并安装目标。
```
***

上面的内容是项目配置内容, 下面是 Windows 系统配置内容 ;









POSIX 线程配置 ( Windows 动态库拷贝 | 注意 32 位库拷贝到 SysWOW64 目录 | 64 位库拷贝到 System32 目录 )

***
```
​拷贝 .dll 动态库到 Windows 系统中 , 如果 Windows 系统中没有对应的动态库 , 运行时会报错 ;​

```


​1. 64 位的 .dll 动态库 : 将 Pre-built.2\dll\x64 目录下的两个 64 位 .dll 动态库 ( pthreadGC2.dll 和 pthreadVC2.dll ) 拷贝到 C:\Windows\System32 目录中 ;​


​① Pre-built.2\dll\x64 下的 动态库 :

![image](https://user-images.githubusercontent.com/87646355/212583284-3d60b62d-abe5-41d5-a3ef-19b9691a9096.png)

​② 拷贝到 C:\Windows\System32后的动态库 :​

![image](https://user-images.githubusercontent.com/87646355/212583312-1ea44fa9-5a6b-4e63-ac51-731ea3126fc8.png)



​2. 32 位的 .dll 动态库 : 将 Pre-built.2\dll\x86 目录下的 5 个 32 位 .dll 动态库 ( pthreadGC2.dll , pthreadGCE2.dll , pthreadVC2.dll , pthreadVCE2.dll , pthreadVSE2.dll ) 拷贝到 C:\Windows\SysWOW64 目录中 ;​

​① 32 位 .dll 动态库 :​

![image](https://user-images.githubusercontent.com/87646355/212583336-f7bb4d62-2f97-412a-8e39-530c7e91b3d2.png)


​② 拷贝 32 位 动态库 : 将 32 位动态库拷贝到 C:\Windows\SysWOW64 目录下 ;​

![image](https://user-images.githubusercontent.com/87646355/212583341-5d2f2154-19b7-460e-8e0d-552d3c45143e.png)





配置代码测试

```C++
​线程使用代码 :​

#include "pthreadpool/pthreadpool.h"
#include <pthread.h>

using namespace std;

int main()
{
  cout << "Hello CMake。" << endl;

  //测试 POSIX 线程方法
  pthread_self();

  return 0;
}
```
