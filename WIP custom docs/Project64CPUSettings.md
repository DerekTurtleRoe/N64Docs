Project64 settings:

CPU core style: Interpreter or recompiler

Function lookup method: Virtual Lookup Table or Physical Lookup Table

Options that apply to all:

Register caching
Advanced Block Linking (Advanced Block Linking is one of Project64's speed optimisation techniques)
Fast SP

Self-modifiying code methods (recompiler only):

Cache - Clear the address of code on a cache write
PI DMA - Clear the code if it is replace via a DMA from the ROM
Start Changed - When executing a block check if the first 4 instructions are the same, clear if different
TLB Unmapped - If the virtual address is unmapped from RDRAM then flush those blocks
Protect Memory - Change the 4K block where any code is written to read-only, writing to that block will generate an execption, the emulator picks that exception up, flushes the code if any write to the block

Protect memory will be removed.

Counter factor, VI Refresh Rate, AI Count per byte may be removed, or only user configurable.

Unaligned DMA is only used as a hack for compatibility with older ROM hacks.

randomize SI/PI interupts, the time it takes to do a SI/PI dma is about the same each time, but it is not exactly the same number of cycles on real n64. When I have an exact value that never changes, so of the games randomness like super smash brothers, the toy taken out of the box changes, when this is fixed it never does. So that just makes the game a little bit more random.

fixed audio timing, when a audio buffer finishes playing, then it triggers an audio interrupt .. Fixed audio timing, tries to work out how many cycles need to be executed for that audio to be finished playing so it is similar to a real n64 timing. With it off, it uses when it actually finishing on the computer.

lets say a SP dma, is about 12 cycles to set up and 2 cycles per byte, you dma 100 bytes, that is 212 cycles, if you calculating it will always be 212 cycles .. but on a real n64, it might be between 200 and 240 cycles, every time you test it will not be 100% the same value

fixed audio timing is going to give guaranteed constant results .. with it off .. it is possibly going to change based on the hardware your running the emualtor on

I have not done tests on dma timing in a long time, so I could be off .. but I remember when I first stated to add timing for dma, I could not write a test for it cause the values kept changing

the cpu and the dma and ram are different chips so it depends on I guess temperatures of machine and I do not know what exactly causes the variation

I am software not hardware :)

most things wait for dma to finish before trying to do anything with it

