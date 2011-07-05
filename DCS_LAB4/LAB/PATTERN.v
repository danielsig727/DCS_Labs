//############################################################################


module PATTERN(//OUTPUT
               CLK,
               INPUT1,
               INPUT2, 
               //INPUT 
               OUT);
//---------------------------------------------------------------------//
output   CLK;
output  [3:0]INPUT1,INPUT2;

input   [5:0] OUT;

//---------------------------------------------------------------------//


reg CLK, RST;
reg [3:0]INPUT1, INPUT2;
reg[5:0] sim_OUT;
integer i, j;
parameter CYCLE = 1;

always #(CYCLE/2.0) CLK=~CLK;
    initial 
        begin 
        CLK=1'b1;
        INPUT1=4'b0;
        INPUT2=4'b0;

        #4; 

		for(i=0; i<16; i++) begin
			for(j=0; j<16; j++) begin
				@(negedge CLK) INPUT1 = i; INPUT2=j;
		        sim_OUT= INPUT1+INPUT2;
        		#1;
		        $write("INPUT1= %x INPUT2= %x  OUT= %x sim_OUT= %x",INPUT1, INPUT2, OUT,sim_OUT);
				if(OUT != sim_OUT) begin
					$write(" <= FAILED!!! QQ\n");
					$finish;
				end else
					$write("\n");
			end
		end




        $finish;


        end     

endmodule


