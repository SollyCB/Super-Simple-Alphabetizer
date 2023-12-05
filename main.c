#define SOL_H_IMPL
#include "../sol.h"

bool is_word_greater(int l1, int l2, char *a1, char *a2) {
    bool ret;
    if (l1 <= l2)
        ret = false;
    else
        ret = true;

    int len = l1 < l2 ? l1 : l2;
    for(int i = 0; i < len; ++i)
        if (a1[i] > a2[i])
            return true;
        else if (a1[i] < a2[i])
            return false;

    return ret;
}

char* alpha(int count, char *data, char c) {
    int *marks = new_array(1024, int);
    int *lens  = new_array(1024, int);
    int tmp    = 0;
    bool add_mark = true;
    for(int i = 0; i < count; ++i) {
        tmp++;
        if (data[i] == c) {
            while(i < count + 1 && data[i + 1] == c) {
                i++;
                tmp++;
            }
            add_mark = true;
            array_add(lens, tmp);
            tmp = 0;
        } else if (add_mark) {
            array_add(marks, i);
            add_mark = false;
        }
    }

    bool sorted = false;
    int tmp_len;
    while(!sorted) {
        sorted = true;
        for(int i = 0; i < array_len(marks) - 1; ++i)
            if (is_word_greater(lens[i], lens[i+1], data + marks[i], data + marks[i+1])) {
                sorted = false;

                tmp        = marks[i];
                tmp_len    = lens [i];
                marks[i+0] = marks[i+1];
                lens [i+0] = lens [i+1];
                marks[i+1] = tmp;
                lens [i+1] = tmp_len;
            }
    }
    char *ret = malloc(count);
    tmp = 0;
    for(int i = 0; i < array_len(marks); ++i) {
        memcpy(ret + tmp, data + marks[i], lens[i]);
        tmp += lens[i];
    }
    return ret;
}

int main(int argc, const char *argv[]) {
    if (argc < 2) {
        println("Alphabetize file by newlines, usage: alphabetize <filename>");
        return 0;
    }

    u64 len;
    char *data = file_read_char(argv[1], &len);
    char *a = alpha(len, data, '\n');

    println("%s", a);

    return 0;
}
