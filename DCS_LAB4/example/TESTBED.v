
`timescale 1ns/10ps
`include "PATTERN.v"
//`ifdef RTL
  `include "LAB3.v"
//`endif
	  		  	
module TESTBED;
  wire CLK, RST, IN_VALID, OUT_VALID;
  wire [2:0]INPUT;
  wire [5:0]OUT;    
    
initial begin
  //`ifdef RTL
    $fsdbDumpfile("LAB3.fsdb");
    $fsdbDumpvars();
  //`endif

end
  //`ifdef RTL
  LAB3     u_LAB    (
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
