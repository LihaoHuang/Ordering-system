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
	int				retVal;
	int				nServAddrLen = sizeof(servAddr);
	int			    port;
	char			parameterip[BUF_SIZE],parameterport[BUF_SIZE];

	while(1)
	{
		//��J���s�userver ip
		printf("�п�J�n�s�u��IP(��JEXIT���}�{��):");
		gets(parameterip);

		//��JEXIT���}�{��
		if(!strcmp(parameterip,"EXIT") || !strcmp(parameterip,"exit"))
		{
			printf("�w�����{��!\n");
			closesocket(sHost);
			WSACleanup();
			system("pause");
			return 0;
		}

		//��J���s�userver port number
		printf("�п�J�n�s�u��port number: ");
		gets(parameterport);
		sscanf(parameterport,"%d",&port);

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
		servAddr.sin_addr.s_addr    =	inet_addr(parameterip);
		servAddr.sin_port           =	htons((short)port);
	
		//�P���A���s�u
		retVal = connect(sHost,(LPSOCKADDR)&servAddr,sizeof(servAddr));

		//�P�_�ϧ_���\�s�u
		if(SOCKET_ERROR == retVal)
		{
			printf("�P���A���s�u����!\n");
			closesocket(sHost);
			WSACleanup();
			continue;
		}
		printf("�s�u���\!\n�������s�u�{���Хu��JEND��E(�j�p�g�ҥi)\n");

		//�P���A�����q
		while(1)
		{
			ZeroMemory(buf,BUF_SIZE);
			printf("�ۤv:");
			scanf("%s",buf);
			//printf("sent:%s\n",buf);

			//��Jend���}�{��
			if(!strcmp(buf,"end") || !strcmp(buf,"END")|| !strcmp(buf,"E")|| !strcmp(buf,"e"))
			{
				printf("�w�����s�u!\n");
				closesocket(sHost);
				WSACleanup();
				break;
			}

			retVal = send(sHost,buf,strlen(buf),0);

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
			printf("���A����: %s\n",buf);	
		}
		getchar();
	}
		/*getchar();
		closesocket(sHost);
		WSACleanup();
		return 0;
		*/	
}