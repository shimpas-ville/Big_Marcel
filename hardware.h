#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>

#define FILE_PATH "registers.bin"
#define FILE_SIZE 1024  // Same size as used in the first program

char* registers_map(const char* file_path, int file_size, int* fd);
int registers_release(void* map, int file_size, int fd);
void Display();
void exhibitionMode(int mode);
void displaySpeed(unsigned int speed);
void statusLED();
void resetAll();
void RGB();
void batteryLevel(int mode);
void timesMessageAppeared();
void messageCharacter();
