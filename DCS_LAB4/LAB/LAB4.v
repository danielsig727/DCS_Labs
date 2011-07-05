
module LAB4(//input
           CLK,
           INPUT1,
           INPUT2,
           //output
           OUT
               );
//-----------input output -------------//           
input CLK;
input [3:0] INPUT1,INPUT2;
output [5:0]OUT;

reg [5:0] OUT;

always @ (posedge CLK)
    OUT<=INPUT1[2:0]+INPUT2[3:0];



endmodule
