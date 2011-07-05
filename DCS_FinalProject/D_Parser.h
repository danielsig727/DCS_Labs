#ifndef D_PARSER_CIRC_H
#define D_PARSER_CIRC_H

#include "D_Circuit.h"

static int NUM_THREADS = 2;

typedef struct _Pattern_symbol Pattern_symbol;
struct _Pattern_symbol{
	char sym[20];
	unsigned long sym_hash;
	unsigned char data;
	Gate *g;
};

typedef struct _Pattern_parse_data Pattern_parse_data;
struct _Pattern_parse_data{
	// Header
	char date[50];
	char timescale[50];
	char scope[50];
	unsigned long time, ntime;
	// Clock
	Pattern_symbol clk;
	// Inputs
	int insymn;
	Pattern_symbol *insyms;
	// Outputs
//	int outsymn;
//	Pattern_symbol *outsyms;
};



int parse_circuit(Circuit *ckt, FILE *in);
int load_header(Circuit *ckt, Pattern_parse_data *pdata, FILE *in);

int output_header(Circuit *ckt, Pattern_parse_data *pdata, FILE *out);

int simulate(Circuit *ckt, Pattern_parse_data *pdata, FILE *in, FILE *out);
int simulate_pthread(Circuit *ckt, Pattern_parse_data *pdata, FILE *in, FILE *out);
int dump(Circuit *ckt, Pattern_parse_data *pdata, FILE *out);

int read_and_load(Circuit *ckt, Pattern_parse_data *pdata, FILE *in);

inline char value_conv(const unsigned char val);

Gate* pattern_get_input_from_symbol(Pattern_parse_data *pdata, const char *str);
//Pattern_parse_data* pattern_construct_header(Circuit *ckt, FILE *in, Pattern_parse_data *pdata);

int getlinen(char *s, FILE *in, int len);

#endif
