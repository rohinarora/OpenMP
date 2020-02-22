* 2_serial_pi.c
  * hello world
  * pragma omp parallel - get me default number of system threads
  * my system has 12 threads. 2 threads per core
* 2_parallel_pi_v1.c
  * pi
  * hello world of OpenMP
  * SPMD. Single program, multiple data
  * Run multiple copies of the program
  * Cyclic/round robin execution of threads
  * run with 1,2,4,6 threads. scalability of threads is terrible. because of false sharing
* 2_parallel_pi_v2.c
  * use padding to prevent false sharing. forces data of each thread to be on distinct cache lines
  * works ! extremely good
  * but hacky poor solution. how would you know the size of L1 cache line? how would your code work across architectures?
* 2_parallel_pi_v3.c