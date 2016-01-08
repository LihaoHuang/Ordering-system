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
		//輸入欲連線server ip
		printf("請輸入要連線的IP(輸入EXIT離開程序):");
		gets(parameterip);

		//輸入EXIT離開程序
		if(!strcmp(parameterip,"EXIT") || !strcmp(parameterip,"exit"))
		{
			printf("已關閉程式!\n");
			closesocket(sHost);
			WSACleanup();
			system("pause");
			return 0;
		}

		//輸入欲連線server port number
		printf("請輸入要連線的port number: ");
		gets(parameterport);
		sscanf(parameterport,"%d",&port);

		//判斷WSAStartup是否啟動
		if(WSAStartup(MAKEWORD(2,2), &wsd) !=0)
		{
			printf("WSAStartup error!\n");
			continue;
		}

		//啟動socket
		sHost = socket(AF_INET,SOCK_STREAM,IPPROTO_TCP);

		//判斷socket是否啟動
		if(INVALID_SOCKET == sHost)
		{
			printf("socket failed!\n");
			WSACleanup();
			continue;
		}

		//使用者連線參數設定
		servAddr.sin_family         =	AF_INET;
		servAddr.sin_addr.s_addr    =	inet_addr(parameterip);
		servAddr.sin_port           =	htons((short)port);
	
		//與伺服器連線
		retVal = connect(sHost,(LPSOCKADDR)&servAddr,sizeof(servAddr));

		//判斷使否成功連線
		if(SOCKET_ERROR == retVal)
		{
			printf("與伺服器連線失敗!\n");
			closesocket(sHost);
			WSACleanup();
			continue;
		}
		printf("連線成功!\n欲關閉連線程式請只輸入END或E(大小寫皆可)\n");

		//與伺服器溝通
		while(1)
		{
			ZeroMemory(buf,BUF_SIZE);
			printf("自己:");
			scanf("%s",buf);
			//printf("sent:%s\n",buf);

			//輸入end離開程序
			if(!strcmp(buf,"end") || !strcmp(buf,"END")|| !strcmp(buf,"E")|| !strcmp(buf,"e"))
			{
				printf("已關閉連線!\n");
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
			printf("伺服器端: %s\n",buf);	
		}
		getchar();
	}
		/*getchar();
		closesocket(sHost);
		WSACleanup();
		return 0;
		*/	
}