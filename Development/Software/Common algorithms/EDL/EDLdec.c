/*EDL decompressor
  decompresses EDL 0,1,2 files as found in TWINE (N64)
  c/o Noah 'Zoinkity' Granath (nefariousdogooder@yahoo.com) Oct. 2008

  You're free to do as you see fit with the source,
  but in all honesty you'd be better off rewritting it
  (I'm really crappy at this sort of thing)
*/
#include <stdio.h>
#include <stdlib.h>

/*#define DATATABLE_32BIT       /*some older systems just don't support long long*/
/*#define DEBUGGERY             /*debug: allocated what[]*/

/*I don't feel like passing these flags around
  so, now its a global variable.  Seriously, it's not that big a deal*/
struct bit_field{
       unsigned int swap      :1;
       unsigned int message   :1;
       unsigned int table     :1;
       unsigned int quiet     :1;
       unsigned int trash     :1;
       } flagrant;

typedef struct {
       unsigned long csize;  /*compressed size*/
       unsigned long dsize;  /*decompressed size*/
       unsigned char type;    /*compression type 0-2*/
       unsigned char endian;  /*big(1) or little(0) endian*/
       } EDL;

/*standard 32bit byteswapping*/
unsigned long byteswap(unsigned long w)
{return (w >> 24) | ((w >> 8) & 0x0000ff00) | ((w << 8) & 0x00ff0000) | (w << 24);
}    

/*standard 16bit byteswapping*/
unsigned short int shortswap(unsigned short int w)
{return (w >> 8) | (w << 8);}

/*flip nibble - optional*/
unsigned char nibswap(unsigned char w)
{return (w>>4) | (w<<4);}

unsigned long swapfile(FILE *in,FILE *out)
{unsigned long x,y;
unsigned char z;

fseek(in,0,SEEK_END);
x=ftell(in);

for(y=0;y<x;y++)
   {fseek(in,y,SEEK_SET);
   z=fgetc(in);
   z=nibswap(z);
   fseek(out,y,SEEK_SET);
   fputc(z,out);
   }

return ftell(out);}

/*error messages*/
int erratta(long code)
{switch(code)
       {case -8: fprintf(stderr,"\a\nNot a valid table entry"); break;
        case -9: fprintf(stderr,"\a\nSamples exceed maximum bitcount"); break;
        default: fprintf(stderr,"\a\nUnknown error %i",code); code=0;
        }
return code;}

/*returns FILE offset to next EDL file, or -1 if not found*/
unsigned long EDLscan(FILE *in, unsigned long pos)
{unsigned long end;

fseek(in,0,SEEK_END);
end=ftell(in);
rewind(in);

while(pos<end)
  {fseek(in,pos,SEEK_SET);
  if(fgetc(in)=='E')
    {if(fgetc(in)=='D')
       {if(fgetc(in)=='L') return pos;
       }
    }
  pos++;
  }

return end;}

/*Fills an EDL struct with candy.  White hot candy*/
int FillEDL(EDL *data, FILE *in, unsigned long pos)
{unsigned long x=0;
    
fseek(in,pos+3,SEEK_SET);
x=fgetc(in);
data->type=x&0xF;
data->endian=x>>7;

fread(&x,4,1,in);
if(data->endian) x=byteswap(x);
data->csize=x;
fread(&x,4,1,in);
if(data->endian) x=byteswap(x);
data->dsize=x;

return 0;}

/*These are the three known decompression routines as stripped from TWINE (N64)
  as a note, the endian value is not used,
  since I can't confirm that it is used outside of the header size values
  Each returns the size of the decompressed file, which can be tested against expected*/
/*store*/
unsigned long EDLdec0(unsigned long pos,FILE *in,FILE *out,unsigned long size,unsigned long max,int endian)
{size+=pos;   /*end of file*/

for(pos+=12;pos<size;pos++)
   {fseek(in,pos,SEEK_SET);
   fputc(fgetc(in),out);
   if(feof(in)) break;
   }
return ftell(out);}

/*this handles the mess of dealing with the 64bit data word,its count, etc
  granted, it doesn't handle it very well, but it does handle it...
  It is nice enough not to devastate anything if you call it when unnecessary*/

/*Older compilers and systems may not support a 64bit datatable
  so, a 32bit version of this table is provided here
  the 64bit one works much faster (fewer table expansions, less file access, etc)
  Note, the definition for the function is different*/
#ifdef DATATABLE_32BIT
unsigned long helper(unsigned long *data,unsigned long bitcount,FILE *in,unsigned long *pos,unsigned long max,int endian)
{unsigned long x,y,z;

if(bitcount>16) return bitcount;   /*essentially, do nothing!*/
z=*data;
y=0;
x=max-*pos;
if(x>2) x=2;   /*#bytes to retrieve from file*/
fseek(in,*pos,SEEK_SET);
fread(&y,x,1,in);
if(endian) y=shortswap(y);
*pos+=x;

*data=y;       /*tack old data on the end of new data for a continuous bitstream*/
*data=*data<<bitcount;
*data|=z;

x*=8;          /*revise bitcount with number of bits retrieved*/
return bitcount+x;}
#else
unsigned long helper(unsigned long long int *data,unsigned long bitcount,FILE *in,unsigned long *pos,unsigned long max,int endian)
{unsigned long x,y,z;

if(bitcount>32) return bitcount;   /*essentially, do nothing!*/
z=*data;
y=0;
x=max-*pos;
if(x>4) x=4;   /*#bytes to retrieve from file*/
fseek(in,*pos,SEEK_SET);
fread(&y,x,1,in);
if(endian) y=byteswap(y);
*pos+=x;

*data=y;       /*tack old data on the end of new data for a continuous bitstream*/
*data=*data<<bitcount;
*data|=z;

x*=8;          /*revise bitcount with number of bits retrieved*/
return bitcount+x;}
#endif

/*generate tables*/
int FillBuffer(unsigned short *large,unsigned char *what,long total,long num,char bufsize)
{unsigned char *buf;
unsigned short *when,*samp,numero=1;
unsigned long *number;
long x,y,z,back;

if(flagrant.table)
  {unsigned char filename[20];
  unsigned short jack;
  unsigned long herb;
  FILE *debuggery;

  sprintf(filename,"what%04i.bin",numero);
  while(debuggery = fopen(filename, "rb"))
   {fclose(debuggery);
   numero++;
   sprintf(filename,"what%04i.bin",numero);
   }
  debuggery=fopen(filename,"wb");

  for(jack=0;jack<total;jack++)
   {herb=what[jack];
   herb=byteswap(herb);
   fwrite(&herb,1,4,debuggery);
   }
  fclose(debuggery);
}/*end debug table*/

       /*my implementation is stupid and alays copies the block, so this uses even more memory than it should
       if(!(what=realloc(what,num))
           {printf("\nVirtual memory exhausted.\nCan not continue.\n\tPress ENTER to quit.");
           getchar();
           return 0;
           }*/
       if(!(when=calloc(num,2)))
         {printf("\nVirtual memory exhausted.\nCan not continue.\n\tPress ENTER to quit.");
         getchar();
         return 0;
         }/*end calloc*/
       if(!(samp=calloc(num,2)))
         {printf("\nVirtual memory exhausted.\nCan not continue.\n\tPress ENTER to quit.");
         getchar();
         return 0;
         }/*end calloc*/
       if(!(number=calloc(16,4)))
         {printf("\nVirtual memory exhausted.\nCan not continue.\n\tPress ENTER to quit.");
         getchar();
         return 0;
         }/*end calloc*/
       memset(large,0,0xC00);         /*both buffers have 0x600 entries each*/

       /*build an occurance table*/
       back=0;  /*back will act as a counter here*/
       for(y=1;y<16;y++)/*sort occurance*/
          {for(x=0;x<total;x++)/*peek at list*/
                {if(what[x]==y)
                   {when[back]=x;
                   back++;
                   number[y]++;
                   }
                }/*end peek*/
          }/*end occurance*/

if(flagrant.table)
  {unsigned char filename[20];
  unsigned short jack;
  unsigned long herb;
  FILE *debuggery;

  sprintf(filename,"when%04i.bin",numero);
  debuggery=fopen(filename,"wb");

  for(jack=0;jack<num;jack++)
   {herb=when[jack];
   herb=byteswap(herb);
   fwrite(&herb,1,4,debuggery);
   }
  fclose(debuggery);
}

       x=0;
       for(y=1;y<16;y++)/*sort nibbles*/
          {for(z=number[y];z>0;z--) 
              {what[x]=y; x++;}
          }/*end sort*/
       free(number);

if(flagrant.table)
  {unsigned char filename[20];
  unsigned short jack;
  unsigned long herb;
  FILE *debuggery;

  sprintf(filename,"order%04i.bin",numero);
  debuggery=fopen(filename,"wb");

  for(jack=0;jack<num;jack++)
   {herb=what[jack];
   herb=byteswap(herb);
   fwrite(&herb,1,4,debuggery);
   }
  fclose(debuggery);
}
       
       /*generate bitsample table*/
       z=what[0];           /*first sample, so counting goes right*/
       back=0;              /*back will act as the increment counter*/
       for(x=0;x<num;x++)
          {y=what[x];
          if(y!=z) {z=y-z; back*=(1<<z); z=y;}
          y=(1<<y)|back;
          back++;
          do{samp[x]=samp[x]<<1;
             samp[x]+=(y&1);
             y=y>>1;
             }while(y!=1);
          }/*end bitsample table*/

if(flagrant.table)
  {unsigned char filename[20];
  unsigned short jack;
  unsigned long herb;
  FILE *debuggery;

  sprintf(filename,"samples%04i.bin",numero);
  debuggery=fopen(filename,"wb");

  for(jack=0;jack<num;jack++)
   {herb=samp[jack];
   herb=byteswap(herb);
   fwrite(&herb,1,4,debuggery);
   }
  fclose(debuggery);
}

       if(!(buf=calloc(1<<bufsize,1)))
         {printf("\nVirtual memory exhausted.\nCan not continue.\n\tPress ENTER to quit.");
         getchar();
         return 0;
         }/*end calloc      80013918*/
       
       for(x=0;x<num;x++)  /*fill buffer    8001392C*/
          {back=what[x];      /*#bits in sample*/
          if(back<bufsize)         /*normal entries*/
            {y=1<<back;
             z=samp[x];       /*offset within buffer*/
            do{
              large[z]=(when[x]<<7) + what[x];
              z+=y;
              }while(!(z>>bufsize));
            }/*end normal*/
          else
            {y=(1<<bufsize)-1; /*this corrects bitmask for buffer entries*/
            z=samp[x]&y;
            buf[z]=what[x];
            }/*end copies*/
          }/*end fill*/

if(flagrant.table)
  {unsigned char filename[20];
  unsigned short jack;
  unsigned long herb;
  FILE *debuggery;

  sprintf(filename,"table1%04i.bin",numero);
  debuggery=fopen(filename,"wb");

  for(herb=0;herb<(1<<bufsize);herb++)
   {jack=large[herb];
   jack=shortswap(jack);
   fwrite(&jack,1,2,debuggery);
   }
  fclose(debuggery);

  sprintf(filename,"buf%04i.bin",numero);
  debuggery=fopen(filename,"wb");

  for(jack=0;jack<(1<<bufsize);jack++)
   {herb=buf[jack];
   fwrite(&herb,1,1,debuggery);
   }
  fclose(debuggery);
}
       
       /*read coded types > bufsize    80013AA8*/
       z=0;      /*value*/
       for(x=0;!(x>>bufsize);x++)/*read buf*/
          {y=buf[x];
          if(y)
            {y-=bufsize;
            if(y>8) return -8;
            back=(z<<7) + (y<<4);  /*value*0x80 + bits<<4*/
            large[x]=back;
            z+=(1<<y);
            }/*end if(y)*/
          }/*end buf reading*/
       free(buf);
       if(z>0x1FF) return -9;
/*
if(flagrant.table)
  {unsigned char filename[20];
  unsigned short jack;
  unsigned long herb;
  FILE *debuggery;

  sprintf(filename,"table2%04i.bin",numero);
  debuggery=fopen(filename,"wb");

  for(herb=0;herb<(1<<bufsize);herb++)
   {jack=large[herb];
   jack=shortswap(jack);
   fwrite(&jack,1,2,debuggery);
   }
  fclose(debuggery);
}
*/
       /*do something tricky with the special entries    80013B3C*/
       back=1<<bufsize;
       for(x=0;x<num;x++)
          {if(what[x]<bufsize) continue;
          z=samp[x] & (back-1);
          z=large[z];     /*in dASM, this is labelled 'short'*/
          y=samp[x]>>bufsize;
          /*80013BEC*/
          do{large[y+(z>>7)+(1<<bufsize)]=(when[x]<<7)+what[x];
             y=y+(1<<(what[x]-bufsize));
             }while((y>>((z>>4)&7))==0);
          }
       free(when);
       free(samp);

if(flagrant.table)
  {unsigned char filename[20];
  unsigned short jack;
  unsigned long herb;
  FILE *debuggery;
  
  sprintf(filename,"table3%04i.bin",numero);
  debuggery=fopen(filename,"wb");

  for(herb=0;herb<((1<<bufsize)+0x200);herb++)
   {jack=large[herb];
   jack=shortswap(jack);
   fwrite(&jack,1,2,debuggery);
   }
  fclose(debuggery);
}
       
return 0;}


/*cool bitwise table type*/
unsigned long EDLdec1(unsigned long pos,FILE *in,FILE *out,unsigned long size,unsigned long max,int endian)
{unsigned char bits[9];  /*what=p->list of slots*/
long x,y,z,stack=0;
unsigned long count=0,num,back;  /*count=#bits in register, num=#to copy, back=#to backtrack*/
unsigned short small[0x600],large[0x600];   /*when=p->occurance in list*/
unsigned char  table1[]={0,1,2,3,4,5,6,7,8,0xA,0xC,0xE,0x10,0x14,0x18,0x1C,0x20,0x28,0x30,0x38,0x40,0x50,0x60,0x70,0x80,0xA0,0xC0,0xE0,0xFF,0,0,0};
unsigned char  table2[]={0,0,0,0,0,0,0,0,1,1,1,1,2,2,2,2,3,3,3,3,4,4,4,4,5,5,5,5,0,0,0,0};
unsigned short table3[]={0,1,2,3,4,6,8,0xC,0x10,0x18,0x20,0x30,0x40,0x60,0x80,0xC0,0x100,0x180,0x200,0x300,0x400,0x600,0x800,0xC00,0x1000,0x1800,0x2000,0x3000,0x4000,0x6000};
unsigned char  table4[]={0,0,0,0,1,1,2,2,3,3,4,4,5,5,6,6,7,7,8,8,9,9,0xA,0xA,0xB,0xB,0xC,0xC,0xD,0xD,0,0};
#ifdef DEBUGGERY
unsigned char *what;
#else
unsigned char what[0x400];
#endif
#ifdef DATATABLE_32BIT
unsigned long data=0;
#else
unsigned long long data=0;       /*64bit datatable container*/
#endif

size+=pos;

for(pos+=12;pos<=size;back=0)
   {memset(bits,0,8); /*clear bits between... stuff*/
   count=helper(&data,count,in,&pos,size,endian);
   x=data&1; data=data>>1; count--;
   
   if(x)     /*mode 1 - tables*/
     {count=helper(&data,count,in,&pos,size,endian);/*build large table*/
     x=data&0x1FF; data=data>>9; count-=9;
     if(flagrant.message) printf("\nmode1\tpos: %X\tout: %X\tdata: %X",pos,ftell(out),data);
     if(x) /*construct tables*/
       {
#ifdef DEBUGGERY
       if(!(what=calloc(x,1)))
         {printf("\nVirtual memory exhausted.\nCan not continue.\n\tPress ENTER to quit.");
         getchar();
         return 0;
         }/*end calloc*/
#else
       memset(what,0,0x400);
#endif
       num=0;    /*true # entries, since 0 entries are not counted!*/
       for(y=0;y<x;y++)/*fill table with nibbles*/
          {count=helper(&data,count,in,&pos,size,endian);
          back=data&1; data=data>>1; count--;
          if(back)/*grab nibble*/
            {count=helper(&data,count,in,&pos,size,endian);
            stack=data&0xF; data=data>>4; count-=4;
            }/*end grab*/
          what[y]=stack;
          if(stack) num++;   /*count nonzero entries*/
          }/*end fill*/
       x=FillBuffer(large,what,x,num,10);
#ifdef DEBUGGERY
       free(what);
#endif
       }/*end construction*/
     if(x<0) {x=erratta(x);
             if(x) return x;}

     count=helper(&data,count,in,&pos,size,endian);/*build smaller table*/
     x=data&0x1FF; data=data>>9; count-=9;
     if(x) /*construct tables*/
       {
#ifdef DEBUGGERY
       if(!(what=calloc(x,1)))
         {printf("\nVirtual memory exhausted.\nCan not continue.\n\tPress ENTER to quit.");
         getchar();
         return 0;
         }/*end calloc*/
#else
       memset(what,0,0x400);
#endif
       num=0;    /*true # entries, since 0 entries are not counted!*/
       for(y=0;y<x;y++)/*fill table with nibbles*/
          {count=helper(&data,count,in,&pos,size,endian);
          back=data&1; data=data>>1; count--;
          if(back)/*grab nibble*/
            {count=helper(&data,count,in,&pos,size,endian);
            stack=data&0xF; data=data>>4; count-=4;
            }/*end grab*/
          what[y]=stack;
          if(stack) num++;   /*count nonzero entries*/
          }/*end fill*/
       x=FillBuffer(small,what,x,num,8);
#ifdef DEBUGGERY
       free(what);
#endif
       }/*end construction*/
     if(x<0) {x=erratta(x);
             if(x) return x;}
     
     /*write data*/
    do{
     count=helper(&data,count,in,&pos,size,endian);/*build smaller table*/
     x=data&0x3FF;
     x=large[x];          /*x=short from thingy*/
     y=x&0xF;             /*y=normal bitcount*/
     z=(x>>4)&7;       /*z=backtrack bitcount*/
     if(flagrant.message) printf("\n\tout: %X\tsample: %04X\tvalue: %X\tdata: %X",ftell(out),x,x>>7,data);
     if(y==0)  /*backtrack entry*/
       {x=x>>7; /*short's data*/
        y=(1<<z)-1;       /*bitmask*/
        count=helper(&data,count,in,&pos,size,endian);
        y=(data>>10)&y;
        x+=y;
        x=large[x+0x400];
        y=x&0xF;
        }/*end backtrack entry*/
     
     data=data>>y; count-=y;
     y=0;
     x=x>>7;       /*data only*/
     if(x<0x100) 
       {fputc(x,out);
       if(ftell(out)>max) return ftell(out);}
     else if(x>0x100)/*copy previous*/
        {z=table2[x-0x101];
        if(z)        /*segment*/
          {count=helper(&data,count,in,&pos,size,endian);
          y=(1<<z)-1;  /*mask*/
          y=data&y; data=data>>z; count-=z;
          }        /*end segment*/
        z=table1[x-0x101];
        num=z+y+3;
        count=helper(&data,count,in,&pos,size,endian);
        x=data&0xFF; x=small[x];

        y=x&0xF;             /*y=normal bitcount*/
        z=(x&0x70)>>4;       /*z=backtrack bitcount*/
        if(y==0)  /*backtrack entry*/
          {x=x>>7; /*short's data*/
          y=(1<<z)-1;       /*bitmask*/
          count=helper(&data,count,in,&pos,size,endian);
          y=(data>>8)&y;
          x+=y;
          x=small[x+0x100];
          y=x&0xF;
          }/*end backtrack entry*/
        data=data>>y; count-=y;
        
        /*pull number of bits*/
        y=0;
        x=x>>7;
        z=table4[x];
        if(z)        /*segment*/
          {count=helper(&data,count,in,&pos,size,endian);
          y=data&((1<<z)-1); data=data>>z; count-=z;
          }        /*end segment*/
        z=table3[x];
        back=z+y+1;

        /*copy run*/
        for(x=0;num>0;num--)
           {z=ftell(out)-back;
           if(z<0 || z>=ftell(out)) x=0;
           else{fseek(out,0-back,SEEK_END);     /*backward position*/
               x=fgetc(out);
               }
           fseek(out,0,SEEK_END);
           fputc(x,out);
           if(ftell(out)>max) return ftell(out);     /*failsafe*/
           }/*end copy run*/
/*        for(x=0;num>0;num-=x)      this is faster but would need a catch
           {x=num;                   to keep it from copying bytes that have
           if(x>8) x=8;              not yet been written
           fseek(out,0-back,SEEK_END);
           fread(bits,1,x,out);
           fseek(out,0,SEEK_END);
           fwrite(bits,1,x,out);
           if(ftell(out)>max) return ftell(out);
           }end debug-sometime-later*/
        }/*end copy previous*/
    }while(x!=0x100);     
   }/*mode 1*/
   else      /*mode 0 - */
     {count=helper(&data,count,in,&pos,size,endian);
     num=data&0x7FFF; data=data>>15; count-=15;
     if(flagrant.message) printf("\nmode0\tpos: %X\tout: %X",pos,ftell(out));
     if(num) 
       {for(fseek(out,0,SEEK_END);num>0;num--)
           {count=helper(&data,count,in,&pos,size,endian);
           x=data&0xFF; data=data>>8; count-=8;
           fputc(x,out);
           }/*end for()*/
       }/*write bytes*/
     }/*mode 0*/

   /*test EOF*/
   count=helper(&data,count,in,&pos,size,endian);
   x=data&1; data=data>>1; count--;
   if(x) return ftell(out);        /*1=EOF marker*/
   }

return ftell(out);}

/*boring RLE magic*/
unsigned long EDLdec2(unsigned long pos,FILE *in,FILE *out,unsigned long size,unsigned long max,int endian)
{unsigned char bits[9];
long x;
unsigned long count=0,num,back;  /*count=#bits in register, num=#to copy, back=#to backtrack*/
#ifdef DATATABLE_32BIT
unsigned long data=0;
#else
unsigned long long int data=0;       /*64bit datatable container*/
#endif

/*set up data and count*/
size+=pos;

for(pos+=12;pos<=size;back=0)
   {memset(bits,0,9); /*clear bits between... stuff*/
   count=helper(&data,count,in,&pos,size,endian);
   x=data&1; data=data>>1; count--;
   if(x)     /*mode 1 - copy*/
     {count=helper(&data,count,in,&pos,size,endian);
     bits[0]=data&1; bits[1]=(data&2)>>1; bits[2]=(data&4)>>2; bits[3]=(data&8)>>3;
     if(flagrant.message) {printf("\nmode1\tpos: %X\tout: %X\tdata: %X",pos,ftell(out),data);
                           printf("\n\t%X%X%X%X",bits[0],bits[1],bits[2],bits[3]);}
     if(bits[0]) {/*bit1:1*/
           num=2;
           data=data>>2; count-=2;
           if(bits[1]) 
             {data=data>>1; count--;
             num++;
             bits[8]=3;
             if(bits[2])
               {bits[8]=11;
               count=helper(&data,count,in,&pos,size,endian);
               num=data&0xFF; data=data>>8; count-=8;
               if(num==0) return ftell(out);   /*this implies #bytes=0, signifying EOF*/
               num+=8;
               }/*bits[2]*/
             }/*bits[1]*/
           }/*bits[0]=1*/
     else{
         bits[8]=3;
         num=4;
         data=data>>3; count-=3;     /*minimum shift*/
         if(bits[1]) num++;
         if(bits[2])
           {bits[8]=4;
           data=data>>1; count--;
           num=2*(num-1)+bits[3];
           if(num==9)          /*special case write mode*/
             {count=helper(&data,count,in,&pos,size,endian);
             num=data&0xF; data=data>>4; count-=4;
             num*=4;
             for(num+=12;num>0;num--)
                {count=helper(&data,count,in,&pos,size,endian);
                 x=data&0xFF; data=data>>8; count-=8;
                 fputc(x,out);
                 if(ftell(out)>max) return ftell(out);     /*failsafe*/
                }
             continue;
             }/*num==9*/
           }/*bits[2]*/
          }/*bits[0]=0*/

     if(bits[8])        /*handle those backward offset types*/
       {count=helper(&data,count,in,&pos,size,endian);  /*copy next 6, then work out size*/
       bits[0]=data&1; bits[1]=(data&2)>>1; 
       bits[2]=(data&4)>>2; bits[3]=(data&8)>>3;
       bits[4]=(data&0x10)>>4; bits[5]=(data&0x20)>>5;
       data=data>>1; count--;
       if(flagrant.message) printf("\t%X\t%X%X%X%X%X%X",bits[8],bits[0],bits[1],bits[2],bits[3],bits[4],bits[5]);
       
       if(bits[0])
         {if(bits[2])
            {if(bits[4])       /*10101 10111 11101 11111*/
               {data=data>>4; count-=4;
               back=0x400;
               if(bits[1]) back+=0x200;
               if(bits[3]) back+=0x100;
               }/*end bits[4]*/
             else              /*101000 101001 101100 101101 111000 111001 111100 111101*/
               {data=data>>5; count-=5;
               back=0x800;
               if(bits[1]) back+=0x400;
               if(bits[3]) back+=0x200;
               if(bits[5]) back+=0x100;
               }/*end bits[4]==0*/
            }/*end bits[2]*/
         else        /*bits[2]==0*/
            {if(bits[1])           /*110*/
               {back=0x100;
               data=data>>2; count-=2;
               }
            else                   /*1000 1001*/
               {data=data>>3; count-=3;
               back=0x200;
               if(bits[3]) back+=0x100;
               }
            }/*end bits[2]==0*/
         }/*end bits[0]*/  
       }/*bits[8]*/
     
     /*get the backward offset*/
     count=helper(&data,count,in,&pos,size,endian);
     back=(data&0xFF)+back+1;        /*assured to copy at least 1 byte*/
     data=data>>8; count-=8;
     if(flagrant.message) printf("\n\tnum: %X\tback: %X",num,back);
     /*copy data from source*/
        for(x=0;num>0;num--)
           {x=ftell(out)-back;
           if(x<0 || x>=ftell(out)) x=0;
           else{fseek(out,0-back,SEEK_END);     /*backward position*/
               x=fgetc(out);
               }
           fseek(out,0,SEEK_END);
           fputc(x,out);
           if(ftell(out)>max) return ftell(out);     /*failsafe*/
           }/*end copy run*/
/*        for(x=0;num>0;num-=x)      this is faster but would need a catch
           {x=num;                   to keep it from copying bytes that have
           if(x>8) x=8;              not yet been written
           fseek(out,0-back,SEEK_END);
           fread(bits,1,x,out);
           fseek(out,0,SEEK_END);
           fwrite(bits,1,x,out);
           if(ftell(out)>max) return ftell(out);
           }end debug-sometime-later*/    
     }/*if()*/
   else{     /*mode 0 - push one byte to output*/
        count=helper(&data,count,in,&pos,size,endian);
        if(flagrant.message) printf("\nmode0\tpos: %X\tout: %X\tdata: %X",pos,ftell(out),data);
        x=data&0xFF; data=data>>8; count-=8;
        fputc(x,out);
        if(ftell(out)>max) return ftell(out);     /*failsafe*/
        }
   }

return ftell(out);}

/*open files, etc*/
int main(int argc, char *argv[])
{char filename[130];
FILE *in,*out;
EDL edl;
unsigned long x,end,cur=0;

flagrant.quiet=1;
flagrant.message=0;
flagrant.swap=0;
flagrant.table=0;
flagrant.trash=0;

for(x=1;x<argc;x++)
    {if(argv[x][0]=='-' || argv[x][0]=='/')
      {switch(argv[x][1])
             {case 'Q': case 'q': flagrant.quiet^=1;      break;
              case 'D': case 'd': flagrant.message^=1;    break;
              case 'S': case 's': flagrant.swap^=1;       break;
              case 'T': case 't': flagrant.table^=1;      break;
              case 'X': case 'x': flagrant.trash^=1;      break;
              case 'H': case 'h': case '?':
                  printf("\nEDL 0-2 decompressor for TWINE (N64)");
                  printf("\n  /Q or -Q\t+\tquiet mode\tonly error text is displayed");
                  printf("\n  /S or -S\t+\tswaps nibbles in output.");
                  printf("\n  /D or -D\t+\tdisplays EDL1/2 debug information");
                  printf("\n  /X or -X\t+\tno output file");
                  printf("\n  /T or -T\t+\toutputs EDL1 intermediary tables for debugging");
                  printf("\n  /H, -H, or -?\tdisplay this help message");
                  printf("\n\n\tPress -enter- to quit\n"); getchar(); return 0;
              }    
      }
    else strcpy(filename,argv[x]);
    }

while (!(in = fopen(filename, "rb"))) {
	printf("\nEDL file? ");
	strcpy(filename,"\0");	
	gets(filename);
    }

fseek(in,0,SEEK_END);
end=ftell(in);
rewind(in);

while((x=EDLscan(in,cur))<end)
  {
  cur=x;
  FillEDL(&edl,in,cur);
  if(flagrant.quiet) printf("\nEDL file at %X - %s\n\ttype: %X\tsize: %X\tdecompressed: %X\t%s endian",cur,edl.type<3 ? "retrievable":"can not retrieve",edl.type ,edl.csize, edl.dsize, edl.endian<1 ? "little":"big");

  if(edl.type>2) continue;
  if(edl.type<1) continue;
  if(edl.csize==0 || edl.dsize==0) continue;

if(cur==0){                        /*lone files retain their filename*/
    strcat(filename,".bin");
    }
else sprintf(filename,"%X.bin",cur);        /*stuff from ROM gets named by offset*/
  while (!(out = fopen(filename, "wb+"))) {
	printf("\noutput binary filename? ");
	strcpy(filename,"\0");	
	gets(filename);
    }

  if(edl.type<1) x=EDLdec0(cur,in,out,edl.csize,edl.dsize,edl.endian);
  else if(edl.type<2) x=EDLdec1(cur,in,out,edl.csize,edl.dsize,edl.endian);
  else x=EDLdec2(cur,in,out,edl.csize,edl.dsize,edl.endian);

  if(flagrant.quiet){
    if(x!=edl.dsize) printf("\nFailed to pull %s properly\n\tgrabbed %X of %X bytes",filename,x,edl.dsize);
    }
  cur+=edl.csize;           /*set new position just after binary*/

  if(flagrant.swap) swapfile(out,out);
  fclose(out);
  if(flagrant.trash) remove(filename);
  }/*end EDL detection loop*/

/*clean up and exit*/
fclose(in);
if(flagrant.quiet) printf("\nNo %s files to be found.\n",cur>0 ? "more":"\aEDL");
return 0;}
