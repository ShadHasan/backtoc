#include <stdio.h>
#include "model/common/keyval.h"
#include "model/common/keyset.h"

void kv_test() {
	adv_lks_keys* keyset = adv_init_lks();
	adv_add_key_lks(keyset, "hello", 2, 0);
	adv_add_key_lks(keyset, "world", 2, 2);
	adv_add_key_lks(keyset, "no idea", 2, 3);
	adv_traverse_lks(keyset);

	adv_add_key_lks(keyset, "world", 2, 1);
	adv_traverse_lks(keyset);

	printf("count keys: %d\n", keyset->count_keys);

	adv_del_key_lks(keyset, "no idea");
	adv_traverse_lks(keyset);
	printf("count keys: %d\n", keyset->count_keys);

	// negative testing if there is not such key. It won't do anything
	adv_del_key_lks(keyset, "idea");
	adv_traverse_lks(keyset);
	printf("count keys: %d\n", keyset->count_keys);

	adv_del_key_lks(keyset, "hello");
	adv_del_key_lks(keyset, "world");
	adv_traverse_lks(keyset);
	printf("count keys: %d\n", keyset->count_keys);

	// initialize as object
	adv_kv_obj* root_kv_obj = adv_init_kv(1);
	// adv_kv_obj* root_kv_array = adv_init_kv(0);
}
