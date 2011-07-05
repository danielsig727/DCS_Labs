//############################################################################


module PATTERN(//OUTPUT
               CLK,
               reset,
               x_in, 
               //INPUT 
               OUT);
//---------------------------------------------------------------------//
output  x_in, CLK, reset;

input [1:0]  OUT;


//---------------------------------------------------------------------//

reg CLK;
reg x_in, reset;
parameter CYCLE=1.0;


always #(CYCLE/2.0) CLK=~CLK;
    initial begin 
        CLK=1'b1;
        x_in = 1'b0;
        reset = 1'b0;
    end

    initial begin
        begin
            @(negedge CLK)  reset=1'b0;
            @(negedge CLK)  reset=1'b1;
            @(negedge CLK)  reset=1'b0;
            @(negedge CLK)  x_in=1'b1;
            @(negedge CLK) ;
            @(negedge CLK) ;
            @(negedge CLK) ;
            @(negedge CLK) ;
            @(negedge CLK) ;
            @(negedge CLK)  x_in=1'b0;
            @(negedge CLK) ;
            @(negedge CLK) ;
            @(negedge CLK) ;
            @(negedge CLK)  x_in=1'b1;
            @(negedge CLK) ;
            @(negedge CLK) ;
            @(negedge CLK) ;


            $finish;
        end         


    end     

endmodule


