#define BUF_SIZE   64
#include "winsock.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[])
{
	WSADATA			wsd;
	SOCKET			sHost;
	SOCKADDR_IN		servAddr;
	char			buf[BUF_SIZE];
	char			check[BUF_SIZE], tel[BUF_SIZE];
	int				order[BUF_SIZE][2];
	int				sub[BUF_SIZE][2];
	int				retVal;
	int				nServAddrLen = sizeof(servAddr);
	int			    port;
	int				i=0;
	int				flag=0,flagsub=0;//change
	char			parameterip[BUF_SIZE],parameterport[BUF_SIZE];

	while(1)
	{
		/*//��J���s�userver ip
		printf("�п�J�n�s�u��IP(��JEXIT���}�{��):");
		gets(parameterip);*/

		printf("******************************ORDING SYSTEM******************************\n");
		printf("Enter any key to continue or Enter exit to shutdown[any key/exit]: ");
		//��JEXIT���}�{��
		gets(parameterip);
		if(!strcmp(parameterip,"EXIT") || !strcmp(parameterip,"exit"))
		{
			printf("Connect shutdown...\n");
			closesocket(sHost);
			WSACleanup();
			system("pause");
			return 0;
		}

		/*//��J���s�userver port number
		printf("�п�J�n�s�u��port number: ");
		gets(parameterport);
		sscanf(parameterport,"%d",&port);*/

		//�P�_WSAStartup�O�_�Ұ�
		if(WSAStartup(MAKEWORD(2,2), &wsd) !=0)
		{
			printf("WSAStartup error!\n");
			continue;
		}

		//�Ұ�socket
		sHost = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

		//�P�_socket�O�_�Ұ�
		if(INVALID_SOCKET == sHost)
		{
			printf("socket failed!\n");
			WSACleanup();
			continue;
		}

		//�ϥΪ̳s�u�ѼƳ]�w
		servAddr.sin_family         =	AF_INET;
		servAddr.sin_addr.s_addr    =	inet_addr("127.0.0.1");
		servAddr.sin_port           =	htons((short)2323);
	
		//�P���A���s�u
		retVal = connect(sHost,(LPSOCKADDR)&servAddr,sizeof(servAddr));

		//�P�_�ϧ_���\�s�u
		if(SOCKET_ERROR == retVal)
		{
			printf("Connect to server failure...\n\n");
			closesocket(sHost);
			WSACleanup();
			continue;
		}
		ZeroMemory(buf,BUF_SIZE);

		printf("�s�� �\�I\n1 A�\:����3���B�i��1�M�B����1��\n2 B�\:�~��1�ӡB�i��1�M�B����1��\n3 �~��\n4 ����\n5 �i��\n6 ����\n\n",buf);
		while(1)
		{
			printf("��J�\�I�s���P�ƶq:(�I����J-1)");
			scanf("%d",&order[flag][0]);
			if(order[flag][0] == -1)	break;

			scanf("%d",&order[flag][1]);
			//printf("sent:%s\n",buf);
			flag+=1;
		}
		
		//�P���A�����q
		while(1)
		{
			printf("�A�I�F�H�U�\�I\n");
			for(i=0; i<flag; i++)
			{
				if(order[i][0]==1) printf("A�\%d��\n",order[i][1]);
				else if(order[i][0]==2) printf("B�\%d��\n",order[i][1]);
				else if(order[i][0]==3) printf("�~��%d��\n",order[i][1]);
				else if(order[i][0]==4) printf("����%d��\n",order[i][1]);
				else if(order[i][0]==5) printf("�i��%d��\n",order[i][1]);
				else if(order[i][0]==6) printf("����%d��\n",order[i][1]);
				else if(order[i][0]==7) printf("A�\%d��\n",order[i][1]);
				else printf("");
			}

			printf("�\�I�T�{:[ok/add/sub/cencel]");
			scanf("%s",check);

			if(!strcmp(check,"add"))
			{
				while(1)
				{
					printf("��J�\�I�s���P�ƶq:(�I�\����J-1)");
					scanf("%d",&order[flag][0]);
					if(order[flag][0] == -1)	break;

					scanf("%d",&order[flag][1]);
					//printf("sent:%s\n",buf);
					flag+=1;
				}
				continue;
			}
			if(!strcmp(check,"sub"))
			{
				while(1)
				{
					printf("��J�n�������\�I�s���P�ƶq:(�������п�J-1)");
					scanf("%d",&sub[flagsub][0]);
					if(sub[flagsub][0] == -1)	break;
					scanf("%d",&sub[flagsub][1]);
					for(i=0;i<flag;i++)
					{
						if(order[i][0] == sub[flagsub][0])
						{
							order[i][1]-=sub[flagsub][1];
							if(order[i][1]<=0)		order[i][0]=0;
						}
					}
					flagsub+=1;
				}
			}
			if(!strcmp(check,"cencel"))
			{
				printf("Cencel the order system...\n");
				system("pause");
				closesocket(sHost);
				WSACleanup();
				return 0;
			}
			if(!strcmp(check,"ok"))
			{
				break;
			}
		}
		printf("�п�J�q�ܸ��X:");
		scanf("%s",&tel);

		ZeroMemory(buf,BUF_SIZE);
		retVal = send(sHost,"�q��w�ͦ�\n",strlen("�q��w�ͦ�\n"),0);
		if(SOCKET_ERROR==retVal)
		{
			printf("send failed!\n");
			closesocket(sHost);
			WSACleanup();
			return 0;
		}

		ZeroMemory(buf,BUF_SIZE);
		retVal = recv(sHost,buf,BUF_SIZE,0);
		if(SOCKET_ERROR==retVal)
		{
			printf("recv failed!\n");
			closesocket(sHost);
			WSACleanup();
			return 0;
		}
		printf("\n���A����: %s\n",buf);	
		printf("\n�I�\���N�۰����}�t��...\n");
		getchar();
		printf("3");getchar();
		printf("2");getchar();
		printf("1");getchar();
		printf("0");getchar();
	}
	/*getchar();
	closesocket(sHost);
	WSACleanup();
	*/
	return 0;
}