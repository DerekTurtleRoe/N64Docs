# Game Pak

*The Nintendo 64 Game Pak (part number NUS-006) is the brand name of the consumer ROM cartridge product that stores game data for the Nintendo 64, released in 1996. As with Nintendo's previous consoles, the Game Pak's design tradeoffs were intended to achieve maximum system speed and minimal base console cost—with less storage space and a higher unit cost per game. Integrating a CD-ROM drive, with its expensive and moving parts, would have drastically increased the console's base price and reduced its performance.*

| Pin | Cart | Solder Side | Pin Cart Component Side |
| ------ | ------ | ------ | ------ |
| Ground | 1 | 26 | Ground |
| Ground | 2 | 27 | Ground |
| AD15 | 3 | 28 | AD0 |
| AD14 | 4 | 29 | AD1 |
| AD13 | 5 | 30 | AD2 |
| Ground | 6 | 31 | Ground |
| AD12 | 7 | 32 | AD3 |
| /Write??? | 8 | 33 | ALE_L |
| 3.3V | 9 | 34 | 3.3V |
| /Read??? | 10 | 35 | ALE_H |
| AD11 | 11 | 36 | AD4 |
| AD10 | 12 | 37 | AD5 |
| 12V | 13 | 38 | 12V |
| 12V | 14 | 39 | 12V |
| AD9 | 15 | 40 | AD6 |
| AD8 | 16 | 41 | AD7 |
| 3.3V | 17 | 42 | 3.3V |
| CIC_DATA1 | 18 | 43 | CIC_DATA2 |
| 1.95 MHz CLK | 19 | 44 | INT1 |
| /COLD_RESET | 20 | 45 | NMI |
| S_DAT | 21 | 46 | Video Sync |
| Ground | 22 | 47 | Ground |
| Ground | 23 | 48 | Ground |
| Left Audio | 24 | 49 | Right Audio |
| Ground | 25 | 50 | Ground |

*The above table is merged from multiple sources and personal knowledge.*

**Note: Pin 19 is 1.95 MHz Clock from the PIF - 62.5 MHz /32**
**While the use of the Read and Write contacts seems obvious, it's actually not 100% confirmed.**

# Board NUS-06A-01 (fully visually confirmable)

- Pin 8 (AKA write) is routed directly to the save IC, no other stops.

- Pin 10 (AKA read) is routed to 2 pins of the game ROM and 1 pin on the save IC.

# Board NUS-07A-01

- Pin 8 (AKA write) is routed to 1 pin on the game ROM (visually confirmable) and 1 pin on the save IC (VM continuity check).

- Pin 10 (aka read) is routed to 2 pins of the game ROM  (visually confirmable) and 1 pin on the save IC (VM Continuity check).
