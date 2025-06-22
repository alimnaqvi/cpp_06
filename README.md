# C++ Module 06: C++ Casts

[![C++ Programming](https://img.shields.io/badge/Language-C%2B%2B-blue.svg)](https://en.wikipedia.org/wiki/C%2B%2B)
[![Makefile](https://img.shields.io/badge/Build-Make-brightgreen.svg)](https://www.gnu.org/software/make/)

This project is part of the C++ modules at 42 School. It provides a deep dive into C++'s type casting mechanisms. Through a series of exercises, we explore the practical applications and differences between `static_cast`, `dynamic_cast`, and `reinterpret_cast`, reinforcing the importance of choosing the correct cast for a given situation.

## Core Concepts Covered

*   Understand and apply different C++ casts:
    *   **`static_cast`**: For safe, compile-time type conversions (e.g., numeric types).
    *   **`reinterpret_cast`**: For low-level, unsafe reinterpretation of bit patterns (e.g., pointer-to-integer).
    *   **`dynamic_cast`**: For safe, run-time downcasting of polymorphic types.
*   Handle C++ literals and perform string-to-numeric conversions using `std::sto*` functions.
*   Implement robust error handling using `try-catch` blocks for conversions and casting.
*   Grasp the concept of **Serialization** in its most basic form.
*   Work with **Polymorphism**, virtual functions, and Run-Time Type Information (RTTI).
*   Use **function templates** to write generic, reusable code and avoid duplication.
*   Design and use **static classes** (non-instantiable utility classes).

## Learning Resources

- [Introduction to literals and operators](https://www.learncpp.com/cpp-tutorial/introduction-to-literals-and-operators/)
- [Introduction to type conversion and static_cast](https://www.learncpp.com/cpp-tutorial/introduction-to-type-conversion-and-static_cast/)
- [Explicit type conversion (casting) and static_cast](https://www.learncpp.com/cpp-tutorial/explicit-type-conversion-casting-and-static-cast/)
- [When to use reinterpret_cast?](https://stackoverflow.com/questions/573294/when-to-use-reinterpret-cast)
- [Dynamic casting](https://www.learncpp.com/cpp-tutorial/dynamic-casting/)
- [std::stoi, std::stol, std::stoll](https://en.cppreference.com/w/cpp/string/basic_string/stol)

## Project Structure

The project is divided into three exercises, each focusing on a different type of cast.

*   `ex00/`: Conversion of scalar types using `static_cast`.
*   `ex01/`: Serialization of a pointer using `reinterpret_cast`.
*   `ex02/`: Identification of a derived class type using `dynamic_cast`.

Each directory contains:
*   `Makefile`: To compile the exercise.
*   `main.cpp`: The main program to test the exercise's features.
*   Header and source files for the classes and functions required by the exercise.

## Implementation Details

### Exercise 00: Conversion of Scalar Types

*   **Task:** Create a program that takes a single command-line argument representing a C++ literal (`char`, `int`, `float`, or `double`) and attempts to convert it to the other three scalar types, printing the result of each conversion.
*   **Implementation:**
    *   A non-instantiable `ScalarConverter` class with a single static method `convert(std::string str)` encapsulates all functionality.
    *   The input string is first trimmed of leading/trailing whitespace.
    *   A series of helper functions (`isChar`, `isFloat`, `isDouble`) attempt to identify the literal's type. These functions rely on `std::stod`, `std::stof`, and `std::stoi` to parse the string.
    *   The `std::sto*` functions are wrapped in a `try-catch` block to handle `std::invalid_argument` (not a number) and `std::out_of_range` (overflow) exceptions.
    *   Once the type is identified, a corresponding `handle<Type>` function is called (e.g., `handleInt`).
    *   These handlers use a set of `castPrint<Type>` function templates to perform the final `static_cast` and print the result. These templates check for potential overflow/underflow before casting (e.g., checking if a `double` value fits within `int` limits before casting).
    *   Special floating-point values like `nan`, `+inf`, and `-inf` are correctly handled and printed as "impossible" for `char` and `int` conversions.
    *   Output for `float` and `double` is formatted to always show at least one decimal place (e.g., `42.0f`).
*   **Key Concepts:** `static_cast`, string-to-numeric conversion, exception handling, function templates, static classes, handling of special floating-point values.

### Exercise 01: Serialization

*   **Task:** Implement a `Serializer` class with static methods to serialize a `Data*` into a `uintptr_t` and deserialize it back, proving the round-trip conversion is successful.
*   **Implementation:**
    *   A simple `Data` struct is defined to serve as the object to be serialized.
    *   The `Serializer` class is made non-instantiable by deleting its copy constructor/assignment and making its default constructor protected.
    *   `static uintptr_t serialize(Data* ptr)`: This method takes a pointer and uses `reinterpret_cast<uintptr_t>(ptr)` to convert the pointer's memory address into an integer value. `uintptr_t` is an integer type guaranteed to be large enough to hold a pointer address.
    *   `static Data* deserialize(uintptr_t raw)`: This method performs the reverse operation, taking the raw integer value and using `reinterpret_cast<Data*>(raw)` to convert it back into a valid pointer to a `Data` object.
    *   The `main` function demonstrates the process by creating a `Data` object, serializing its pointer, deserializing the integer back to a pointer, and verifying that the deserialized pointer is identical to the original.
*   **Key Concepts:** `reinterpret_cast`, `uintptr_t`, basic serialization, pointer-integer conversion, static utility classes.

### Exercise 02: Identify Real Type

*   **Task:** Given a pointer or reference to a `Base` class, identify which of its derived classes (`A`, `B`, or `C`) it actually is.
*   **Implementation:**
    *   A polymorphic `Base` class is defined with a `virtual` destructor. This is crucial for `dynamic_cast` to work.
    *   Three empty classes, `A`, `B`, and `C`, publicly inherit from `Base`.
    *   A `generate()` function randomly instantiates one of `A`, `B`, or `C` and returns a `Base*` pointing to it.
    *   `identify(Base* p)`: This overload takes a pointer. It uses a series of `if` statements with `dynamic_cast<Derived*>(p)`. `dynamic_cast` will return a valid pointer if the object `p` points to is of type `Derived` (or a class derived from it); otherwise, it returns `nullptr`. The first non-null result identifies the type.
    *   `identify(Base& p)`: This overload takes a reference. It uses a series of `try-catch` blocks. `dynamic_cast<Derived&>(p)` will succeed if the cast is valid, but it will throw a `std::bad_cast` exception if it is not. By catching the exception, we can try the next type until one succeeds.
*   **Key Concepts:** `dynamic_cast`, polymorphism, virtual functions, Run-Time Type Information (RTTI), downcasting, `std::bad_cast` exception, differences in `dynamic_cast` behavior for pointers vs. references.

## How to Compile and Run

Each exercise has its own `Makefile` and must be compiled and run from its respective directory.

1.  Navigate to the specific exercise directory (e.g., `ex00`, `ex01`, `ex02`).
    ```bash
    cd exXX
    ```
2.  Use `make` to compile the project.
    ```bash
    make
    ```
3.  This will create an executable file (`convert`, `serialize`, or `realType`).
4.  Run the executable. Note that `ex00` requires a command-line argument.
    ```bash
    # For ex00
    ./convert 42.0f
    
    # For ex01
    ./serialize

    # For ex02
    ./realType
    ```

**Other Make Commands:**

*   `make clean`: Removes the object files.
*   `make fclean`: Removes object files and the executable.
*   `make re`: Performs `fclean` followed by `make`.

**Example (Compiling and running Exercise 00):**

```bash
cd ex00
make
./convert "a"
./convert 42
./convert -inff
```