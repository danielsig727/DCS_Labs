#ifndef D_CKT_H
#define D_CKT_H

#define MAX_DELAY 90
#define MAX_NAME_LEN 10
#define DEFAULT_INPUT_NUM 50

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <pthread.h>

//enum _GATE_TYPE {STATIC_0, STATIC_1, NOT, NAND, NOR , INPUT};
#define D_STATIC_0           0x01
#define D_STATIC_1           0x02
#define D_NOT                0x03
#define D_NAND               0x04
#define D_NOR                0x05
#define D_AND                0x06
#define D_OR                 0x07
#define D_INPUT              0x08
#define D_BUFFER             0x09

#define D_OUTPUT_FLAG        0x80
#define D_TYPE_MASK          0x7f
#define GATE_TYPE(t)         ((t) & D_TYPE_MASK)
#define GATE_IS_OUTPUT(t)    ((t) & (~D_TYPE_MASK))

#define GATE_DINDEX_CVT(x)   (((x) >= MAX_DELAY) ? ((x) % MAX_DELAY) : (x))

#define GATE_GET_DATA(g, x)  (((g)->type == D_INPUT) ? ((g)->data[0]) : ((g)->data[x]))

typedef unsigned char Gate_type_t;

typedef struct _Gate Gate;
struct _Gate{
    Gate_type_t type;
    char name[MAX_NAME_LEN+1];
	unsigned long name_hash;
    Gate **inputs;
    int inputn, inputcap;
    int delay;
    unsigned char data[MAX_DELAY];
};

typedef struct _Circuit Circuit;
struct _Circuit{
    char name[MAX_NAME_LEN+1];
    int gaten, gatecap, notn, nandn, norn;
    Gate* gates;
    int inputn, inputcap;
    Gate* inputs;
    char output_names[20000];
	int outputn, outputcap;
    Gate** outputs;
	unsigned int data_begin;
};

enum _D_CIRC_ERR {SUCCESS, FAIL};
typedef enum _D_CIRC_ERR D_circ_err_t;

int circuit_init(Circuit *ckt, const char *name, int gaten, int inputn, int outputn);
void circuit_destroy(Circuit *ckt);
void circuit_print(Circuit *ckt, FILE *out);

void circuit_add_output(Circuit *ckt, const char *name);
void circuit_finalize_outputs(Circuit *ckt);
Gate* circuit_add_gate(Circuit *ckt, Gate_type_t type, const char* name, int delay);
Gate* circuit_get_gate_by_name(Circuit *ckt, const char* name);
Gate** gate_extend_input_list(Gate *g);

Gate* gate_add_input(Gate *g, Gate *in);
Gate* gate_add_input_by_name(Gate *g, Circuit *ckt, const char *name);
Gate* circuit_add_gate_and_inputs(Circuit *ckt, Gate_type_t type, const char* name, int delay, const char *inputs); //inputs saperated by blank

Gate* gate_evaluate(Gate *g, Circuit *ckt);
Gate* gate_pop_front(Gate *g, Circuit *ckt);
Gate* gate_fill2(Gate *g, Circuit *ckt);


typedef struct _GateEvalData GateEvalData;
struct _GateEvalData{
	pthread_t thread;
	int threadID;
	Circuit *ckt;
	pthread_barrier_t *barrier1, *barrier2;
	Gate *startg;
	unsigned int step;
	int stop;
};

void* gate_batch_eval_worker(void *data);

#endif
