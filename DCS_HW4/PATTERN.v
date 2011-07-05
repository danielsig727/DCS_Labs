//############################################################################


module PATTERN(//OUTPUT
               RST,
               CLK,
               IN_VALID,
               INPUT, 
               //INPUT 
               OUT,
               OUT_VALID);
//---------------------------------------------------------------------//
output  RST, CLK, IN_VALID;
output  [2:0]INPUT;

input   [2:0] OUT;
input   OUT_VALID;

//---------------------------------------------------------------------//

//---------------------------------------------------------------------//

reg CLK, RST, IN_VALID;
reg [2:0]INPUT;
integer i;
parameter CYCLE=1.0, number=5, number2=10, number3=7,number4=9;


always #(CYCLE/2.0) CLK=~CLK;
    initial begin 
        CLK=1'b1;
        RST = 1'b0;
        IN_VALID =1'b0;
        INPUT=3'b0;
    end

   initial begin
                    @(negedge CLK) RST =1'b1;
                    @(negedge CLK) RST =1'b0;
        for(i=1;i<=number;i=i+1)
                    @(negedge CLK);
                    
                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd5; 

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd3;

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd4;

                   @(negedge CLK) IN_VALID = 1'b0; INPUT=3'd0;

        for(i=1;i<=number2;i=i+1)
                    @(negedge CLK);

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd5;

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd3;

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd4;

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd7;

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd2;

                    @(negedge CLK) IN_VALID = 1'b0; INPUT=3'd0;



        for(i=1;i<=number3;i=i+1)
                    @(negedge CLK);


                    @(negedge CLK);

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd2;

                    @(negedge CLK) IN_VALID = 1'b0; INPUT=3'd0;



        for(i=1;i<=number4;i=i+1)
                    @(negedge CLK);

        $finish;


    end     

endmodule


