module P26f(input [1:0] S,
		input [3:0] D,
		input CLK,
		output reg [3:0] Q);

always @ (CLK) begin
	case(S)
		2'b00: Q <= Q;
		2'b01: Q <= ~Q;
		2'b10: Q <= 0;
		2'b11: Q <= D;
	endcase
end

endmodule
