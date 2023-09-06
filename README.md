# fwContainers


## Info

- [Building HashMap from Scratch in C for Sum Of Two Problem Solving on LeetCode](https://medium.com/@alexey.medvecky/building-hashmap-from-scratch-in-c-for-sum-of-two-problem-solving-on-leetcode-ab3d81f9ab65)
-

## Small ToDo

- implement `void* container_peek(const container_t* container, size_t index)` function
- test `void* container_peek(const container_t* container, size_t index)` function
- implement `bool container_resize(ontainer_t* container, size_t new_size)` function
- test `bool container_resize(ontainer_t* container, size_t new_size)` function
- refactoring of `dict`
- testing `dict`
- refactoring of `set`
- testing `set`
- implement separate core hash table structure
- testing core hash table structure

## Big ToDo

- Implement of Hash Table (https://www.youtube.com/watch?v=2Ti5yvumFTU&list=PL9IEJIKnBJjFiudyP6wSXmykrn67Ykqib&index=4)
- Implemet to data copy modes: deep copy, simple copy
- Add Unit tests
- Add thread safety (use atomic access and mutex)
- Split core on dynamic and static types
- Think about `volatile`
- FIFO блокируется при переполнении, в отличие от кольцевого буфера
- Add algoruthms: sort, find, print, fromArray, toArray, iterator
- Rework all for using status codes
- В Java используется похожий подход, но массив растет медленнее. Размер нового массива определяется следующим образом: size = (size * 3) / 2 + 1;
- Replace standard assert on special library assert QC_ASSERT()
- [Set](https://tproger.ru/translations/sets-for-beginners/)

## Allocators

- [Аллокаторы памяти](https://habr.com/ru/post/505632/)
- [Менеджмент памяти или как реже стрелять себе в ногу](https://habr.com/ru/post/473294/)
- [Происхождение и эволюция аллокатора памяти в С](https://habr.com/ru/post/707032/)
- [tlsf](https://github.com/mattconte/tlsf)
- [Malloc-Implementations](https://github.com/emeryberger/Malloc-Implementations)
- [tinyalloc](https://github.com/thi-ng/tinyalloc)
- [umm_malloc](https://github.com/dimonomid/umm_malloc)

## LINKS

- [qlibc](https://github.com/wolkykim/qlibc)
- [c-algorithms](https://github.com/fragglet/c-algorithms/tree/master/src)
- [C-Macro-Collections](https://github.com/LeoVen/C-Macro-Collections)
- [sc](https://github.com/tezc/sc)
- [fifofast](https://github.com/nqtronix/fifofast)
- [Используем черную магию для создания быстрого кольцевого буфера](https://habr.com/ru/company/otus/blog/557310/)


## Names

- Quasi Containers (QC)/Quasi Collections (QC)/Quasi Collections C (QCC)
- Ugly Containers (UC)
- Imaginary Containers (IC)
