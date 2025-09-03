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
	adv_kv_obj* root_kv_obj = adv_kv_init_obj();
	adv_kv_add_obj_str(root_kv_obj, "key1", "value1");
	adv_kv_traverse_obj(root_kv_obj);
	adv_kv_add_obj_str(root_kv_obj, "key2", "value2");
	adv_kv_traverse_obj(root_kv_obj);
	adv_kv_add_obj_str(root_kv_obj, "key3", "value3");
	adv_kv_traverse_obj(root_kv_obj);

	// initialize as array
	adv_kv_obj* kv_array_1 = adv_kv_init_arr();

	// adding array to object type
	adv_kv_add_obj_arr(root_kv_obj, "key4", kv_array_1);
	adv_kv_traverse_arr(kv_array_1);
	adv_kv_traverse_obj(root_kv_obj);

	// adding string to array type
	adv_kv_add_arr_str(kv_array_1, "value1");
	adv_kv_add_arr_str(kv_array_1, "value2");
	adv_kv_traverse_obj(root_kv_obj);

	// adding same object to object against new key
	// Don't try because key5 will create loop
	// adv_kv_add_obj_obj(root_kv_obj, "key5", root_kv_obj);
	// adv_kv_traverse_obj(root_kv_obj);

	adv_kv_obj* kv_obj_1 = adv_kv_init_obj();
	adv_kv_add_obj_str(kv_obj_1, "key1", "value1");
	adv_kv_add_obj_str(kv_obj_1, "key2", "value2");
	adv_kv_add_obj_obj(root_kv_obj, "key5", kv_obj_1);
	printf("=========");
	adv_kv_traverse_obj(root_kv_obj);
	printf("=========");
}
