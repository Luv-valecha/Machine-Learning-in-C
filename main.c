#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<stdbool.h>
#include<unistd.h>
#include"machine_learning.h"

void typewriter_print(char *str, unsigned int milliseconds, int colour_code)
{
  for (; *str != '\0'; str++)
  {
    printf("\x1b[38;5;%d;1m", colour_code);
    putchar(*str);
    fflush(stdout);
    usleep(milliseconds * 700);
    printf("\x1b[0m");
  }
}

int main(){
    printf("                      ");
    typewriter_print("WELCOME TO MACHINE LEARNING IN C\n",60,197);
    printf("                                ");
    typewriter_print("Main Menu\n",70,197);
    typewriter_print("Please enter your training file name: ",60,208);
    char filename[200];
    scanf("%s",filename);
    typewriter_print("Please enter your test file name: ",60,208);
    char test_filename[200];
    scanf("%s",test_filename);
    typewriter_print("\nPlease select the model to use:\n",60,208);
    typewriter_print("1. Data Scaling\n",60,208);
    typewriter_print("2. Linear Regression\n",60,208);
    typewriter_print("3. Logistic Regression\n",60,208);
    typewriter_print("4. K Nearest Neighbour\n",60,208);
    typewriter_print("5. Exit\n",60,208);
    typewriter_print("Enter option: ",60,208);
    int option;
    scanf("%d",&option);
    int choice=0;
    switch (option)
    {
    case 1:
        typewriter_print("Choose scaler type:\n",60,208);
        typewriter_print("1. Min Max Scaler\n",60,208);
        typewriter_print("2. Standard Scaler\n",60,208);
        typewriter_print("3. Main Menu\n",60,208);
        do{
            scanf("%d",&choice);
            switch (choice)
            {
            case 1:
                min_max_scaler(filename,test_filename);
                break;
            case 2:
                standard_scaler(filename,test_filename);
                break;
            case 3:
                main();
                break;
            default:
                printf("Invalid choice\n");
                break;
            }

        }while((choice<1)||(choice>2));
        break;

    case 2:
        linear_regression(filename,test_filename);
        break; 
    
    case 3:
        logistic_regression(filename,test_filename);
        break;

    case 4:
        KNN(filename,test_filename);
        break;

    case 5:
        exit(0);

    default:
        typewriter_print("Invalid option",60,196);
        main();
        break;
    }

    return 0;
}