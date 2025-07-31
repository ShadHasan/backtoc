#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
        char* str;
} key;

typedef struct {
        key* keys;
        unsigned int count;
} key_set;


// Below is linked list base key set which have easy deletion
// unlike array style key set which required complete shift in case of deletion


typedef struct l_key_set l_key_set;

struct l_key_set {
        char* str;
        l_key_set* next;
};

void init_lks(l_key_set* lks) {
        // Below commented line not work because lks already have allocated memory and you allocating another memory
        // Hence it lead to segmentation fault
        // lks = (l_key_set*)malloc(sizeof(l_key_set));
        lks->str = "(.)";
        lks->next = NULL;
}

void add_key_lks(l_key_set* lks, char* str) {

        l_key_set* t_lks;
        t_lks = (l_key_set*)malloc(sizeof(l_key_set));
        t_lks->str = str;
        t_lks->next = NULL;
        bool ignore = false;
        while(lks->next != NULL) {
                if (strcmp(lks->next->str, str) == 0) {
                        ignore = true;
                        break;
                }
                lks = lks->next;
        }
        if (!ignore) {
                lks->next = t_lks;
        }
}

void del_key_lks(l_key_set* lks, char* str) {
        l_key_set* root = lks;
        l_key_set* prev = lks;
        lks = lks->next;
        while (lks != NULL) {
                if(strcmp(lks->str, str)==0) {

                        if (lks->next == NULL) {
                                prev->next = NULL;
                        } else {
                                prev->next = lks->next;
                        }
                        free(lks);
                        break;
                }
                prev = lks;
                lks = lks->next;
        }
}

int index_key_lks(l_key_set* lks, char* str) {
        int index = -1;
        int count = 0;
        lks = lks->next;
        while (lks != NULL) {
                if (strcmp(lks->str, str) == 0) {
                        index = count;
                        break;
                }
                lks = lks->next;
                count++;
        }
        return index;
}


void traverse_lks(l_key_set* lks) {
        while (lks != NULL) {
                printf("%s->",lks->str);
                lks = lks->next;
        }
        printf("NULL\n");
}
/*
*/

int main() {
        int i;
        key_set ks;
        ks.count = 0;

        printf("1");
        ks.keys = (key*)malloc(sizeof(key)*(++ks.count));
        ks.keys[0].str = "hello";
        printf("2");
        printf("%s", ks.keys[0].str);
        ks.keys = (key*)realloc(ks.keys, sizeof(key)*(++ks.count));
        ks.keys[1].str = "hello2";
        ks.keys = (key*)realloc(ks.keys, sizeof(key)*(++ks.count));
        ks.keys[2].str = "hello3";


        for (i = 0; i < ks.count; i++) {
                printf("%s", ks.keys[i].str);
        }
        for (i = 0; i < ks.count; i++) {
                printf("%s", ks.keys[i].str);
        }

        char* teststr;
        bool tb;

        printf("%s", teststr);
        printf("%d", tb);

        l_key_set lks;

        init_lks(&lks);

        add_key_lks(&lks, "test1");
        add_key_lks(&lks, "test2");
        // printf("%d", (lks==NULL));

        add_key_lks(&lks, "test3");
        traverse_lks(&lks);

        del_key_lks(&lks, "test2");
        traverse_lks(&lks);

        del_key_lks(&lks, "test1");
        traverse_lks(&lks);

        add_key_lks(&lks, "test2");
        traverse_lks(&lks);

        del_key_lks(&lks, "test2");
        traverse_lks(&lks);

        del_key_lks(&lks, "test3");
        traverse_lks(&lks);

        return 0;
}
