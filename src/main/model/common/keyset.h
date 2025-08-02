#ifndef ADVANIEN_COMMON_KEYVAL
#define ADVANIEN_COMMON_KEYVAL

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Below is linked list base key set which have easy deletion
// unlike array style key set which required complete shift in case of deletion
typedef struct adv_l_key_set adv_l_key_set;

struct adv_l_key_set {
        char* str;
        adv_l_key_set* next;
};

void adv_init_lks(l_key_set* lks) {
        lks->str = "(.)";
        lks->next = NULL;
}

void adv_add_key_lks(adv_l_key_set* lks, char* str) {

	adv_l_key_set* t_lks;
	t_lks = (adv_l_key_set*)malloc(sizeof(adv_l_key_set));
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

void adv_del_key_lks(adv_l_key_set* lks, char* str) {
	adv_l_key_set* root = lks;
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

int adv_index_key_lks(adv_l_key_set* lks, char* str) {
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


void adv_traverse_lks(adv_l_key_set* lks) {
        while (lks != NULL) {
                printf("%s->",lks->str);
                lks = lks->next;
        }
        printf("NULL\n");
}

#endif
