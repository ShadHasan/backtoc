#ifndef ADVANIEN_COMMON_KEYSET
#define ADVANIEN_COMMON_KEYSET

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Below is linked list base key set which have easy deletion
// unlike array style key set which required complete shift in case of deletion
typedef struct adv_l_key_set adv_l_key_set;

typedef struct {
	char* key;
	int index;
	int type;
	int type_index;
} adv_lks_index_data;

struct adv_l_key_set {
        char* str;
        int type;           // This is used to defined type for key-val
        int type_index;     // This basically hold index, again some extra attribute
        adv_l_key_set* next;
};

typedef struct {
	adv_l_key_set* keys;
	int count_object;
	int count_array;
	int count_string;
	int count_keys;
} adv_lks_keys;

void adv_init_lks(adv_lks_keys* lks) {
	lks->keys* = NULL;
    lks->count_object = 0;
    lks->count_keys = 0;
    lks->count_array = 0;
    lks->count_string = 0;
}

void adv_add_key_lks(adv_lks_keys* lks, char* str, int type) {
	adv_l_key_set* t_lks;
	t_lks = (adv_l_key_set*)malloc(sizeof(adv_l_key_set));
	// array 0, object 1, string 2
	switch (type) {
		case 0:
			t_lks->type_index = lks->count_array++;
			t_lks->type = 0;
			break;
		case 1:
			t_lks->type_index = lks->count_object++;
			t_lks->type = 1;
			break;
		case 2:
			t_lks->type_index = lks->count_string++;
			t_lks->type = 2;
			break;
	}
	t_lks->next = NULL;
	t_lks->str = str;
	adv_l_key_set* keys = lks->keys;
	bool ignore = false;
	while(keys != NULL) {
		if (strcmp(keys->str, str) == 0) {
			keys->type = type;
			ignore = true;
			break;
		}
		keys = keys->next;
	}
	if (!ignore) {
		lks->next = t_lks;
	}
}

void adv_add_key_with_attr_lks(adv_l_key_set* lks, char* str, int type, int type_index) {

	adv_l_key_set* t_lks;
	t_lks = (adv_l_key_set*)malloc(sizeof(adv_l_key_set));
	t_lks->str = str;
	t_lks->type = type;
	t_lks->type_index = type_index;
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

void adv_del_key_lks(adv_l_key_set* lks, char* str) {
	adv_l_key_set* prev = lks;
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

adv_index_data adv_index_key_lks(adv_l_key_set* lks, char* str) {
	int index = -1;
	adv_lks_index_data index_data;
	int count = 0;
	lks = lks->next;
	while (lks != NULL) {
		if (strcmp(lks->str, str) == 0) {
			index_data.index = count;
			index_data.key = str;
			index_data.type = lks->type;
			index_data.type_index = lks->type_index;
			break;
		}
		lks = lks->next;
		count++;
	}
	return index_data;
}


void adv_traverse_lks(adv_l_key_set* lks) {
        while (lks != NULL) {
                printf("%s->",lks->str);
                lks = lks->next;
        }
        printf("NULL\n");
}

#endif
