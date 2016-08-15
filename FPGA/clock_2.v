module clock_2(clk_in,clk_out,reset);

	input wire clk_in;
	input wire reset;
	output  clk_out;
 
	reg [1:0]count;
	reg clk_out;
	
	initial clk_out = 0;
   initial count = 2'b0;

	always @ (posedge clk_in or posedge reset) begin
		if(reset == 1'b1) begin
			clk_out = 0;
			count = 2'b0;
		end else begin
			count = (count != 2) ? (count + 1) : 1;
		  	clk_out = (count%1) ? clk_out : ~clk_out;
		end
	end
		
endmodule