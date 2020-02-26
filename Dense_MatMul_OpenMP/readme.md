### Usage
 clang -fopenmp -L/usr/local/opt/llvm/lib -I/usr/local/opt/llvm/include <filename.c> -o <output> && ./\<output>

### Speeding up dense matrix multiplication using openMP and blocking (ensures less cache miss)
* Improves naive matrix multiply from 550ms to 44ms
* Hardware: 15 inch Macbook Pro 2019

#### Naive matrix multiplication
* Source- M-M_naive.c
```
Time for the loop = 550.06 milliseconds
Element 0,0 = 131.472137
Element 63,63 = 131.706528
Element 511,511 = 133.296707
```

#### Matrix multiplication with blocking
* Source- M-M_blocked.c
```
Time for the loop = 323.61 milliseconds
Element 0,0 = 131.472122
Element 63,63 = 131.706589
Element 511,511 = 133.296707
```

#### Matrix multiplication with OpenMP
* Source- M-M_omp.c
```
Time for the loop = 91 milliseconds
Element 0,0 = 131.472137
Element 63,63 = 131.706604
Element 511,511 = 133.296707
```

#### Matrix multiplication with blocking and OpenMP
* Source- M-M_blocked_omp.c
```
Time for the loop = 44 milliseconds
Element 0,0 = 131.472137
Element 63,63 = 131.706589
Element 511,511 = 133.296707
```
