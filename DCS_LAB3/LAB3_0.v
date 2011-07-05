
module LAB3(//input
           CLK,
           RST, 
           IN_VALID,
           INPUT,
           //output
           OUT,
           OUT_VALID
               );
//-----------input output -------------//           
input RST, CLK, IN_VALID;
input [2:0] INPUT;
output [2:0]OUT;
output OUT_VALID;

reg [2:0] OUT;
reg OUT_VALID;
//reg [1:0] CURRENT_STATE, NEXT_STATE;
//reg [1:0] COUNTER_read,COUNTER_out;
//reg [2:0] reg1, reg2, reg3, reg4, reg5;



//-------------Counter--------------------------
//always @(posedge CLK)
 //   if()
  //      COUNTER<=3'b000;
    //else if()
     //   COUNTER<=COUNTER +1'b1;
    //else
     //   COUNTER<=COUNTER:



////----------register definition 




////-------------------- OUT and OUT_VALID---------
    



endmodule
