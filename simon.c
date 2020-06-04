#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>


uint32_t simon32_64_dec(uint32_t ct,uint64_t k) {
 uint16_t y= (uint16_t)ct;
 uint16_t x= (uint16_t)(ct>>16);
 uint16_t tmp;
 uint64_t z = 0b0001100111000011010100100010111110110011100001101010010001011111;
 uint16_t c = pow(2,16)-4;
 uint32_t p;
 uint16_t kr[32];
 for (int i=0;i<4;i++) {
  kr[i] = k;
  k=k>>16; 
 }
  
 for (int i=4; i<32; i++) {
  tmp = ((uint16_t)((kr[i-1]>>3)|(kr[i-1]<<13))) ^ kr[i-3];
  tmp ^= ((uint16_t)(tmp>>1|tmp<<15));
  kr[i] =  kr[i-4] ^ tmp ^ ((z>>(i-4))&1) ^ c;
 }

 for (int i=0; i<32; i++) {
  tmp = y;
  y = x^ (((uint16_t)(y<<1|y>>15))&((uint16_t)(y<<8|y>>8))) ^ ((uint16_t)(y<<2|y>>14)) ^ kr[31-i];
  x = tmp;
 }
 
 p=x;
 p = p<<16|y;
 return p;
}


uint32_t simon32_64_enc(uint32_t p,uint64_t k) {
 uint16_t y= (uint16_t)p;
 uint16_t x= (uint16_t)(p>>16);
 uint16_t tmp;
 uint64_t z = 0b0001100111000011010100100010111110110011100001101010010001011111;
 uint16_t c = pow(2,16)-4;
 uint32_t ct;
 uint16_t kr[32];
 for (int i=0;i<4;i++) {
  kr[i] = k;
  k=k>>16;
 }
  
 for (int i=0; i<32; i++) {
  if(i>=4) {
   tmp = ((uint16_t)((kr[i-1]>>3)|(kr[i-1]<<13))) ^ kr[i-3];
   tmp ^= ((uint16_t)(tmp>>1|tmp<<15));
   kr[i] =  kr[i-4] ^ tmp ^ ((z>>(i-4))&1) ^ c;
  } 
  tmp = x;
  x = y^ (((uint16_t)(x<<1|x>>15))&((uint16_t)(x<<8|x>>8))) ^ ((uint16_t)(x<<2|x>>14)) ^ kr[i];
  y = tmp;
 }
 
 ct=x;
 ct = ct<<16|y;
 return ct;
}

void main() {
 char ch;
 printf("-- SIMON32/64 --\n"); 
 printf("\n1.encrypt\n2.decrypt\n\nenter your choice...");
 scanf("%c",&ch);
 while(ch=='1'|ch=='2') {
  if(ch=='1'){
   uint32_t p;
   uint64_t k;
   printf("p (hex) : ");
   scanf("%" SCNx32, &p);
   printf("k (hex) : ");
   scanf("%" SCNx64, &k);
   printf("c (hex) : %x\n",simon32_64_enc(p,k));
  }
  else {
   uint32_t c;
   uint64_t k;
   printf("c (hex) : ");
   scanf("%" SCNx32, &c);
   printf("k (hex) : ");
   scanf("%" SCNx64, &k);
   printf("p (hex) : %x\n",simon32_64_dec(c,k));
  }
  printf("\n1.encrypt\n2.decrypt\n\nenter your choice...");
  scanf(" %c",&ch);
 }
}
