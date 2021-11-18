#include <iostream>
#include <vector>
#include <string>
using namespace std;
int main()
{
    string a = "jfdiaoja";
    cout << a << endl;
    int msgs[2] = {1, 2};
    for (auto msg : msgs)
    {
        cout << msg << endl;
    }
    return 0;
}