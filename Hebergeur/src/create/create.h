#ifndef __CREATE__
#define __CREATE__

#include "get.h"
#include <unistd.h>

int write_conf(ConfContent cf){
  char* cfname = (char*) malloc(100);
  sprintf(cfname, "/home/tojo/Documents/CGI/Hebergeur/confs/%s.conf", cf.conf_name);

  FILE* cf_file = fopen(cfname,"w+");
  if(cf_file==NULL){
    printf("<html>");
    printf("<head><meta charset=UTF8></head>");
    printf("Echec de la création du fichier de configuration: %s\n", cfname);
    printf("</html>");
    return 0;
  }

  fprintf(cf_file, "<VirtualHost %s:80>\n", cf.ip_addr);

  fprintf(cf_file, "  ServerName %s\n", cf.server_name);
  fprintf(cf_file, "  ServerAdmin %s\n", cf.server_admin);
  fprintf(cf_file, "  DocumentRoot %s\n", cf.document_root);
  fprintf(cf_file, "  ScriptAlias %s %s\n", cf.script_alias, cf.script_dir);

  fprintf(cf_file, "  <Directory %s>\n", cf.document_root);
  fprintf(cf_file, "    Require all granted\n");
  fprintf(cf_file, "  </Directory>\n");

  fprintf(cf_file, "  <Directory %s>\n", cf.script_dir);
  fprintf(cf_file, "    Options +ExecCGI\n");
  fprintf(cf_file, "    Require all granted\n");
  fprintf(cf_file, "  </Directory>\n");

  fprintf(cf_file, "<VirtualHost>\n");

  fclose(cf_file);

  return 1;

}

#endif
