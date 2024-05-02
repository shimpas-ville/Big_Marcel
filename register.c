#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/stat.h>
#include "hardware.h"



int main() {
    int fd;
    // Open the file and map it into memory
    char* map = registers_map(FILE_PATH, FILE_SIZE, &fd);
    if (map == NULL) {
        return EXIT_FAILURE;
    }

    
    // Write a new value to R0
    //*r0 = *r0 | 0x01;
    //*r0 = *r0 & (0x1 << 13);
    // Release resources
    
    int commandPrompt = -1;
    
    while (commandPrompt!=10) {
    printf("Digite a opção:\n1 - Display (Ligar/ Desligar)\n2 - Modo de Exibição\n3 - Velocidade do Display\n5 - Reset\n6 - RGB\n7- Nível de Bateria\n10 - Sair\n");
    scanf("%d", &commandPrompt);
    switch (commandPrompt)
    {
    case 1:
        Display();
        break;
    case 2:
        int exMode;
        printf("Digite o modo de exibição:\n00-padrão\n01-deslizante\n10-piscante\n11-ambos");
        scanf("%d", &exMode);
        exhibitionMode(exMode);
    case 3:
        break;
    // case 4:
    //     statusLED();
    //     break;
    case 5: 
        resetAll();
        break;
    case 6:
        RGB();
        break;
    case 7:
        int exBat;
        printf("Digite o nível:\n00-crítico\n01-baixo\n10-médio\n11-alto");
        scanf("%d", &exBat);
        exhibitionMode(exBat);
        break;
    default:
        break;
    }
    }

    if (registers_release(map, FILE_SIZE, fd) == -1) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}


