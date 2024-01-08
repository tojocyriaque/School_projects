#ifndef __IP_VER__
#define __IP_VER__

#include <splitstr.h>
#include <ctype.h>

int valid_addr(char* ip){
  char** spl = split(ip,".");
  for(int i=0; i<4; i++){
    if(atoi(spl[i])>255){
      return 0;
    }
  }
  return 1;
}

int valid_form(char* ip){
  char c;
  int i=0;
  while(i<strlen(ip)){
    c=ip[i];
    if( c!='.' && (c<'0' || c>'9') ){
      return 0;
    }
    i++;
  }
  return 1;
}

int is_valid_IP(char* ip){
  if(!valid_form(ip)){
    return 0;
  }
  else if(!valid_addr(ip)){
    return 0;
  }
  return 1;
}

#endif
