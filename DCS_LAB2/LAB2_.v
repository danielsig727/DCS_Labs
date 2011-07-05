module LAB2(//input
           input CLK,
           input RST, 
           //output
           output reg [5:0] OUT);
//-----------input output -------------//           

always @ (posedge CLK or posedge RST) begin
	if(RST)
		OUT <= 6'b000001;
	else begin
		for(int i=1; i<=5; i++)
			OUT[i] <= OUT[i-1];
		OUT[0] <= OUT[5];
	end
end

endmodule


