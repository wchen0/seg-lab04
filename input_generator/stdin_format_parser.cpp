#include "input_generator.h"


static string read_fmt_file(const string& filename) {
    string buf;
    FILE* fp = fopen(filename.c_str(), "r");
    if(!fp) {
        printf("cannot find format file `%s`\n", filename.c_str());
        assert(0);
    }
    char ch = 0;
    while (fscanf(fp, "%c", &ch) == 1 && !feof(fp)) {
        buf += ch;
    }
    fclose(fp);
    return buf;
}


static string gen_rand_int(int left, int right) {
    // return string of an random integer between left and right
    if(right < left) {
        printf("error in gen_rand_int, left=%d, right=%d\n", left, right);
        assert(0);
    }
    int r = rand() % (right - left + 1) + left;
    char buf[301];
    sprintf(buf, "%d", r);
    string ret = buf;
    return ret;
}

static char gen_rand_char() {
    char r1 = rand() % ('z' - 'a' + 1) + 'a';
    char r2 = rand() % ('Z' - 'A' + 1) + 'A';
    if (rand() % 2 == 0) {
        return r1;
    } else {
        return r2;
    }
}

static string gen_rand_string(int left, int right) {
    if(right < left) {
        printf("error in gen_rand_string, left=%d, right=%d\n", left, right);
        assert(0);
    }
    int len = rand() % (right - left + 1) + left;
    string ret;
    for (int i = 0; i < len; i++) {
        ret += gen_rand_char();
    }
    return ret;
}


/*
* strtok:
* https://cplusplus.com/reference/cstring/strtok/
*/

static string gen_input(const string& fmt) {
    srand((unsigned)time(0));

    char format[301];
    strcpy(format, fmt.c_str());
    char* token = nullptr;
    token = strtok(format, "(");

    int left = 0, right = 0;
    string ret;

    while (token) {
        if (strcmp(token, "int") == 0) {
            token = strtok(nullptr, ",");
            assert(sscanf(token, "%d", &left));
            token = strtok(nullptr, ")");
            assert(sscanf(token, "%d", &right));
            ret += gen_rand_int(left, right);
            ret += ' ';
        } else if (strcmp(token, "char") == 0) {
            ret += gen_rand_char();
            ret += ' ';
        } else if (strcmp(token, "string") == 0) {
            token = strtok(nullptr, ",");
            assert(sscanf(token, "%d", &left));
            token = strtok(nullptr, ")");
            assert(sscanf(token, "%d", &right));
            ret += gen_rand_string(left, right);
            ret += ' ';
        } else {
            printf("invaid data type: %s\n", token);
            assert(0);
        }
        // split when finding ' ' or '('
        token = strtok(nullptr, " (");
    }
    return ret;
}

void generate_input(const string& fmt_filename, const string& ret_filename) {
    string fmt = read_fmt_file(fmt_filename);
    string input = gen_input(fmt);
    FILE* fp = fopen(ret_filename.c_str(), "w");
    if(!fp) {
        printf("cannot write in %s\n", ret_filename.c_str());
        assert(0);
    }
    fprintf(fp, "%s", input.c_str());
    fclose(fp);
    printf("write random data in %s\n", ret_filename.c_str());
}
