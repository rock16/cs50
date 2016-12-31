#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>



int main(void)
{
    char line [] = "GET /hello.html   /http/1.1";
    char *method = strtok(line, " ");
    char *target = strtok(NULL, " ");
    char *v = strtok(NULL, " ");
    int space = strlen(target) + strlen(v) + strlen(method);
    printf("%i, %i", (int)strlen(line), space);
    
}
