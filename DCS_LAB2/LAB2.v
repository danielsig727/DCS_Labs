module DEC(input [2:0] S,
	output reg [5:0] OUT);
always @ (S) begin
	OUT = 0;
	OUT[S] = 1;
end
endmodule

module LAB2(//input
           input CLK,
           input RST, 
           //output
           output [5:0] OUT);
//-----------input output -------------//           

reg [2:0] count;
DEC haha(.S(count), .OUT(OUT));

always @ (posedge CLK or posedge RST) begin
	if(RST)
		count <= 0;
	else
		count <= (count == 5) ? 0 : count + 1;
end


endmodule
