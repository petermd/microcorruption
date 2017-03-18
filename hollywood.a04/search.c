#include <stdio.h>
#include <stdlib.h>

static inline unsigned short swap(unsigned short a) {
  unsigned short m=a>>8;
  unsigned short l=a&0xff;
  return (l<<8)|m;
}

void simulate(unsigned int inp[], int len) {
  unsigned short r4=0,r6=0;
  for (int i=0;i<len;i++)
  {
    r4+=inp[i];
    r4=swap(r4);
    r6^=inp[i];
    r6^=r4;
    r4^=r6;
    r6^=r4;
    printf("%d: %04x -> %04x %04x\n",i,inp[i],r4,r6);
  }
}

void search(int matchr4, int matchr6) {

  unsigned short i,j,k,r4,r6;

  // inputsize of 5 means the last digit is 00, so limit the search
  for (k=0x100;k>=0;k--) {
    printf("searching 0x%x\n",k);
    for (j=0;j<0xffff;j++) {
      for (i=0;i<0xffff;i++) {

        r4=swap(i+j)^k;

        if (r4!=matchr4)
          continue;

        r6=swap((swap(i)^j)+k);

        if (r6!=matchr6)
          continue;

        printf("\n0x%04x 0x%04x 0x%04x => 0x%4x / 0x%4x\n",i,j,k,r4,r6);
        printf("ok\n");
        exit(0);
      }
    }
  }

  printf("fail\n");
}

int main(int argc, char** argv) {
  // d9cd254eaa
  unsigned int test[]={0xcdd9,0x4e25,0x00aa};
  simulate(test,3);
  //search(0xfeb1,0x9298);
}
