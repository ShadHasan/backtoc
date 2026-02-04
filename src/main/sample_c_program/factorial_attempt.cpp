/*
 * MingW64 Test Permutation code without recursion
 */

#include <iostream>
#include <algorithm> // Required for std::copy
#include <iterator>  // Required for std::begin and std::end (C++11+)

using namespace std;


int factorial(int num) {
    if ( num <= 0 )
        return 1;
    int i = 1;
    int ftl = 1;
    while (i <= num) {
        ftl = ftl * i;
        i++;
    }
    return ftl;
}

void rest_array(int* arr, int arr_len, int leave_element_index, int* sub_array) {
    int s_a_i = 0;
    for (int i = 0; i < arr_len; i++) {
        if (leave_element_index == i)
            continue;
        sub_array[s_a_i] = arr[i];
        s_a_i++;
    }
}

void dissect_factor(int* arr, int arr_len) {
    int significant = arr[0];
    int ftl = factorial(arr_len - 1);
    int sub_array[arr_len-1];
    for (int i = 0; i < arr_len; i++) {
        for (int j = 0; j < ftl; j++) {
            rest_array(arr, arr_len, i, sub_array);
            cout << arr[i] << "--";
            for (int k = 0; k < arr_len-1; k++) {
                cout << sub_array[k];
            }
            cout << endl;
        }
    }
}

void get_subarray(int* arr, int arr_len, int* permutation_arr, int permutation_arr_len, int* sub_arr, int &sub_arr_count) {
    // add to subarray when flag = 1 and if found ignore
    int flag;
    int sub_array_count = 0;
    for (int i = 0; i < arr_len; i++) {
        flag = 1;
        for (int j = 0; j < permutation_arr_len; j++) {
            if (permutation_arr[j] == arr[i])
                flag = 0;
        }
        if (flag == 1) {
            sub_arr[sub_array_count] = arr[i];
            sub_array_count++;
        }
    }
    sub_arr_count = sub_array_count;
}

void print_array(int* arr, int len) {
    for (int i = 0; i < len; i++) {
        cout << arr[i];
    }
    cout << "::" << len << endl;
}

void sub_array_reset(int* arr, int len) {
	for (int k = 0; k < len; k++) {
		arr[k] = -1;
	}
}

void init_permutation(int** permuatation, int w, int h) {
	for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			permuatation[i][j] = -1;
		}
	}
}

void display_all_permute(int** permutation, int w, int h) {
    for (int i = 0; i < w; i++) {
		for (int j = 0; j < h; j++) {
			cout << permutation[i][j];
		}
		cout << endl;
	}
}

int check_to_skip(int* arr, int arr_len, int match) {
    for (int i = 0; i < arr_len; i++) {
        if (arr[i] == match)
            return 1;
    }
    return 0;
}

void permutation(int permutation_len, int* arr, int arr_len) {
	int sub_arr[arr_len];
	int sub_arr_count;
	int next_factorial_iter = arr_len - 1;
	int int_factorial = factorial(arr_len);
	int permutation_arr[int_factorial][permutation_len];
	int next_factorial;
	int independent_counter;
	int k_int = 0;
	int flag = 0; // 0 not set, 1 set

    // initializing permatation matrix
    for (int i = 0; i < int_factorial; i++) {
        for (int j = 0; j < permutation_len; j++) {
            permutation_arr[i][j] = -1;
            cout << permutation_arr[i][j];
        }
    }

    cout << "===========================" << endl;

    for (int i = 0; i < permutation_len; i++) {
		next_factorial = factorial(next_factorial_iter);
		if (i == 0) {
            for (int k = 0; k < arr_len; k++) {
                for (int j = 0; j < next_factorial; j++) {
                    permutation_arr[j + (next_factorial*k)][i] = arr[k];
                }
            }
		} else {
            independent_counter = 0;
            while (independent_counter < int_factorial) {
                flag = 0;
                for (int k = k_int; k < arr_len; k++) {
                    for (int j = 0; j < next_factorial; j++) {
                        if (check_to_skip(permutation_arr[independent_counter], permutation_len, arr[k]) == 0) {
                            flag = 1;
                            permutation_arr[independent_counter][i] = arr[k];
                            independent_counter++;
                            cout << "hello " << independent_counter << ", ";
                        }
                        if (independent_counter >= int_factorial)
                            break;
                    }
                    if (independent_counter >= int_factorial)
                            break;
                }
                if (flag == 1)
                    k_int = 0;
                else
                    k_int++;
            }
		}
		next_factorial_iter--;
    }
	cout << "===========================" << endl;

    // display_all_permute(permutation_arr, int_factorial, permutation_len);

    for (int i = 0; i < int_factorial; i++) {
		for (int j = 0; j < permutation_len; j++) {
			cout << permutation_arr[i][j];
		}
		cout << endl;
	}

}

int main()
{
    int arr[4] = {1, 2, 3, 4};
    cout << "Hello world!" << endl;
    dissect_factor(arr, 4);
    int arr2[3][2] = {-1};

    for (int j = 0; j < 3; j++) {
        for (int i = 0; i < 2; i++) {
            cout << arr2[j][i];
        }
        cout << endl;
    }

    permutation(4, arr, 4);

    int arr3[5] = {1, 2, 3, 4, 5};
    permutation(5, arr3, 5);

    cout << "Final Hello" << endl;
    return 0;
}
