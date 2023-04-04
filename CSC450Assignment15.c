#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
    const char * filePath = "genesis.txt";
    const char * copyPath = "genesis_copy.txt";
    FILE * inputStream = fopen(filePath, "rb");
    FILE * outputStream = fopen(copyPath, "wb");
    int size = 0;
    fseek(inputStream, 0, SEEK_END);
    size = ftell(inputStream);
    int end = 0;
    end = size / 2;
    int p_id = fork();
    if (p_id == 0){
        fseek(inputStream, 0, SEEK_SET);
        char buffer[end];
        fread(buffer, end, 1, inputStream);
        fwrite(buffer, end, 1, outputStream);
        fflush(outputStream);
        fclose(inputStream);
        fclose(outputStream);
    } else {    
        fseek(inputStream, end + 1, SEEK_SET);
        char buffer[size - end];
        fread(buffer, (size-end), 1, inputStream);
        fseek(outputStream, end + 1, SEEK_SET);
        sleep(1);
        fwrite(buffer, (size-end), 1, outputStream);
        fflush(outputStream);
        fclose(inputStream);
        fclose(outputStream);
    }
    return 0;
}