# 1 枚举类型
https://www.runoob.com/w3cnote/cpp-enum-intro.html
## 1.1 定义和说明
1. 用户定义若干枚举常量的集合
```cpp
enum <类型名> {<枚举常亮表>}
enum color_set1 { RED,BLUE,WHITE,BLACK};
enum week {Sun=7, Mon=1, Tue, Wed, Thu, Fri, Sat};
//枚举常量Sun,Mon,Tue,Wed,Thu,Fri,Sat的值分别为7、1、2、3、4、5、6。
enum fruit_set {apple, orange, banana=1, peach, grape}
//枚举常量apple=0,orange=1, banana=1,peach=2,grape=3。
enum letter_set {'a','d','F','s','T'}; //枚举常量不能是字符常量
enum year_set{2000,2001,2002,2003,2004,2005}; //枚举常量不能是整型常量
enum letter_set {a, d, F, s, T};//合法
enum year_set{y2000, y2001, y2002, y2003, y2004, y2005};//合法
```
2. 枚举常量表
枚举常量表——由枚举常量构成。"枚举常量"或称"枚举成员"，是以标识符形式表示的整型量，表示枚举类型的取值。枚举常量表列出枚举类型的所有取值，各枚举常量之间以"，"间隔，且必须各不相同。取值类型与条件表达式相同。
3. 枚举常量取值
枚举常量代表该枚举类型的变量可能取的值，编译系统为每个枚举常量指定一个整数值，默认状态下，这个整数就是所列举元素的序号，序号从0开始。 可以在定义枚举类型时为部分或全部枚举常量指定整数值，在指定值之前的枚举常量仍按默认方式取值，而指定值之后的枚举常量按依次加1的原则取值。 各枚举常量的值可以重复。例如：
## 1.2 枚举变量的使用
```cpp
color_set1 color1, color2;//定义枚举类型之后，就可以定义该枚举类型的变量
enum {Sun,Mon,Tue,Wed,Thu,Fri,Sat} weekday1, weekday2;//类型与变量同时定义（甚至类型名可省）
enum color_set1 {RED, BLUE, WHITE, BLACK} color1, color2;
enum color_set2 { GREEN, RED, YELLOW, WHITE} color3, color4;
color3 = RED;           //将枚举常量值赋给枚举变量
color4 = color3;        //相同类型的枚举变量赋值，color4的值为RED
int i = color3;        //将枚举变量赋给整型变量，i的值为1
int j = GREEN;         //将枚举常量赋给整型变量，j的值为0
if (color3==color4) cout<<"相等"；//比较同类型枚举变量color3，color4是否相等
cout<< color3<WHITE;//输出的是变量color3与WHITE的比较结果，结果为1
cout >> color3;   //非法,枚举变量可以直接输出，但不能直接输入
color1=1; //非法,不能直接将常量赋给枚举变量
color1=color3;  //非法，不同类型的枚举变量之间不能相互赋值
// 枚举变量的输入输出一般都采用switch语句将其转换为字符或字符串；枚举类型数据的其他处理也往往应用switch语句，以保证程序的合法性和可读性。
```

# 2 枚举类(强类型枚举)
https://zhuanlan.zhihu.com/p/96863644
## 2.1 定义和说明
1. 语法形式
```cpp
enum class enum_class_name:底层类型 {枚举常量表}//默认的底层类型是int
enum class Type { General, Light, Medium, Heavy};//所有枚举常量都是int类型
enum class Type: char { General, Light, Medium, Heavy};//所有枚举常量都是字符类型
enum class Category { General=1, Pistol, MachineGun, Cannon};//后面的枚举常量值依次增加
```
2. 枚举类的优势
强作用域，其作用域限制在枚举类中，避免在不同的枚举类里面枚举常量重名的问题，Type::General
3. 类型转换
枚举类对象不可以与整型隐式转换（在枚举类型里面，可以用int i = color3,枚举类就不可以了）
4. 无法比较不同枚举类的对象
## 2.2 使用
1. 枚举类转换为整数，static_cast<int>(枚举类名::枚举常量)
2. 整数转为枚举类
```cpp
enum class Type
{
    NONE = 1,
    APPLE = 2
};
Type type = Type(2);
```
