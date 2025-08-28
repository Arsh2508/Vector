#include <iostream>
#include "Vector.hpp"

int main() {
    using Vec = Vector<int>;

    // Test default constructor
    Vec v1;
    std::cout << "v1 empty? " << std::boolalpha << v1.empty() << "\n";

    // Test constructor with size and value
    Vec v2(5, 10);
    std::cout << "v2: " << v2 << "\n";

    // Test push_back
    v2.push_back(20);
    std::cout << "v2 after push_back(20): " << v2 << "\n";

    // Test emplace_back
    v2.emplace_back(30);
    std::cout << "v2 after emplace_back(30): " << v2 << "\n";

    // Test copy constructor
    Vec v3(v2);
    std::cout << "v3 (copy of v2): " << v3 << "\n";

    // Test move constructor
    Vec v4(std::move(v3));
    std::cout << "v4 (moved from v3): " << v4 << "\n";

    // Test copy assignment
    Vec v5;
    v5 = v2;
    std::cout << "v5 (assigned from v2): " << v5 << "\n";

    // Test move assignment
    Vec v6;
    v6 = std::move(v5);
    std::cout << "v6 (move assigned from v5): " << v6 << "\n";

    // Test insert (single value)
    v6.insert(2, 99);
    std::cout << "v6 after insert(2, 99): " << v6 << "\n";

    // Test insert (count, value)
    v6.insert(3, 3, 77);
    std::cout << "v6 after insert(3, 3, 77): " << v6 << "\n";

    // Test emplace at position
    v6.emplace(1, 555);
    std::cout << "v6 after emplace(1, 555): " << v6 << "\n";

    // Test erase single element
    v6.erase(0);
    std::cout << "v6 after erase(0): " << v6 << "\n";

    // Test erase range
    v6.erase(1, 4);
    std::cout << "v6 after erase(1,4): " << v6 << "\n";

    // Test front/back/at/operator[]
    std::cout << "v6 front: " << v6.front() << ", back: " << v6.back() << "\n";
    std::cout << "v6[0]: " << v6[0] << ", at(0): " << v6.at(0) << "\n";

    // Test size/capacity/empty
    std::cout << "v6 size: " << v6.size() << ", capacity: " << v6.capacity() << ", empty? " << v6.empty() << "\n";

    // Test clear
    v6.clear();
    std::cout << "v6 after clear, empty? " << v6.empty() << "\n";

    // Test swap
    Vec a(3, 1);
    Vec b(2, 99);
    std::cout << "Before swap: a=" << a << ", b=" << b << "\n";
    swap(a, b);
    std::cout << "After swap: a=" << a << ", b=" << b << "\n";

    // Test equality/inequality
    Vec x(2, 5), y(2, 5), z(3, 5);
    std::cout << "x == y? " << (x == y) << ", x != z? " << (x != z) << "\n";

    Vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    for(auto it = v.begin(); it != v.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for(auto it = v.cbegin(); it != v.cend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for(auto it = v.rbegin(); it != v.rend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    for(auto it = v.crbegin(); it != v.crend(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;

    return 0;
}
