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

#define BATCH_SIZE 12

using namespace std;

void generate_input(const string& fmt_filename, const string& ret_filename);


#endif
