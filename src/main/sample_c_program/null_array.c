#include <stdio.h>
#include <stdlib.h>

int main() {
        char** array;
        int i;
        array = (char**)malloc(3*sizeof(char**));

        array[0] = "hello";
        array[1] = NULL;
        array[2] = "world";

        for (i=0;i<3;i++) {
                printf("%s", array[i]);   // please not next line with null end up seg fault in print hence next linesep
                printf("\n");
        }
        // array[1] = (char*)malloc(36*sizeof(char));  // without this line it fail
        array[1] = "most likely to fail to segmentation\0";

        for(i=0; i<3; i++) {
                printf("%s", array[i]);
                printf("\n");
        }

        array[1] = NULL;
        for(i=0; i<3; i++) {
                printf("%s", array[i]);
                printf("\n");
        }
        array[1] = "let see it \\ work";
        for(i=0; i<3; i++) {
                printf("%s", array[i]);
                printf("\n");
        }
        return 0;
}
