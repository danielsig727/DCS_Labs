
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
output [5:0]OUT;
output OUT_VALID;

reg [5:0] OUT;
reg OUT_VALID;
reg [1:0] CURRENT_STATE, NEXT_STATE;
reg [2:0] COUNTER_read,COUNTER_out;
reg [2:0] reg1, reg2, reg3, reg4, reg5;
reg [5:0] ACC;
//----------wire-----------------------//
//always @(posedge CLK)
 //   if(RST)
  //      COUNTER<=3'b000;
   // else if (COUNTER == 3'b101)
    //    COUNTER<=3'b000;
    //else
     //   COUNTER<=COUNTER +1'b1;

//----------main design ----*Gate level------//
//ex:sAND3 g1(OUT,IN[0],IN[1],IN[2]);
always @ (posedge CLK)
   if(RST)
       CURRENT_STATE<=2'b00;
   else 
       CURRENT_STATE<=NEXT_STATE;

always @*
   case(CURRENT_STATE)
     2'b00:
         if(IN_VALID==1'b1)
             NEXT_STATE<=2'b01;
         else
             NEXT_STATE<=CURRENT_STATE;

     2'b01:
         if(IN_VALID==1'b0)
             NEXT_STATE<=2'b10;
         else 
             NEXT_STATE<=CURRENT_STATE;

     2'b10:
         if(COUNTER_out>COUNTER_read)
             NEXT_STATE<=2'b00;
         else
             NEXT_STATE<=CURRENT_STATE;
    endcase

always @ (posedge CLK)
   if(CURRENT_STATE==2'b00)
       COUNTER_read<=3'b000;
   else if(IN_VALID==1'b1)
       COUNTER_read<=COUNTER_read+1'b1;
   else
       COUNTER_read<=COUNTER_read;
always @ (posedge CLK)
  if(CURRENT_STATE==2'b00)
       COUNTER_out<=3'b000;
   else if(CURRENT_STATE==2'b10)
       COUNTER_out<=COUNTER_out+1'b1;


always @ (posedge CLK)
    if(CURRENT_STATE==2'b00)
        if(IN_VALID==1'b0)
            reg1<=3'b000;
        else 
            reg1<=INPUT;
    else
       reg1<=reg1;



always @ (posedge CLK)
    if(CURRENT_STATE==2'b00)
       reg2<=3'b000;
    else if (COUNTER_read==3'b000)
       reg2<=INPUT;
    else
       reg2<=reg2;

always @ (posedge CLK)
    if(CURRENT_STATE==2'b00)
       reg3<=3'b000;
    else if (COUNTER_read==3'b001)
       reg3<=INPUT;
    else
       reg3<=reg3;

always @ (posedge CLK)
    if(CURRENT_STATE==2'b00)
       reg4<=3'b000;
    else if (COUNTER_read==3'b010)
       reg4<=INPUT;
    else
       reg4<=reg4;

always @ (posedge CLK)
    if(CURRENT_STATE==2'b00)
       reg5<=3'b000;
    else if (COUNTER_read==3'b011)
       reg5<=INPUT;
    else
       reg5<=reg5;

always @ (posedge CLK)
    if(CURRENT_STATE==2'b10)
       OUT_VALID<=1'b1;
    else
       OUT_VALID<=1'b0;
    
always @ (posedge CLK)
    if(CURRENT_STATE==2'b10)
        if(COUNTER_out>COUNTER_read)
            OUT<=ACC;
        else if(COUNTER_out==3'b000)
            OUT<=reg1;
        else if(COUNTER_out==3'b001)
            OUT<=reg2;
        else if(COUNTER_out==3'b010)
            OUT<=reg3;
        else if(COUNTER_out==3'b011)
            OUT<=reg4;
        else if(COUNTER_out==3'b100)
            OUT<=reg5;
        else 
            OUT<=3'b0;
    else
       OUT<=3'b0;

always @ *
    ACC<= reg1+reg2+reg3+reg4+reg5;

endmodule
