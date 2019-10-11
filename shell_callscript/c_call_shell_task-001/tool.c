#include <stdio.h>
int main(int argc, char *argv[])
{
 /*int i;*/
if(argc>1)
{
  char *a[]={"6","2","0","0","1","2"} ;
  if ((strcmp(argv[1],a[0])==0)&&(strcmp(argv[2],a[1])==0)&&(strcmp(argv[3],a[2])==0)&&(strcmp(argv[4],a[3])==0)&&(argc==6))
  {
    if (strcmp(argv[5],a[4])==0)
     {system("sh ./hello.sh &");}
    else if(strcmp(argv[5],a[5])==0)
     {system("sh ./hello.sh");}
  }
}
else
printf("no parameter(s)\n");
/*for (i=0;i<argc;i++)
{ printf("%s\n",argv[i]);*/
  printf("This C program ends\n");
  reyurn 0;
}

