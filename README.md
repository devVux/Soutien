# **C++ Header-Only Library for Enforcing Call-Ordered Pipelines**

A lightweight, header-only C++ library for enforcing and validating the correct execution order of functions in a pipeline. It ensures that functions are only executed if their dependencies (prerequisite functions) have been called, making it ideal for building robust, dependency-aware workflows.

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
#include "function_dependencies.hpp"

int main() {
    auto a = []() { std::cout << "a() executed\n"; };
    auto b = []() { std::cout << "b() executed\n"; };
    auto c = []() { std::cout << "c() executed\n"; };
    auto d = []() { std::cout << "d() executed\n"; };

    auto task_a = FunctionDependencies::createGuardedFunction(a, "a");
    task_a(); // Executes a()
    
    auto task_b = FunctionDependencies::createGuardedFunction(b, "b");
    
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
1. Download or copy the header file `FunctionDependencies.hpp`.
2. Include it in your project:
   ```cpp
   #include "FunctionFependencies.hpp"
   ```
3. Use the `FunctionDependencies` namespace and helper macros to define and enforce your pipelines.

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

- **`is_satisfied()`**:
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

### **Contributing**
Contributions are welcome! If you find a bug or have a feature request, please open an issue or submit a pull request.

---

### **License**
This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.
