`include "GateDelay.v"

module LAB1(//input
           IN, 
           //output
           OUT);
//-----------input output -------------//           
input [8:0]IN;
output OUT;

//----------wire-----------------------//
wire [7:0] L1;
wire [4:0] L2;
wire [2:0] L3;
wire OUT;

//----------main design ----*Gate level------//
//ex:sAND3 g1(OUT,IN[0],IN[1],IN[2]);
sNAND3 t11(L1[0], IN[0], IN[1], IN[2]);
sNAND3 t12(L1[1], IN[3], IN[4], IN[5]);
sNAND3 t13(L1[2], IN[6], IN[7], IN[8]);
sNAND3 t14(L1[3], IN[0], IN[3], IN[6]);
sNAND3 t15(L1[4], IN[1], IN[4], IN[7]);
sNAND3 t16(L1[5], IN[2], IN[5], IN[8]);
sNAND3 t17(L1[6], IN[0], IN[4], IN[8]);
sNAND3 t18(L1[7], IN[2], IN[4], IN[6]);

sNAND2 t21(L2[0], L1[0], L1[1]);
sNAND2 t22(L2[1], L1[2], L1[3]);
sNAND2 t23(L2[2], L1[4], L1[5]);
sNAND2 t24(L2[3], L1[6], L1[7]);

sNOR2 t31(L3[0], L2[0], L2[1]);
sNOR2 t32(L3[1], L2[2], L2[3]);

sNAND2 t4(OUT, L3[0], L3[1]);
             
endmodule

