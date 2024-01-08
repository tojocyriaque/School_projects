#include "../create/get.h"
#include "../create/create.h"

#include <stdio.h>
#include "../verification/verify.h"

void copy_conf(char* cfname){
  char* create = (char*) malloc(500);

  //for arch linux distro
  sprintf(create,"cp /home/tojo/Documents/CGI/Hebergeur/confs/%s.conf /etc/httpd/conf/extra/",cfname);

  //for debian distro
  //sprintf(create,"sudo cp %s /etc/apache2/sites-available",cfname);

  system(create);
}

int already_hosted(char* ip, char* srvname){
  char* str = (char*) malloc(100);

  FILE* file = fopen("/etc/hosts","r");
  if(file==NULL){
    printf("Cannot access /etc/hosts\n");
    exit(1);
  }

  while(fgets(str,100,file)!=NULL){
	  if(strstr(str,ip)!=NULL && strstr(str,srvname)!=NULL){
	  	fclose(file);
		  return 1;
	  }
  }

  fclose(file);
  return 0;
}

void config_host(char* ip, char* srvname){
  char* config = (char*) malloc(100);
  //system("echo >> /etc/hosts");
  sprintf(config,"echo %s	%s >> /etc/hosts", ip, srvname);
  system(config);
}

void redirect_to_index(){
  printf("Content-Type: text/html \n\n");
  printf("<html><head><meta http-equiv='refresh' content='0;url=http://www.hebergeur.mg'></head></html>");
}

int create_conf(){
  ConfContent cf = get_content();
  int success = 0;

  if(is_valid_conf(cf)){
    success = write_conf(cf);
    copy_conf(cf.conf_name);
    if(!already_hosted(cf.ip_addr,cf.server_name)){
      config_host(cf.ip_addr, cf.server_name);
    }
  }

  if(success){
    redirect_to_index();
  }

  return 0;
}

