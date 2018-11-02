using namespace std;

#include <vector>
#include <iostream>
#include <fstream>
#include <thread>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define DATA_SIZE 1034
#define ACK_SIZE 6

/* GLOBAL VARIABLES */
struct sockaddr_in send_addr, recv_addr;
socklen_t send_addr_len;
int sock;

char word[24] = "Hello from sendfile.cpp";

void listenForACK() {
    char ack[ACK_SIZE];

    while (true) {
        // socklen_t recv_addr;
        recvfrom(sock, (char *) ack, ACK_SIZE, 0, (struct sockaddr *) &send_addr, &send_addr_len);
        cout << "ACK received: " << ack << endl;
    }
}

int main(int argc, char ** argv) {

    char * file_name;
    char * destination_ip;
    int windowsize;
    int buffersize;
    int destination_port;

    if (argc != 6) {    // insufficient arguements given
        cout << "The correct command is:" << endl;
        cout << "./sendfile <filename> <windowsize> <buffersize> <destination_ip> <destination_port>" << endl << endl;
        cout << "Arguement count: " << argc << endl;
        return -1;  // exiting
    } else {
        file_name = argv[1];
        windowsize = atoi(argv[2]) * DATA_SIZE;
        buffersize = atoi(argv[3]) * DATA_SIZE;      // buffer only contains data
        destination_ip = argv[4];
        destination_port = atoi(argv[5]);
    }
    
    // initializing socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        cout << "Socket failed to be created" << endl;
        return EXIT_FAILURE;
    }

    // declaring send (client) address
    send_addr_len = sizeof(send_addr);
    memset((char *) &send_addr, 0, sizeof(send_addr));
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(destination_port);

    // declaring receive (server) address
    memset((char *) &recv_addr, 0, sizeof(recv_addr));

    // converting IPv4 numbers-and-dots notation into binary form
    if (inet_aton(destination_ip, &send_addr.sin_addr) <= 0) {
        cout << "Invalid address or address not supported" << endl;
        return EXIT_FAILURE;  // exiting program
    }

    // binding send (client) to socket
    bind(sock, (const struct sockaddr *) &send_addr, sizeof(send_addr));

    thread ack_thread(listenForACK);

    // message to be sent
    // {{{{ belum dibagi per 1024 }}}}
    ///////////// vector<char> v_buffer = readFileToBuffer(file_name);

    // buffer to store message
    char * buffer = new char[buffersize];

    cout << "word count: " << sizeof(word) << endl;

    // trying :)
    for (int i = 0; i < sizeof(word); i++) {
        // sending message
        sendto(sock, (const void *) word[i], sizeof(word), 0 , (struct sockaddr *) &send_addr, send_addr_len);
    }

    // // receive message
    // recvfrom(sock, buffer, buffersize, 0, (struct sockaddr *) &send_addr, &send_addr_len);
    // cout << "message from server: " << buffer << endl;
    

    // SLIDING WINDOW
    // how? :(

    // okey, the {{{ outline }}}:
    // 1. breakdown message?
    // 2. how to do the windowsize & buffer size?
    // 3. how to know the windowsize is full?
    // 4. how to encode the frame so it is sendable?
    // 5. sending message & recieving ack?
    // 6. the timeout?
    // 7. thread?

    return 0;
}