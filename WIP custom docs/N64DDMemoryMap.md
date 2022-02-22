# Nintendo 64 Disk Drive memory map

0x05000000 - 64DD I/O
0x06000000 - 64DD IPL ROM / Development Disk IPL Cartridge ROM

0x0FE00000 - Capture Cassette I/O

0x0FE70000 - Smart Media Card I/O

0x0FFD0000 - Modem Cassette I/O
0x18000000 - Modem Cassette Library ROM
* I/O Map *
0x05000000 - C2 Sector Buffer				(ASIC_C2_BUFF)
0x05000400 - Data Sector Buffer				(ASIC_SECTOR_BUFF)

0x05000500 - Data					(ASIC_DATA)
0x05000504 - Misc Register				(ASIC_MISC_REG)
0x05000508 - Command / Status				(ASIC_CMD / ASIC_STATUS)
0x0500050C - Current Track				(ASIC_CUR_TK)
0x05000510 - Buffer Manager Status/Control		(ASIC_BM_STATUS / ASIC_BM_CTL)
0x05000514 - Sector Error Status			(ASIC_ERR_SECTOR)
0x05000518 - Sequencer Status/Control			(ASIC_SEQ_STATUS / ASIC_SEQ_CTL)
0x0500051C - Current Sector				(ASIC_CUR_SECTOR)
0x05000520 - Hard Reset					(ASIC_HARD_RESET)
0x05000524 - C1						(ASIC_C1_S0)
0x05000528 - Sector Size (in bytes)			(ASIC_HOST_SECBYTE)
0x0500052C - C1						(ASIC_C1_S2)
0x05000530 - Sectors per Block, Full Size		(ASIC_SEC_BYTE)
0x05000534 - C1						(ASIC_C1_S4)
0x05000538 - C1						(ASIC_C1_S6)
0x0500053C - Current Address?				(ASIC_CUR_ADDR)
0x05000540 - ID						(ASIC_ID_REG)
0x05000544 - Test Read					(ASIC_TEST_REG)
0x05000548 - Test Write					(ASIC_TEST_PIN_SEL)

0x05000580 - Microsequencer RAM				(MSEQ_RAM_ADDR)
* PI Settings *
64DD I/O (Cartridge Domain 2)
LAT = 0x03 = 4 cycles
PWM = 0x06 = 7 cycles
PGS = 0x06 = 256 bytes page size?
RLS = 0x02 = 3 cycles
64DD IPL ROM (Cartridge Domain 1)
ROM Header contains 0x80270740

LAT = 0x40 = 65 cycles
PWM = 0x07 = 8 cycles
PGS = 0x07 = 512 bytes page size
RLS = 0x02 = 3 cycles
Capture Cassette I/O (Cartridge Domain 2)
LAT = 0x01 = 2 cycles
PWM = 0x09 = 10 cycles
PGS = 0x07 = 512 bytes page size
RLS = 0x03 = 4 cycles
Capture Cassette Data (Cartridge Domain 2)
LAT = 0x32 = 51 cycles
PWM = 0x04 = 5 cycles
PGS = 0x07 = 512 bytes page size
RLS = 0x01 = 2 cycles
Modem Cassette I/O (Cartridge Domain 2)
LAT = 0x05 = 6 cycles
PWM = 0x06 = 7 cycles
PGS = 0x05 = 128 bytes page size?
RLS = 0x02 = 3 cycles
Modem Cassette ROM (Cartridge Domain 1)
ROM Header contains 0x80371240 (TODO)
