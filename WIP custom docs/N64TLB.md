N64 TLB
Jump to navigationJump to search
A virtual address is converted into a physical address by using the internal TLB. The internal TLB is a full-associative memory having 32 entries, and one entry is mapped with an odd and even numbers in pairs. The size of these pages can be 4K, 16K, 64K, 256K, 1M, 4M, or 16M, and can be specified for each entry. When a virtual address is given, each TLB entry checks the 32 entries whether the virtual address coincides with the virtual address appended with the ASID area stored to the Entry Hi register. If the addresses coincide (if a hit occurs), a physical address is generated from the physical address in the TLB and an offset. If the addresses do not coincide (if a miss occurs), an exception occurs, and the TLB entry is written by software from a page table on the memory. The software either writes the TLB entry over the entry selected by the index register, or writes it to a random entry indicated by the random register. If there are two or more TLB entries that coincide, the TLB operation is not correctly executed. In this case, the TLB-Shutdown (TS) bit of the status register is set to 1, and then the TLB cannot be used.

Virtual-to-Physical Address Translation
Converting a virtual address to a physical address begins by comparing the virtual address from the processor with the virtual addresses in the TLB; there is a match when the virtual page number (VPN) of the address is the same as the VPN field of the entry, and either:

the Global (G) bit of the TLB entry is set, or
the ASID field of the virtual address is the same as the ASID field of the TLB entry.
This match is referred to as a TLB hit. If there is no match, a TLB Miss exception is taken by the processor and software is allowed to reference a page table of virtual/physical addresses in memory and to write its contents to the TLB. If there is a virtual address match in the TLB, the physical address is output from the TLB and concatenated with the Offset, which represents an address within the page frame space. The Offset does not pass through the TLB. The lower bits of the virtual address are output as is.

COP0 Registers
Operating Mode

An in-depth look at the Translation Lookaside Buffer
I figured I'd not "reinvent the wheel" since Viper182 already noted this in his hacking tutorial and servers as a good synopses and brief rundown for parasyte's more in-depth elaboration below.


TLB mapping is pretty evil in the eyes of ASM hackers. This is the reason you don't see 1337 ASM codes for Goldeneye and very few for Perfect Dark. It's like some kind of address aliasing. When you set a breakpoint on Goldeneye, for example, the PC address returned will be something other than the real PC address; in Goldeneye's case you'll get an address beginning with something like '7F' instead of '80'. There's no known way to get around it on the console, but you can with Nemu 0.8. If you set a Breakpoint on a TLB mapped game in Nemu, you'll see all the opcodes in the TLB addresses. The trick is finding the real ones. Rightclick the break address and choose the --> Memory Debugger. This will bring up the memory editor, but notice the addresses shown are the same address you saw in the debugger (TLB mapped). Look at the 32-Bit value of the first (break) address there. Bring up the Search window and do a 32-Bit search for that value. If you got more than 1 result, you'll have to figure out which one it is by comparing the opcodes before/after the one you searched for. There you have it, you got around one of the most evil programming tricks in the book. :) [1]

The following was done by parasyte

FORMATS

EntryLo0 & EntryLo1:
 00 pppppppppppppppppppppppp ccc d v g
 (32-bit: 2.24.3.1.1.1)

 p = Page frame number; the upper bits of the physical address.
 c = Specifies the TLB page coherency attribute. (See below)
 d = Dirty. If this bit is set, the page is marked as dirty and, therefore, writable
     This bit is actually a write-protect bit that software can use to prevent alteration
     of data.
 v = Valid. If this bit is set, it indicated that the TLB entry is valid; otherwise, a
     TLBL or TLBS miss occurs.
 g = Global. If this bit is set in both Lo0 and Lo1, then the process ignores the ASID
     during TLB lookup.


PageMask:
 0000000 mmmmmmmmmmmm 0000000000000
 (32-bit: 7.12.13)

 m = Page comparison mask


EntryHi:
 vvvvvvvvvvvvvvvvvvv 00000 aaaaaaaa
 (32-bit: 19.5.8)

 v = Virtual page number divided by 2 (maps to two pages)
 a = Address space ID field. (ASID) An 8-bit field that lets multiple processes share
     the TLB; each process has a distinct mapping of otherwise identical virtual page
     numbers.
NOTES ON TLB PAGE COHERENCY (c bits)

The TLB page coherency attribute (C) bits specify whether references to the page should be cached; if cached, the algorithm selects between several coherency attributes. The table below shows the coherency attributes selected by the C bits.

TLB Page Coherency (C) Bit Values

Reserved
Reserved
Uncached
Cacheable noncoherent (noncoherent)
Cacheable coherent exclusive (exclusive)
Cacheable coherent exclusive on write (sharable)
Cacheable coherent update on write (update)
Reserved
TRANSLATING VIRTUAL ADDRESSES TO PHYSICAL ADDRESSES

In order to translate virtual to physical addresses, you must be able to read each TLB entry, looking for a virtual address hit.

Start by dumping the TLB entries one-by-one. First, load the CP0 Index register withthe TLB entry index you wish to dump. You should start with 0x00, and work your way up to 0x2F. That gives 48 total TLB entries. After loading CP0 Index with the entry number, call a TLBR instruction. This will dump the TLB entry to the EntryLo0, EntryLo1, PageMask, and EntryHi registers in the formats described above.

After the TLB entry has been dumped, begin decoding the data in each register.

To decode a TLB entry, start with the m bits from the PageMask register. This value tells the size of a virtual page for the TLB entry. The page size can be determined by checking the values against the following table.

0x0000: 4KB   (0x1000 bytes)
0x0003: 16KB  (0x4000 bytes)
0x000F: 64KB  (0x10000 bytes)
0x003F: 256KB (0x40000 bytes)
0x00FF: 1MB   (0x100000 bytes)
0x03FF: 4MB   (0x400000 bytes)
0x0FFF: 16MB  (0x1000000 bytes)
If the value is anything other than listed, the page size is undefined\erroneous. Here is a bit of C which will allow you to grab the page size and a page mask:

u32 mask = (PageMask >> 1) | 0x0FFF;
u32 pagesize = mask+1;


Next, extract the virtual page number from EntryHi, based on PageMask.

u16 tmp = PageMask | 0x1FFF;
u32 vpn = EntryHi & ~tmp;
Then use the virtual page number as a mask to the virtual address. If the result is the same as the vpn, it's counted as a hit. If not, restart the process with the next TLB index.

if ((vaddr & vpn) != vpn) continue;
If it's a hit, find out if the virtual address is on an odd or even page, based on the TLB page size.

u32 odd = vaddr & pagesize;
Now perform a bitwise AND on EntryLo0 or EntryLo1, depending on the 'odd' variable. If the result is 0, the page frame is invalid. If successful, extract the page frame number. If not, restart the process with the next TLB index.

u32 pfn;
if (!odd) {
  if (!(EntryLo0 & 0x02)) continue;
  pfn = (EntryLo0 >> 6) & 0x00FFFFFF;
}
else {
  if (!(EntryLo1 & 0x02)) continue;
  pfn = (EntryLo1 >> 6) & 0x00FFFFFF;
}
Finally, if it gets this far, mask the virtual address with the 'mask' variable created earlier. Then attach the physical page number, and OR with 0x80000000 to complete the process. Lastly, exit the loop. Checking the remaining entries for a hit is not required.

u32 paddr = (0x80000000 | (pfn * pagesize) | (vaddr & mask));
break;
And there you have it! Your paddr variable will be a pointer to the translated address. Now you should be able to use this info to add a new N64 code type to your AR ROM. Maybe the code type could be something like this...

4sxxxxxx nnnn
aaaaaaaa vvvv
Where s is the size, 8- or 16-bit, x's can be expanded on later, n's are the number of virtual addresses following. a's and v's are the virtual address, and value to write, respectively. The number of a\v lines following the 4-code will be determined by nnnn+1, giving a total of 65536 virtual addresses, max. If that's too much, use 00nn, for 256 total.

An example TLB code for GoldenEye 007 would look like this:

Infinite Health, All Levels
41000000 0000
7F089CC0 2400
This code would work great, because the virtual address is always 7F089CC0, but the physical address changes after you exit a level. If it's possible to simply write to the virtual address, bypassing all the manual translation, then by all means, do it that way. Either way, TLB codes are needed.