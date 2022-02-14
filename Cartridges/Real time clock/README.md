The real time clock (RTC) is accessed via PIF on channel 5 (counting 1-6).
It uses three PIF commands not normally used in games: 6, 7, 8.

The clock itself consists of 0x18 bytes, accessed in 0x8 clusters. Block 0 acts as a device controller, and the time can be found on block 2. Currently, the use of the second block is unknown. All three blocks have read/write access. It is interesting to note that the time kept on the clock is in decimal, not hexadecimal. The year is read as an offset from 1900.

In order to write to the RTC, you must first untoggle the read-only bitflags in the control register for the appropriate block#, and you will also want to disable the clock temporarily. When finished, be certain to set them back to their original settings and reactivate the timer.

Clock data:

Block 0:	Control registers

0x0	1	Control register hi
01	Block 1 read-only when set
02	Block 2 read-only when set
0x1	1	Control register lo
02	Set when timer running
04	Deactivate timer

Block 1:

Unknown? No known access within Animal Forest (the only game known to use the RTC besides Nintendo 64 Disk Drive games)

Block 2:	Time registers: all time stored as decimal values!

0x0	1	Seconds
0x1	1	Minutes
0x2	1	Hours
0x3	1	Day of week
0x4	1	Day of month
0x5	1	Month
0x6	2	Year since 1900 (Intel byte-swapping like all PIF data)

PIF command 6: RTC status	01.03:06;dddd.ss
Superficially identical to a normal PIFcmd0 status request.

0x0	1	Write: 1
0x1	1	Read: 3
0x2	1	Command: 6
0x3	2	Device type; RTC should return 1000 (assuming 16k EEPROM returns 4000)
0x5	1	Status flags
01	Unknown; fails access
02	Unknown; fails access
80	Busy

PIF command 7: Read RTC block	02.09:07.bb;dddddddddddddddd.ss

0x0	1	Write: 2
0x1	1	Read: 9
0x2	1	Command: 7
0x3	1	Block # (0-2)
0x4	8	Data
0xC	1	Status

PIF command 8: Write RTC block	0A.01:08.bb.dddddddddddddddd;ss

0x0	1	Write: 10
0x1	1	Read: 1
0x2	1	Command: 8
0x3	1	Block # (0-2)
0x4	8	Data
0xC	1	Status

This information was provided by Zoinkity. Without Zoinkity's work, a lot of information would be unknown or poorly documented. Thank you so much for all your hard work Zoinkity!