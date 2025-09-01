#include <stdio.h>
// #include "model/common/keyval.h"
#include "model/common/keyset.h"

void kv_test() {
	// initialize as object
	// adv_kv_obj* root_kv_obj = adv_init_kv(1);
	// adv_kv_obj* root_kv_array = adv_init_kv(0);

	adv_lks_keys* keyset = adv_init_lks();
	adv_add_key_lks(keyset, "hello", 2, 0);
	adv_add_key_lks(keyset, "world", 2, 2);
	adv_add_key_lks(keyset, "no idea", 2, 3);

	adv_traverse_lks(keyset);

}
