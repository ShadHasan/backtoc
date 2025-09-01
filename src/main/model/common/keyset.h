#ifndef ADVANIEN_COMMON_KEYSET
#define ADVANIEN_COMMON_KEYSET

#include <stdio.h>
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

adv_lks_keys* adv_init_lks() {
	adv_lks_keys* lks = (adv_lks_keys*)malloc(sizeof(adv_lks_keys));
	lks->keys = NULL;
    lks->count_object = 0;
    lks->count_keys = 0;
    lks->count_array = 0;
    lks->count_string = 0;
    return lks;
}

void adv_lks_key_inc(adv_lks_keys* lks, adv_l_key_set* t_lks, int type) {
	switch (type) {
		case 0:
			lks->count_array++;
			t_lks->type = 0;
			break;
		case 1:
			lks->count_object++;
			t_lks->type = 1;
			break;
		case 2:
			lks->count_string++;
			t_lks->type = 2;
			break;
	}
}

void adv_lks_key_dec(adv_lks_keys* lks, int type) {
	switch (type) {
		case 0:
			lks->count_array--;
			break;
		case 1:
			lks->count_object--;
			break;
		case 2:
			lks->count_string--;
			break;
	}
}

void adv_add_key_lks(adv_lks_keys* lks, char* str, int type, int type_index) {
	adv_l_key_set* t_lks = (adv_l_key_set*)malloc(sizeof(adv_l_key_set));

	// array 0, object 1, string 2
	adv_lks_key_inc(lks, t_lks, type);

	t_lks->next = NULL;
	t_lks->str = str;
	t_lks->type_index = type_index;

	adv_l_key_set* current_key = lks->keys;
	adv_l_key_set* keys = lks->keys;

	bool found = false;

	while(keys != NULL) {
		current_key = keys;
		if (strcmp(keys->str, str) == 0) {
			found = true;
			break;
		}
		keys = keys->next;
	}
	if (!found) {
		if (current_key != NULL) {
			current_key->next = t_lks;
		} else {
			lks->keys = t_lks;
		}
	} else {
		int current_type = keys->type;
		adv_lks_key_dec(lks, current_type);
		adv_lks_key_inc(lks, keys, type);
		keys->type = type;
		keys->type_index = type_index;
	}
}

void adv_del_key_lks(adv_lks_keys* lks, char* str) {
	int count = 0;
	int found = false;
	adv_l_key_set* keys = lks->keys;
	adv_l_key_set* prev = lks->keys;
	while (keys != NULL) {
		if(strcmp(keys->str, str)==0) {
			if (count == 0) {
				if (keys->next == NULL) {
					lks->keys = NULL;
				} else {
					lks->keys = lks->keys->next;
				}
			}
			else {
				if (keys->next == NULL) {
					prev->next = NULL;
				} else {
					prev->next = keys->next;
				}
			}
			found = true;
			free(keys);
			break;
		}
		prev = keys;
		keys = keys->next;
		count++;
	}
	if (found) {
		adv_lks_key_dec(lks, keys->type);
	}
}

adv_lks_index_data adv_index_key_lks(adv_lks_keys* lks, char* str) {
	adv_l_key_set* keys = lks->keys;
	adv_lks_index_data index_data;
	index_data.index = -1;
	int count = 0;
	while (keys != NULL) {
		if (strcmp(keys->str, str) == 0) {
			index_data.index = count;
			index_data.key = str;
			index_data.type = keys->type;
			index_data.type_index = keys->type_index;
			break;
		}
		keys = keys->next;
		count++;
	}
	return index_data;
}


void adv_traverse_lks(adv_lks_keys* lks) {
	adv_l_key_set* keys = lks->keys;
	while (keys != NULL) {
			printf("%s->",keys->str);
			keys = keys->next;
	}
	printf("NULL\n");
}

#endif
