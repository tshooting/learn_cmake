# ch3
## 3.1 内部编译和外部编译
1. 内部编译：在CMakeLists.txt所在的目录下面，执行cmake && make
2. 外部编译：不在CMakeList.txt所在的目录进行编译，假设在目录下建立build文件夹
    mkdir build && cd build && cmake .. && make
    * cmake .. 中的.. 就是去寻找要编译的CMakeLists.txt ，因为就在build的上层，所以是..
    * 执行了cmake .. 之后就会产生makefile文件
    * make clean 对构建结果进行清理（清理的是make 产生的结果）
    * 所以编译路径是ch3/build，工程路径是 ch3/
## 3.2 project命令
1. project 命令用来定义工程名称
2. 指令大小写无关，但是参数和变量 大小写相关
3. 执行了project(ch3)之后，自动生成了两个变量PROJECT_BINARY_DIR(编译路径)、PROJECT_SOURCE_DIR(工程路径)
## 3.3 set 命令
1. set用来显示的定义变量
2. set(src_list main1.cpp) src_list是变量的名称，main1.cpp是变量的值
## 3.4 message 命令
1. message(STATUS "this is binary dir " ${PROJECT_BINARY_DIR})
    * 这里的status 不能小写(参数区分大小写)，生成的结果是 “-- this is source dir path”
2. message 有三种命令 SEND_ERROR,STATUS,FATAL_ERROR 
## 3.5 add_executable命令
1. add_executable(hello ${src_list})
    * 生成hello可执行文件，使用${}来获取变量值，if语句在判断的时候直接使用变量名
## 3.6 当前文件的CMakeLists.txt
```cmake
project(hello)
set(src_list main.cpp)
message(STATUS "this is binary dir " ${PROJECT_BINARY_DIR})
message(STATUS "this is source dir " ${PROJECT_SOURCE_DIR})
add_executable(hello ${src_list})
```