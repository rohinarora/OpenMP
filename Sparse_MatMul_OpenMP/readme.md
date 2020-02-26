### Usage
 clang -fopenmp -L/usr/local/opt/llvm/lib -I/usr/local/opt/llvm/include <filename.c> -o <output> && ./<output>

### Speeding up sparse matrix multiplication using openMP and sparse computation
* Improves naive matrix multiply from 490ms to 7ms (2ms using -O3 flag)
* Hardware: 15 inch Macbook Pro 2019

#### Naive matrix multiplication
* Source- M-M_sparse_naive.c
```
Time for the loop = 479.532000
The value of c[0][0] = 12556.00
The value of c[31][32] = 13286.00
The value of c[510][0] = 12264.00
The value of c[511][511] = 27652.00
```

#### Matrix multiplication with openMP and sparse computation
* Source- M-M_sparse_naive.c
```
Time for the loop = 7.957000
The value of c[0][0] = 12556.00
The value of c[31][32] = 13286.00
The value of c[510][0] = 12264.00
The value of c[511][511] = 27652.00
```
