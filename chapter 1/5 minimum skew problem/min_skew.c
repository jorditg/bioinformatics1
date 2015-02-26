#include "gen.h"
#include "stdio.h"

#define MAX_MIN 20

void calculate_skew(char * genome, float * skew, size_t size);
void k_movile_mean(int k, float *from, float* to, size_t size);
size_t find_min(float *array, size_t size, size_t * out);
void print_array_c_f(char * g, float * array, size_t size);
void print_array_f(float * array, size_t size);

int main(int argc, char* argv[]) 
{
	size_t size;
	int k;
	size_t nr_output, i;
	
	//k = atoi(argv[1]);	// media movil de k elementos
	
	char * genome = load_genome("test.txt", &size);
	float * skew = malloc(size*sizeof(float));
	float * mm = malloc(size*sizeof(float));
	size_t * out = (size_t *) malloc(MAX_MIN*sizeof(size_t));
	
	calculate_skew(genome, skew, size);
	//print_array_f(skew, size);
	//k_movile_mean(k, skew, mm, size);
	//print_array_f(mm, size);
	
	nr_output = find_min(skew, size, out);
	for(i=0;i<nr_output;i++)
		printf("%i ", out[i]);
	printf("\n");
	
	free(genome);
	free(skew);
	free(out);
	return 0;
} 

void calculate_skew(char * genome, float * skew, size_t size)
{
	size_t i;
	
	memset(skew, 0, size);
	skew[0] = (genome[0]=='G')?1:0;
	skew[0] = (genome[0]=='C')?-1:0;
	for(i=1;i<size;i++)
	{
		if(genome[i]=='G')
			skew[i] = skew[i-1] + 1;
		else if(genome[i]=='C')
			skew[i] = skew[i-1] - 1;
		else
			skew[i] = skew[i-1];
		
	}
}


size_t find_min(float *array, size_t size, size_t * out)
{
	size_t i;
	size_t i_o = 0;
	int min = 0;
	
	for(i=0;i<size;i++)
	{
		if(array[i] == min) {		
			out[i_o++] = i+1;
		} else if(array[i] < min) {
			min = array[i];
			i_o = 0;
			out[i_o++] = i+1;
		} 
		if(i_o == MAX_MIN)	// removes possibility of buffer overflow in output
			break;
	}
	
	return i_o;
}


void print_array_c_f(char * g, float * array, size_t size)
{
	size_t i;
	
	for(i=0;i<size;i++)
		printf("%c\t%f\n", g[i], array[i]);
}

void print_array_f(float * array, size_t size)
{
	size_t i;
	for(i=0;i<size;i++)
		printf("%f\n", array[i]);
}
