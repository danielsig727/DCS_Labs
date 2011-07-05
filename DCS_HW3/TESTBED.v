`timescale 1ns/10ps
`include "PATTERN.v"
//`ifdef RTL
  `include "5_12a.v"
//`endif
	  		  	
module TESTBED;
  wire x_in, CLK, reset;
  wire [1:0]OUT;    
    
initial begin
  //`ifdef RTL
    $fsdbDumpfile("P5_12.fsdb");
    $fsdbDumpvars();
  //`endif

end
  //`ifdef RTL
  P5_12     u_5_12    (
                    .x_in(x_in),
                    .CLK(CLK),
                    .reset(reset), 
                    .OUT(OUT));
  //`endif                    

  PATTERN u_PATTERN(
                    .x_in(x_in),
                    .CLK(CLK),
                    .reset(reset),
                    .OUT(OUT));
  
  
endmodule
