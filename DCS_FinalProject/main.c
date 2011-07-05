#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <time.h>

/* global state */
struct timespec  start_time;                                 
struct timespec  end_time;  

#include "D_Circuit.h"
#include "D_Parser.h"

FILE *inc = NULL, *inp = NULL, *out = NULL;

int main(int argc, char **argv){
    if(argc < 3){
        fprintf(stderr, "Usage: %s input_circuit input_pattern [output_pattern]\n", argv[0]);
        exit(1);
    }
	char buffer[81];
	inc = fopen(argv[1], "r");
	assert(inc !=  NULL);
	inp = fopen(argv[2], "r");
	assert(inp != NULL);
	if(argc == 3){
		strcpy(buffer, "output_");
		strncat(buffer, argv[1], 20);
		strcat(buffer, "_");
		strncat(buffer, argv[2], 20);
		strcat(buffer, ".vcd");
		fprintf(stderr, "Output filename not specified, using \"%s\" instead.\n", buffer);
		out = fopen(buffer, "w");
	}else{
		out = fopen(argv[3], "w");
	}
	assert(out != NULL);
//	while(getlinen(buffer, inc, 81) != EOF){}

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start_time); //stdio scanf ended, timer starts

	Circuit mainc;
//	char t[50];
//	fscanf(inc, "%s", t);
//	printf("%s\n", t);
	parse_circuit(&mainc, inc);
//	circuit_print(&mainc, stderr);
	Pattern_parse_data pdata_main;
	load_header(&mainc, &pdata_main, inp);
	output_header(&mainc, &pdata_main, out);
	simulate(&mainc, &pdata_main, inp, out);

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end_time);
	//printf("sizeof(start_time.tv_sec):%d, sizeof(start_time.tv_nsec):%d\n", sizeof(start_time.tv_sec), sizeof(start_time.tv_nsec));
	//printf("s_time.tv_sec:%ld, s_time.tv_nsec:%ld\n", start_time.tv_sec, start_time.tv_nsec);
	//printf("e_time.tv_sec:%ld, e_time.tv_nsec:%ld\n", end_time.tv_sec, end_time.tv_nsec);
	double execution_time = (double)end_time.tv_sec + (double)end_time.tv_nsec/1000000000.0 - (double)start_time.tv_sec - (double)start_time.tv_nsec/1000000000.0;
	printf("\nExecution Time:%.4f(s)\n\n", execution_time);

	fclose(inc);
	fclose(inp);
	fclose(out);

}
