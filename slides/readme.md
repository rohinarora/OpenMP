* Slide 16. Good. Parallelism is a subset of concurrency. Slide 17
* Expose concurrency in a problem, and map it on to processing units so that they they actually execute at the same time. - Parallelism
* Slide 18. Good
* Slide 19. All the hard work is "Finding the concurrency, and the algorithm strategy to parallelize.". The last step brings in OpenMP/any other framework. which is trivial
* What is OpenMP- Slide 19,20,21,22
  * pragma. compiler directives
  * structured block
* Slide 31. SMP, NUMA. Good
* Slide 33, 34. Modern machines are NUMA
* Slide 35, 36. Program memory and threads. Threads are light weight processes
* Slide 36. Good
* Slide 39. Good.
  * Use synchronization to protect data conflicts.
  *  Synchronization is expensive so change how data is accessed to minimize the need for synchronization.
* OpenMP main points
  * Threads working in shared address space
  * (Unintended) Sharing that will lead to race conditions
  * Use synchronization to prevent race conditions
  * Manage data to reduce the amount of synchronization required
* Creating threads in OpenMP
  * fork join model
  * slide 46. under the hood
    * Only three threads are created because the last parallel section will be invoked from the parent thread.
  * #pragma omp parallel num_threads(4)
* Slide 52. When we enter parallel region in OMP, we request a particular number of threads. The ENV can choose to give us fewer threads. Therefore, must query inside the ENV how many threads were actually allotted.
* Slide 55. false sharing. parallel code not giving expected performance. Same thing also rephrased on slide 66
* Slide 56-58. Padding. Hacky. Good performance but not good solution
  * Padding arrays requires deep knowledge of the cache architecture. Move to a machine with different sized cache lines and your software performance falls apart
  * Using synchronization is better solution
* Slide 61
  * There is a lot of overhead is creating these critical sections. So design your code in a way that makes sure some substantial work is being done by all threads before they hit critical section
  * Forms of synchronization.
    * Barrier. Slide 63. All threads wait till everyone completes
    * Mutual Exclusion. Slide 64. Only one thread at a time. Serializes the code. So keep this minimal runtime.
    * Atomic. Slide 65. Provides mutual exclusion but only applies to the update of a memory location. When in doubt, use critical (mutual exclusion)
* Slide 69-72. Use synchronization for pi program. More explanation in main readme. (v3 code)
* Slide 74. Good. SPMD vs worksharing
* Slide 75.
  * "#pragma omp parallel" must be there to create threads/request OS for threads. "#pragma omp for" only uses the threads given by the OS
  * Takes care of the cyclic distribution we were doing earlier automatically ([v1](../Code/2_parallel_pi_v1.c))
  * private(i) can be made explicit
* Slide 76.
  * sequential naive code
  * SIMD code. Similar thing done previously in [v1](../Code/2_parallel_pi_v1.c)
  * Neat code with #pragma omp for
* Slide 77
  * Worksharing constructs
  * Compiler doesn't know how to distribute work in worksharing mechanism. Telling it explicitly is good
  * The schedule clause affects how loop iterations are mapped onto threads
  * static. compile time. If no chuck, 1 is default
  * Dynamic runtime. When work across iterations changes a lot. Like thread pool example. Sieve of Eratosthenes. Slide 78. more
  * guided. not used anymore
  * more in slides
  * would only need static and dynamic in most cases
* Slide 79. Shorthand
* #pragma omp for must follow "for loop"
* Slide 80. Working with loops
  * Make the loop iterations independent
  * Expose concurrency in a problem, and map it on to processing units so that they they actually execute at the same time
* Slide 81. For nested loops. Use collapse(num loops
  * Useful if outer loop is O(no. of threads)
* Slide 82-84. Reduction. reduction (op : list)
* Slide 83.
  * The variables in “list” must be shared in the enclosing parallel region
  * See Slide :Inside a parallel or a work-sharing construct
* Slide 84. Initial values. Also discussed in GPU class
* Slide 91. Different schedules
* Slide 94. Barriers
  * Implicit barrier at the end of a "pragma omp parallel " region. Can't remove this barrier
  * Implicit barrier at the end of a for worksharing construct. Here it means at end of "#pragma omp for"
    * Can turn this off using nowait. If you think its next lines of code won't depend on the loop compute
* Slide 95. Master Construct
  * The master construct denotes a structured block that is only executed by the master thread.
  * Use when you want just 1 thread to do something. No synchronization here. The other threads just skip it
  * keeping #pragma omp barrier after master is a good practice
* Slide 96. Single. Worksharing construct
  * The first thread that reaches here does the work. But single is a worksharing construct. Barriers are implicit at end of worksharing constructs. Hence no explicit barrier needed with single (as needed with master).  Can remove this implicit barrier using nowait
* Slide 97, Sections. Worksharing construct
  * #pragma omp sections
  * Implicit barrier at end of "#pragma omp sections"
* Slide 98. Lock
  * Lowest level of mutual exclusion synchronization
  * Lock variable type is defined in omp.h-> lock_t
  * omp_init_lock()
  * omp_set_lock()
  * omp_unset_lock()
  * omp_destroy_lock()
  * omp_test_lock()- normally if you check a lock, it automatically goes into wait if its busy. This just checks if its free or not, and based on it, does some action
* Slide 99. Example- Making a histogram. Code on slide
  * Imagine histogram is huge. Updating bins.
  * Need to ensure no two bins are updated by 2 threads at the same time.
  * If i put this in critical section, entire histogram update is serialized.
  * Have a lock for each bin. This is the case of un-contended lock. The chance of 2 threads updating same bin at the same time is very low
* Slide 100. Runtime library routines.
  * omp_get_max_threads() - max threads possible. Use this to safely set the largest array for each thread. As arrays were set in ../Code/2_parallel_pi_v1.c
  * omp_in_parallel()- Imagine sometimes a function is called within a parallel region.Sometimes its not. This checks whether i am in a parallel region
  * omp_set_dynamic() -  sets dynamic mode
  * omp_get_dynamic()- checks whether i am in dynamic mode
  * omp_num_procs() - How many processors in the system?
* Slide 101. Code. Runtime routines in action. See slide
* Slide 102. Environment Variables. See slides
  * OMP_NUM_THREADS
  * OMP_STACKSIZE
  * OMP_WAIT_POLICY
    * Use passive only when you think thread will be sleeping for a long time.
    * If wait time is small, let the thread spin (active)
    * Putting the thread to sleep and waking it up has a cost
  * OMP_PROC_BIND
    * Bind thread to a processor, and do not move it. NUMA architectures
    * Binding may have a cost. Ideally, if one processor gets too busy, OS might put threads on another core. Won't be possible with binding on
* Slide 104. Data environment
  * Heap/global shared
  * Stack private
* Slide 105
