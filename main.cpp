#include <iostream>
#include "Vector.hpp"

int main() 
{
    Vector<int> vec(3, 4);

    Vector vec2 = vec;
    
    vec2.push_back(3);
    vec2.push_back(7);

    vec2.pop_back();

    std::cout << vec2;
    return 0;
}