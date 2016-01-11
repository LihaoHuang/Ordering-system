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
		/*//輸入欲連線server ip
		printf("請輸入要連線的IP(輸入EXIT離開程序):");
		gets(parameterip);*/

		printf("******************************ORDING SYSTEM******************************\n");
		printf("Enter any key to continue or Enter exit to shutdown[any key/exit]: ");
		//輸入EXIT離開程序
		gets(parameterip);
		if(!strcmp(parameterip,"EXIT") || !strcmp(parameterip,"exit"))
		{
			printf("Connect shutdown...\n");
			closesocket(sHost);
			WSACleanup();
			system("pause");
			return 0;
		}

		/*//輸入欲連線server port number
		printf("請輸入要連線的port number: ");
		gets(parameterport);
		sscanf(parameterport,"%d",&port);*/

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
		servAddr.sin_addr.s_addr    =	inet_addr("127.0.0.1");
		servAddr.sin_port           =	htons((short)2323);
	
		//與伺服器連線
		retVal = connect(sHost,(LPSOCKADDR)&servAddr,sizeof(servAddr));

		//判斷使否成功連線
		if(SOCKET_ERROR == retVal)
		{
			printf("Connect to server failure...\n\n");
			closesocket(sHost);
			WSACleanup();
			continue;
		}
		ZeroMemory(buf,BUF_SIZE);

		printf("編號 餐點\n1 A餐:炸機3塊、可樂1杯、薯條1份\n2 B餐:漢堡1個、可樂1杯、薯條1份\n3 漢堡\n4 炸機\n5 可樂\n6 薯條\n\n",buf);
		while(1)
		{
			printf("輸入餐點編號與數量:(點完輸入-1)");
			scanf("%d",&order[flag][0]);
			if(order[flag][0] == -1)	break;

			scanf("%d",&order[flag][1]);
			//printf("sent:%s\n",buf);
			flag+=1;
		}
		
		//與伺服器溝通
		while(1)
		{
			printf("你點了以下餐點\n");
			for(i=0; i<flag; i++)
			{
				if(order[i][0]==1) printf("A餐%d份\n",order[i][1]);
				else if(order[i][0]==2) printf("B餐%d份\n",order[i][1]);
				else if(order[i][0]==3) printf("漢堡%d份\n",order[i][1]);
				else if(order[i][0]==4) printf("炸機%d份\n",order[i][1]);
				else if(order[i][0]==5) printf("可樂%d份\n",order[i][1]);
				else if(order[i][0]==6) printf("薯條%d份\n",order[i][1]);
				else if(order[i][0]==7) printf("A餐%d份\n",order[i][1]);
				else printf("");
			}

			printf("餐點確認:[ok/add/sub/cencel]");
			scanf("%s",check);

			if(!strcmp(check,"add"))
			{
				while(1)
				{
					printf("輸入餐點編號與數量:(點餐完輸入-1)");
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
					printf("輸入要取消的餐點編號與數量:(取消完請輸入-1)");
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
		printf("請輸入電話號碼:");
		scanf("%s",&tel);

		ZeroMemory(buf,BUF_SIZE);
		retVal = send(sHost,"訂單已生成\n",strlen("訂單已生成\n"),0);
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
		printf("\n伺服器端: %s\n",buf);	
		printf("\n點餐完將自動離開系統...\n");
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