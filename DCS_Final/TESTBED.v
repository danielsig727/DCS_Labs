
`timescale 1ns/10ps
`include "PATTERN.v"
//`ifdef RTL
  `include "Final.v"
//`endif
	  		  	
module TESTBED;
  wire CLK, RST, IN_VALID, OUT_VALID;
  wire [2:0]INPUT;
  wire OUT;    
    
initial begin
  //`ifdef RTL
    $fsdbDumpfile("Final.fsdb");
    $fsdbDumpvars();
  //`endif

end
  //`ifdef RTL
  Final     u_LAB    (
                    .CLK(CLK),
                    .RST(RST), 
                    .IN_VALID(IN_VALID),
                    .INPUT(INPUT),
                    .OUT(OUT),
                    .OUT_VALID(OUT_VALID));
  //`endif                    

  PATTERN u_PATTERN(
                    .CLK(CLK),
                    .RST(RST),
                    .IN_VALID(IN_VALID),
                    .INPUT(INPUT),
                    .OUT(OUT),
                    .OUT_VALID(OUT_VALID));
  
  
endmodule
