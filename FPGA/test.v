
module test(

	inout wire            a,
	inout wire            b1,
    inout wire            b2,
	input wire	   c
	
);
 
 
 tranif1 switch1 (a, b1, c);
 tranif0 switch2 (a, b2, c);
/*
 reg [4:0]count;
	initial clk_out = 3'b0;
    initial count = 3'b0;

	always @ (posedge clk or posedge rst) begin
        if(rst == 1'b1) begin
            clk_out = 3'b0;
            count = 3'b0;
        end else begin
		count = (count != 12) ? (count + 1) : 1;
        
        clk_out[0] = (count%2) ? clk_out[0] : ~clk_out[0];
        clk_out[1] = (count%3) ? clk_out[1] : ~clk_out[1];
        clk_out[2] = (count%4) ? clk_out[2] : ~clk_out[2];
        end
	end
*/
endmodule