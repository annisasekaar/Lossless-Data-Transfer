using namespace std;

#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
    const char * file_name;
    int windowsize;
    int buffersize;
    int port;
    if (argc != 5) {
        cout << "Correct command:" << endl;
        cout << "./recvfile <filename> <windowsize> <buffersize> <port>" << endl;
        cout << endl << "Arguement count: " << argc << endl;
        return -1;
    } else {
        file_name = argv[1];
        windowsize = atoi(argv[2]);
        buffersize = atoi(argv[3]);
        port = atoi(argv[4]);
    }

    // creating socket
    struct sockaddr_in soc_addr_send;
    struct sockaddr_in soc_addr_recv;
    socklen_t sock_send_len = sizeof(soc_addr_send);

    // creating socket
    int sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // declaring address
    memset((char *) &soc_addr_recv, 0, sizeof(soc_addr_recv));
    soc_addr_recv.sin_family = AF_INET;
    soc_addr_recv.sin_port = htons(port);
    soc_addr_recv.sin_addr.s_addr = htonl(INADDR_ANY);

    // binding socket to selected port
    bind(sock, (struct sockaddr*) &soc_addr_recv, sizeof(soc_addr_recv));

    cout << "Waiting for data..." << endl;

    //akan dipake buat framenya
    char * buffer = new char[buffersize];

    // receiving message
    int recv_len = recvfrom(sock, buffer, buffersize, 0, (struct sockaddr *) &soc_addr_send, &sock_send_len);
    cout << "Message recieved from client: " << buffer << endl;

    // send back
    char word[] = "Hello too from reciever!!";
    sendto(sock, word, sizeof(word), 0, (struct sockaddr*) &soc_addr_send, sock_send_len);


    return 0;
}
