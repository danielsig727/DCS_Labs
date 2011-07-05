
`timescale 1ns/10ps
`include "PATTERN.v"
//`ifdef RTL
  `include "LAB2.v"
//`endif
	  		  	
module TESTBED;
  wire CLK, RST;
  wire [5:0]OUT;    
    
initial begin
  //`ifdef RTL
    $fsdbDumpfile("LAB2.fsdb");
    $fsdbDumpvars();
  //`endif

end
  //`ifdef RTL
  LAB2     u_LAB    (
                    .CLK(CLK),
                    .RST(RST), 
                    .OUT(OUT));
  //`endif                    

  PATTERN u_PATTERN(
                    .CLK(CLK),
                    .RST(RST),
                    .OUT(OUT));
  
  
endmodule
