/**
 * @author Rohin Arora
 * @email rohinarora07@gmail.com
 * @create date 2020-02-22
 * @modify date 2020-02-22
 
 use of # pragma omp parallel
 
 **/



#include <stdio.h>
#include <omp.h>
int main(int argc, char const *argv[]) {
  # pragma omp parallel
  {
    int ID= omp_get_thread_num();
    printf("hello(%d)",ID);
    printf("world(%d)\n",ID);

  }
  return 0;
}
