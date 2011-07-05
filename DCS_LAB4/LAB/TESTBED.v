
`timescale 1ns/10ps
`include "PATTERN.v"
//`ifdef RTL
  `include "LAB4.v"
//`endif
	  		  	
module TESTBED;
  wire CLK;
  wire [3:0]INPUT1,INPUT2;
  wire [5:0]OUT;    
    
initial begin
  //`ifdef RTL
    $fsdbDumpfile("LAB4.fsdb");
    $fsdbDumpvars();
  //`endif

end
  //`ifdef RTL
  LAB4     u_LAB    (
                    .CLK(CLK),
                    .INPUT1(INPUT1),
                    .INPUT2(INPUT2),
                    .OUT(OUT));
  //`endif                    

  PATTERN u_PATTERN(
                    .CLK(CLK),
                    .INPUT1(INPUT1),
                    .INPUT2(INPUT2),
                    .OUT(OUT));
  
  
endmodule
