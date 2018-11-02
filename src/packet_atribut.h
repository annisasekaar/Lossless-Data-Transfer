#ifndef PACKET_ATRIBUT_H
#define PACKET_ATRIBUT_H
#include <chrono>
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>

#define this_time chrono::high_resolution_clock::now
#define time_stamp chrono::high_resolution_clock::time_point
#define time_length(end, start) chrono::duration_cast<chrono::milliseconds>(end - start).count()
#define sleep_for(x) this_thread::sleep_for(chrono::milliseconds(x));

#define MAX_DATA 1024
#define MAX_FRAME 1034
#define ACK_LENGTH 6



typedef unsigned char byte;

char checksum (char * frame , int size);
int createFrame(char * frame, int seqNum, int dataLength, char * data, bool eot );
void createACK(int seqNum, char *ack , bool error);
bool readFrame(int * seqNum, char * data, int * dataLength, bool *eot , char * frame);
bool readACK(int *seqNum, bool *error, char *ack);

#endif