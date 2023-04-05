#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
    char * filePath = "genesis.txt";
    char * copyPath = "genesis_copy.txt";
    FILE * inputStream = fopen(filePath, "rb+");
    FILE * outputStream = fopen(copyPath, "wb+");
    int size = 0;
    fseek(inputStream, 0, SEEK_END);
    size = ftell(inputStream);
    int set2 = 0;
    set2 = size / 2;
    int set1=size-set2;
    //Create Fork
    int p_id = fork();
    //For second half of the file
    if (p_id == 0){
        fseek(inputStream, 0, SEEK_SET);
        char buffer[set2];
        fread(buffer, set2, 1, inputStream);
        fwrite(buffer, set2, 1, outputStream);
        fflush(outputStream);
        fclose(inputStream);
        fclose(outputStream);
       //For first half of file
    } 
    else {    
        fseek(inputStream, set2 + 1, SEEK_SET);
        char buffer[set1];
        fread(buffer, (set1), 1, inputStream);
        fseek(outputStream, set2 + 1, SEEK_SET);
        sleep(1);
        fwrite(buffer, (set1), 1, outputStream);
        fflush(outputStream);
        fclose(inputStream);
        fclose(outputStream);
    }
    return 0;
}