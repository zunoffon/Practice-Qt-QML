/* A simple server in the internet domain using TCP
   The port number is passed as an argument */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>    //Thư viện chứa các cấu trúc cần thiết cho socket
#include <netinet/in.h>    //Thư viện chứa các hằng số, cấu trúc khi sử dụng địa chỉ trên internet
#include <errno.h>

#define PORTNUMBER 1069

void settingSocket (int *Socket, struct sockaddr_in *serverAddr, struct sockaddr_in *clientAddr, int PortNum)
{
    //Khoi tao gia tri cho cac vung nho
    memset(serverAddr, '0', sizeof(serverAddr));
    memset(clientAddr, '0', sizeof(clientAddr));

    //Thiet lap dia chi server
    serverAddr->sin_family = AF_INET;      //default
    serverAddr->sin_addr.s_addr = INADDR_ANY;  //ip server
    serverAddr->sin_port = htons(PortNum);      //port number

    //Tao socket
    *Socket = socket(AF_INET, SOCK_STREAM, 0);
    if (*Socket < 0)
        error("ERROR opening socket");
}

void bindSocketToServer(int Socket, struct sockaddr_in serverAddr)
{
    //bind socket
    if (bind(Socket, (struct sockaddr *) &serverAddr,sizeof(serverAddr)) < 0)
    {
        error("ERROR on binding");
    }
}

void listenFromClient(int Socket, int numberOfConnection)
{
    //listening
    listen(Socket, numberOfConnection);    //Toi da 5 backlog trong hang doi
}

char *readDataFromSocket(int Socket, int SizeBuffer)
{
    char RecvBuff[SizeBuffer];
    int n;
    memset(RecvBuff, 0, SizeBuffer);
    //read data from socket
    n = read(Socket, RecvBuff, SizeBuffer - 1);    //block den khi co du lieu tu client gui toi
    if (n < 0) error("ERROR reading from socket");

    return RecvBuff;
}

void writeDataViaSocket(int Socket, char *str)
{
    int n;
    n = write(Socket, str, sizeof(str));
    if (n < 0) error("ERROR writing to socket");
}

int main(int argc, char *argv[])
{
    int mSocketFd;  //socket server tạo ra để nghe kết nối
    int mNewSocketFd; //socket tạo ra khi server chấp nhận một kết nối từ client
    int mPortNumber = PORTNUMBER; //So hieu cong dich vu
    
    struct sockaddr_in serverAddress, clientAddress; //Cấu trúc chứa thông tin địa chỉ server, client
    
    settingSocket(&mSocketFd, &serverAddress, &clientAddress, mPortNumber);
    bindSocketToServer(mSocketFd, serverAddress);
    listenFromClient(mSocketFd, 5);

    int n, len;
    len = sizeof(clientAddress);

    //Server su dung mot vong lap de lien tuc nghe va phuc vu client ket noi den
    while(1)
    {
        printf("Server is listening at port %d\n", mPortNumber);
        mNewSocketFd = accept(mSocketFd, (struct sockaddr *) &clientAddress, (socklen_t*)&len);
        if (mNewSocketFd < 0)
        {
            error("ERROR on accept");
            continue;
        }
        else
        {
            while(1)
            {
                /*Read Data*/
                printf("Message from client: %s\n",readDataFromSocket(mNewSocketFd, 256)); //256bytes

                /*Write Data*/
                char mSendBuff[256];
                printf("Please enter the message: ");
                memset(mSendBuff, 0, 256); //Khoi tao buffer
                fgets(mSendBuff,255,stdin); //Chua thong diep doc tu ban phim
                writeDataViaSocket(mNewSocketFd, mSendBuff);

                //close(mNewSocketFd);    //Dong ket noi cua client
                sleep(1);
            }
        }

//        char s[255]; //Chua thong tin dia chi client ket noi den
//        inet_ntop(clientAddress.sin_family,(struct sockaddr *)&clientAddress,s, sizeof s);
//        printf("server: got connection from %s\n", s);

//        /*Read Data*/
//        printf("Message from client: %s\n",readDataFromSocket(mNewSocketFd, 10)); //10bytes

//        /*Write Data*/
//        writeDataViaSocket(mNewSocketFd, "Goodbye!\n");

//        //close(mNewSocketFd);    //Dong ket noi cua client
//        sleep(1);
    }
    
    close(mSocketFd);
    return 0;
}

