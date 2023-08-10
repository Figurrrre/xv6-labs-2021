// user/sleep.c
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h" //由于实验初期不清楚需要什么头文件，通过模仿其他程序进行的尝试

int main(int argc, char *argv[])//通过查阅资料和程序发现，命令行参数通过数组argv[]传给main函数，argc为数组长度
 {
    if (argc != 2) 
    {
        fprintf(2, "Usage: wrong sleep ticks\n");
        exit(1); // 当参数个数不等于所要求的2时，模仿其他程序输出错误提示
    }
    sleep(atoi(argv[1])); // 使用atoi()函数将string参数转化为sleep()所需的int
    exit(0);
}
