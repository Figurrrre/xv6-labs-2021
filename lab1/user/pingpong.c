#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
int main(int argc, char *argv[]) 
{
    int pipe_ftos[2];//父进程到子进程的管道
    int pipe_stof[2];//子进程到父进程的管道
    char buff[5];//存储管道信息
    int size;//读取信息大小
    //创建两个管道
    pipe(pipe_ftos);
    pipe(pipe_stof);
    int pid=fork();
    if(pid==0)//子进程代码部分
    {
    	close(pipe_ftos[1]);//关闭父进程到子进程管道的子端写功能
		close(pipe_stof[0]);//关闭子进程到父进程管道的子端读功能
    	if((size=read(pipe_ftos[0],buff,sizeof(buff)))>0) 
		{
            printf("%d: received ",getpid());
            write(1,buff,size);
        }
		
		write(pipe_stof[1],"pong\n",5);
		close(pipe_stof[1]);//用完即关
		exit(0);
	}
	else
	{
		close(pipe_stof[1]);//关闭子进程到父进程管道的父端写功能
		close(pipe_ftos[0]);//关闭父进程到子进程管道的父端读功能
		write(pipe_ftos[1],"ping\n",5);
		if((size=read(pipe_stof[0],buff,sizeof(buff)))>0)
		{
			printf("%d: received ",getpid());
            write(1,buff,size);
		}
		close(pipe_ftos[1]);//用完即关
	}
    exit(0);
}
