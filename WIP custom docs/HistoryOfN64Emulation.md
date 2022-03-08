# History of Nintendo 64 emulation

## Nintendo 64 emulators

Project Unreality, released on February 27, 1998, was the first Nintendo 64 emulator that could run several homebrew ROMs and could show the Nintendo 64 logo screen of Mortal Kombat Trilogy and Wave Race 64. It was discontinued after the two main developers decided to join a game development company to create commercial Nintendo 64 games.

UltraHLE, released on January 28, 1999, was so good that it angered Nintendo. The source code to this emulator was leaked, and shortly thereafter it was cancelled and never touched again.

Nemu64, released on December 11, 1998, was one of the first Nintendo 64 emulators that used a plugin system that is still used by Project64 and was used in early versions of Mupen64Plus. It is also known for its extensive debug features which most emulators lack.

Project64 was released on May 26, 2001.

Project64 Legacy is a fork of Project64 with the intention of maintaining compatibility with older operating systems and older plugins. It also has a new ROM database, cheat database, and other small changes.

Project64k was a netplay-focused fork of Project64, but has been discontinued. The AQZ plugin is recommended over this for netplay since it is much more stable and reliable, and Kaillera servers are also not maintained anymore and they are closed-source.

Mupen64, the base to Mupen64Plus, was released December 10, 2001 by Hacktarux. On August 26, 2005, Mupen64 version 0.5 was released. It was the last version of Mupen64 by Hacktarux.

Mupen64Plus's oldest release I could find was 1.3 release candidate 1 on Mar 23, 2008. In October 2007, Mupen64 was forked by Richard Goedeken (richard42). His work went through several releases before settling on the name Mupen64Plus. The original repo has an original create date of Mar 19, 2008.

Sixtyforce is a Mac-exclusive emulator developed by Gerrit Goossen.

## Nintendo 64 RDP plugins

Apparently according to MooglyGuy: "It's got an interesting enough story behind it, too.

Initially, Ville Linde was maintaining the N64 driver in MAME, but after he took a long break, I ended up prodding at it. At some point, angrylion ended up improving it, and split it out into the more standard N64-emulator plugin architecture, and continued to improve it.

Eventually I ported his improvements back over to MAME ca. 10 years ago or so, then proceeded to do a bunch of short-sighted optimizations that in retrospect did more harm than good to the code structure. Meanwhile, angrylion has continued to improve the standalone plugin, but my changes in MAME have unfortunately made it significantly harder to merge the intervening 10 years' worth of fixes from angrylion back in.

At some point I plan to take a stab at just wiping the slate clean and bringing angrylion's fork back into MAME piecemeal, at which point it will still be slow, but at least not slow plus broken in numerous edge cases (and some not-edge cases, like Yoshi's Story).

All this to say, stuff like this makes me glad I went with BSD-3-Clause for the files I had a majority stake in when the relicensing push happened back around 2015 or so. It makes it less of a hassle for other projects to potentially make use of anything I've touched.

That said, I still support the advice to go with paraLLEl-RDP. There's nothing stopping anyone from taking either the RDP code in MAME, or preferably angrylion's current code, and more or less just boxing it into a compute shader and calling it a day, but paraLLEl-RDP is completely turn-key, fast, low-level, and an all-around great thing.

MAME's RDP implementation is based on an old version of angrylion's RDP implementation, which itself is based on a much older version of MAME's implementation. They're completely intertwined, though angrylion's implementation is considerably better than MAME's implementation these days for reasons I outlined further up the thread.

You're right that paraLLEl-RDP is a completely different thing, and honestly, it's what I'd push people in the direction of these days. It's got the right balance of speed, ease of use, and being low-level enough to handle pretty much any edge case."

Angrylion's RDP was released on 2012-02-07

angrylion-rdp-plus was released on Mar 10, 2012

Paralell-RDP was released on May 7, 2020

GLideN64 was released on Oct 1, 2014. Primarily developed by Gonetz and Olivieryuyu

Jabo's Direct3D - 

Rice video - 

Glide64 - 

z64gl - 

HatCat/cxd4's pixel-accurate plugin - 

Shunyuan's SoftGaphic plugin - 

## Nintendo 64 RSP plugins

mupen64plus-rsp-hle was first commited on Oct 22, 2009

cxd4-rsp was first commited to GitHub on Jan 15, 2013

Paralell-RSP was first commited on Jan 29, 2020

z64 RSP plugin's - 

## Nintendo 64 audio plugins

Azimer's audio - Source on GitHub in Oct 2017?

Weinershnitzel Azimer fork - Github commit on April 29, 2015?

Jabo's DirectSound - 

Shunyuan's HLE audio plugin - 

## Nintendo 64 input plugins

Project64-input - 

cxd4-keyboard - 

N-Rage - 
