/* Straight selection sort (Knuth 5.2.3 working with lowest elem) - BWallner 2021 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 20        /* Array size */
#define MAX 100000  /* Just some large number */

static void sort_inplace( unsigned short a[], unsigned short size )
{
	unsigned short current;
	unsigned short leap;
	unsigned short index_s;
	unsigned int smallest;
	
	for( current = 0; current < (size-1); current++)
	{
		smallest = MAX;
		leap = (N-1);
		/* Iterate leap from last element to current */
		while( leap > current )
		{
			/* Check if leap element is smaller than smallest */
			if( a[leap] < smallest )
			{
				/* Update smallest and save index  */
				smallest = a[leap];
				index_s = leap;
			}
			leap--;
		}
		
		if( a[current] > smallest )
		{
			/*  Exchange current elment with smallest found */
			a[index_s] = a[current];
			a[current] = smallest;
		}
	}
}

static void print_array( unsigned short a[], unsigned short size )
{
	unsigned short i;
	for( i = 0; i < size; i++)
	{
		printf("a[%d]=%d\t", i, a[i]);
	}
	printf("\n");
}

static void test_order( unsigned short a[], unsigned short size  )
{
	unsigned short failed;
	unsigned short i;
	
	failed = 0;
	for( i = 0; i < (size-1); i++)
	{
		if( a[i+1] < a[i] )
		{
			failed = 1;
			break;
		}			
	}
	
	printf("\n");
	if( 1 == failed )
	{
		printf("Sorting FAILED\n");
	}
	else
	{
		printf("Sorting SUCCESS\n");
	}
}

int main(void)
{
	unsigned short a[N];
	unsigned short i;
	time_t t;
	
	/* Generate sequence of random numbers */
	/* between 0 and 49.                   */
	srand((unsigned) time(&t));
	for( i=1; i<=N; i++)
	{
		a[N-i] = rand() % 50; //(unsigned int)i;
	}
	
	/* Print original array */
	print_array( &a[0], N );
	
	/* Sort array */
	sort_inplace( &a[0], N );
	
	/* Print sorted array */
	print_array( &a[0], N );
	
	/* Test increasing order */
	test_order( &a[0], N );

	return 0;
}