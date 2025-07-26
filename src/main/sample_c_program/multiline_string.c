#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct string_array string_array;

struct string_array {
        int count;
        int* offset;
        unsigned int length;
        char* s_arr;
};

void init_string_array(string_array* string_arr) {
        string_arr->s_arr = NULL;
        string_arr->count = 0;
        string_arr->length = 0;
        string_arr->offset = (int*)malloc(sizeof(int)*1);
        string_arr->offset[0] = 0;
}

void add_string_to_string_array(string_array* string_arr, char* string) {
        if (string_arr->s_arr == NULL) {
                string_arr->s_arr = (char*)malloc(sizeof(string));
        } else {
                string_arr->s_arr = (char*)realloc(string_arr->s_arr, sizeof(string_arr->s_arr)+sizeof(string));
                string_arr->offset = (int*)realloc(string_arr->offset, sizeof(int)*(string_arr->count+1));
                string_arr->offset[string_arr->count] = string_arr->length;
        }
        strcat(string_arr->s_arr, string);
        string_arr->length = strlen(string_arr->s_arr);
        string_arr->count++;
}

char* get_by_index_string_array(string_array* string_arr, int index) {
        if(index >= string_arr->count || index < 0) {
                return NULL;
        } else {
                unsigned int offset = string_arr->offset[index];
                unsigned int limit = strlen(string_arr->s_arr);
                if(string_arr->count > (index+1)) {
                        limit = string_arr->offset[index+1];
                }
                char* temp = (char*)calloc(sizeof(char), limit-offset);
                strncpy(temp, string_arr->s_arr + offset, limit);
                temp[limit-offset] = '\0';
                return temp;
        }
}

int main() {
        char** string1 = NULL;
        char** string2 = NULL;
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

        // struct is already have allocate memory. so initializing as pointer mean array of struct. Here we just need to initialize as a struct.
        string_array str_arr1;
        init_string_array(&str_arr1);
        printf("initialize\n");
        add_string_to_string_array(&str_arr1, "hello");
        printf("ist\n");
        add_string_to_string_array(&str_arr1, "hello2");

        char* fet_str = get_by_index_string_array(&str_arr1, 0);
        printf("%s", fet_str);
        return 0;
}
