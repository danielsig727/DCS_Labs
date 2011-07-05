#include <string.h>
#include <pthread.h>
#include "D_Parser.h"
#include "D_Hash.h"

#define LINECAP 1023

int parse_circuit(Circuit *ckt, FILE *in){
	char line[LINECAP+1];
	int inputn = -1,
		outputn = -1,
		notn = -1,
		nandn = -1,
		norn = -1,
		andn = -1,
		orn = -1,
		bufn = -1,
		gaten = -1;

	///////////////////////////
	//    Process header     //
	///////////////////////////
	getlinen(line, in, LINECAP);
	sscanf(line, "# INPUT %d", &inputn);
	getlinen(line, in, LINECAP);
	sscanf(line, "# OUTPUT %d", &outputn);
	getlinen(line, in, LINECAP);
    if(strstr(line,"# NOT") != NULL){
		sscanf(line,"# NOT %d",&notn);
		getlinen(line, in, LINECAP);
	}
    if(strstr(line,"# AND") != NULL){
		sscanf(line,"# AND %d",&andn);
		getlinen(line, in, LINECAP);
	}
    if(strstr(line,"# OR") != NULL){
		sscanf(line,"# OR %d",&orn);
		getlinen(line, in, LINECAP);
	}
    if(strstr(line,"# NAND") != NULL){
		sscanf(line,"# NAND %d",&nandn);
		getlinen(line, in, LINECAP);
	}
    if(strstr(line,"# NOR") != NULL){
		sscanf(line,"# NOR %d",&norn);
		getlinen(line, in, LINECAP);
	}
    if(strstr(line,"# BUF") != NULL){
		sscanf(line,"# BUF %d",&bufn);
		getlinen(line, in, LINECAP);
	}
	gaten = inputn + notn + andn + orn + nandn + norn + bufn;
	circuit_init(ckt, "DCS_FINAL_PROJECT", gaten, inputn, outputn);


	///////////////////////////
	//    Process gates      //
	///////////////////////////
	char *cp1, *cp2, *cp3;
	int tmpi;
	while(line[0] != '\0'){
//		printf("-> %s\n", line);

		if(line[0] == '\"'){                      // comment directive
			goto end_parseline;
		}		
		if(strstr(line, "STAT_RPT") != NULL){     // directive for printing curcuit report
			circuit_print(ckt, stdout);
			goto end_parseline;
		}


		if(strstr(line,"INPUT(") != NULL){
			cp1 = strtok_r(line, " ()=\r\n\t", &cp3);  //"INPUT"
			cp1 = strtok_r(NULL, ")", &cp3); // "Name"
			circuit_add_gate(ckt, D_INPUT, cp1, 0);
		}else if(strstr(line,"OUTPUT(") != NULL){
			cp1 = strtok_r(line, " ()=\r\n\t", &cp3);  //"OUTPUT"
			cp1 = strtok_r(NULL, ")", &cp3); // "Name"
			circuit_add_output(ckt, cp1);
		}else if(strstr(line,"NOT") != NULL){
			cp1 = strtok_r(line, " ()=\r\n\t", &cp3);  // "Name" 
			tmpi = atoi(strtok_r(NULL, " ()=\r\n\t", &cp3)); // "(delay)"
			cp2 = strtok_r(NULL, " ()=\r\n\t", &cp3); // "NOT"
			cp2 = strtok_r(NULL, ")", &cp3); // inputs
//			printf("===> %s (%d) = NOT ( %s )\n", cp1, tmpi, cp2);
			circuit_add_gate_and_inputs(ckt, D_NOT, cp1, tmpi, cp2);
		}else if(strstr(line,"NAND") != NULL){
			cp1 = strtok_r(line, " ()=\r\n\t", &cp3);  // "Name" 
			tmpi = atoi(strtok_r(NULL, " ()=\r\n\t", &cp3)); // "(delay)"
			cp2 = strtok_r(NULL, " ()=\r\n\t", &cp3); // "NAND"
			cp2 = strtok_r(NULL, ")", &cp3); // inputs
//			printf("===> %s (%d) = NAND ( %s )\n", cp1, tmpi, cp2);
			circuit_add_gate_and_inputs(ckt, D_NAND, cp1, tmpi, cp2);
		}else if(strstr(line,"NOR") != NULL){
			cp1 = strtok_r(line, " ()=\r\n\t", &cp3);  // "Name" 
			tmpi = atoi(strtok_r(NULL, " ()=\r\n\t", &cp3)); // "(delay)"
			cp2 = strtok_r(NULL, " ()=\r\n\t", &cp3); // "NOR"
			cp2 = strtok_r(NULL, ")", &cp3); // inputs
//			printf("===> %s (%d) = NOR ( %s )\n", cp1, tmpi, cp2);
			circuit_add_gate_and_inputs(ckt, D_NOR, cp1, tmpi, cp2);
		}else if(strstr(line,"AND") != NULL){
			cp1 = strtok_r(line, " ()=\r\n\t", &cp3);  // "Name" 
			tmpi = atoi(strtok_r(NULL, " ()=\r\n\t", &cp3)); // "(delay)"
			cp2 = strtok_r(NULL, " ()=\r\n\t", &cp3); // "AND"
			cp2 = strtok_r(NULL, ")", &cp3); // inputs
//			printf("===> %s (%d) = AND ( %s )\n", cp1, tmpi, cp2);
			circuit_add_gate_and_inputs(ckt, D_AND, cp1, tmpi, cp2);
		}else if(strstr(line,"OR") != NULL){
			cp1 = strtok_r(line, " ()=\r\n\t", &cp3);  // "Name" 
			tmpi = atoi(strtok_r(NULL, " ()=\r\n\t", &cp3)); // "(delay)"
			cp2 = strtok_r(NULL, " ()=\r\n\t", &cp3); // "OR"
			cp2 = strtok_r(NULL, ")", &cp3); // inputs
//			printf("===> %s (%d) = OR ( %s )\n", cp1, tmpi, cp2);
			circuit_add_gate_and_inputs(ckt, D_OR, cp1, tmpi, cp2);
		}else if(strstr(line,"BUF") != NULL){
			cp1 = strtok_r(line, " ()=\r\n\t", &cp3);  // "Name" 
			tmpi = atoi(strtok_r(NULL, " ()=\r\n\t", &cp3)); // "(delay)"
			cp2 = strtok_r(NULL, " ()=\r\n\t", &cp3); // "BUF"
			cp2 = strtok_r(NULL, ")", &cp3); // inputs
//			printf("===> %s (%d) = BUF ( %s )\n", cp1, tmpi, cp2);
			circuit_add_gate_and_inputs(ckt, D_BUFFER, cp1, tmpi, cp2);
		}else{
			fprintf(stderr, "parse_circuit: Unrecognized directive: %s\n", line);
		}
end_parseline:
		getlinen(line, in, LINECAP);
	}
	circuit_finalize_outputs(ckt);
	return 0;

}

int load_header(Circuit *ckt, Pattern_parse_data *pdata, FILE *in){
	char line[512], *tok, *stat, tmps1[50], tmpc1;
	Gate *tmpgp;
	unsigned char *tmpucp;
//	Pattern_symbol *procsym;
	pdata->time = pdata->ntime = 0;

	pdata->insymn = 0;
	pdata->insyms = (Pattern_symbol*) malloc(ckt->inputn * sizeof(Pattern_symbol));
//	pdata->outsymn = 0;
//	pdata->outsyms = (Pattern_symbol*) malloc(ckt->outputn * sizeof(Pattern_symbol));
	// Construct input pattern header data
	getlinen(pdata->date, in, 49);
	getlinen(pdata->timescale, in, 49);
	getlinen(pdata->scope, in, 49);
	// Construct input symbol hash table
	getlinen(line, in, 511);
	while(1){
//		printf("-> %s\n", line);
		tok = strtok_r(line, " \t", &stat);  // $var
		if(strncmp(tok, "$var", 4) != 0)    // $upscope $end
			break;
		tok = strtok_r(NULL, " \t", &stat);  // wire/reg
		tok = strtok_r(NULL, " \t", &stat);  // 1
		tok = strtok_r(NULL, " \t", &stat);  // (symbol)
		strncpy(tmps1, tok, 49);
		tok = strtok_r(NULL, " \t", &stat);  // (gate name)
		if(strncmp(tok, "CLK", 4) == 0){    // if (gate name) == CLK
			fprintf(stderr, "clock detected! %s\n", tmps1);
			strncpy(pdata->clk.sym, tmps1, 19);
			pdata->clk.sym_hash = hash_string(tmps1);
		}else{                              // if not
			tmpgp = circuit_get_gate_by_name(ckt, tok);
			if(tmpgp == NULL && tmpgp->type != D_INPUT)
				fprintf(stderr, "Error parsing pattern file: Gate \"%s\" should exist and be a input\n", tok);
			assert(tmpgp != NULL);
			assert(GATE_TYPE(tmpgp->type) == D_INPUT);  // It should be a input gate
			strncpy(pdata->insyms[pdata->insymn].sym, tmps1, 19);
			pdata->insyms[pdata->insymn].sym_hash = hash_string(tmps1);
			pdata->insyms[pdata->insymn].g = tmpgp;
			++pdata->insymn;
		}
		getlinen(line, in, 511);
	}
	if(pdata->insymn != ckt->inputn)
		fputs("Inputs are not fully assigned in pattern file! Aborting...\n", stderr);
	assert(pdata->insymn == ckt->inputn);

	getlinen(line, in, 511);                // $enddefinitions $end
	
	/////////////////////
	// Input initial value
	////////////////////
	getlinen(line, in, 511);                // $dumpvars
	assert(strncmp(line, "$dumpvars", 9) == 0);

	read_and_load(ckt, pdata, in);

	getlinen(line, in, 511);
	if(line[0] == '#')
		sscanf(line + 1, "%lu", &pdata->ntime);
	
	fprintf(stderr, "Initial values loading done!\n");
//	fprintf(stderr, "#%lu... ", pdata->ntime);
}

int read_and_load(Circuit *ckt, Pattern_parse_data *pdata, FILE *in){
	static char line[512], tmpc1;
	Gate *tmpgp;
	unsigned char *tmpucp;
	int i;
	while(getlinen(line, in, 511) != EOF){
		if(line[0] == '#'){
			sscanf(line + 1, "%lu", &pdata->ntime);
//			fprintf(stderr, "#%lu... ", pdata->ntime, line+1);
			return 1;
		}
		if(strncmp(line, "$end", 4) == 0)
			return 1;
//		fprintf(stderr, "=> %s => %c - %s\n", line, line[0], line + 1);
		tmpgp = pattern_get_input_from_symbol(pdata, line + 1);
		if(tmpgp == NULL)
			tmpucp = &(pdata->clk.data);
		else
			tmpucp = tmpgp->data;
		switch(line[0]){
			case '0': *tmpucp = 0; break;
			case '1': *tmpucp = 1; break;
			case 'x': *tmpucp = 2; break;
			default:
				fprintf(stderr, "Value %c for signal %s not recognized!\n", tmpc1, (tmpgp ? tmpgp->name : "CLK"));
				assert(0);
		}
	}
	pdata->ntime = 999999;
	return 0;
}

int output_header(Circuit *ckt, Pattern_parse_data *pdata, FILE *out){
	// Easy! ;)
	int i;
	fputs(pdata->date, out);
	fputc('\n', out);
	fputs(pdata->timescale, out);
	fputc('\n', out);
	fputs(pdata->scope, out);
	fputc('\n', out);
	for(i=0; i<ckt->inputn; ++i)
		fprintf(out, "$var wire\t1 !%s\t%s $end\n", ckt->inputs[i].name, ckt->inputs[i].name);
#ifdef OUTPUT_ALL
	for(i=0; i<ckt->gaten; ++i)
		fprintf(out, "$var wire\t1 !%s\t%s $end\n", ckt->gates[i].name, ckt->gates[i].name);
#else
	for(i=0; i<ckt->outputn; ++i)
		fprintf(out, "$var wire\t1 !%s\t%s $end\n", ckt->outputs[i]->name, ckt->outputs[i]->name);
#endif
	fputs("$var reg\t1 CLK\tCLK $end\n", out);
	fputs("$upscope $end\n$enddefinitions $end\n", out);
	/////////////////////
	// Output initial value
	////////////////////
	fputs("$dumpvars\n", out);
	dump(ckt, pdata, out);
	fputs("$end\n", out);
}

int simulate(Circuit *ckt, Pattern_parse_data *pdata, FILE *in, FILE *out){
	int state, i;
	Gate *g, *maxg = ckt->gates + ckt->gaten;
	while(1){
		pdata->time = pdata->ntime;
//		fprintf(stderr, "#%lu... ", pdata->time);
		state = read_and_load(ckt, pdata, in);
		if(pdata->clk.data == 1)
			fprintf(out, "#%lu\n1CLK\n", pdata->time);
		else{
			for(g = ckt->gates; g != maxg; ++g)
				gate_evaluate(g, ckt);
			dump(ckt, pdata, out);
/*			for(g = ckt->gates; g != maxg; ++g)
				gate_pop_front(g);*/
			for(g = ckt->gates; g != maxg; ++g)
				gate_fill2(g, ckt);
			ckt->data_begin = GATE_DINDEX_CVT(ckt->data_begin + 1);
		}
		if(!state)
			break;
	}
	fputs("\nSimulation done!\n", stderr);
}

int simulate_pthread(Circuit *ckt, Pattern_parse_data *pdata, FILE *in, FILE *out){
	int state, i;
	Gate *g, *maxg = ckt->gates + ckt->gaten;
	GateEvalData *tdata = (GateEvalData*) malloc(NUM_THREADS * sizeof(GateEvalData));
	pthread_barrier_t barrier1, barrier2;
	pthread_barrier_init(&barrier1, NULL, NUM_THREADS + 1);
	pthread_barrier_init(&barrier2, NULL, NUM_THREADS + 1);
	for(i=0; i<NUM_THREADS; ++i){
		tdata[i].threadID = i;
		tdata[i].ckt = ckt;
		tdata[i].startg = ckt->gates + i;
		tdata[i].step = NUM_THREADS;
		tdata[i].stop = 0;
		tdata[i].barrier1 = &barrier1;
		tdata[i].barrier2 = &barrier2;
		pthread_create(&(tdata[i].thread), NULL, gate_batch_eval_worker, &(tdata[i]));
	}
	while(1){
		pdata->time = pdata->ntime;
		state = read_and_load(ckt, pdata, in);
//		fprintf(stderr, "#%lu... ", pdata->time);
		if(pdata->clk.data == 1)
			fprintf(out, "#%lu\n1CLK\n", pdata->time);
		else{
			pthread_barrier_wait(&barrier1);
//fputc('e', stderr);
			pthread_barrier_wait(&barrier2);
			dump(ckt, pdata, out);
			for(g = ckt->gates; g != maxg; ++g)
				gate_fill2(g, ckt);
			ckt->data_begin = GATE_DINDEX_CVT(ckt->data_begin + 1);
		}
		if(!state)
			break;
	}
	for(i=0; i<NUM_THREADS; ++i)
		tdata[i].stop = 1;
	pthread_barrier_wait(&barrier1);
	void *tmp;
	for(i=0; i<NUM_THREADS; ++i)
		pthread_join(tdata[i].thread, &tmp);
	fputs("\nSimulation done!\n", stderr);
}

Gate* pattern_get_input_from_symbol(Pattern_parse_data *pdata, const char *str){
	unsigned long hash = hash_string(str);
	int i;
	if(hash == pdata->clk.sym_hash)
		if(strncmp(str, pdata->clk.sym, 3) == 0)
			return NULL;
	for(i=0; i<pdata->insymn; ++i)
		if(hash == pdata->insyms[i].sym_hash)
			if(strncmp(str, pdata->insyms[i].sym, 49) == 0)
				return pdata->insyms[i].g;
	fprintf(stderr, "Input pattern symbol: %s not defined\n", str);
	assert(0);
}

int dump(Circuit *ckt, Pattern_parse_data *pdata, FILE *out){
	if(pdata->time)
		fprintf(out, "#%lu\n", pdata->time);    // time
	
	// Clock
	fprintf(out, "%cCLK\n", value_conv(pdata->clk.data));
	
	// the rest inputs and outputs
	int i;
	unsigned int dbegin = ckt->data_begin;
	Gate *g;
	for(i=0; i<ckt->inputn; ++i){
		g = &(ckt->inputs[i]);
		fprintf(out, "%c!%s\n", value_conv(g->data[dbegin]), g->name);
	}
#ifdef OUTPUT_ALL
	for(i=0; i<ckt->gaten; ++i){
		g = &(ckt->gates[i]);
		fprintf(out, "%c!%s\n", value_conv(g->data[dbegin]), g->name);
	}
#else
	for(i=0; i<ckt->outputn; ++i){
		g = ckt->outputs[i];
		fprintf(out, "%c!%s\n", value_conv(g->data[dbegin]), g->name);
	}
#endif
}

inline char value_conv(const unsigned char val){
	switch(val){
		case 0: return '0';
		case 1: return '1';
		case 2: return 'x';
		default: return '?';
	}
}

int getlinen(char *s, FILE *in, int len){
	int c;
	char cnt = 0, *str = s;
	while(1){
		c = fgetc(in);
		if(c == EOF || c == '\r' || c == '\n'/* || c == '\t'*/){
			if(cnt){
				*str = '\0';
				break;
			}
			if(c == EOF){
				*str = '\0';
				break;
			}
		}else{
			if(cnt == len-1){
				*str = '\0';
				break;
			}
				*(str++) = c;
			cnt++;
		}
	}
//	printf("-> %s\n", s);
	if(c == EOF)
		return EOF;
	return cnt;
}


