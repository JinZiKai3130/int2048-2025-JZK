/*
Time: 2021-10-21
Test: mul
std Time: 0.01s
Time Limit: 1.00s
*/

#include "int2048.h"

sjtu::int2048 a, b;

int main()
{
    int T;
    std::cin >> T;
    while (T--)
    {
        std::cin >> a >> b;
        // std::cout << "cin ok" << std::endl;
        std::cout << a * b << '\n';
        // std::cout << "cout ok1" << std::endl;
        std::cout << (a *= b) << '\n';
        // std::cout << "cout ok2" << std::endl;
        a *= b;
        // std::cout << "a = " << a << '\n';
        a *= a;
        // std::cout << "a = " << a << '\n';
        a *= b;
        // std::cout << "a = " << a << '\n';
        std::cout << (b *= a) << '\n';
    }
}