#ifndef __INCLUDES__
#define __INCLUDES__

    #include <stdio.h>
    #include <alct.h>
    #include <ctype.h>
    #include <unistd.h>
    #include <string.h>

    void error_alarm(char* text){
        printf("<FONT color='red'><P>%s</P></FONT>", text);
    }

    void labelize(char* text, char* color){
        printf("<LABEL><FONT color='%s'><P>%s</P></FONT></LABEL>", color, text);
    }

#endif