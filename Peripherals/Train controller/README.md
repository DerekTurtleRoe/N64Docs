Densha de Go 64 Train Controller info

I believe this data was taken from a Zoinkity document, but I can't confirm that at the moment.

Returned Status:
20 04 00

Buttons:
start	10000000
select	00100000
A	40000000
B	80000000
C	00200000

Throttle returns fixed values for each state.  From top to bottom:
28000000
21000000
20000000
09000000
08000000
01000000

The brake has a series of divisions from 000E0000 on the left to 00000000 on the right.  Between each division (between clicks on the left and ranges on the right) the value 000F is passed.
From upper left to the bottom, blue range.  Each value is a fixed "click":
000E0000
000D0000
000C0000
000B0000
000A0000
00090000
00080000
00070000
00060000
The red zone does not have fixed "clicks"; it is divided into five divisions, returning 000F0000 between the values.  Divisions are at regular intervals, but it would be best if somebody could get the actual angual difference between them.
00050000
00040000
00030000
00020000
00010000
Both far left clicks return 00000000 when set.