The C++ standard library provides very useful containers (e.g., unordered_map and unordered_set) that are not present in the C library. Often, there is also a need to integrate C++ code with C code.

Write a C++ module called "hash" that provides hash tables for sequences of uint64_t numbers in the C language. It should consist of a header file "hash.h" declaring the module's interface and a "hash.cc" file containing its implementation. This module should provide the following functions:

````
unsigned long hash_create(hash_function_t hash_function);
```

Creates a hash table and returns its identifier. The `hash_function` parameter is a pointer to a hashing function that produces a **uint64_t number** and has parameters ``uint64_t const*`` and ``size_t``.

``void hash_delete(unsigned long id);``

Deletes the hash table with the given identifier if it exists. Otherwise, it does nothing.

``size_t hash_size(unsigned long id);``

Returns the number of sequences stored in the hash table with the given identifier or 0 if such a hash table does not exist.

``bool hash_insert(unsigned long id, uint64_t const* seq, size_t size);``

    Inserts the sequence of integers `seq` with length `size` into the hash table with the given identifier. The result indicates whether the operation was successful. The operation fails if there is no such hash table, if the hash table already contains the sequence, if the `seq` parameter is NULL, or if the `size` parameter is 0.

``bool hash_remove(unsigned long id, uint64_t const* seq, size_t size);``

Removes the sequence of integers `seq` with length `size` from the hash table with the given identifier. The result indicates whether the operation was successful. The operation fails if there is no such hash table, if the hash table does not contain the sequence, if the `seq` parameter is NULL, or if the `size` parameter is 0.

``void hash_clear(unsigned long id);``

If the hash table with the given identifier exists and is not empty, it removes all elements from it. Otherwise, it does nothing.

``bool hash_test(unsigned long id, uint64_t const* seq, size_t size);``

Returns true if a hash table with the given identifier exists and contains the sequence of integers `seq` with length `size`. It returns false in other cases, including when the `seq` parameter is **NULL** or the `size` parameter is 0.

All global variables and helper functions that are not part of the module's interface should be hidden from the external world.

The functions should print diagnostic information to the standard error stream. The correctness of parameters and function execution can be checked using assertions. Compiling with the **-DNDEBUG** flag should disable printing and assertions. Handling standard error output should be done using C++ streams.

A **NULL** function pointer for the hashing function is invalid.

The expected solution should make use of containers and methods provided by the C++ standard library. Do not define your own structures or classes, except possibly for creating a hash table object. Do not store the user-supplied uint64_t const* pointers directly, as users may modify the data pointed to or free the memory.

Avoid excessive conditional compilation. The parts of the source code performing the specified operations of the hash module should not depend on the way it is compiled (with or without the **-DNDEBUG** flag) as otherwise, diagnostic information would be meaningless.

An example of using the hash module in the C language can be found in the **"hash_test1.c"** file.

People are often resourceful and want to use code that can be used in C in C++ as well. Ensure that the **"hash.h"** header file can be used in C++ in such a way that the hash module's interface is placed in the "jnp1" namespace and is not visible in the global namespace. An example of using it in C++ can be found in the **"hash_test2.cc"** file.

Compilation of the examples:

```
bash
g++ -Wall -Wextra -O2 -std=c++17 -c hash.cc -o hash.o
gcc -Wall -Wextra -O2 -std=c17 -c hash_test1.c -o hash_test1.o
g++ -Wall -Wextra -O2 -std=c++17 -c hash_test2.cc -o hash_test2.o
g++ hash_test1.o hash.o -o hash_test1
g++ hash_test2.o hash.o -o hash_test21
g++ hash.o hash_test2.o -o hash_test22
```
