
`timescale 1ns/10ps
`include "PATTERN.v"
//`ifdef RTL
  `include "LAB1.v"
//`endif
	  		  	
module TESTBED;
  wire [8:0] IN;
  wire OUT;    
    
initial begin
  //`ifdef RTL
    $fsdbDumpfile("LAB1.fsdb");
    $fsdbDumpvars();
  //`endif

end
  //`ifdef RTL
  LAB1     u_LAB    (
                    .IN(IN), 
                    .OUT(OUT));
  //`endif                    

  PATTERN u_PATTERN(
                    .IN(IN),
                    .OUT(OUT));
  
  
endmodule
