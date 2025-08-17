#include <iostream>
#include <vector>
#include "Vector.hpp"

int main() 
{
    Vector<int> vec1;
    Vector<int> vec2(2);
    Vector<int> vec3(3, 4);

    vec1.assign(3, 4);
    

    std::cout << vec1 << std::endl;
    std::cout << vec2 << std::endl;
    std::cout << vec3 << std::endl;

    if(vec1 == vec3) {
        std::cout <<"vec1 == vec2\n";
    }

    if(vec1 != vec2) {
        std::cout << "vec1 != vec2\n";
    }

    std::cout << vec1.front() << std::endl;
    std::cout << vec2.back()<< std::endl;
    std::cout << vec3.at(2)<< std::endl;

    return 0;
}