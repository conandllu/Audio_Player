module clock_switch_in (data_in,data_clk_in,data_en_in,data_out,rst);
	input [7:0] data_in;
	input data_clk_in;
	input data_en_in;
	input rst;
	output [7:0] data_out;

	reg [7:0]data_out;
	reg clk_out;

	always @ (posedge rst or posedge data_clk_in or posedge data_en_in )
	begin
		if(rst)
		begin
			data_out = 8'hFF;
		end
		if(data_en_in)
		begin
			data_out = data_in;
		end

	end

endmodule