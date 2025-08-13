#include <iostream>
#include <vector>
#include "Vector.hpp"

int main() 
{
    Vector<int> vec1;
    Vector<int> vec2(2);
    Vector<int> vec3(3, 4);

    std::cout << vec1 << std::endl;
    std::cout << vec2 << std::endl;
    std::cout << vec3 << std::endl;

    return 0;
}