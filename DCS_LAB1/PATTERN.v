//############################################################################


module PATTERN(//OUTPUT
               IN, 
               //INPUT 
               OUT);
//---------------------------------------------------------------------//
output  [8:0] IN;

input   OUT;

//---------------------------------------------------------------------//
//   critical = critical path cycle time (ns)
//---------------------------------------------------------------------//
integer critical = 9.5;

//---------------------------------------------------------------------//

reg CLK;
reg [8:0] IN;
integer i,j,correct_out;
parameter CYCLE=1.0, number=10;


always #(CYCLE/2.0) CLK=~CLK;
    initial begin 
        CLK=1'b1;
        IN=9'b0_0000_0000;
    end

    initial begin
        for(i=1;i<=number;i=i+1)
        begin
            @(negedge CLK)
            if(i==1)
                begin
                    IN=9'b111111111;
                end
            else if(i==2)
            	begin
                    IN=9'b000000000;
            	end
            else if(i==3)
                begin
                    IN=9'b110010111;
                end
     	    else if(i==4)
            	begin
                    IN=9'b1110_0000_0;
            	end
     	    else if(i==5)
            	begin
                    IN=9'b101010100;
                end
            else if(i==6)
                begin
                    IN=9'b0001_1100_0;
     	    	end
     	    else if(i==7)
     	        begin
                    IN=9'b001010100;
     	    	end
            else if(i==8)
                begin
                    IN=9'b0000_0011_1;
                end
            else if(i==9)
                begin
                    IN=9'b1000_1000_1;
                end
            else if(i==10)
                begin
                    IN=9'b1011_1010_0;
                end
           $display("!!Pattern  %d IN = %b\nstart time %t",i,IN,$time);
           for(j=1;j<=critical;j=j+1)
                 @(posedge CLK);
         
           	//begin
           correct_out = (IN[0]&IN[1]&IN[2]) | (IN[3]&IN[4]&IN[5]) | (IN[6]&IN[7]&IN[8])| (IN[0]&IN[3]&IN[6])| (IN[1]&IN[4]&IN[7])| (IN[2]&IN[5]&IN[8])| (IN[0]&IN[4]&IN[8])| (IN[2]&IN[4]&IN[6]);

            #1 if(correct_out !== OUT)
                begin
                    $display("time %t\n",$time);
                    $display("Fail \n");
                    $display("!!Correct   OUTPUT IS    %d\n",correct_out);
                    $display("!!YOUR      OUTPUT IS    %d\n",OUT);
                    @(posedge CLK);
                    @(posedge CLK);
                    @(posedge CLK);
                    $finish;
           	end         
             $display("end time %t PASS!!",$time);


        end
        //   @(posedge CLK);
            $display(" \\(¡Ã¡¾¡Ã)/(\\¡Ã¡¾)/\\(     )/\\(¡¾¡Ã/)\\(¡Ã¡¾¡Ã)/");
                    $finish;
    end     
//$finish;

endmodule


