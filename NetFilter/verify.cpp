#include "verify.h"

bool isValid(Rule rule){
    if(rule.chain!="INPUT" && rule.mac.size()>0){
        return false;
    }
    if(rule.destPorts.size()>1 && rule.srcPorts.size()>1){
        std::cout << "Dest | Src => " << rule.destPorts.size() << " | " << rule.srcPorts.size() << std::endl;
        return false;
    }
    if(rule.protocol=="all"){
        if(rule.destPorts.size()>1 || rule.srcPorts.size()>1){
            return false;
        }
    }
    if( (rule.chain=="INPUT" && rule.destIface!="unspecified") ||
        (rule.chain=="OUTPUT" && rule.srcIface!="unspecified")){
        std::cout << "Resaka interface" << std::endl;
        return false;
    }
    return true;
}

QString ruleToCommand(Rule rule){
    QString command{"sudo iptables -A "};
    command += rule.chain+" ";

    command += " -p "+rule.protocol+" ";
    if(rule.destPorts.size()>0 || rule.srcPorts.size()>0){
        command += "-m multiport ";
    }
    if(rule.destPorts.size()>1){
        command += " --dports ";
        for(QString port: rule.destPorts){
            command += " "+port+" ";
        }
    }
    if(rule.srcPorts.size()>1){
        command += " --sports ";
        for(QString port: rule.srcPorts){
            command += " "+port+" ";
        }
    }

    if(rule.mac.size()==17){
        command += " -m mac --mac-source "+rule.mac+" ";
    }
    if(rule.srcAddr.size()>0){
        command += " -s "+rule.srcAddr+" ";
    }
    if(rule.destAddr.size()>0){
        command += " -d "+rule.destAddr+" ";
    }

    if(rule.srcIface!="unscpecified"){
        command += " -i "+rule.srcIface+" ";
    }
    if(rule.destIface!="unspecified"){
        command += " -o "+rule.destIface+" ";
    }

    command += " -j "+rule.policy;
    return command;
}
