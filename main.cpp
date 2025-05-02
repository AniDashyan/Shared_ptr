#include <iostream>
#include "SharedPtr.hpp"

int main() {
    // Test 1: Construction and initial use count
    SharedPtr<int> sp1(new int(42));
    std::cout << "Test 1 - Initial use count: " << sp1.use_count() << '\n';
    std::cout << "Test 1 - Dereference: " << *sp1 << '\n';

    // Test 2: Copy constructor and use count
    SharedPtr<int> sp2 = sp1;
    std::cout << "Test 2 - Use count after copy: " << sp1.use_count() << '\n';
    std::cout << "Test 2 - sp2 value: " << *sp2 << '\n';

    // Test 3: Assignment operator and use count
    SharedPtr<int> sp3;
    sp3 = sp2;
    std::cout << "Test 3 - Use count after assignment: " << sp1.use_count() << '\n';
    std::cout << "Test 3 - sp3 value: " << *sp3 << '\n';

    // Test 4: Reset and use count
    sp3.reset(new int(100));
    std::cout << "Test 4 - Use count after reset: " << sp1.use_count() << '\n';
    std::cout << "Test 4 - sp3 new value: " << *sp3 << '\n';

    // Test 5: Swap
    SharedPtr<int> sp4(new int(200));
    std::cout << "Test 5 - Before swap: sp4 = " << *sp4 << ", sp3 = " << *sp3 << '\n';
    sp4.swap(sp3);
    std::cout << "Test 5 - After swap: sp4 = " << *sp4 << ", sp3 = " << *sp3 << '\n';

    // Test 6: Operator[] (array access) with double
    double* arr = new double[3]{1.1, 2.2, 3.3};
    SharedPtr<double> sp5(arr);
    std::cout << "Test 6 - Array access: sp5[0] = " << sp5[0] << ", sp5[1] = " << sp5[1] << ", sp5[2] = " << sp5[2] << '\n';

    // Test 7: Unique check
    std::cout << "Test 7 - Is sp1 unique? " << (sp1.unique() ? "Yes" : "No") << '\n';
    sp2.reset();
    std::cout << "Test 7 - Is sp1 unique after sp2 reset? " << (sp1.unique() ? "Yes" : "No") << '\n';

    // Test 8: WeakPtr functionality
    SharedPtr<int> sp6(new int(300));
    WeakPtr<int> wp1(sp6);
    std::cout << "Test 8 - wp1 expired before reset: " << (wp1.expired() ? "Yes" : "No") << '\n';
    sp6.reset();
    std::cout << "Test 8 - wp1 expired after reset: " << (wp1.expired() ? "Yes" : "No") << '\n';
    
    // Test 9: WeakPtr lock
    SharedPtr<int> sp7(new int(400));
    WeakPtr<int> wp2(sp7);
    {
        SharedPtr<int> sp8 = wp2.lock();
        std::cout << "Test 9 - Locked sp8 value: " << *sp8 << ", Use count: " << sp7.use_count() << '\n';
    }
    std::cout << "Test 9 - Use count after sp8 destruction: " << sp7.use_count() << '\n';

    // Test 10: Get raw pointer
    SharedPtr<int> sp9(new int(600));
    int* raw_ptr = sp9.get();
    std::cout << "Test 10 - Raw pointer value: " << *raw_ptr << '\n';

    return 0;
}