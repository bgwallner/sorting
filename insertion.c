/* Straight selection sort (Knuth 5.2.3 working with lowest elem) - BWallner 2021 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 8         /* Array size */
#define MAX 65535   /* Just some large number */

/* Declarations */
static void print_array( unsigned short a[], unsigned short size,
                        unsigned short index1, unsigned short index2,
                        unsigned char with_index );
static void sort_inplace( unsigned short a[], unsigned short size );
static void sort_not_inplace( unsigned short a[], unsigned short sorted[], unsigned short size );
static void test_order( unsigned short a[], unsigned short size  );

/* Static functions */

static void sort_inplace( unsigned short a[], unsigned short size )
{
	unsigned short current;
	unsigned short leap;
	unsigned short index_s;
	unsigned int smallest;
	
	for( current = 0; current < (size-1); current++)
	{
		leap = (size-1);
		smallest = MAX;
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

        /* Print data before switching */
        printf("\n");
		print_array( &a[0], size, index_s, current, 1 );
		
		if( a[current] > smallest )
		{
			/*  Exchange current element with smallest found */
			a[index_s] = a[current];
			a[current] = smallest;
		}
		print_array( &a[0], size, 0, 0, 0 );
	}
}

static void sort_not_inplace( unsigned short a[], unsigned short sorted[], unsigned short size )
{
	unsigned short current;
	unsigned short leap;
	unsigned short index_s;
	unsigned int smallest;

	current=0;
	while( current < size )
	{
		leap = 0;
		smallest = MAX;
		/* Iterate leap from first element to last */
		while( leap < size )
		{
			/* Check if leap element is smaller than smallest */
			if( a[leap] < smallest )
			{
				/* Update smallest and save index  */
				smallest = a[leap];
				index_s = leap;
			}
			leap++;
		}

        /* Original array */
        printf("\n");
		print_array( &a[0], size, 0, 0, 0 );

		/*  Assign MAX to found smallest element */
		a[index_s] = MAX;
		sorted[current] = smallest;

		/* Print modified original and sorted array */
		print_array( &a[0], size, 0, 0, 0 );
		print_array( &sorted[0], size, 0, 0, 0 );

        /* New iteration */
		current++;
	}
}

static void print_array( unsigned short a[], unsigned short size,
                         unsigned short index1, unsigned short index2,
                         unsigned char with_index )
{
	unsigned short i;
	for( i = 0; i < size; i++)
	{
		if( 1 == with_index)
		{
			if( i == index2 )
			{
				printf("(c)a[%d]=%d\t", i, a[i]);
			}
			else if( i == index1 )
			{
				printf("(s)a[%d]=%d\t", i, a[i]);
			}
			else
			{
				printf("   a[%d]=%d\t", i, a[i]);
			}
		}
		else
		{   if( MAX == a[i])
			{
				printf("   a[%d]=0x%X\t", i, a[i]);
			}
			else
			{
				printf("   a[%d]=%d\t", i, a[i]);
			}
		}
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
	printf("TESTING RESULT\n");
	printf("--------------\n");
	if( 1 == failed )
	{
		printf("Sorting: FAILED\n");
	}
	else
	{
		printf("Sorting: SUCCESS\n");
	}
	printf("\n");
}

/* Global functions */
int main(void)
{
	unsigned short a[N] = {0};
	unsigned short b[N] = {0};
	unsigned short s[N] = {0};
	unsigned short i;
	time_t t;

    printf("\n");
	printf("Program START...\n");
	printf("\n");
	printf("(c) current element (s) smallest element found in range [(c)+1 <- NMAX]\n");
	
	/* Generate sequence of random numbers */
	/* between 0 and 99.                   */
	srand((unsigned) time(&t));
	for( i=0; i<N; i++)
	{
		a[i] = rand() % 100;
		b[i] = a[i];
	}

	/* Sort array in-place */
	sort_inplace( &a[0], N );

	/* Test increasing order */
	test_order( &a[0], N );

	printf("\n");
	printf("find smallest value and add to new array, range [0->NMAX] in every iteration\n");

    /* Sorting not in-place */
	sort_not_inplace( &b[0], &s[0], N);

	/* Test increasing order */
	test_order( &a[0], N );

	printf("Program END\n");
	printf("\n");

	return 0;
}