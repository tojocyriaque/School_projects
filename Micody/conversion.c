#include <stdio.h>      
//#include <string.h>      
      
int conversion(int ariary,int franc);      
void displayResult(int ariary,int franc);      
      
int main(){      
      
   printf("Conversion\n");      
      
//   int  ariary=0;      
   int  franc=0;      
      
   printf("Otrinona ny volanao : ");      
   scanf("%d",&ariary);      
      
   franc=conversion(ariary,franc);      
      
   displayResult(ariary,franc);      
      
// printf("%d       %s        %s        %s\n",_LINE_,_FILE_,_DATE_,_TIME_);      
      
   return 0;      
}      
      
int conversion(int ariary,int franc){      
   franc= ariary * 5;      
      
   return franc;      
}      
      
void displayResult(int ariary,int franc){      
   printf("Aoka ary ho fantatrao fa ny %d ariary dia %d franc\n",ariary,franc);      
}      
      
