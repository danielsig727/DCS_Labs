module LAB3(input CLK,
			input RST, 
			input IN_VALID,
			input [2:0] INPUT,
			output reg [2:0] OUT,
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
		endcase
	end
end

always @ (posedge CLK or posedge RST) begin
	if(RST) begin
		cnt <= 0;
		cnto <= 0;
		OUT <= 0;
		OUT_VALID <= 0;
	end else begin
		case(state)
		IDLE: begin
			cnt <= 0;
			cnto <= 0;
		end
		READ: begin
			data[cnt] <= ibuf;
			cnt <= cnt + 1;
		end
		OUTPUT: begin
			if(cnto != cnt) begin
				OUT_VALID <= 1;
				OUT <= data[cnto];
				cnto <= cnto + 1;
			end else begin
				OUT_VALID <= 0;
				OUT <= 0;
//				cnto <= 0;
			end
		end
		endcase
	end
end

endmodule
