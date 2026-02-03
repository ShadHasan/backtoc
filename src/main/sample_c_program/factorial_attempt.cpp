#include <iostream>

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

int main()
{
    int arr[4] = {1, 2, 3, 4};
    cout << "Hello world!" << endl;
    dissect_factor(arr, 4);

    return 0;
}
