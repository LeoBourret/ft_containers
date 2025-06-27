# 📦 ft_containers: Reimplementation of C++ STL Containers

![Language: C++](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)
![Standard: C++98](https://img.shields.io/badge/Standard-C%2B%2B98-orange.svg)
![School: 42 Paris](https://img.shields.io/badge/School-42_Paris-orange.svg)
![Grade: 125/100](https://img.shields.io/badge/Grade-125/100-brightgreen.svg)

## ✨ Overview

`ft_containers` is a highly challenging core project from 42 Paris, focused on **reimplementing key containers from the C++ Standard Template Library (STL)**. The objective was to build custom versions of `vector`, `map`, `stack`, and (as a bonus) `set` from scratch. The implementations strictly adhere to their original interface, behavior, and complexity requirements, primarily based on the C++98 standard, without using any part of the original STL in the final custom containers.

This project provided an invaluable deep dive into C++ templating, generic programming, iterators, complex data structures (like Red-Black Trees), memory allocation strategies, and the underlying mechanisms of common C++ containers. It rigorously tested my understanding of Object-Oriented Programming (OOP) principles and low-level resource management in C++.

## 🌟 Implemented Containers & Features

### **1. `ft::vector`**

*   **Dynamic Array:** A sequence container that can change its size dynamically.
*   **Contiguous Storage:** Elements are stored contiguously, allowing efficient random access.
*   **Iterator Support:** Fully implemented random access iterators, enabling standard algorithm usage.
*   **Memory Management:** Custom memory allocation and reallocation logic to manage growth and shrinkage.

### **2. `ft::map`**

*   **Associative Array (Key-Value Pairs):** Stores elements formed by a combination of a key value and a mapped value.
*   **Sorted by Keys:** Elements are ordered by their keys using a strict weak ordering. Implemented using a **Red-Black Tree** to ensure `O(log n)` insertion, deletion, and search times.
*   **Bidirectional Iterators:** Support for traversing elements in both directions.
*   **Balanced Tree Implementation:** Demonstrates knowledge of complex, self-balancing tree-based data structures.

### **3. `ft::stack`**

*   **Container Adaptor:** Provides a LIFO (Last-In, First-Out) stack functionality, built on top of an underlying container (e.g., `ft::vector` or `std::deque`).
*   **Basic Stack Operations:** Implements `push`, `pop`, `top`, `empty`, and `size`.

### **4. `ft::set` (Bonus Part)**

*   **Sorted Unique Elements:** An associative container that stores unique elements in a specific order.
*   **Red-Black Tree Implementation:** Mandatory to implement using a **Red-Black Tree**, ensuring efficient `O(log n)` complexity for insertions, deletions, and lookups.
*   **Bidirectional Iterators:** Fully functional bidirectional iterators for element traversal.
*   **Demonstrates Mastery:** Successfully tackling this bonus confirms an advanced understanding of self-balancing binary search trees and complex algorithms.

### **General Implementations & Core Learnings**

*   **Generic Programming:** Extensive use of C++ templates to create generic containers that work with any data type.
*   **Iterators System:** Design and implementation of custom iterator classes for each container, including `std::iterators_traits`, `std::reverse_iterator`, comparison, arithmetic, and dereferencing operations.
*   **Metaprogramming Concepts:** Introduction to concepts like `std::enable_if` and `SFINAE` (Substitution Failure Is Not An Error).
*   **Type Traits:** Implementation of `std::is_integral` for type checking.
*   **Utility Functions:** Implementation of `std::equal`, `std::lexicographical_compare`, `std::pair`, and `std::make_pair`.
*   **Custom Allocator Support:** Ability to use `std::allocator` for memory management within the containers.
*   **Performance & Complexity:** Rigorous focus on respecting the original STL complexity requirements (e.g., `O(1)` for `vector` random access, `O(log n)` for tree operations).
*   **Rigorous Testing:** Development of comprehensive test suites to ensure correctness and strict adherence to STL behavior and performance.

## 🛠️ Technologies Used

*   **Language:** C++ (primarily C++98 standard)
*   **Concepts:** Object-Oriented Programming (OOP), Generic Programming (Templates), Advanced Data Structures (**Red-Black Trees**), Iterators, Memory Management (Allocators), Algorithm Complexity Analysis, Metaprogramming (SFINAE).

## 🚀 How to Use & Compile

This repository contains only the header files (`.hpp`) for the custom containers, which are designed to be directly included in your C++ projects.

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/LeoBourret/ft_containers.git
    cd ft_containers
    ```
2.  **Include in your C++ project:**
    To use the `ft::` containers, simply include their respective header files in your `.cpp` source files.
    For example, to use `ft::vector` and `ft::map`:
    ```cpp
    #include "containers/vector.hpp"
    #include "containers/map.hpp"

    // Your main code using ft::vector and ft::map
    ```
3.  **Compile your C++ program:**
    You will need a C++ compiler (like g++). Ensure you specify the C++98 standard, as the containers are implemented adhering to it.
    ```bash
    g++ -Wall -Wextra -Werror -std=c++98 your_program.cpp -o your_program
    # Example for a test executable that uses your ft:: containers
    # g++ -Wall -Wextra -Werror -std=c++98 main_test.cpp -I./containers -o test_ft_containers
    ```
    (Note: Adjust `main_test.cpp` and `-I./containers` according to your specific test file and structure.)

## 🎓 Learning Outcomes

This project significantly enhanced my expertise in:

*   **Advanced C++ Programming:** Mastery of templates, inheritance, polymorphism, operator overloading, and meta-programming concepts.
*   **Core Data Structures & Algorithms:** In-depth understanding and practical implementation of `vector`, `map` (Red-Black Trees), `stack`, and `set` (Red-Black Trees).
*   **Generic Programming:** Ability to write highly reusable and type-agnostic code conforming to STL principles.
*   **Low-Level Memory Management:** Custom allocation, deallocation, and exception safety in C++.
*   **API Design & Conformity:** Replicating complex standard library interfaces precisely, including iterators and type traits.
*   **Performance Optimization:** Understanding and achieving specific algorithmic complexities.
*   **Test-Driven Development:** Developing robust test suites for complex libraries.

---
