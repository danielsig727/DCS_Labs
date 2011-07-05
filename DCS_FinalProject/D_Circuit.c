#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <pthread.h>
#include "D_Circuit.h"
#include "D_Hash.h"

int circuit_init(Circuit *ckt, const char *name, int gaten, int inputn, int outputn){
    strncpy(ckt->name, name, MAX_NAME_LEN);
    ckt->gatecap = gaten;
    ckt->gaten = ckt->nandn = ckt->norn = ckt->notn = ckt->inputn = ckt->outputn = 0;
    ckt->gates = (Gate*) malloc(sizeof(Gate) * ckt->gatecap);
#ifdef DEBUG
	assert(ckt->gates != NULL);
#endif
    if(ckt->gates == NULL)
        return 1;
    ckt->inputcap = inputn;
	ckt->inputn = 0;
    ckt->inputs = (Gate*) malloc(sizeof(Gate) * ckt->inputcap);
#ifdef DEBUG
	assert(!(ckt->inputcap != 0 && ckt->inputs == NULL));
#endif
    if(ckt->inputcap != 0 && ckt->inputs == NULL)
        return 2;

	ckt->output_names[0] = '\0';
    ckt->outputcap = outputn;
	ckt->outputn = 0;
    ckt->outputs = (Gate**) malloc(sizeof(Gate*) * ckt->outputcap);
#ifdef DEBUG
	assert(!(ckt->outputcap != 0 && ckt->outputs == NULL));
#endif
    if(ckt->outputcap != 0 && ckt->outputs == NULL)
        return 3;
	ckt->data_begin = 0;
}

void circuit_destroy(Circuit *ckt){
    int i;
    for(i=0; i<ckt->inputn; ++i){
        free((ckt->inputs + i)->name);
    }
    for(i=0; i<ckt->outputn; ++i){
        free(ckt->outputs);
    }
    for(i=0; i<ckt->gaten; ++i){
        free((ckt->gates + i)->name);
        free((ckt->gates + i)->inputs);
    }
}

void circuit_print(Circuit *ckt, FILE *out){
    int i, j;
    Gate *g;
    fputs("==== Circuit Info ====\n", out);
    fprintf(out, "Name: %s\n", ckt->name);
    fprintf(out, "# of inputs: %d (Util. %d)\n", ckt->inputcap, ckt->inputn);
    fprintf(out, "# of outputs: %d (Util. %d)\n", ckt->outputcap, ckt->outputn);
    fprintf(out, "# of gates: %d (Util. %d / NAND: %d / NOR: %d / NOT: %d)\n", ckt->gatecap, ckt->gaten, ckt->nandn, ckt->norn, ckt->notn);
    fputc('\n', out);
    for(i=0; i<ckt->inputn; ++i){
        g = ckt->inputs + i;
        fprintf(out, "Input %02d: %s\n", i, g->name);
        fprintf(out, "\tData: %1d\n", (g->data)[0]);
    }
    for(i=0; i<ckt->outputn; ++i){
        g = ckt->outputs[i];
        fprintf(out, "Output %02d: %s\n", i, g->name);
    }
    for(i=0; i<ckt->gaten; ++i){
        g = ckt->gates + i;
        fprintf(out, "Gate %02d: %s (%lu)\n", i, g->name, g->name_hash);
        fputs("\tType:", out);
        switch(GATE_TYPE(g->type)){
            case D_STATIC_0:
                fputs("STATIC_0", out);
                break;
            case D_STATIC_1:
                fputs("STATIC_1", out);
                break;
            case D_NAND:
                fputs("NAND", out);
                break;
            case D_NOR:
                fputs("NOR", out);
                break;
            case D_AND:
                fputs("AND", out);
                break;
            case D_OR:
                fputs("OR", out);
                break;
            case D_NOT:
                fputs("NOT", out);
                break;
            case D_BUFFER:
                fputs("BUFFER", out);
                break;
            default:
                fputs("UNKNOWN!", out);
        }
		if(GATE_IS_OUTPUT(g->type))
			fputs(" + OUTPUT\n", out);
		else
			fputc('\n', out);
        fprintf(out, "\tDelay: %d", g->delay);
        fprintf(out, "\tInputs: (%d/%d) ", g->inputn, g->inputcap);
        for(j=0; j<g->inputn; ++j){
            fprintf(out, "%s, ", (g->inputs)[j]->name);
        }
        fputc('\n', out);
        fputs("\tData: ", out);
        for(j=0; j<MAX_DELAY; ++j){
            fprintf(out, "%1d", (int) (g->data)[j]);
            if(j && (j%80 == 0))
                fputc('\n', out);
        }
		fputs("\n\t      ", out);
		for(j=0; j<ckt->data_begin; ++j)
			fputc(' ', out);
		fputs("|", out);
        fputs("\n\n", out);
    }
    fputs("==== End of Report ====\n", out);
}

void circuit_add_output(Circuit *ckt, const char *name){
	strncat(ckt->output_names, name, 11);
	strncat(ckt->output_names, "/", 2);
}

void circuit_finalize_outputs(Circuit *ckt){
	Gate *g;
	char *tmp, *stat;
	tmp = strtok_r(ckt->output_names, "/", &stat);
	while(tmp != NULL){
		g = circuit_get_gate_by_name(ckt, tmp);
		if(g == NULL) 
			fprintf(stderr, "Error! Output Gate \"%s\" not found! (circuit_finalize_outputs)\n", tmp);
		assert(g != NULL);
		ckt->outputs[ckt->outputn] = g;
		g->type |= D_OUTPUT_FLAG;
		ckt->outputn++;
		tmp = strtok_r(NULL, "/", &stat);
	}
}

Gate* circuit_add_gate(Circuit *ckt, Gate_type_t type, const char* name, int delay){
/*	static int md = 0;
	if(delay > md){
		md = delay;
		fprintf(stderr, "%d ", md);
	}*/
    Gate *procg;
    if(type == D_INPUT){
        if(ckt->inputn == ckt->inputcap)
            return NULL;
        procg = &((ckt->inputs)[ckt->inputn]);
        procg->type = D_INPUT;
        strncpy(procg->name, name, MAX_NAME_LEN);
		procg->name_hash = hash_string(name);
        procg->delay = 0;
        ckt->inputn++;
    }else {
        if(ckt->gaten == ckt->gatecap)
            return NULL;
        procg = &((ckt->gates)[ckt->gaten]);
        procg->type = type;
        strcpy(procg->name, name);
		procg->name_hash = hash_string(name);
        procg->delay = delay;
        procg->inputn = 0;
        procg->inputcap = DEFAULT_INPUT_NUM;
        procg->inputs = (Gate**) malloc(DEFAULT_INPUT_NUM * sizeof(Gate*));
        ckt->gaten++;
        switch(type){
            case D_NAND:
                ckt->nandn++;
                break;
            case D_NOR:
                ckt->norn++;
                break;
            case D_NOT:
                ckt->notn++;
                break;
        }
		memset(procg->data, 2, MAX_DELAY);
    }
    return procg;
}

Gate* circuit_get_gate_by_name(Circuit *ckt, const char* name){
    int i;
	unsigned long hash = hash_string(name);
    for(i=0; i<ckt->inputn; ++i)
		if((ckt->inputs + i)->name_hash == hash)
	        if(strncmp((ckt->inputs + i)->name, name, MAX_NAME_LEN) == 0)
    	        return &(ckt->inputs)[i];
/*    for(i=0; i<ckt->outputn; ++i)
        if(strncmp((ckt->outputs + i)->name, name, MAX_NAME_LEN) == 0)
            return &(ckt->outputs)[i];*/
	Gate *maxg = ckt->gates + ckt->gaten;
	Gate *g;
    for(g=ckt->gates; g!=maxg; ++g)
		if(g->name_hash == hash)
	        if(strncmp(g->name, name, MAX_NAME_LEN) == 0)
	            return g;

    return NULL;
}

Gate* gate_add_input(Gate *g, Gate *in){
    if(g->inputn == g->inputcap )
        gate_extend_input_list(g);
    g->inputs[g->inputn] = in;
    g->inputn ++;
    return g;
}


Gate* gate_add_input_by_name(Gate *g, Circuit *ckt, const char *name){
    Gate *in = circuit_get_gate_by_name(ckt, name);
	if(in != NULL)
    	return gate_add_input(g, in);
	else{

#ifdef DEBUG
		assert(in != NULL);
#endif 
		fprintf(stderr, "gate_add_input_by_name error: input gate \"%s\" not found!\n", name);
		return NULL;
	}
}

Gate* circuit_add_gate_and_inputs(Circuit *ckt, Gate_type_t type, const char* name, int delay, const char *inputs){
	Gate *g;
	g = circuit_add_gate(ckt, type, name, delay);
	assert(g != NULL);
	char args[1024], *in, *stat;
	strncpy(args, inputs, 1023);
	in = strtok_r(args, ", \t\r\n", &stat);
	while(in != NULL){
		gate_add_input_by_name(g, ckt, in);
		in = strtok_r(NULL, ", \t\r\n", &stat);
	}
	return g;
}

Gate** gate_extend_input_list(Gate *g){
//    Gate **newl = (Gate**) malloc(g->inputcap * 2 * sizeof(Gate*));
    Gate **newl = (Gate**) realloc(g->inputs, g->inputcap * 2 * sizeof(Gate*));
	assert(newl != NULL);
    if(newl != NULL){
        g->inputs = newl;
        g->inputcap *= 2;
    }else{
        free(g->inputs);
    }
    return g->inputs;
}

Gate* gate_evaluate(Gate *g, Circuit *ckt){
	int i;
	unsigned char curr;
	unsigned int dbegin = ckt->data_begin;
	switch(GATE_TYPE(g->type)){
		case D_INPUT:
		case D_STATIC_0:
		case D_STATIC_1:
			return g;
			break;
		case D_NOT:
			if(GATE_GET_DATA(g->inputs[0], dbegin) != 2)
				g->data[GATE_DINDEX_CVT(dbegin + g->delay)] = !GATE_GET_DATA(g->inputs[0], dbegin);
			else
				g->data[GATE_DINDEX_CVT(dbegin + g->delay)] = 2;
			break;
		case D_BUFFER:
			g->data[GATE_DINDEX_CVT(dbegin + g->delay)] = GATE_GET_DATA(g->inputs[0], dbegin);
			break;
		case D_NAND:
		case D_AND:
			curr = 1;
			for(i=0; i<g->inputn; ++i){
				if(GATE_GET_DATA(g->inputs[i], dbegin) == 0){
					curr = 0;
					break;
				}
				if(GATE_GET_DATA(g->inputs[i], dbegin) == 2){
					curr = 2;
//					break;
				}

			}
			if(curr != 2)
				g->data[GATE_DINDEX_CVT(dbegin + g->delay)] = (GATE_TYPE(g->type) == D_NAND) ? (!curr) : curr;
			else
				g->data[GATE_DINDEX_CVT(dbegin + g->delay)] = 2;

			break;

		case D_NOR:
		case D_OR:
			curr = 0;
			for(i=0; i<g->inputn; ++i){
				if(GATE_GET_DATA(g->inputs[i], dbegin) == 1){
					curr = 1;
					break;
				}
				if(GATE_GET_DATA(g->inputs[i], dbegin) == 2){
					curr = 2;
				}
			}
			if(curr != 2)
				g->data[GATE_DINDEX_CVT(dbegin + g->delay)] = (GATE_TYPE(g->type) == D_NOR) ? (!curr) : curr;
			else
				g->data[GATE_DINDEX_CVT(dbegin + g->delay)] = 2;
			break;
		default:
			fprintf(stderr, "Eval error in gate \"%s\": tpye= %x\n", g->name, g->type);
			circuit_print(ckt, stderr);
			assert(0);
	}

	return g;
}
Gate* gate_pop_front(Gate *g, Circuit *ckt){
	if(g->type == D_INPUT)
		return g;
	int i;
	for(i=0; i<MAX_DELAY - 1; ++i)
		g->data[i] = g->data[i+1];
	g->data[MAX_DELAY - 1] = 2;
	return g;
}

Gate* gate_fill2(Gate *g, Circuit *ckt){
//	if(g->type == D_INPUT)
//		return g;
	g->data[ckt->data_begin] = 2;
	return g;
}

void* gate_batch_eval_worker(void *data){
	GateEvalData *d = (GateEvalData*) data;
	Gate *g, *maxg = d->ckt->gates + d->ckt->gaten;
//	fputc('c', stderr);
	while(1){
		pthread_barrier_wait(d->barrier1);
//		fputc('s', stderr);
		if(d->stop)
			return NULL;
		for(g = d->startg; g < maxg; g += d->step){
			gate_evaluate(g, d->ckt);
//			fprintf(stderr, "%d ", g - d->ckt->gates);
		}
		pthread_barrier_wait(d->barrier2);
	}
}
