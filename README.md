# **`SoutienFlow`: C++ Header-Only Library for Enforcing Call-Ordered Pipelines**

A lightweight, header-only C++17 library for enforcing and validating the correct execution order of functions in a pipeline. It ensures that functions are only executed if their dependencies (prerequisite functions) have been called, making it ideal for building robust, dependency-aware workflows.


The name `SoutienFlow` (from French "SoutienFlow", meaning "support") reflects the library's purpose of supporting and enabling robust, dependency-aware workflows.

---

## **Features**
- **Dependency Validation**: Ensures functions are only executed if their dependencies have been called.
- **Header-Only**: Easy to integrate into any C++ project—just include the header file.
- **Flexible Pipelines**: Supports arbitrary dependency chains and complex workflows.
- **Clear Error Reporting**: Provides informative messages when dependencies are not met.
- **Lightweight**: No external dependencies—pure C++17.

---

### **Example Usage**
```cpp
#include "SoutienFlow.h"

int main() {
    auto a = []() { std::cout << "a() executed\n"; };
    auto b = []() { std::cout << "b() executed\n"; };
    auto c = []() { std::cout << "c() executed\n"; };
    auto d = []() { std::cout << "d() executed\n"; };

    auto task_a = SoutienFlow::createGuardedFunction(a, "a");
    task_a(); // Executes a()
    
    auto task_b = SoutienFlow::createGuardedFunction(b, "b");
    
    auto task_c = GUARDED_FUNCTION(c, task_a, task_b); // Requires a() and b()
    task_c(); // Fails because b() has not been executed
    
    auto task_d = GUARDED_FUNCTION(d, task_c); // Requires c()
    task_d(); // Fails because c() was not executed
}
```

**Output**:
```
a() executed
Dependency `b` not met. Blocking `c`
Dependency `c` not met. Blocking `d`
```

---

### **Installation**
1. Download or copy the header file `SoutienFlow.hpp`.
2. Include it in your project:
   ```cpp
   #include "SoutienFlow.h"
   ```
3. Use the `SoutienFlow` namespace and helper macros to define and enforce your pipelines.

---

### **API Reference**
#### **Core Components**
- **`GuardedFunction<Func, Requirements...>`**:
  - Wraps a function and its dependencies.
  - Ensures the function is only executed if all dependencies are satisfied.

- **`createGuardedFunction(Func func, const char* name, Dependencies... deps)`**:
  - Creates a `GuardedFunction` with the given function, name, and dependencies.

- **`GUARDED_FUNCTION(func, ...)`**:
  - A macro for creating a `GuardedFunction` with automatic name inference.

#### **Methods**
- **`operator()`**:
  - Executes the function if all dependencies are satisfied.
  - Prints an error message if any dependency is not met.

- **`satisfied()`**:
  - Returns `true` if the function has been executed, `false` otherwise.

- **`name()`**:
  - Returns the name of the function.

---

### **Why Use This Library?**
- **Enforce Correct Execution Order**: Prevent bugs caused by out-of-order execution.
- **Declarative Pipelines**: Clearly define dependencies between functions.
- **Debugging Made Easy**: Get clear error messages when dependencies are not met.
- **No Overhead**: Header-only design ensures minimal impact on your project.

---

### **Possible Improvements**
Here’s a concise list of **possible improvements** for your library:

### **1. Shared Dependency States**
- **Problem**: Currently, each `GuardedFunction` stores its dependencies by value, so changes to one instance don’t affect others.
- **Improvement**: Use `std::shared_ptr` or `std::reference_wrapper` to share dependency states across instances.

### **2. Support for Return Values**
- **Problem**: The library only supports `void` functions.
- **Improvement**: Modify `operator()` to return a `std::optional` or propagate results from dependencies to dependent functions.

### **3. Support for Non-Void Dependencies**
- **Problem**: Dependencies cannot pass data to dependent functions.
- **Improvement**: Allow dependencies to return values that are passed as arguments to dependent functions.

### **4. Cycle Detection**
- **Problem**: Cyclic dependencies (e.g., `A` requires `B`, and `B` requires `A`) can cause infinite loops or undefined behavior.
- **Improvement**: Implement cycle detection by tracking the call stack during execution and throwing an error if a cycle is detected.

### **5. Recursive Error Reporting**
- **Problem**: Errors only report direct unmet dependencies, not the root cause (e.g., `A` fails because `B` fails because `C` fails).
- **Improvement**: Recursively check and report the full chain of unmet dependencies.

### **6. Custom Error Handling**
- **Problem**: Error messages are hardcoded to `std::cout`.
- **Improvement**: Allow users to inject a custom logger or error handler (e.g., a lambda or function pointer).

### **7. Thread Safety**
- **Problem**: The library is not thread-safe.
- **Improvement**: Add support for concurrent execution by using mutexes or atomic variables to protect shared state.

### **8. Timeout Mechanism**
- **Problem**: If a dependency is never satisfied, the function will never execute.
- **Improvement**: Add a timeout mechanism to cancel execution if dependencies are not met within a specified time.

### **9. Dependency Graphs**
- **Problem**: The library only supports linear dependencies.
- **Improvement**: Extend the library to support dependency graphs, where a function can have multiple independent dependency chains.

### **10. Compile-Time Checks**
- **Problem**: Dependency errors are only detected at runtime.
- **Improvement**: Use `constexpr` or template metaprogramming to detect invalid dependencies at compile time.

---

### **Contributing**
Contributions are welcome! If you find a bug or have a feature request, please open an issue or submit a pull request.

---

### **License**
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
