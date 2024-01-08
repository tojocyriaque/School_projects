#ifndef __CONF_STRUCT__
#define __CONF_STRUCT__

typedef struct {
  char* conf_name;
  char* ip_addr;
  char* server_name;
  char* server_admin;
  char* document_root;
  char* script_alias;
  char* script_dir;
} ConfContent;

#endif
