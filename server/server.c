#define BUF_SIZE   64
#include <stdio.h>
#include <stdlib.h>
#include <winSock.h>
int main()
{
	WSADATA 	wsd;
	int 		sockfd; // server listenning socket! 
	int			new_fd; // server accepted socket!
	int 		numbytes;
	struct		sockaddr_in my_addr;
	struct 		sockaddr_in their_addr;
	int 		sin_size;
	char 		buf[100];
	char		list[100];
	int			retVal;	


	if (WSAStartup(MAKEWORD(2,2), &wsd) != 0)
	{
		printf("WSAStartup failed!\n");
		return -1;
	}
	
	if( (sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP))==INVALID_SOCKET )
	{
		printf("socket failed!\n");
		WSACleanup();//
		return  -1;
	}
	
	my_addr.sin_family =AF_INET;
	my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	my_addr.sin_port = htons((short) 2323);
	sin_size  = sizeof(my_addr);
    
    // binding 
	if(bind(sockfd,(struct sockaddr *) &my_addr, sin_size) == -1)
	{
		printf("binding failed!\n");
		closesocket(sockfd);
		WSACleanup();//
		return  -1;
	}
    	
    // Starting listening
	if(listen(sockfd, 10) == -1)
	{
		printf("binding failed!\n");
		closesocket(sockfd);
		WSACleanup();//
		return  -1;
	}
	
	while(1)
	{
		// Waiting for clients to come-in
		printf("伺服器等待連線中!\n");
		if ((new_fd=accept(sockfd, (struct sockaddr *) &their_addr, &sin_size)) == -1)
		{
			printf("accepting failed!\n");
			closesocket(sockfd);
			WSACleanup();//
			return  -1;
		}
    	//server first make a receive!
		printf("用戶端已開始連線\n\n");
		
		
		if( (numbytes=recv(new_fd,buf,strlen(buf),0)) <=0) break;
		//printf("Receive %d bytes,",numbytes);
		buf[numbytes]='\0';
		printf("來自%s的用戶",inet_ntoa(their_addr.sin_addr));
		printf("訊息: %s \n",buf);

		// server send back what it received.
		ZeroMemory(buf,BUF_SIZE);
		sscanf("點餐系統已收到訂單!","%s",buf);
	   	if ((numbytes=send(new_fd, buf, strlen(buf),0)) <= 0) break;
		printf("強制令使用者離開\n");
		printf("用戶端已結束連線\n.\n.\n.\n");
	}
	 closesocket(new_fd);
	 closesocket(sockfd);
	 WSACleanup();
	 system("pause");
	 return 0;
}