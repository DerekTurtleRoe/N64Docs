# NUS-64

From Jlukas and the original thread:

The NUS software on the cart is designed to work ONLY on the special NUS Checker hardware system. While the physical flash cart can technically run on a standard SNES, the NUS test software programmed on it MUST be used in combination with the Checker hardware to use its functions. All those red Caution messages you see when booting the cart is errors where the program is trying to communicate with the special hardware and not receiving the responses it expects.

Standard controllers aren’t supported by the software at all, further proof that it’s not meant for regular systems. All user input goes through a special register instead. Apparently, the NUS Checker hardware has its own kind of controller (or more likely, has buttons or a keypad located on the front panel) that must be used to navigate the menus.

It’s possible to create fake input by using cheat codes to navigate through the menus. But there’s not much to explore or do as it’s not running on the correct system. As its name suggests, it just checks the hardware and vice versa and that’s about it.

## CHR Data

General Info

The cartridge is 8 megabit (1,048,576 bytes) LoROM (without header, and all following addresses assume it’s not present).

Internal cart info starting at $007FC0 is almost completely blank except for required values (e.g., reset vector).

Address range $080000-0FFFFF is a mirror of $000000-07FFFF

Cassette is designed only to be used with NUS Checker.

The program doesn’t recognize standard SNES controllers. User I/O is done through register $21C6.

## Patch Info

These address ranges are damaged (approximate):

```
$000980-00FFFF
$0305F0-0306FF
$0D9BA0-0DFFFF
```

The following individual bytes are not the same between mirrors:

```
Offset  - Value, Mirror - Notes
$0000A0 - $00,$80 - $80 is correct, used to jump to address $80C8
$017FFF - $28,$A8 - $A8 is probably correct, unused space area?
$026E22 - $B0,$F8 - $F8 is probably correct, unused space area?
$047D18 - $18,$9A - $9A is probably correct, unused space area?
$047D19 - $48,$EA - $EA is probably correct, unused space area?
$0F9D93 - $FA,$F8 - $FA is probably correct, unused space area?
$0F9F92 - $AB,$A9 - $AB is probably correct, unused space area?
$0F9F93 - $8A,$88 - $8A is probably correct, unused space area?
```

## Patch Codes

Use these patch codes (Action Replay cheats) to skip past error messages and see the different menus.

When you see the Caution message on bootup, enter the following 3 patch codes and then use reset (ie, so the codes are active on bootup).

```
Patch code 008E1380 skips AD CONVERTER ERROR
Patch code 008E9780 skips NUS POWER-ON ERROR
Patch code 008EBB80 skips START SIGNAL ERROR

```

After applying these changes, instead of showing a Caution screen, the screen will be blank for several seconds before the program continues to load.

Next, a screen will appear “DATA SHEET CHECK”. This finishes after several seconds (usually with an error)

When the text EXIT appears on the bottom of the screen, enter patch code 00914600 to view the main menu.

As standard controllers are not supported, to access submenus you must enter one of the following patch code sets, and reset.

After the Data Sheet Check, the selected submenu will appear in place of the main menu.

```
0087B8xx
0087B9yy

XXyy
F8A3 - Clear all data sheets in SHVC cassette
ADA5 - Cassette Check*
A5B3 - Data Sheet Set
29B8 - Data Sheet Copy
54BF - EEPROM Copy
CDC2 - Stand Alone
BAC9 - Dump List
B2CC - Data Sheet Check
85D1 - Cassette Check*
E2D4 - Cassette Check*
```

- When screen is loaded, enter patch code 00A5F380 to proceed to the next screen (won’t work if error “Cannot check this cassette” is displayed).”

## Strings

Below are random strings I found looking through the ROMs.

0x24200: NAK1989 S-CG-CADVer1.11 930511 F

0x81010: DATA SHEET CHECK

0x85580: CASSETTE CHECK

0x810D6: DATA SHEET(S) ARE FIXED.

0x8111A: DATA SHEET(S) ARE LOST.

0x811BC: Various

```
CAUTION
CHECKER IS OUT OF CONTROL
ERROR OCCURED IN CHECKER !!
CANNOT CONTINUE...
PLEASE POWER OFF AND TRY AGAIN
   (NUS POWER-ON ERROR)
   (START SIGNAL ERROR)
   (AD CONVERTOR ERROR)
    (END SIGNAL ERROR)
  (STANDBY SIGNAL ERROR)
 (INT CHECK SIGNAL ERROR)
```

`0x81B76`: Various

```
NUMBER....
CODE...
CIC........
MASKROM........
MBIT
EEPROM.................
KBIT
KBIT
```

`0x821B2`: Various

```
SELECT MODE.                  ----------------OK      
NO DATA SHEET !!              ------------------------
CANNOT RECORD MORE !!         ------------------------
INPUT DATA SHEET.             
CLEAR   EXIT    RECORD  CLEAR ?                       
--------CANCEL  OK      RECORD ?                      
--------CANCEL  OK      OVERWRITE ?                   
--------CANSEL  OK      EXECUTING.....                
------------------------COMPLETE.                     
------------------------CHECK SUM ERROR !!            
------------------------ILLEGAL DATA ERROR !!         
------------------------SELECT COPY DIRECTION.        
--------EXIT    EXECUTE REALLY ?                      
--------CANCEL  OK      CANNOT COPY !!                
------------------------VERIFY ERROR !!               
------------------------DATA SHEET VIEW.              
--------EXIT    --------DELETE ?                      
--------CANCEL  OK      INPUT NUMBER.                 
BY CODE EXIT    OK      INPUT CODE.                   
BY NO   EXIT    OK      NOT FOUND !!                  
------------------------CHECK ?                       
--------CANCEL  OK      CHECK DATA SHEET...           
------------------------ERROR OCCURRED !!             
--------EXIT    --------FORMAT ?                      
--------CANCEL  OK      SELECT COPY DIRECTION AND SIZE
--------CANCEL  OK      NO CASSETTE !!                
------------------------DUMMYDUMMYDUMMYDUMMYDUMMYDUMMY
EDIT    EXIT    --------DUMMYDUMMYDUMMYDUMMYDUMMYDUMMY
--------EXIT    --------DUMMYDUMMYDUMMYDUMMYDUMMYDUMMY
DUMP    EXIT    --------SELECT MODE.                  
--------CANCEL  OK      CANNOT CHECK THIS CASSETTE.   
--------CANCEL  --------SELECT DATA SHEET.            
INSERT CASSETTE.              ATTACH TEST-PIN.          
NOT START CHECK !!            OVER CURRENT !!      
PUSH START BUTTON.            CHECKING...
NOT FINISH CHECK !!           PULLOUT CASSETTE.             
POWER.........................
12V POWER.....................
3.3V VOLTAGE.................
V12V VOLTAGE..................
VEUT RESET-....................
```

```
STAND ALONE
3.3V VOLTAGE:       (  )
3.3V CURRENT:       (  )
 12V VOLTAGE:       (  )
 12V CURRENT:       (  )
BAT. VOLTAGE:       (  )
SRAM VOLTAGE:       (  )
BAT. CURRENT:       (  )
BAT. CURRENT:       (  )
```

## SRAM Strings

These abbreviation strings were located in the SRAM, and a wild guess here, refer to something, many match up with released game codes that I have added next to them:

```
TE16
TE16
NSWP  Star Wars: Shadows of the Empire Japan
NSHJ  Saikyou Haniu Shogi
NSMJ  ShinDou Super Mario 64
NPWJ  Pilotwings 64 Japan
NSME  makerom - NSME (Nintendo Super Mario English)
NPWE  Pilotwings 64 USA
NWRJ  Shindou Wave Race 64 Kawasaki Jet Ski Rumble Japan
NMKE  Mortal Kombat Trilogy (USA)
NWRE  Wave Race 64
NWGE  Wayne Gretzky's 3D Hockey (USA)
NKIE  Killer Instinct Gold
NJ2J  Wonder Project J2 Japan
NCUE  Cruis'N USA
NSWE  Star Wars: Shadows of the Empire USA
NSTJ  St Andrews Old Course Japan
NJPJ  Japanese Jikkyou J League Perfect Striker
NPKJ  King of Pro Baseball Yakyuu
NMMJ  Mahjong Master
NKTJ  Mario Kart 64 Japan
NXGE  NBA Hang Time
NPWP  Pilotwings 64 Europe
NSMP  Super Mario 64 Europe
NWGE  Wayne Gretzky's 3D Hockey (USA)
NSWP  Star Wars: Shadows of the Empire Japan
NTUD  Turok: Dinosaur Hunter Europe
NJPP  International Superstar Soccer 64
NTUP  Turok: Dinosaur Hunter Europe
NKTP  Mario Kart 64 Europe
NGEP  GoldenEye 007 Europe
NWGP  Virtual Pro Wrestling 64
NFXP  Star Fox 64 Europe
NKIP  Killer Instinct Gold Europe
NDMP  Doom 64 Europe
NMRP  Multi Racing Championship Europe
NBMP  Bomberman 64 Europe
NTRP  Top Gear Rally UK
NCFP  ClayFighter 63 1/3 Europe
NQ8P  NFL Quarterback Club 98 Europe
NTMP  Mischief Makers Europe
NLCP  Automobili Lamborghini Scandinavia
NHGP  F1 Pole Position 64 Europe
NDYP  Diddy Kong Racing Europe

N8IP  FIFA 98 UK
NCUP  World Cup 98 USA
NH5P  Winter Olympics '98
NQKP  Quake Nintendo 64
NMYP  Mortal Kombat Mythologies: Sub Zero France
NDHP  Dual Heroes PAL
N8WP  World Cup 98 Europe
NTUD  Turok: Dinosaur Hunter Europe
NFOD  Forsaken 64 (Germany)
NGCP  GT 64: Championship Edition Europe
NBKE  Top Gear Hyper-Bike USA

NKAF  Fighters Destiny France
NKAD  Fighters Destiny Europe
NBKP  Banjo Kazooie Europe

SRAM
TE16
```

There are 3 ROMs provided, one I was sent with the cart from eBay and another when I attempted to dump it, and one patched. The one from the auction seems more correct based on corrupted strings in my own. Not provided with the auction was the SRAM, which has more strings in it.