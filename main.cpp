#include     <stdio.h>      /*��׼�����������*/
#include     <stdlib.h>     /*��׼�����ⶨ��*/
#include     <unistd.h>     /*Unix��׼��������*/
#include     <sys/types.h>  /**/
#include     <sys/stat.h>   /**/
#include     <fcntl.h>      /*�ļ����ƶ���*/
#include     <termios.h>    /*PPSIX�ն˿��ƶ���*/
#include     <errno.h>      /*����Ŷ���*/
#include     <iostream>

using namespace std;

/***@brief  ���ô���ͨ������
*@param  fd     ���� int  �򿪴��ڵ��ļ����
*@param  speed  ���� int  �����ٶ�
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
*@breif �򿪴���
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
		if ((nread = write(fd, buff, 1))>0)         //����
		{
			cout << "SUCCESS" << endl;
			sleep(1);
		}
		//if((nread = read(fd, buff, 1))>0)         //����
		//{
		//    cout<< "RECEIVED" <<endl;
		//}
	}
}