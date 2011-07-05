
module Final(
           CLK,
           RST,
           IN_VALID,
           INPUT,
           OUT,
           OUT_VALID
               );
//-----------input output -------------//           
input RST, CLK, IN_VALID;
input [2:0] INPUT;
output reg OUT;
output reg OUT_VALID;

//--------------------------------------//

parameter IDLE = 0, READ0 = 1, READ1 = 2, READ2 = 3, OUTPUT = 4;

reg [2:0] state;
reg [2:0] nstate;
reg [2:0] data0;
reg [2:0] data1;
reg [2:0] data2;

wire [2:0] check;

assign check[0] = ({1'b0, data1} + {1'b0, data2}) > {1'b0, data0};
assign check[1] = ({1'b0, data0} + {1'b0, data2}) > {1'b0, data1};
assign check[2] = ({1'b0, data0} + {1'b0, data1}) > {1'b0, data2};

always @ (posedge CLK or RST) 
	if(RST)
		state <= IDLE;
	else
		state <= nstate;

always @ * begin
	if(RST)
		nstate = IDLE;
	else begin
		case(state)
			IDLE:
				if(IN_VALID) nstate = READ0;
				else nstate = state;
			READ0: nstate = READ1;
			READ1: nstate = READ2;
			READ2: nstate = OUTPUT;
			OUTPUT: nstate = IDLE;
		endcase
	end
end


always @ (posedge CLK)
	if(state == IDLE && IN_VALID)
		data0 <= INPUT;

always @ (posedge CLK)
	if(state == READ0)
		data1 <= INPUT;

always @ (posedge CLK)
	if(state == READ1) begin
		data2 <= INPUT;
	end

always @ (posedge CLK or RST) begin
	if(state == READ2)
		OUT_VALID <= 1;
	else 
		OUT_VALID <= 0;
end

always @ (posedge CLK or RST) begin
	if(state == READ2)
		OUT <= &check;
	else
		OUT <= 0;
end


endmodule
