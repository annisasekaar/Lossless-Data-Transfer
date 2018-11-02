#ifndef PACKET_ATRIBUT_H
#define PACKET_ATRIBUT_H
#include <chrono>
#include <stdlib.h> 
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>

#define MAX_DATA_SIZE 1024
#define MAX_FRAME_SIZE 1034
#define ACK_SIZE 6

#define current_time chrono::high_resolution_clock::now
#define time_stamp chrono::high_resolution_clock::time_point
#define elapsed_time(end, start) chrono::duration_cast<chrono::milliseconds>(end - start).count()
#define sleep_for(x) this_thread::sleep_for(chrono::milliseconds(x));

typedef unsigned char byte;

char cheksum(char * frame, int count);
int createFrame(char * frame, int seqNum, int dataLength, char * data, bool eot );
void createACK(int seqNum, char *ack , bool error);
bool readFrame(int * seqNum, char * data, int * dataLength, bool *eot , char * frame);
bool readACK(int *seqNum, bool *error, char *ack);

#endif