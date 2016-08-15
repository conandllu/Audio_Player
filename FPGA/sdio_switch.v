module sdio_switch (sdio_cmd,sdio_cmda,sdio_cmdb,sdio_d,sdio_da,sdio_db,sdio_cs,sdio_ck,sdio_cka,sdio_ckb);
	inout [3:0] sdio_d;
	inout [3:0] sdio_da;
	inout [3:0] sdio_db;
	inout sdio_cmd;
	inout sdio_cmda;
	inout sdio_cmdb;
	input sdio_cs;
	input sdio_ck;
	output sdio_cka;
	output sdio_ckb;

	tranif0(sdio_d[0], sdio_da[0], sdio_cs);
	tranif0(sdio_d[1], sdio_da[1], sdio_cs);
	tranif0(sdio_d[2], sdio_da[2], sdio_cs);
	tranif0(sdio_d[3], sdio_da[3], sdio_cs);
	tranif0(sdio_cmd, sdio_cmda, sdio_cs);

	tranif1(sdio_d[0], sdio_db[0], sdio_cs);
	tranif1(sdio_d[1], sdio_db[1], sdio_cs);
	tranif1(sdio_d[2], sdio_db[2], sdio_cs);
	tranif1(sdio_d[3], sdio_db[3], sdio_cs);
	tranif1(sdio_cmd, sdio_cmdb, sdio_cs);
	
	assign sdio_cka = (sdio_cs == 0)?sdio_ck:0;
	assign sdio_ckb = (sdio_cs == 1)?sdio_ck:0;
	
endmodule