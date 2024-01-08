#ifndef __VERIFY__
#define __VERIFY__

#include "ip.h"
#include "srvname.h"
#include "admin.h"
#include "doc.h"
#include "../create/conf_struct.h"

int is_valid_conf(ConfContent cf){
  if (!is_valid_IP(cf.ip_addr)){
    printf("Invalid IP adress\n");
    return 0;
  }

  else if(!is_valid_srvname(cf.server_name)){
    printf("Invalid server name\n");
    return 0;
  }

  else if(!is_valid_dir(cf.document_root) || !is_valid_dir(cf.script_dir)){
    printf("Invalid directory\n");
    return 0;
  }

  return 1;
}

#endif
