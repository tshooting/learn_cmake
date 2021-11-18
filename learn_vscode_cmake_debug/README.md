# 0. 准备工作
教程：https://code.visualstudio.com/docs/cpp/config-linux
mkdir learn_debug
cd learn_debug
mkdir .vscode
mkdir ch1
cd ch1
touch helloworld.cpp
# 1. c_cpp_properties.json 配置文件
## 1.1 生成
1. 先执行Ctrl+Shift+P，显示控制面板，在控制面板处输入“C/C++”，然后选择 C/C++: Edit Configurations (UI)
2. 在.vscode下面生成了c_cpp_properties.json
## 1.2 举例配置
```bash
{
    "configurations": [
        {
            "name": "Linux",
            "includePath": [
                "${workspaceFolder}/**"
            ],
            "defines": [],
            "compilerPath": "/usr/bin/gcc",
            "cStandard": "c11",
            "cppStandard": "c++17",
            "intelliSenseMode": "linux-gcc-x64"
        }
    ],
    "version": 4
}
```
# 2. tasks.json 作用的是编译程序，生成可执行文件
## 2.1 生成
1. Terminal > Configure Default Build Task
2. Choose C/C++: g++ build active file，就会在.vscode下面生成tasks.json
3. 在-g前面添加,"-std=c++17",编译的时候使用c++17标准
## 2.2 介绍每一个参数的用途
1. command 指定要运行的程序
2. args 数组指定将传递给 g++ 的命令行参数
    1. ${file}指的是helloworld.cpp
    2. ${fileDirname} 是要编译的文件所在的目录
    3. ${fileBasenameNoExtension} 和要编译的文件同名
    4. -g 编译，-o 生成的可执行文件的路径；
    5. 如果想编译多个文件成一个可执行文件，那么就将${file}，"${workspaceFolder}/*.cpp" 或者"${fileDirname}/*.cpp"，视情况而定
    6. 在-g前面添加,"-std=c++17",编译的时候使用c++17标准
3. lable：是可以随便修改的，在编译过程中会输出
4. 在group中的"isDefault":true 是使得快捷键生效的（Ctrl+Shift+B）
## 2.3 生成可执行文件
1. 现在是ch1 目录下面有helloworld.cpp ，在learn_debug/.vscode 下面有一个task.json
2. 在terminal 目录下面找到run build task（Ctrl+Shift+B），就会在ch1下面生成同名的可执行文件
3. 可以 cd ch1 && ./helloworld  就可以运行可执行文件了
## 2.4 详细配置
### 2.4.1 如果只是普通了几个文件 想直接编译
``` bash
{
	"version": "2.0.0",
	"tasks": [
		{
			"type": "shell",
			"label": "project_make",
			"command": "/usr/bin/g++",
			"args": [
				"-std=c++17",
				"-g",
				"${file}",
				"-o",
				"${fileDirname}/${fileBasenameNoExtension}"
			],
			"options": {
				// 应该是去到哪个目录下面去执行这个文件
				"cwd": "${fileDirname}"
			},
			"problemMatcher": [
				"$gcc"
			],
			"group": {
				"kind": "build",
				"isDefault": true
			},
			"detail": "compiler: /usr/bin/g++"
		}
	]
}
```
### 2.4.2 如果想要make
```bash
{
	"version": "2.0.0",
	"tasks": [
		{
			"type": "shell",
			"label": "project_make",
			"command": " if [[ ! -e build  ]]; then mkdir build; fi && cd build && cmake .. && make",
			"args": [
			],
			"options": {
				// 应该是去到哪个目录下面去执行这个文件
				"cwd": "${fileDirname}"
			},
			"problemMatcher": [
				"$gcc"
			],
			"group": {
				"kind": "build",
				"isDefault": true
			},
			"detail": "compiler: /usr/bin/g++"
		}
	]
}
```
# 3. launch.json GDB debug用的
## 3.1 生成文件
1. Run > Add Configuration...  
2. choose C++ (GDB/LLDB).
3. Choose g++ build and debug active file.
## 3.2 文件参数作用
1. program : 执行需要debug的文件，在这里就是ch1/helloworld
2. stopAtEntry： 是否停止在入口（mian函数开始的时候）,默认为false；可以改成true，当debug的时候就会停止在入口出，相当于替用户设置了一个在main处的断点
3. preLaunchTask ： 在debug之前进行编译，preLaunchTask的值要和tasks.json中"label"的值要一致。
## 3.3 开始进行debug
1. 快捷见F5，或者run > start debugging 
## 3.4 详细配置
```bash
{
    "version": "0.2.0",
    "configurations": [
        {
            "name": "g++ - Build and debug active file",
            "type": "cppdbg",
            "request": "launch",
            "program": "${fileDirname}/build/hello",
            "args": [],
            "stopAtEntry": true,
            "cwd": "${fileDirname}",
            "environment": [],
            "externalConsole": false,
            "MIMode": "gdb",
            "setupCommands": [
                {
                    "description": "Enable pretty-printing for gdb",
                    "text": "-enable-pretty-printing",
                    "ignoreFailures": true
                }
            ],
            "preLaunchTask": "project_make",
            "miDebuggerPath": "/usr/bin/gdb",
            "logging": {
                "trace": true,
                "traceResponse": true
            }
        }
    ]
}
```
# 4 cmake + debug
## 4.1 CMakeLists.txt 中把debug打开
```cmake
project(hello)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CUDA_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED on)
set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11  -pthread" )

set(src_list helloworld.cpp)
message(STATUS "this is binary dir " ${PROJECT_BINARY_DIR})
message(STATUS "this is source dir " ${PROJECT_SOURCE_DIR})
add_executable(hello ${src_list})
```
# 5 配置gdb
1. 配置pretty printer
```bash
# 使用svn下载的方法示例（前提是已经安装了svn）
mkdir ~/.gdb
cd ~/.gdb
svn co svn://gcc.gnu.org/svn/gcc/trunk/libstdc++-v3/python stlprettyprinter
```
2. 配置.gdbinit
```bash
python
import sys
sys.path.insert(0, 'xxx/.gdb/stlprettyprinter') # 按实际情况修改目录
from libstdcxx.v6.printers import register_libstdcxx_printers
register_libstdcxx_printers (None)
end

```
