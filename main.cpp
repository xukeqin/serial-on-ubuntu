#include     <stdio.h>      /*标准输入输出定义*/
#include     <stdlib.h>     /*标准函数库定义*/
#include     <unistd.h>     /*Unix标准函数定义*/
#include     <sys/types.h>  /**/
#include     <sys/stat.h>   /**/
#include     <fcntl.h>      /*文件控制定义*/
#include     <termios.h>    /*PPSIX终端控制定义*/
#include     <errno.h>      /*错误号定义*/
#include     <iostream>

using namespace std;

/***@brief  设置串口通信速率
*@param  fd     类型 int  打开串口的文件句柄
*@param  speed  类型 int  串口速度
*@return  void*/

int speed_arr[] = { B115200, B38400, B19200, B9600, B4800, B2400, B1200, B300,
B38400, B19200, B9600, B4800, B2400, B1200, B300, };
int name_arr[] = { 115200, 38400, 19200, 9600, 4800, 2400, 1200, 300,
38400, 19200, 9600, 4800, 2400, 1200, 300, };
void set_speed(int fd, int speed)
{
	int   i;
	int   status;
	struct termios   Opt;
	tcgetattr(fd, &Opt);
	for (i = 0; i < sizeof(speed_arr) / sizeof(int); i++)
	{
		if (speed == name_arr[i])
		{
			tcflush(fd, TCIOFLUSH);
			cfsetispeed(&Opt, speed_arr[i]);
			cfsetospeed(&Opt, speed_arr[i]);
			status = tcsetattr(fd, TCSANOW, &Opt);
			if (status != 0)
				perror("tcsetattr fd1");
			return;
		}
		tcflush(fd, TCIOFLUSH);
	}
}

/**
*@breif 打开串口
*/
int OpenDev(char *Dev)
{
	int    fd = open(Dev, O_RDWR);
	if (-1 == fd)
	{
		perror("Can't Open Serial Port");
		return -1;
	}
	else
		return fd;

}
/**
*@breif     main()
*/
int main(int argc, char **argv)
{
	cout << "hihihi" << endl;
	int fd;
	int nread;
	int buff[3] = { 180, 171, 172 };
	char *dev = "/dev/ttyS0";
	fd = OpenDev(dev);
	if (fd>0)
		set_speed(fd, 115200);
	else
	{
		printf("Can't Open Serial Port!\n");
		exit(0);
	}
	while (1)
	{
		if ((nread = write(fd, buff, 1))>0)         //收数
		{
			cout << "SUCCESS" << endl;
			sleep(1);
		}
		//if((nread = read(fd, buff, 1))>0)         //发数
		//{
		//    cout<< "RECEIVED" <<endl;
		//}
	}
}