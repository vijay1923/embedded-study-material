#include"header.h"

void main()
{

if(fork()==0)
{
printf("In c pid=%d\n",getpid());
sleep(20);
printf("In c after sleep...\n");
exit(1);
}
else
{
int r,s;
printf("In p before wait... pid=%d\n",getpid());
r=wait(&s);
if(WIFEXITED(s))
printf("Normal termination %d\n",WEXITSTATUS(s));
else if(WIFSIGNALED(s))
printf("Ubnormal termination %d\n",WTERMSIG(s));

//printf("In p after wait r=%d s=%d\n",r,s);
while(1);

}

}
