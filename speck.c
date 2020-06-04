#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>

uint32_t speck32_64_dec(uint32_t c,uint64_t k) {
 uint16_t y= (uint16_t)c;
 uint16_t x= (uint16_t)(c>>16);
 uint32_t p;
 uint16_t kr[22], l[22];
 kr[0] = k; 
 for (int i=0;i<3;i++) {
  k=k>>16;
  l[i] = k;
 } 
 for (int i=0; i<22; i++) {
  l[i+3] = (((uint16_t)(l[i]>>7|l[i]<<9)) + kr[i]) ^ (uint16_t)i;
  kr[i+1] = ((uint16_t)(kr[i]<<2|kr[i]>>14)) ^ l[i+3];   
  } 
 for (int i=0; i<22; i++) {
  y = x^y;
  y = (uint16_t)(y>>2|y<<14);
  x = (x^kr[21-i])-y;
  x = (uint16_t)(x<<7|x>>9);
 } 
 p=x;
 p = p<<16|y;
 return p;
}

uint32_t speck32_64_enc(uint32_t p,uint64_t k) {
 uint16_t y= (uint16_t)p;
 uint16_t x= (uint16_t)(p>>16);
 uint32_t c;
 uint16_t kr[22], l[22];
 kr[0] = k;
 for (int i=0;i<3;i++) {
  k=k>>16;
  l[i] = k;
 } 
 for (int i=0; i<22; i++) {
  l[i+3] = (((uint16_t)(l[i]>>7|l[i]<<9)) + kr[i]) ^ (uint16_t)i;
  kr[i+1] = ((uint16_t)(kr[i]<<2|kr[i]>>14)) ^ l[i+3];   
  }  
 for (int i=0; i<22; i++) {
  x = (((uint16_t)(x>>7|x<<9)) + y) ^ kr[i];
  y = ((uint16_t)(y<<2|y>>14)) ^ x;
 } 
 c=x;
 c = c<<16|y;
 return c;
}

void main() {
 char ch;
 printf("-- SPECK32/64 --\n"); 
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
   printf("c (hex) : %x\n",speck32_64_enc(p,k));
  }
  else {
   uint32_t c;
   uint64_t k;
   printf("c (hex) : ");
   scanf("%" SCNx32, &c);
   printf("k (hex) : ");
   scanf("%" SCNx64, &k);
   printf("p (hex) : %x\n",speck32_64_dec(c,k));
  }
  printf("\n1.encrypt\n2.decrypt\n\nenter your choice...");
  scanf(" %c",&ch);
 }
}
