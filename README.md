[![UnitTests](https://github.com/Zamuhrishka/UglyContainers/actions/workflows/RunTests.yml/badge.svg?branch=master)](https://github.com/Zamuhrishka/UglyContainers/actions/workflows/RunTests.yml)

# Ugly Containers

The primary goal of writing this library was an attempt to study data structures and algorithms. As is commonly known, the best way to learn something is to implement it. However, implementing data structures in languages like Python and C++ isn't as intriguing, as these languages already have built-in data structures. Therefore, C was chosen as the main development language. Another reason for this choice was the ambition to create a convenient and universal library for working with data structures and algorithms.

## Disclaimer

![Alt text](docs/Disclaimer.png)

## Project Structure

The project consists of the following modules:

- core
- interface
- algorithms

### Core Module

This is the central module of the entire library which implements the universal container for data storage.

A universal container holds user data and provides the necessary operations to work with this data:

- `resize`: Changes the size of the container.
- `push_front`: Adds an element to the beginning of the container.
- `pop_front`: Removes an element from the beginning of the container.
- `push_back`: Adds an element to the end of the container.
- `pop_back`: Removes an element from the end of the container.
- `insert`:  Inserts an element at a specified index.
- `extract`: Extracts an element from a specified index.
- `replace`: Replaces an element at a specified index.
- `at`: Returns the element at a specified index without removing it.
- `erase`: Deletes the element at a specified index.
- `peek`: Returns a pointer to the element at a specified index without removing it.
- `clear`: Clears the container of all elements.
- `size`: Returns the number of elements in the container.

These functions cover almost the entire range of operations necessary for working with a data container.

The container is termed universal for two reasons:

- It can store any type of data: `bool`, `uint8_t`, `uint16_t`, `uint32_t`, structures, etc. However, the container cannot store mixed data types. The universality of data type storage is achieved by working with data through `void` pointers and specifying the size of stored data in bytes via the `esize` argument. Here are examples of creating containers for different data types:

```c
container_t* container = container_create(sizeof(bool), CONTAINER_LINKED_LIST_BASED);
container_t* container = container_create(sizeof(uint8_t), CONTAINER_LINKED_LIST_BASED);
container_t* container = container_create(sizeof(uint32_t), CONTAINER_LINKED_LIST_BASED);
```

Working with data through `void` pointers would look like this:

```c
uint8_t input = 0x55;
bool status = container_push_front(container, (void*)&input);
```

![Alt text](docs/container_important.png)

- A universal container can be implemented based on either a linked list or a vector. The specific type is chosen when creating the container using the second type argument, which can take two values: `CONTAINER_LINKED_LIST_BASED` and  `CONTAINER_VECTOR_BASED`.

```c
container_t* container = container_create(sizeof(uint8_t), CONTAINER_LINKED_LIST_BASED);
container_t* container = container_create(sizeof(uint8_t), CONTAINER_VECTOR_BASED);
```

This decision was made because, for different data structures like queues and stacks, it's convenient to choose different containers: for queues, a doubly linked list is **typically** the best fit, while for stacks, a vector is preferred. To offer users greater flexibility in choosing a container for a specific data structure, while maintaining a unified interface, the decision was made to combine the operation of linked lists and vectors through a single container interface, allowing the user to choose which of the two containers best suits their needs.

Thus, the `Core` module consists of the `container` module, which provides an interface for working with the container, and sub-modules: `linked_list` and `vector`, which implement the container for data storage and ensure the operation of all necessary operations based on the specific data structure: linked list or vector.

### Interface Module

This module contains various interfaces for integrating external libraries.

#### Allocator Interface

The Ugly Containers uses dynamic memory allocation and accordingly requires an allocator to work. This interface is used specifically for connecting external allocators.
By default the Ugly Containers uses the allocator of the standard C library and if you are satisfied with it, you don't need to do anything. However, if you want to use an allocator other than the standard one, you need to use the allocator registration functions from this interface:

```c
allocation_cb_register(custom_alloc_function);
free_cb_register(custom_free_function);
```

![Alt text](docs/alloc_warning.png)

### Algorithms

This module contains implementations of various algorithms for working with containers: sorting, searching, comparing, converting to an array and back. To provide more flexibility for the implementation of many functions, the [Default and named arguments](https://medium.com/@aliaksandr.kavalchuk/default-and-named-arguments-in-c-functions-9af8c4e34f9b) method is used. Thanks to this method, many functions support default arguments. For example, the default sorting algorithm is the bubble method, so if this method suits you, you don't need to specify it when calling a function:

```c
bool res = uc_sort(.container = container);
```

But if you want to apply a different method, you can specify it in the `sort` argument:

```c
bool res = uc_sort(.container = container, .sort=UC_SELECTION_SORT, .order=SORT_DESCENDING);
```

## Unit Tests

I am not a QA engineer, so my approach to the organization of testing may seem strange, but I divided the tests into two types: unit tests and functional tests, which are located in the corresponding folders in the `test` directory.

- unit tests - test individual functions.
- functional tests - test the module functionality. For example, whether the sorting function sorts the data correctly and the comparison function compares the data.

All tests were written by using [Ceedling framework](https://github.com/ThrowTheSwitch/Ceedling).
So for run unit tests you need to install this framework using instruction from framework [repository](https://github.com/ThrowTheSwitch/Ceedling) and execute command `ceedling test:all`.

## Examples

The main idea I had in mind when developing this library is to make it as flexible and versatile as possible. So everyone can use this library for their own implementations of data structures, but keep in mind the information from the disclaimer. I am developing my implementation of queue, stack, ring buffer and others in this repository: [UglyDataStructures](https://github.com/Zamuhrishka/UglyDataStructures)

## Contributing

Bug reports and/or pull requests are welcome. In case of any questions please contact me. All contact information can be found on my profile main page.
