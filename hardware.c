#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include "hardware.h"

unsigned short *base_address;
unsigned short *r0;
unsigned short *r1;
unsigned short *r2;
unsigned short *r3;

// Function to open or create the file and map it into memory
char* registers_map(const char* file_path, int file_size, int* fd) {
    *fd = open(file_path, O_RDWR | O_CREAT, 0666);
    if (*fd == -1) {
        perror("Error opening or creating file");
        return NULL;
    }

    // Ensure the file is of the correct size
    if (ftruncate(*fd, file_size) == -1) {
        perror("Error setting file size");
        close(*fd);
        return NULL;
    }

    // Map the file into memory
    char *map = mmap(0, file_size, PROT_READ | PROT_WRITE, MAP_SHARED, *fd, 0);
    if (map == MAP_FAILED) {
        perror("Error mapping file");
        close(*fd);
        return NULL;
    }

    
    base_address = (unsigned short *)map;
    r0 = base_address + 0x00;
    r1 = base_address + 0x01;
    r2 = base_address + 0x02;
    r3 = base_address + 0x03;
    printf("base_address: %p\n", (void*)base_address);
    printf("r0: %p\n", (void*)r0);
    printf("r1: %p\n", (void*)r1);
    printf("r2: %p\n", (void*)r2);
    printf("r3: %p\n", (void*)r3);
    return map;
}

// Function to release mapped memory and file descriptor
int registers_release(void* map, int file_size, int fd) {
    if (munmap(map, file_size) == -1) {
        perror("Error unmapping the file");
        close(fd);
        return -1;
    }

    if (close(fd) == -1) {
        perror("Error closing file");
        return -1;
    }

    return 0;
}

void Display() {
    //*r0 = *r0 | ~(0x0001);
    *r0 = *r0 ^ (0x0001);
    // unsigned short int maskReset = ~(0x0001)<<13;
    // *r0 = *r0 & maskReset;
}

void exhibitionMode(int mode) {
    unsigned short int mask = ~(0x0003 << 1);
    *r0 = *r0 & mask;
    switch (mode)
    {
    case 00:
        break;
    case 01:
        unsigned short int mask1 = (0x0002 << 1);
        *r0 = *r0 & mask1;
        break;
    case 10:
        unsigned short int mask2 = (0x0001 << 1);
        *r0 = *r0 & mask2;
        break;
    case 11:
        unsigned short int mask3 = (0x0003 << 1);
        *r0 = *r0 & mask3;
        break;
    default:
        break;
        }
}

void displaySpeed(unsigned int speed) {

}

void operationLED() {
   
}

void statusLED() {
    unsigned short int mask = (0x1800);
    *r0 = *r0 | mask;
}

void resetAll() {
    unsigned short int maskZero = (0x0000);
    unsigned short int maskSet = (0x1c11);
    *r0 = *r0 & maskZero;
    *r0 = *r0 | maskSet;
    // unsigned short int maskReset = (0x0001)<<13;
    // *r0 = *r0 | maskReset;
}

void RGB() {
    
}

void batteryLevel(int mode) {
    unsigned short int mask = ~(0x0003);
    *r1 = *r1 & mask;
    switch (mode)
    {
    case 00:
        break;
    case 01:
        unsigned short int mask1 = (0x0002);
        *r0 = *r0 | mask1;
        break;
    case 10:
        unsigned short int mask2 = (0x0001);
        *r0 = *r0 | mask2;
        break;
    case 11:
        unsigned short int mask3 = (0x0003);
        *r0 = *r0 | mask3;
        break;
    default:
        break;
        }
}

void timesMessageAppeared() {

}

void messageCharacter() {

}

// #define FILE_PATH "registers.bin"
// #define FILE_SIZE 1024  // Same size as used in the first program
// #define MODE_DEFAULT 0
// #define MODE_SLIDE 1
// #define MODE_FLASH 2
// #define MODE_SLIDE_FLASH 3
// unsigned int exMode = MODE_DEFAULT;
// unsigned int valueMode = 0x00;
// #define BATTERY_CRITIC 0
// #define BATTERY_LOW 1
// #define BATTERY_MEDIUM 2
// #define BATTERY_HIGH 3
// unsigned int exMode = BATTERY_HIGH;


// //Zera todos os bits
// unsigned int clear(unsigned short *x)
// {
//     return *x & 0;
//     //return 0;
// }

// // Seta um único bit
// unsigned int setbit(unsigned short *x, int bit)
// {
//     return *x | (0x1 << bit);
// }

// // Resseta um único bit
// unsigned int clearbit(unsigned short *x, int bit)
// {
//     return *x & ~(0x1 << bit);
// }

// //Inverte o valor de um único bit
// unsigned int invertbit(unsigned short *x, int bit)
// {
//     return *x ^ (0x1 << bit);
// }

// // Retorna o estado de um determinado bit (retorna 0 ou 1)
// int testbit(unsigned short *x, int bit)
// {
//     return  (*x & (0x1 << bit)) == 0 ? 0 : 1;
// }

// int display(unsigned short *reg) {
//     invertbit(*reg, 0);
// }

// int exhibitionMode(unsigned int Mode, unsigned short *reg) {
//     switch (Mode)
//     {
//     case MODE_DEFAULT:
//         clearbit(*reg, 1);
//         clearbit(*reg, 2);
//         break;
//     case MODE_SLIDE:
//         clearbit(*reg, 1);
//         clearbit(*reg, 2);
//         invertbit(*reg,2);
//         break;
//     case MODE_FLASH:
//         clearbit(*reg, 1);
//         clearbit(*reg, 2);
//         invertbit(*reg,1);
//         break;
//     case MODE_SLIDE_FLASH:
//         clearbit(*reg, 1);
//         clearbit(*reg, 2);
//         invertbit(*reg,2);
//         invertbit(*reg,1);
//         break;
//     default:
//         break;
//     }
// }