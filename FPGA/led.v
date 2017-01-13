module LED (clk,leda,rst);
input clk;
input rst;
output [3:0]leda;

reg [3:0]leda;

parameter MAX= 10_000_000;

integer i = 0;

always @ (posedge clk or posedge rst)
begin
if(rst)
	begin
		leda <= 4'd0;
	end
	else
	begin
		if(i == MAX)
		begin
			i <= 1'd0;
			leda <= leda + 1'b1;
		end
		else
		begin
			i <= i + 1'd1;
		end
	end
end
endmodule