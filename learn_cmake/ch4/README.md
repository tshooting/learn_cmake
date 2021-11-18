# ch4
# 4.1 关于add_subdirectory()
## 4.1.1 目录结构
1. 下面是ch4的目录结构(cd ch4 && tree)
.
├── bin
├── CMakeLists.txt (add_subdirectory(subtest) add_subdirectory(subtry))
├── README.md
├── runhello.sh
├── subtest
│   ├── CMakeLists.txt (add_executable(hello1 ${src_list}))
│   └── main.cpp
└── subtry
    ├── CMakeLists.txt (add_executable(hello2 ${src_list}))
    └── main.cpp
 
## 4.1.2 功能
1. add_subdirectory 是向当前工程添加存放源文件的子目录，可以执行中间二进制文件和目标二进制存放的位置
2. add_subdirectory(subtest),外部编译完之后，会在生成build/subtest,里面有中间结果和可执行文件
3. add_subdirectory(subtest bin)，相当于将subtest重命名为 bin，会在生成build/bin,里面有中间结果和可执行文件
4. 如果在subtest 文件夹 下面的 CMakeLists.txt里面 添加上一句话 
   set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
   那么中间结果在build/subtest里面，可执行文件在build/subtest/bin里面
5. 如果只在 ch4/CMakeLists.txt里面添加，set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)，那么子目录里面生成的所有的可执行文件都在build/bin里面，子目录的中间文件在build/子目录里面

## 4.1.3 总结
1. 每一个包含源码的子目录下面都应该有对应的CMakeLists.txt
2. 在相对根目录（在本次测试中 就是ch4）也创建CMakeLists.txt，使用add_subdirectory(子目录名称),将所有的子目录加入
3. 在相对根目录下面的CMakeLists.txt里面，添加 set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin),这样子目录下面所有的可执行文件都将在build/bin里面
## 4.2 CMakeLists.txt的内容
1. ch4/CMakeLists.txt
```cmake
project(ch4)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
add_subdirectory(subtest)
add_subdirectory(subtry)
```
2. ch4/subtest/CMakeLists.txt
```cmake
project(ch4_sub1)
set(src_list main.cpp)
add_executable(hello1 ${src_list})
```
