# List of Nintendo 64 ROM and save file formats

#### Common ROM formats

.bin - a raw binary dump of a particular title (can be big or little-endian, or byte-swapped)
.rom - Sometimes used if a ROM is of unknown byte order, similar to .bin

```
WARNING: These doesn't necessarily have to be an N64 ROM, so be sure to check it first with something like Info64, ROM64, romjudge, etc! These can also be dumps of various N64-related backup systems, flash carts, or development hardware.
```

```
Note: Emulators sometimes confuse file extensions with actual byte order, so it's good to be cautious about any and all ROM dumps.
```

.z64 - ROM dumps produced by or compatible with the Z64, with data stored in the N64's native big-
endian byte order.
.v64 - ROM dumps produced by or compatible with the Doctor V64, with data stored in a byte-swapped
version of the N64's native byte order.
.n64 - Indicates ROM dumps stored in little-endian byte order.
.N64 - The extension used by the makerom utility of GCCexe as part of the official SDK. It's in the big-endian format.
.ndd - This is a Nintendo 64 Disk Drive dump. These can be LBA order or sector order. There are tools to convert to and from both, so they can be either if they have this extension.

#### Uncommon ROM formats

.pal - Sometimes used to indicate ROM dumps of games released in PAL territories, in any format
.usa - Sometimes used to indicate ROM dumps of games released in NTSC territories, in any format
.jap - Sometimes used to indicate ROM dumps of games released in Japan, in any format
.u64 - I'm not 100% sure what this file type is to be honest, I haven't seen it used in the wild personally. If you know what it is used for, let me know! Maybe related to uCON64?

N64 Dynamic Drive?
.d64 - n64mdisk (SDK) output format. Big-endian.

#### Save file formats:

.mpk - Controller Pak saves
.srm - SRAM saves
.epk - EEPROM saves
.fla - FlashRAM saves (Ares saves as .flash)
.ram, .eeprom, and .pak are usually FlashRAM, EEPROM, and Controller Pak saves respectively.

*Note: Some emulators may not save in big-endian, but in little-endian. It is unknown why this is done.*

Some emulators also might report corrupt data, others just show it as if its a new game if the memory card hasn't been "initialized" or "formatted". Sometimes this also occurs if the save format isn't recognized.

Some Nintendo 64 games (rare especially) create .mpk files even though they use an on-cart save type.

Apparently Project64 and Mupen64Plus saves aren't interchangeable, probably due to CPU and memory bugs, or differences in implementation of the same standard.

Project64 saves both SRAM and flash in little-endian, whereas they're big-endian on hardware. But for some reason Controller Pak files are saved in little-endian...

64drive does both SRAM/FlashRAM in big-endian.

EverDrive 64 does saves in little-endian. It is compatible with Project64/Mupen64 saves, but not with Not64 saves.

The RetroArch cores concatenate every possible save into one file, including paks for each controller.

Note that the actual byte order of a ROM may not always be the one expected from its file extension.

| Type | Offset | Size |
|--------|--------|
| EEPROM | 0 | 2048 |
| Controller Pak 1 | 2048 | 32768 |
| Controller Pak 2 | 34816 | 32768 |
| Controller Pak 3 | 67584 | 32768 |
| Controller Pak 4 | 100352 | 32768 |
| SRAM | 133120 | 32768 |
| Flash | 165888 | 131072 |

Not64 is padded differently:
```
#define EEPROM                  0x200       // 512 bytes (EEPROM 4 Kbits) (used in physical cartridges)
#define EEPROMx4                0x800       // 2 KiB (EEPROM 16 Kbits) (used in physical cartridges) (used in Project64 and Wii64/Not64)
#define EEPROMx8                0x1000      // 4 KiB (EEPROM 32 Kbits) (used in Sixtyforce)
#define EEPROMx32               0x4000      // 16 KiB (EEPROM 128 Kbits) (used in Wii N64 Virtual Console)
#define SRAM                    0x8000      // 32 KiB (SRAM 256 Kbits) (used in physical cartridges) (used in all emulators)
#define FlashRAM                0x20000     // 128 KiB (FlashRAM 1024 Kbits) (used in physical cartridges) (used in all emulators)
#define CtrlPak                 0x8000      // 32 KiB (SRAM 256 Kbits) (used in physical Controller Paks) (used in Sixtyforce)
#define CtrlPakx4               0x20000     // 128 KiB (SRAM 1024 Kbits) (used in Wii64/Not64)
#define CtrlPakx8               0x40000     // 256 KiB (SRAM 2048 Kbits) (used in Project64)
```

*Example of big-endian vs little-endian vs byte-swapped:*

Value (ASCII big-endian)				S	U	P	E	R		M	A	R	I	O		6	4	
Value (ASCII big-endian byte-swapped)	U	S	E	P		R	A	M	I	R		O	4	6
Value (ASCII little-endian)				E	P	U	S	A	M		R		O	I	R			4	6
