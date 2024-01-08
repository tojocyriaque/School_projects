#ifndef __SRV_VER__
#define __SRV_VER__

#include <string.h>
#include <ctype.h>

int is_valid_srvname(char* srvname){
  char c;
  int i;
  while(i<strlen(srvname)){
    c=srvname[i];
    if(c!='.' && c!='_' && c!='@' && !isdigit(c) && !isalpha(c)){
      return 0;
    }
    i++;
  }
  return 1;
}

#endif
