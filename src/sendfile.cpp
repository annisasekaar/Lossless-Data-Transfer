using namespace std;

#include <vector>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

vector<char> readFileToBuffer(char* file_name) {
    /**
     * reading file and put it in buffer
     **/

    // reading from file
    ifstream in_file (file_name, std::ios::binary);

    // getting file size in byte
    in_file.seekg(0, in_file.end);
    long file_size = in_file.tellg();
    in_file.seekg(0, in_file.beg);

    // allocating memory
    char * buffer = new char[file_size];

    // read and copy file to buffer
    in_file.read(buffer, file_size);

    // vector buffer
    /* static vector<char> v_buf; */
    vector<char> vector_buffer;
    for (int i = 0; i < file_size; i++) {
        vector_buffer.push_back(buffer[i]);
    }

    // closing file
    in_file.close();

    // deleting buffer
    delete[] buffer;

    return vector_buffer;
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
        windowsize = atoi(argv[2]);
        buffersize = atoi(argv[3]);
        destination_ip = argv[4];
        destination_port = atoi(argv[5]);
    }

    // creating socket
    struct sockaddr_in send_addr;
    socklen_t addr_len = sizeof(send_addr);
    
    // initializing socket
    int sock;
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        cout << "Socket failed to be created" << endl;
        return -1;
    }

    // declaring address
    memset((char *) &send_addr, 0, sizeof(send_addr));
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(destination_port);

    // converting IPv4 numbers-and-dots notation into binary form
    if (inet_aton(destination_ip, &send_addr.sin_addr) <= 0) {
        cout << "Invalid address or address not supported" << endl;
        return -1;  // exiting program
    }

    // message to be sent
    // {{{{ belum dibagi per 1024 }}}}
    ///////////// vector<char> v_buffer = readFileToBuffer(file_name);

    // buffer to store message
    char * buffer = new char[buffersize];

    char word[] = "Hello from sendfile\0"; 
    
    // sending message
    sendto(sock, word, sizeof(word), 0 , (struct sockaddr *) &send_addr, addr_len);

    // receive message
    recvfrom(sock, buffer, buffersize, 0, (struct sockaddr *) &send_addr, &addr_len);
    cout << "message from server: " << buffer << endl;
    
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