#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include<unistd.h>
#include <fcntl.h>
#include <windows.h>


HANDLE serial_port;
DCB dcbSerialParams;
COMMTIMEOUTS timeouts;
// Lecture continue des données du port série
char read_buf[256];
DWORD num_bytes;

int InitPort();
int ReturnValeurLue();