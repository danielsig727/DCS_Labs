

module LAB(//input
           CLK,
           MODE, 
           IN_A, 
           IN_B, 
           //output
           OUT);
//-----------input output  **signed or unsigned-------------//           
    input wire CLK;
    input wire MODE;
    input wire signed [3:0] IN_A;
    input wire signed [3:0] IN_B;
    output reg signed [7:0] OUT;
//    OUT <= 0;

//----------main design ----**Can use behavioral model------//
    always@(posedge CLK)
    begin
        switch(MODE)
        case 0:
            OUT <= IN_A + IN_B;
            break;
        case 1:
            OUT <= IN_A * IN_B;
            break;
        endcase
    end


             
endmodule

