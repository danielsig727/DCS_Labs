module LAB3(input CLK,
			input RST, 
			input IN_VALID,
			input [2:0] INPUT,
			output reg [5:0] OUT,
			output reg OUT_VALID);

parameter IDLE = 0, READ = 1, OUTPUT = 2;
reg [2:0] state;
reg [2:0] nstate;
reg [2:0] data0;
reg [2:0] data1;
reg [2:0] data2;
reg [2:0] data3;
reg [2:0] data4;
reg [5:0] sum;
reg [3:0] incnt;
reg [3:0] outcnt;

always @ (posedge CLK or RST)
	if(RST)
		state <= 0;
	else
		state <= nstate;

always @ * begin
	if(RST)
		nstate <= 0;
	else begin
		case(state)
			IDLE: 
				if(IN_VALID) nstate = READ;
				else nstate = IDLE;
			READ:
				if(~IN_VALID) nstate = OUTPUT;
				else nstate = READ;
			OUTPUT:
				if(incnt + 1 == outcnt) nstate = IDLE;
				else nstate = OUTPUT;
		endcase
	end
end

always @ (posedge CLK)
	if(state == IDLE && IN_VALID) begin
		data0 <= INPUT;
		sum <= INPUT;
		incnt <= 1;
	end

always @ (posedge CLK)
	if(state == READ & IN_VALID) begin
		case(incnt)
			0: data0 <= INPUT;
			1: data1 <= INPUT;
			2: data2 <= INPUT;
			3: data3 <= INPUT;
			4: data4 <= INPUT;
		endcase
//		data[incnt] <= INPUT;
		sum <= sum + INPUT;
		incnt <= incnt + 1;
	end

always @ (posedge CLK)
	if(state == READ & ~IN_VALID) begin
		outcnt <= 0;
	end

always @ (posedge CLK)
	if(state == OUTPUT) begin
		if(outcnt < incnt) begin
			OUT_VALID <= 1;
//			OUT <= data[outcnt];
			case(outcnt)
				0: OUT <= data0;
				1: OUT <= data1;
				2: OUT <= data2;
				3: OUT <= data3;
				4: OUT <= data4;
			endcase
			outcnt <= outcnt + 1;
		end else if(outcnt == incnt) begin
			OUT_VALID <= 1;
			OUT <= sum;
			outcnt <= outcnt + 1;
		end
	end


always @ (posedge CLK or RST)
	if(RST || ((state == OUTPUT) && (outcnt == incnt + 1))) begin
		OUT_VALID <= 0;
		OUT <= 0;
	end


endmodule
