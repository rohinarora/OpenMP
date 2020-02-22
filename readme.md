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
* Slide 55. false sharing. parallel code not giving expected performance
* Slide 56-58. Padding. Hacky. Good performance but not good solution
