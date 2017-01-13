module clock_switch_out (clk_in0,clk_in1,clk_in2,clk_in3,clk_in4,clk_in5,clk_in6,clk_in7,clk_in8,clk_in9,clk_in10,clk_in11,clk_in12,clk_in13,clk_in14,data_in,clk_out,next,rst);
	input clk_in0,clk_in1,clk_in2,clk_in3,clk_in4,clk_in5,clk_in6,clk_in7,clk_in8,clk_in9,clk_in10,clk_in11,clk_in12,clk_in13,clk_in14;
	input [7:0] data_in;
	input next;
	input rst;
	output clk_out;

	reg clk_out;

	always @ (data_in or  rst or next or clk_in0 or clk_in1 or clk_in2 or clk_in3 or clk_in4 or clk_in5 or clk_in6 or clk_in7 or clk_in8 or clk_in9 or clk_in10 or clk_in11 or clk_in12 or clk_in13 or clk_in14)
	begin
		if(rst)
		begin
			clk_out = 1'b0;
		end
		else
		begin
			case (data_in)
				8'b00000000: clk_out <= clk_in0;  //44.1KHz@16bit    1.4112Mhz 0x00
				8'b00100000: clk_out <= clk_in14; //44.1KHz@24bit    2.1168Mhz 0x20
				8'b01000000: clk_out <= clk_in1;  //44.1KHz@32bit    2.8824Mhz 0x40
				8'b00000100: clk_out <= clk_in2;  //176.4KHz@16bit   5.6448Mhz 0x04
				8'b00100100: clk_out <= clk_in3;  //176.4KHz@24bit   8.4672Mhz 0x24
				8'b01000100: clk_out <= clk_in4;  //176.4KHz@32bit  11.2896Mhz 0x44
				8'b00000001: clk_out <= clk_in5;  //48KHz@16bit      1.536 Mhz 0x01
				8'b00100001: clk_out <= clk_in6;  //48KHz@24bit      2.304 Mhz 0x21
				8'b01000001: clk_out <= clk_in7;  //48KHz@32bit      3.072 Mhz 0x41
				8'b00000010: clk_out <= clk_in7;  //96KHz@16bit      3.072 Mhz 0x02
				8'b00100010: clk_out <= clk_in9;  //96KHz@24bit      4.608 Mhz 0x22
				8'b01000010: clk_out <= clk_in10; //96KHz@32bit      6.144 Mhz 0x42
				8'b00000011: clk_out <= clk_in8;  //128KHz@16bit     4.096 Mhz 0x03
				8'b00100011: clk_out <= clk_in10; //128KHz@24bit     6.144 Mhz 0x23
				8'b01000011: clk_out <= clk_in11; //128KHz@32bit     8.192 Mhz 0x43
				8'b00000101: clk_out <= clk_in10; //192KHz@16bit     6.144 Mhz 0x05
				8'b00100101: clk_out <= clk_in12; //192KHz@24bit     9.216 Mhz 0x25
				8'b01000101: clk_out <= clk_in13; //192KHz@32bit    12.288 Mhz 0x45
				
				8'b10000000: clk_out <= clk_in1;  //DSD              2.8224Mhz
				
				8'b11111111: clk_out <= 1'b0;       //Reset
				
				default:     clk_out <= 1'b0;
			endcase
		end
	end

endmodule