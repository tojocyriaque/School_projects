#ifndef __DOC_VER__
#define __DOC_VER__

#include <string.h>

int is_valid_dir(char* dir){
  if(strstr(dir,"//")!=NULL || strstr(dir,"\\")){
    return 0;
  }
  return 1;
}

#endif

