module LAB3(input CLK,
			input RST, 
			input IN_VALID,
			input [2:0] INPUT,
			output reg [5:0] OUT,
			output reg OUT_VALID);

reg [1:0] state;
reg [1:0] nstate;
parameter 	IDLE = 0,
			READ = 1,
			OUTPUT = 2;
reg [2:0] ibuf;
reg ivbuf;
reg [2:0] cnt;
reg [2:0] cnto;
reg [2:0] data [5:0];
reg [5:0] sum;

always @ (posedge CLK or posedge RST) begin
	if(RST)
		state <= IDLE;
	else
		state <= nstate;
end

always @ (posedge CLK or posedge RST) begin
	if(RST)
		ibuf <= 0;
	else	
		ibuf <= INPUT;
end

always @ (IN_VALID or OUT_VALID or posedge RST) begin
	if(RST)
		nstate = IDLE;
	else begin 
		case(state)
		IDLE:
			if(IN_VALID)
				nstate = READ;
			else
				nstate = state;
		READ:
			if(~IN_VALID)
				nstate = OUTPUT;
			else 
				nstate = state;
		OUTPUT:
			if(~OUT_VALID)
				nstate = IDLE;
			else
				nstate = state;
		default:
			nstate = state;
		endcase
	end
end

always @ (posedge CLK or posedge RST) begin
	if(RST || state == IDLE)
		cnt <= 0;
	else if(state == READ)
		cnt <= cnt + 1;
end

always @ (posedge CLK) begin
	if(state == READ)
		data[cnt] <= ibuf;
end

always @ (posedge CLK or posedge RST) begin
	if(RST || state == IDLE)
		sum <= 0;
	else if(state == READ)
		sum <= sum + ibuf;
end

always @ (posedge CLK or posedge RST) begin
	if(RST || state == IDLE)
		cnto <= 0;
	else if(state == OUTPUT) begin
		if(cnto != cnt + 1)
			cnto <= cnto + 1;
//		else
//			cnto <= 0;
	end
end

always @ (posedge CLK or posedge RST) begin
	if(RST || state == IDLE)
		OUT_VALID <= 0;
	else if(state == OUTPUT) begin
		if(cnto != cnt + 1)
			OUT_VALID <= 1;
		else
			OUT_VALID <= 0;
	end
end

always @ (posedge CLK) begin
	if(state != OUTPUT)
		OUT <= 0;
	else begin
		if(cnto < cnt)
			OUT <= data[cnto];
		else if(cnto == cnt)
			OUT <= sum;
		else
			OUT <= 0;
	end
end

endmodule
