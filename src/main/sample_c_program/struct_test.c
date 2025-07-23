#include <stdio.h>
#include <string.h>

typedef struct d_datatype d_datatype;

extern char** dd_keys;

struct d_datatype {
        char name[100];
        int x;
        d_datatype *child;
};

// Struct variable can be accessed by '.' or '->' it depend whether it is non-pointer or pointer decalration respectively
// Note: NULL assignment only supported by point
void set_d_datatype(d_datatype* dd, int val, d_datatype* child) {
        dd->x = val;
        dd->child = child;
}

void set_d_datatype_val(d_datatype* dd, int val) {
        dd->x = val;
}

void set_d_datatype_name(d_datatype* dd, char* name) {
                strcpy(dd->name, name);
}

void set_d_datatype_child(d_datatype* dd, d_datatype* child) {
        dd->child = child;
}

int get_d_datatype_val(d_datatype* dd) {
        return dd->x;
}


// Note d_datatype could have been returned instead of d_datatype* then we could not return which is needed incase no node
// have matching name.
d_datatype* search_by_name_d_datatype(d_datatype* root_dd, char* name) {
        d_datatype* temp = root_dd;
        while ( temp->child != NULL ) {
                if( strcmp(temp->name, name) == 0 ) {
                        return temp;
                }
                temp = temp->child;
        }
        return NULL;
}

int main() {
        d_datatype root_dd;
        d_datatype dd1;
        d_datatype dd2;

        set_d_datatype(&root_dd, 30, NULL);
        set_d_datatype_name(&root_dd, "root");
        printf("test %d", root_dd.x);

        set_d_datatype_val(&dd1, 10);
        set_d_datatype_name(&dd1, "one");
        set_d_datatype_val(&dd2, 40);
        set_d_datatype_name(&dd2, "two");

        set_d_datatype_child(&root_dd, &dd1);
        set_d_datatype_child(&dd1, &dd2);

        d_datatype* fetch = search_by_name_d_datatype(&root_dd, "one");
        printf("Node name: %s value: %d", fetch->name, fetch->x);

        printf("\n");

        return 0;
}
