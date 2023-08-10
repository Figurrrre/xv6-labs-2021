#include "kernel/types.h"
#include "user/user.h"
void process(int p[])
{
	close(p[1]);
	int prime;
	if(read(p[0],&prime,4)>0)
	{
		fprintf(1,"prime %d\n",prime);
		int pip[2];
		pipe(pip);
		if(fork()>0)
		{
			close(pip[0]);
			int i;
			while(read(p[0],&i,4)>0)
				if(i%prime!=0)
					write(pip[1],&i,4);
			close(pip[1]);
			wait(0);
		}
		else
		{
			close(p[0]);
			process(pip);
		}
	}
}
int main(int argc,char *argv[])
{
	int p[2];
	pipe(p);
	int pid=fork();
	if(pid>0)
	{
		close(p[0]);
		fprintf(1,"prime 2\n");
		for(int i=3;i<=35;i++)
			if(i%2!=0)
				write(p[1],&i,4);
		close(p[1]);
		wait(0);
	}
	else
		process(p);
	exit(0);
}