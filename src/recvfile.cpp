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

#define FRAME_SIZE 1034
#define ACK_SIZE 6

/* GLOBAL VARIABLES */
// struct sockaddr_in soc_addr_send, soc_addr_recv;
struct sockaddr_in send_addr, recv_addr;
int sock;
socklen_t sock_send_len;

void sendACK() {
    char ack[ACK_SIZE];
    char frame[FRAME_SIZE];

    while (true) {
        recvfrom(sock, (char *) frame, ACK_SIZE, 0, (struct sockaddr *) &send_addr, &sock_send_len);
        cout << "recieved: " << frame << endl;

        // >>> ini kirim balik ACK <<<
        sendto(sock, (char *) frame, sizeof(frame), 0, (struct sockaddr *) &send_addr, sock_send_len);
    }
}

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
        return EXIT_FAILURE;
    } else {
        file_name = argv[1];
        windowsize = atoi(argv[2]) * DATA_SIZE;
        buffersize = atoi(argv[3]) * DATA_SIZE;
        port = atoi(argv[4]);
    }

    // creating socket
    sock_send_len = sizeof(send_addr);

    // creating socket
    sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

    // declaring receive (server) address
    memset((char *) &recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(port);
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // binding socket to selected port
    bind(sock, (struct sockaddr*) &recv_addr, sizeof(recv_addr));

    cout << "Waiting for data..." << endl;

    //akan dipake buat framenya
    char * buffer = new char[buffersize];

    // receiving message
    recvfrom(sock, buffer, buffersize, 0, (struct sockaddr *) &send_addr, &sock_send_len);
    cout << "Message recieved from client: " << buffer << endl;

    // send back
    char word[] = "Hello too from reciever!!";
    sendto(sock, word, sizeof(word), 0, (struct sockaddr*) &send_addr, sock_send_len);

    return 0;
}
