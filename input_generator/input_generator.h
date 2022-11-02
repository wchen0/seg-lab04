#ifndef __OUT_GEN__
#define __OUT_GEN__

#include <string>
#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <string>
#include <vector>

#include <dirent.h>
#include <unistd.h>
#include <filesystem>
#include <sys/stat.h>
#include <sys/types.h>

#define BATCH_SIZE 16

using namespace std;

void generate_input(const string& fmt_filename, const string& ret_filename);


#define L_RED       "\e[1;31m"
#define L_GREEN     "\e[1;32m"
#define NONE        "\e[0m"
#define printf_g(fmt, ...)   printf(L_GREEN fmt NONE, ##__VA_ARGS__)
#define printf_r(fmt, ...)   printf(L_RED fmt NONE, ##__VA_ARGS__)


#endif
