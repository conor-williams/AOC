#include <stdio.h>
#include <string.h>
#include <stdlib.h>

f(char*s){for(s+=9;(*s+=*s-57?1:8)>90;*s--=48);}



#define LENGTH(a) (sizeof(a)/sizeof*(a))

char *test[]={
  "00CODEGOLF",
  "9ZZZZZZZZZ",
  "ABCDEFGH9Z",
  "0123456789"};

int main(int argc,char **argv) {
  char **s=test,*t;
  int count=LENGTH(test);

  if(argc>1) {
    s=argv+1;
    count=argc-1;
  }

  for(;count-->0;) {
    f(t=strdup(*s));
    printf("%s + 1 = %s\n",*s++,t);
    free(t);
  }
}
