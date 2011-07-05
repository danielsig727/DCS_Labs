
module P5_12(//input
	input CLK,
    input x_in,
    input reset, 
           //output
    output wire [1:0] OUT);
//-----------input output -------------//           

reg [1:0] state;

always @ (posedge CLK or reset) begin
	if(reset)
		state <= 0;
	else if(x_in)
		state <= state + 1;
end

assign OUT[1] = (state == 2) || (state == 3);
assign OUT[0] = (state == 1) || (state == 2);

endmodule

