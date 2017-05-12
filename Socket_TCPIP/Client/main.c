#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <errno.h>

#define SERVERADDRESS "192.168.1.111"
#define PORTNUMBER 1069

void settingSocket(int *Socket, struct sockaddr_in *serverAddr, int PortNum, char *IP)
{
    //Tao socket
    *Socket = socket(AF_INET, SOCK_STREAM, 0);
    if (*Socket < 0)
    {
        error("ERROR opening socket");
    }
    memset(serverAddr, '0', sizeof(serverAddr));
    //Thiet lap dia chi cua server de ket noi den
    serverAddr->sin_family = AF_INET;        //Mac dinh
    serverAddr->sin_port = htons(PortNum);    //Cong dich vu
    //Dia chi ip/domain may chu
    if (inet_pton(AF_INET, IP, &serverAddr->sin_addr) <= 0)
    {
        printf("\n inet_pton error occured\n");
    }
}

void connectToServer(int Socket, struct sockaddr_in serverAddr)
{
    //Goi ham connect de thuc hien mot ket noi den server
    if( connect(Socket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
    {
        printf("\n Error : Connect Failed \n");
    }
}

char *readDataFromServer(int Socket, int SizeBuffer)
{
    //Nhan du lieu tu server
    char RecvBuff[SizeBuffer];
    int n;
    memset(RecvBuff, 0, SizeBuffer);
    n = read(Socket, RecvBuff, SizeBuffer - 1);    //block den khi co du lieu tu client gui toi
    if (n < 0) error("ERROR reading from socket");

    return RecvBuff;
}

void writeDataToServer(int Socket, char *str)
{
    int n;
    n = write(Socket, str, sizeof(str));
    if (n < 0) error("ERROR writing to socket");
}

int main(int argc, char *argv[])
{
    int mSocketFd, mPortNumber, n;
    char *mIP;

    struct sockaddr_in serverAddress; //Cau truc chua dia chi server ma client can biet de ket noi toi

    mPortNumber = PORTNUMBER;
    mIP = SERVERADDRESS;

    settingSocket(&mSocketFd, &serverAddress, mPortNumber, mIP);
    connectToServer(mSocketFd, serverAddress);
    while(1)
    {
        /*Write Data*/
        char mSendBuff[256];
        printf("Please enter the message: ");
        memset(mSendBuff, 0, 256); //Khoi tao buffer
        fgets(mSendBuff,255,stdin); //Chua thong diep doc tu ban phim

        writeDataToServer(mSocketFd, mSendBuff);

        /*Read Data*/
        printf("Message from server: %s\n",readDataFromServer(mSocketFd, 256)); //256bytes
    }
    /*Write Data*/
    char mSendBuff[256];
    printf("Please enter the message: ");
    memset(mSendBuff, 0, 256); //Khoi tao buffer
    fgets(mSendBuff,255,stdin); //Chua thong diep doc tu ban phim

    writeDataToServer(mSocketFd, mSendBuff);

    /*Read Data*/
    printf("Message from server: %s\n",readDataFromServer(mSocketFd, 10)); //10bytes

    close(mSocketFd); //Dong socket
    return 0;
}
