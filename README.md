# SharedPtr and WeakPtr Implementation

## Overview

This project implements `SharedPtr` and `WeakPtr` in C++, smart pointers for managing dynamically allocated objects. `SharedPtr` enables shared ownership, automatically freeing the resource when the last pointer is destroyed. `WeakPtr` provides a non-owning reference to a `SharedPtr`-managed object, allowing safe access without extending its lifetime. These classes replicate the functionality of `std::shared_ptr` and `std::weak_ptr`.

## Build & Run

To build and run the project, follow these steps:

1. **Clone the repository:**
   ```bash
   git clone https://github.com/AniDashyan/Shared_ptr
   cd Shared_ptr
   ```

2. **Build the project**
   ```bash
   cmake -S . -B build
   cmake --build build --config Release
   ```
3. **Run the executable**

   ```bash
   ./build/Shared_ptr
   ```

## Example Output

Below is an example output from running the test cases in `main.cpp`:

```
Test 1 - Initial use count: 1
Test 1 - Dereference: 42
Test 2 - Use count after copy: 2
Test 2 - sp2 value: 42
Test 3 - Use count after assignment: 3
Test 3 - sp3 value: 42
Test 4 - Use count after reset: 2
Test 4 - sp3 new value: 100
Test 5 - Before swap: sp4 = 200, sp3 = 100
Test 5 - After swap: sp4 = 100, sp3 = 200
Test 6 - Array access: sp5[0] = 1.1, sp5[1] = 2.2, sp5[2] = 3.3
Test 7 - Is sp1 unique? No
Test 7 - Is sp1 unique after sp2 reset? Yes
Test 8 - wp1 expired before reset: No
Test 8 - wp1 expired after reset: Yes
Test 9 - Locked sp8 value: 400, Use count: 2
Test 9 - Use count after sp8 destruction: 1
Test 10 - Raw pointer value: 600
```

This output shows the creation, copying, and resetting of `SharedPtr` objects, interaction with `WeakPtr`, and proper resource cleanup.
