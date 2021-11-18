#include <iostream>
using namespace std;
enum class Type
{
    NONE = 1,
    APPLE = 2
};
int main()
{
    Type type = Type(2);
    if (type == Type::NONE)
    {
        cout << static_cast<int>(type) << endl;
    }
    else
    {
        cout << "not equal" << endl;
    }
    return 0;
}