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

input    OUT;
input   OUT_VALID;

//---------------------------------------------------------------------//

//---------------------------------------------------------------------//

reg CLK, RST, IN_VALID;
reg [2:0]INPUT;
integer i;
parameter CYCLE=1.0;


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
                    #5;
 
                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd7; 

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd7;

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd7;

                    @(negedge CLK) IN_VALID = 1'b0; INPUT=3'd0;

                    for(i=0;i<8;i=i+1)
                        begin
                            @(negedge CLK)
                            if((OUT_VALID==1'b1)&(OUT!=1))
                            begin
                                $display("P1 Error\n");
//                                $finish;
                            end 
                        end
                    
                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd1;

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd2;

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd1;

                    @(negedge CLK) IN_VALID = 1'b0; INPUT=3'd0;

                    for(i=0;i<7;i=i+1)
                        begin
                            @(negedge CLK)
                            if((OUT_VALID==1'b1)&(OUT!=0))
                            begin
                                $display("P2 Error\n");
//                                $finish;
                            end
                        end

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd3;

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd1;

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd1;

                    @(negedge CLK) IN_VALID = 1'b0; INPUT=3'd0;

                    for(i=0;i<7;i=i+1)
                        begin
                            @(negedge CLK)
                            if((OUT_VALID==1'b1)&(OUT!=0))
                            begin
                                $display("P3 Error\n");
//                                $finish;
                            end
                        end

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd3;

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd4;

                    @(negedge CLK) IN_VALID = 1'b1; INPUT=3'd6;

                    @(negedge CLK) IN_VALID = 1'b0; INPUT=3'd0;

                  
                    for(i=0;i<7;i=i+1)
                        begin
                            @(negedge CLK)
                            if((OUT_VALID==1'b1)&(OUT!=1))
                            begin
                                $display("P4 Error\n");
//                                $finish;
                            end
                        end



        $finish;


    end     

endmodule


