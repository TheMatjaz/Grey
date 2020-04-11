Grey codes a.k.a. Reflected binary codes in C, made simple
===============================================================================

Grey codes or Reflected binary codes are encodings of unsigned integers
such that two adjacent values have only 1 bit of difference. Originally
designed for electromechanical switches so that the state would transition
cleanly from one value to the other without other values being represented
in between. More details on 
[Wikipedia](https://en.wikipedia.org/wiki/Gray_code).

This is a tiny tiny C99 library that converts unsigned integers of any size
from and to Grey codes.

By default, the library will operate on `uint64_t` integers for conversions
from/to Grey codes. If you prefer using smaller integer (but also limit the 
domain of the Grey codes and their values), redefine the macro `GREY_UINTBITS`
to 32, 16 or 8 instead of 64.


Usage example
----------------------------------------

```c
    // Convert to Grey code
    grey_code_t my_code = grey_to(10); // my_code is now 0b1111 = 0x0F = 15
    
    // Convert from Grey code
    grey_int_t my_value = grey_from(my_code);  // my_value is now 10 again
    
    // Handy macro for incrementing Grey codes
    grey_code_t my_code = grey_to(103);  // my_code is now 84, representing 103
    my_code = grey_incr(my_value);  // my_code is now 92, representing 104
    my_value = grey_from(my_code);  // my_value is now 103
    
    // Or for decrementing
    my_code = grey_decr(85);
    
    // Or for custom addition/subtraction (may be unsafe!)
    my_code = grey_add(85, 5);
    
    // Printing format
    my_code = grey_to(42);
    printf("Int %u "
           "= Grey decimal %" GREY_FMT
           " = Grey lowercase hex 0x%" GREY_FMTx
           " = Grey uppercase hex 0x%" GREY_FMTX "\n",
           42, my_code, my_code, my_code);

    // Converting to binary string
    char binstr[GREY_UINTBITS + 1];
    uint8_t len = grey_binstr(binstr, 7);  // str now contains "111\0", len is 3
```

You can also check the `tst/test.c` file for more examples.




Include it in your project
----------------------------------------

### Static source inclusion

Copy the `inc/grey.h` and `src/grey.c` files into your existing
C project, add them to the source folders and compile. Done.

If you prefer using smaller integers, redefine `GREY_UINTBITS`.


### Compiling into all possible targets

```
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release -DGREY_UINTBITS=64
cmake --build .
```

This will build all targets:

- a `libgrey.dylib`/`libgrey.dll` shared library
- a `libgreystatic.a` static library
- a test runner executable `test_grey`
- the Doxygen documentation (if Doxygen is installed)

To compile with the optimisation for size, use the
`-DCMAKE_BUILD_TYPE=MinSizeRel` flag instead.

If you prefer using smaller integers, set `-DGREY_UINTBITS=32` (or 16 or 8).
