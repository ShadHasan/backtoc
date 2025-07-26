#include <stdio.h>
#include <stdlib.h>

int main() {
        char** string1;
        char** string2;
        char c = 'a';
        char* string = NULL;
        int i, j;
        string1 = (char**)malloc(sizeof(string)*1);
        for (j=0; j < 3; j++) {
                while(c != '\n') {
                        // scanf("%c", &c);     // One character at time.
                        // printf("%c", c);
                        if (string == NULL) {
                                string = (char *)malloc(sizeof(char) * 1);
                        } else {
                                string = (char *)realloc(string, (i+1) * sizeof(char));
                        }
                        scanf("%c", &c);     // since memory buffer not allocated it is obviusly fall in segment fault
                        string[i] = c;
                        printf("This string %s", string);
                        // if(c != '\n')
                        //      break;
                        i++;
                }
                if ( (j+1) > 1)
                        string1 = (char**)realloc(string1, sizeof(string)*(j+1));
                string1[j] = string;
                printf("2 dimension %s", string1[j]);
                // resetting inner loop variable for next iteration of string capture
                i = 0;
                c = 'a';
                free(string);
                string = NULL;

        }

        return 0;
}
