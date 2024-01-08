#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main(){
  char* create = (char*) malloc(500);
  strcpy(create,"sudo cp /home/tojo/Documents/CGI/Hebergeur/confs/mysite.conf /etc/httpd/conf/extra/");
  system(create);
  return 0;
}
