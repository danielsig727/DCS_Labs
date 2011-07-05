//############################################################################


module PATTERN(//OUTPUT
               RST,
               CLK, 
               //INPUT 
               OUT);
//---------------------------------------------------------------------//
output  RST, CLK;

input   [5:0] OUT;

//---------------------------------------------------------------------//

//---------------------------------------------------------------------//

reg CLK, RST;
integer i;
parameter CYCLE=1.0, number=15;


always #(CYCLE/2.0) CLK=~CLK;
    initial begin 
        CLK=1'b1;
        RST = 1'b0;
    end

   initial begin
                    @(negedge CLK) RST =1'b1;
                    @(negedge CLK) RST =1'b0;
        for(i=1;i<=number;i=i+1)
                    @(negedge CLK);
                    
        $finish;


    end     

endmodule


