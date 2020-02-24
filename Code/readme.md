### Usage

* clang -fopenmp  -L/usr/local/opt/llvm/lib -I/usr/local/opt/llvm/include \<filename\> && ./a.out
* Works with clang version 9.0.1 , x86_64-apple-darwin19.3.0

### Code Examples

```
1. Hello World
2. Pi
3. Mandelbrot Set
```

* [1_hello_world.c](./src/1.c)
  * hello world of OpenMP
  * code in structured block following "# pragma omp parallel" is executed by every thread possibly available
  ```
  # pragma omp parallel
  ```

* [2_serial_pi.c](./src/2_serial_pi.c)
  * serial program to calculate pi via integration
  * pragma omp parallel - get me default number of system threads
  * my system has 12 threads. 2 threads per core
* [2_parallel_pi_v1.c](./src/2_parallel_pi_v1.c)
  * Extends [v1](./src/2_parallel_pi_v1.c). Calculate pi with OpenMP
  * Key ideas -
    * Promote scalar (sum) to an array dimensioned by number of threads to avoid race condition
    * Only one thread should copy the number of threads to the global value to make sure multiple threads writing to the same address don’t conflict.
    * For loop uses the most common trick in SPMD programs to create a cyclic/round robin distribution of loop(threads) iterations
  * run with 1,2,4,6 threads. scalability of threads is terrible. because of false sharing
  * worse performance than [v1](./src/2_parallel_pi_v1.c)
* [2_parallel_pi_v2.c](./src/2_parallel_pi_v2.c)
  * use padding to prevent false sharing. forces data of each thread to be on distinct cache lines
  * better performance than [v1](./src/2_parallel_pi_v1.c)
  * but hacky poor solution. how would you know the size of L1 cache line? wouldn't work across architectures
* [2_parallel_pi_v3.c](./src/2_parallel_pi_v3.c)
  * Use synchronization to prevent false sharing and also prevent use of padding
  * Create a scalar local to each thread to accumulate partial sums.
    * Now sum variable on stack of each loop. False sharing automatically eliminated
  * Pi summation within the critical section now, since the local variable sum will be lost with stack once threads end
  * Performance as good as [v2](./src/2_parallel_pi_v2.c). Portable code.
  * Lesson: Put #pragma omp critical on the code where work done is minimal. Do not serialize your program. (Slide 71)
* [2_parallel_pi_v4.c](./src/2_parallel_pi_v4.c)
  * Start with [serial pi program](./src/2_serial_pi.c) and add "omp for","reduction"
  * As good performance as it gets
* [2_parallel_pi_v4_2.c](./src/2_parallel_pi_v4.c)
  * Better implementation of [2_parallel_pi_v4.c](./src/2_parallel_pi_v4.c)
  * Just 2 line change wrt [serial version](./src/2_serial_pi.c)
* [3_mandel_bug.c](./src/3_mandel_bug.c)
  * Buggy version of Mandelbrot set. Incorrect answer
* [3_mandel_fix.c](./src/3_mandel_fix.c). Fixed
  ```
  1. firstprivate(eps) private(c, i, j)
  2. void testpoint(struct d_complex c) and void testpoint(struct d_complex);
  3. #pragma omp atomic
        numoutside++;
  4. testpoint(c);
  ```
