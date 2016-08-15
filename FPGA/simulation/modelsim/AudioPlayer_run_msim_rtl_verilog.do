transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -vlog01compat -work work +incdir+J:/Project/Audio\ Player/FPGA {J:/Project/Audio Player/FPGA/PLL_225792.v}
vlog -vlog01compat -work work +incdir+J:/Project/Audio\ Player/FPGA {J:/Project/Audio Player/FPGA/PLL_24576_1.v}
vlog -vlog01compat -work work +incdir+J:/Project/Audio\ Player/FPGA {J:/Project/Audio Player/FPGA/clock_switch_in.v}
vlog -vlog01compat -work work +incdir+J:/Project/Audio\ Player/FPGA {J:/Project/Audio Player/FPGA/clock_switch_out.v}
vlog -vlog01compat -work work +incdir+J:/Project/Audio\ Player/FPGA {J:/Project/Audio Player/FPGA/clock_2.v}
vlog -vlog01compat -work work +incdir+J:/Project/Audio\ Player/FPGA {J:/Project/Audio Player/FPGA/clock_4.v}
vlog -vlog01compat -work work +incdir+J:/Project/Audio\ Player/FPGA/db {J:/Project/Audio Player/FPGA/db/pll_225792_altpll.v}
vlog -vlog01compat -work work +incdir+J:/Project/Audio\ Player/FPGA/db {J:/Project/Audio Player/FPGA/db/pll_24576_1_altpll.v}

