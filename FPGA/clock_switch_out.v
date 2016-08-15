module clock_switch_out (clk_in,data_in,clk_out,next,rst);
	input [14:0] clk_in;
	input [7:0] data_in;
	input next;
	input rst;
	output clk_out;

	wire [14:0] clk_in;
	reg clk_out;

	always @ (posedge rst or posedge next)
	begin
		if(rst)
		begin
			clk_out = 1'b0;
		end
	
		if(next)
		begin
			case (data_in)
				8'b00000000: clk_out = clk_in[0];  //44.1KHz@16bit    1.4112Mhz
				8'b00100000: clk_out = clk_in[14]; //44.1KHz@24bit    2.1168Mhz
				8'b01000000: clk_out = clk_in[1];  //44.1KHz@32bit    2.8824Mhz
				8'b00000100: clk_out = clk_in[2];  //176.4KHz@16bit   5.6448Mhz
				8'b00100100: clk_out = clk_in[3];  //176.4KHz@24bit   8.4672Mhz
				8'b01000100: clk_out = clk_in[4];  //176.4KHz@32bit  11.2896Mhz
				8'b00000001: clk_out = clk_in[5];  //48KHz@16bit      1.536 Mhz
				8'b00100001: clk_out = clk_in[6];  //48KHz@24bit      2.304 Mhz
				8'b01000001: clk_out = clk_in[7];  //48KHz@32bit      3.072 Mhz
				8'b00000010: clk_out = clk_in[7];  //96KHz@16bit      3.072 Mhz
				8'b00100010: clk_out = clk_in[9];  //96KHz@24bit      4.608 Mhz
				8'b01000010: clk_out = clk_in[10]; //96KHz@32bit      6.144 Mhz
				8'b00000011: clk_out = clk_in[8];  //128KHz@16bit     4.096 Mhz
				8'b00100011: clk_out = clk_in[10]; //128KHz@24bit     6.144 Mhz
				8'b01000011: clk_out = clk_in[11]; //128KHz@32bit     8.192 Mhz
				8'b00000101: clk_out = clk_in[10]; //192KHz@16bit     6.144 Mhz
				8'b00100101: clk_out = clk_in[12]; //192KHz@24bit     9.216 Mhz
				8'b01000101: clk_out = clk_in[13]; //192KHz@32bit    12.288 Mhz
				
				8'b10000000: clk_out = clk_in[1];  //DSD              2.8224Mhz
				
				8'b11111111: clk_out = 1'b0;       //Reset
				
				default:     clk_out = 1'b0;
			endcase
		end
	end

endmodule