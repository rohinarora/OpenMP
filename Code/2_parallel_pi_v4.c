/**
 * @author Rohin Arora
 * @email rohinarora07@gmail.com
 * @create date 2020-02-22
 * @modify date 2020-02-24
 
This program will numerically compute the integral of

                  4/(1+x*x)

from 0 to 1.  The value of this integral is pi -- which
is great since it gives us an easy way to check the answer.

Start with serial pi and addin openMP for, reduction
 */

#include <stdio.h>
#include <omp.h>
#define NUM_THREADS 12
static long long num_steps = 1000000000;
double step;
int main()
{
	double pi, sum = 0.0;
	double start_time, run_time;
	step = 1.0 / (double)num_steps;
	omp_set_num_threads(NUM_THREADS);
	start_time = omp_get_wtime();
#pragma omp parallel
	{
		int i;
		double x; // must be declared here so that x is local to each thread. If this is global. All threads would be accessing this memory all the time. Either wrong result, ot too slow
#pragma omp for reduction(+ \
						  : sum)
		for (i = 1; i <= num_steps; i++)
		{
			x = (i - 0.5) * step;		// or (i+0.5)*step; if i starts from 0
			sum += 4.0 / (1.0 + x * x); // 4.0 and 1.0 ensure this is double
		}
	}

	pi = step * sum;
	run_time = omp_get_wtime() - start_time;
	printf("\n pi with %lld steps is %lf in %lf seconds\n ", num_steps, pi, run_time);
}
