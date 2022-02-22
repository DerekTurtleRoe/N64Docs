Tuesday, February 15, 2022 1:48 AM

# Nintendo 64 Memory Map

## Virtual Memory Map

| Address Range | Name | Description |
|--------|--------|
| 0x00000000 - 0x7FFFFFFF | KUSEG | User segment, TLB mapped |
| 0x80000000 - 0x9FFFFFFF | KSEG0 | Kernel segment 0, directly mapped, cached |
| 0xA0000000 - 0xBFFFFFFF | KSEG1 | Kernel segment 1, directly mapped, uncached |
| 0xC0000000 - 0xDFFFFFFF | KSSEG | Kernel supervisor segment, TLB mapped |
| 0xE0000000 - 0xFFFFFFFF | KSEG3 | Kernel segment 3, TLB mapped |

## Physical Memory Map

| Address Range | Name | Description |
|--------|--------|
| 0x00000000 - 0x003FFFFF |	RDRAM | RDRAM located on motherboard |
| 0x00400000 - 0x007FFFFF | RDRAM | RDRAM from Expansion Pak (if present) |
| 0x00800000 - 0x03EFFFFF | Reserved | Unknown usage |
| 0x03F00000 - 0x03FFFFFF | RDRAM Registers | RDRAM Registers |
| 0x04000000 - 0x04000FFF | RSP DMEM | RSP Data Memory |
| 0x04001000 - 0x04001FFF | RSP IMEM | RSP Instruction Memory |
| 0x04002000 - 0x0403FFFF | Unknown | Unknown |
| 0x04040000 - 0x040FFFFF |	RSP Registers | RSP DMAs, status, semaphore, program counter, IMEM BIST status |
| 0x04100000 - 0x041FFFFF | RDP Command Registers | RDP DMAs, clock counters for: clock, buffer busy, pipe busy, and TMEM load |
| 0x04200000 - 0x042FFFFF | RDP Span Registers | TMEM BIST status, DP Span testing mode |
| 0x04300000 - 0x043FFFFF | MIPS Interface (MI) | Init mode, ebus test mode, RDRAM register mode, hardware version, interrupt status, interrupt masks |
| 0x04400000 - 0x044FFFFF | Video Interface (VI) | Video control registers |
| 0x04500000 - 0x045FFFFF | Audio Interface (AI) | Audio DMAs, Audio DAC clock divider |
| 0x04600000 - 0x046FFFFF | Peripheral Interface (PI) | Cartridge port DMAs, status, Domain 1 and 2 speed/latency/page-size controls |
| 0x04700000 - 0x047FFFFF | RDRAM Interface (RI) | Operating mode, current load, refresh/select config, latency, error and bank status |
| 0x04800000 - 0x048FFFFF | Serial Interface (SI) | SI DMAs, PIF status |
| 0x04900000 - 0x04FFFFFF | Unused | Unused |
| 0x05000000 - 0x05FFFFFF | Cartridge Domain 2 Address 1 | N64DD control registers (if present) |
| 0x06000000 - 0x07FFFFFF | Cartridge Domain 1 Address 1 | N64DD IPL ROM (if present) |
| 0x08000000 - 0x0FFFFFFF | Cartridge Domain 2 Address 2 | Cartridge SRAM (if present) |
| 0x10000000 - 0x1FBFFFFF | Cartridge Domain 1 Address 2 | Cartridge ROM |
| 0x1FC00000 - 0x1FC007BF | PIF ROM (IPL1/2) | Executed on boot |
| 0x1FC007C0 - 0x1FC007FF | PIF RAM	| Controller and EEPROM communication, and during IPL1/2 is used to read startup data from the PIF |
| 0x1FC00800 - 0x1FCFFFFF | Reserved | Unknown usage |
| 0x1FD00000 - 0x7FFFFFFF | Cartridge Domain 1 Address 3 | Mapped to same address range on physical cartridge port |
| 0x80000000 - 0xFFFFFFFF | External SysAD device bus | Unknown usage (Unconfirmed: possibly used by processors, cache, and/or RAM for communication) |

**Note: Cartridge Domains 1 and 2 are mapped one-to-one on the cartridge/bottom port. It is not known at this time what Domain 1 Address 3 was used for, if at all, but flash carts may have some use for that address range.**
