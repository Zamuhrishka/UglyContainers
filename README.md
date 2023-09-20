<img src="https://github.com/Zamuhrishka/UglyContainers/workflows/UnitTest/badge.svg?branch=master">
# Ugly Containers












## Info

- [Building HashMap from Scratch in C for Sum Of Two Problem Solving on LeetCode](https://medium.com/@alexey.medvecky/building-hashmap-from-scratch-in-c-for-sum-of-two-problem-solving-on-leetcode-ab3d81f9ab65)
-

## Small ToDo

[] Add some wrapper macro for structures
[] FIFO блокируется при переполнении, в отличие от кольцевого буфера
[] Add decrease memory function for Vector
[] Rework all for using status codes
[x] Replace standard assert on special library assert QC_ASSERT()
[] Add algorithms: sort, find, print, fromArray, toArray, iterator
[] Implemet to data copy modes: deep copy, simple copy
[] Add thread safety (use atomic access and mutex)
[] Split core on dynamic and static types
[] Think about `volatile`
[] В Java используется похожий подход, но массив растет медленнее. Размер нового массива определяется следующим образом: size = (size * 3) / 2 + 1;
[] Check code by memory sanitazer

## Examples

- [qlibc](https://github.com/wolkykim/qlibc)
- [c-algorithms](https://github.com/fragglet/c-algorithms/tree/master/src)
- [C-Macro-Collections](https://github.com/LeoVen/C-Macro-Collections)
- [sc](https://github.com/tezc/sc)
- [fifofast](https://github.com/nqtronix/fifofast)
- [Используем черную магию для создания быстрого кольцевого буфера](https://habr.com/ru/company/otus/blog/557310/)

### Set

- [Set](https://tproger.ru/translations/sets-for-beginners/)

### Hash Table

- Implement of Hash Table (https://www.youtube.com/watch?v=2Ti5yvumFTU&list=PL9IEJIKnBJjFiudyP6wSXmykrn67Ykqib&index=4)

### Allocators

- [Аллокаторы памяти](https://habr.com/ru/post/505632/)
- [Менеджмент памяти или как реже стрелять себе в ногу](https://habr.com/ru/post/473294/)
- [Происхождение и эволюция аллокатора памяти в С](https://habr.com/ru/post/707032/)
- [tlsf](https://github.com/mattconte/tlsf)
- [Malloc-Implementations](https://github.com/emeryberger/Malloc-Implementations)
- [tinyalloc](https://github.com/thi-ng/tinyalloc)
- [umm_malloc](https://github.com/dimonomid/umm_malloc)
