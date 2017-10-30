#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void Menu(){
        printf("*************** MENU ***************\n" );
        printf("1.\n");
        printf("2.\n");
        printf("3.\n");
        printf("4.\n");
        printf("5. Exit\n");
}

int main(){
        /* if(argc != 3)  {
                printf("Wrong number of argument!!\n");
                printf("Syntax: program filename1 filename2\n" );
                return 1;
        }
        */
        
        int menu;
        do{
                Menu();
                printf("Selection: ");
                scanf("%d", &menu);
                
                switch(menu){
                case 1:
                        break;
                case 2:
                        break;
                case 3:
                        break;
                case 4:
                        break;
                case 5:
                        break;
                default:
                        printf("INVALID VALUE!\n");
                        break;
                }
        } while(menu != 5);

        return 0;
}
