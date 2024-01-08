#ifndef __GET__
#define __GET__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "conf_struct.h"

char* repl(char* str, char* tag, char* rep){
  char* replaced = (char*) malloc(500);
  char* step = (char*) malloc(100);
  char* start = (char*) malloc(500);strcpy(start,str);strcat(start,tag);
  char* end = strstr(start,tag);

  int k = 0;

  for(int i=0; str[i]!='\0'; i++){
    if(strstr(start,tag)!=NULL){
      strncpy(step,start,end-start);step[end-start]='\0';
      start = end+strlen(tag);
      end = strstr(start,tag);
      strcat(replaced,step);
      strcat(replaced,rep);
    }
  } 
  replaced[strlen(replaced)-strlen(rep)] = '\0';
  return replaced;
}

ConfContent get_content(){
  ConfContent cf;
  cf.conf_name = (char*) malloc(50);
  cf.ip_addr = (char*) malloc(15);
  cf.server_name = (char*) malloc(50);
  cf.server_admin = (char*) malloc(100);
  cf.document_root = (char*) malloc(200);
  cf.script_alias = (char*) malloc(20);
  cf.script_dir = (char*) malloc(200);

  char* len = getenv("CONTENT_LENGTH");    
  if(len==NULL){
    printf("No data posted!\n");
    exit(1);
  }

  char* data = (char*) malloc(1000);fscanf(stdin, "%[^\n]", data);
  data = repl(data,"%40","@");
  data = repl(data,"%2F","/");
  data = repl(data,"%C3%A9","é");
  data = repl(data,"%C3%A8","è");
  data = repl(data,"%C3%A7","ç");
  data = repl(data,"%C3%A0","à");

  sscanf(data, "cfname=%[^&]&ip=%[^&]\
                &servername=%[^&]&serveradmin=%[^&]\
                &docroot=%[^&]&scriptalias=%[^&]&scriptdir=%[^&]&submit=submit",
        cf.conf_name, cf.ip_addr,
        cf.server_name, cf.server_admin,
        cf.document_root, cf.script_alias, cf.script_dir);


  return cf;
}

#endif
