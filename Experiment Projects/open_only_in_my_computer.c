//  Program that only runs on my machine

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

char *GetUniqueIds(char *filename)
{
    // file1 = /sys/class/dmi/id/product_uuid
    // file2 = /etc/machine-id
    FILE *fptr = fopen(filename, "r");

    if (fptr == NULL)
    {
        printf("Error opening file");
        return 0;
    }

    char temp[256];

    if (fgets(temp, sizeof(temp), fptr) == NULL)
    {
        fclose(fptr);
        return NULL;
    }

    fclose(fptr);

    int len = strlen(temp);
    if(len > 0 && temp[len-1] == '\n'){
        temp[len-1] = '\0';
    }
    char *result = malloc(len + 1);
    if (result == NULL)
    {
        printf("Malloc failed");
        return NULL;
    }

    strcpy(result, temp);
    return result;
}

char *GetUserName()
{
    char *user = getenv("USER");
    if (!user)
        user = getenv("LOGNAME");
    if (user)
    {
        return user;
    }

    else
    {
        printf("USERNAME and LOGNAME not set");
        exit(0);
    }
}

bool is_vm()
{
    int ret = system("systemd-detect-virt --quiet --vm");
    if (ret == 0)
    {
        return false;
    }

    else
    {
        return true;
    }
}

int main()
{

    char *MotherBoardId = GetUniqueIds("/etc/machine-id");
    char *MachineId = GetUniqueIds("/sys/class/dmi/id/product_uuid");
    // char* id = strcat(MotherBoardId, MachineId);
    char *username = GetUserName();

    // if(env_load(".", false) != 0){
    //     printf("Error loading .env file");
    //     return 0;
    // }

    if (((strcmp(MotherBoardId, "29c09c199d26475daff58ad85e2decf3")) == 0) && ((strcmp(MachineId, "c9704acc-32f5-11b2-a85c-99e1713cee8f")) == 0))
    {
        if (strcmp(username, "pranav") && (is_vm()))
        {
            
            printf("This program will run on this machine");
            
        }

        else{
            printf("This program will not run on this machine");
        }
    }

    else{
        printf("This program will not run on this machine");
    }

    // printf("%s", id);
    free(MotherBoardId);
    free(MachineId);

    // printf("%s", GetUserName());

    return 0;
}
