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


#define L_RED       "\e[1;31m"
#define L_GREEN     "\e[1;32m"
#define NONE        "\e[0m"
#define printf_g(fmt, ...)   printf(L_GREEN fmt NONE, ##__VA_ARGS__)
#define printf_r(fmt, ...)   printf(L_RED fmt NONE, ##__VA_ARGS__)


using namespace std;


std::filesystem::path base_path;    // =argv[1]=input/ 


int checkIdentical(const string& filename1, const string& filename2) {
    // currently under 'input' directory
    // return 0 if not identical
    // return 1 if identical
    // return 3 if error occurs
    char ch = 0;

    FILE* fp1 = fopen(filename1.c_str(), "r");
    if (!fp1) return 3;

    string str1;
    while (fscanf(fp1, "%c", &ch) && !feof(fp1)) {
        str1 += ch;
    }
    fclose(fp1);


    FILE* fp2 = fopen(filename2.c_str(), "r");
    if (!fp2) return 3;

    string str2;
    while (fscanf(fp2, "%c", &ch) && !feof(fp2)) {
        str2 += ch;
    }
    fclose(fp2);


    int l1 = str1.length(), l2 = str2.length();
    if (l1 != l2) return false;
    int i = 0;
    for (i = 0; i < l1 && i < l2; i++) {
        if (str1[i] != str2[i]) return false;
    }
    if (i < l1) return false;
    if (i < l2) return false;

    return true;
}


static vector<string> get_all_cluster_names() {
    // currently under 'input' directory
    // find all cluster folder in 'input'
    char* cur_dir = get_current_dir_name();
    DIR* dirStream = opendir(cur_dir);
    free(cur_dir);
    assert(dirStream);
    dirent* dirInfo;
    vector<string> foldername;

    while ((dirInfo = readdir(dirStream)) != 0) {
        if (dirInfo->d_name[0] == '.') {
            continue;
        }
        if (dirInfo->d_type == 4) {  // is directory
            foldername.emplace_back(dirInfo->d_name);
            printf("cluster directory: %s\n", foldername.back().c_str());
        }
    }
    closedir(dirStream);
    return foldername;
}


int count_output_files(const string& set_name) {
    // count how many output files there are with in an '_out' directory
    DIR* dirStream = opendir(set_name.c_str());
    assert(dirStream);
    dirent* dirInfo;
    int cnt = 0;
    while ((dirInfo = readdir(dirStream)) != 0) {
        if (dirInfo->d_name[0] == '.') {
            continue;
        }
        if (strlen(dirInfo->d_name) >= 4 &&
            strcmp(dirInfo->d_name + (int)strlen(dirInfo->d_name) - 4, ".txt") == 0 &&
            dirInfo->d_type == 8) {                                 // file 'xxx.txt'
            cnt++;
        }
    }
    closedir(dirStream);
    return cnt;
}


void record_equivalent_pairs(const string& set_name1, const string& set_name2) {
    char* cur_dir = get_current_dir_name();
    string record_filename = cur_dir;
    free(cur_dir);
    record_filename += "/equal.csv";

    FILE* fp = fopen(record_filename.c_str(), "a");
    if (!fp) {
        printf("cannot create result file: %s\n", record_filename.c_str());
        assert(0);
    }

    string tmp1 = set_name1;
    int l1 = tmp1.length();
    tmp1.at(l1 - 4) = '.'; tmp1.at(l1 - 3) = 'c'; tmp1.at(l1 - 2) = 'p'; tmp1.at(l1 - 1) = 'p';
    string tmp2 = set_name2;
    int l2 = tmp2.length();
    tmp2.at(l2 - 4) = '.'; tmp2.at(l2 - 3) = 'c'; tmp2.at(l2 - 2) = 'p'; tmp2.at(l2 - 1) = 'p';
    fprintf(fp, "%s,%s\n", (base_path / tmp1).c_str(), (base_path / tmp2).c_str());
    fclose(fp);
}

void record_inequivalent_pairs(const string& set_name1, const string& set_name2) {
    char* cur_dir = get_current_dir_name();
    string record_filename = cur_dir;
    free(cur_dir);
    record_filename += "/inequal.csv";

    FILE* fp = fopen(record_filename.c_str(), "a");
    if (!fp) {
        printf("cannot create result file: %s\n", record_filename.c_str());
        assert(0);
    }
    
    string tmp1 = set_name1;
    int l1 = tmp1.length();
    tmp1.at(l1 - 4) = '.'; tmp1.at(l1 - 3) = 'c'; tmp1.at(l1 - 2) = 'p'; tmp1.at(l1 - 1) = 'p';
    string tmp2 = set_name2;
    int l2 = tmp2.length();
    tmp2.at(l2 - 4) = '.'; tmp2.at(l2 - 3) = 'c'; tmp2.at(l2 - 2) = 'p'; tmp2.at(l2 - 1) = 'p';
    fprintf(fp, "%s,%s\n", (base_path / tmp1).c_str(), (base_path / tmp2).c_str());
    fclose(fp);
}

void record_error_pairs(const string& set_name1, const string& set_name2) {
    char* cur_dir = get_current_dir_name();
    string record_filename = cur_dir;
    free(cur_dir);
    record_filename += "/error.csv";

    FILE* fp = fopen(record_filename.c_str(), "a");
    if (!fp) {
        printf("cannot create result file: %s\n", record_filename.c_str());
        assert(0);
    }

    string tmp1 = set_name1;
    int l1 = tmp1.length();
    tmp1.at(l1 - 4) = '.'; tmp1.at(l1 - 3) = 'c'; tmp1.at(l1 - 2) = 'p'; tmp1.at(l1 - 1) = 'p';
    string tmp2 = set_name2;
    int l2 = tmp2.length();
    tmp2.at(l2 - 4) = '.'; tmp2.at(l2 - 3) = 'c'; tmp2.at(l2 - 2) = 'p'; tmp2.at(l2 - 1) = 'p';
    fprintf(fp, "%s,%s\n", (base_path / tmp1).c_str(), (base_path / tmp2).c_str());
    fclose(fp);
}


bool flag_num_in_ouputsets = true;
// use to count how many random tests there are within a cluster
int num_in_ouputsets;


bool compare_one_output_set_pair(const string& set_name1, const string& set_name2) {
    // return true if compare runs successfully
    // false if error occurs
    int cnt1 = count_output_files(set_name1);
    int cnt2 = count_output_files(set_name2);
    if (cnt1 != cnt2) {
        printf_r("find %d output files in %s, but there are %d output files in %s\n"
            "cannot compare these two output sets\n",
            cnt1, set_name1.c_str(), cnt2, set_name2.c_str());
        record_error_pairs(set_name1, set_name2);
        return false;
    }

    if (cnt1 == 0 && cnt2 == 0) {
        printf("both %s and %s have 0 output file, skip\n");
        return true;
    }

    if (flag_num_in_ouputsets) {
        flag_num_in_ouputsets = false;
        num_in_ouputsets = cnt1;
    }

    for (int i = 0; i < cnt1; i++) {
        char tmp[12] = "";
        sprintf(tmp, "/%d.txt", i);
        string fn1 = set_name1 + tmp;
        string fn2 = set_name2 + tmp;
        int ans = checkIdentical(fn1, fn2);
        if (ans == 0) {
            record_inequivalent_pairs(set_name1, set_name2);
            return true;
        }
        if (ans == 3) {
            record_error_pairs(set_name1, set_name2);
            return false;
        }
    }
    record_equivalent_pairs(set_name1, set_name2);
    return true;
}


static void compare_output_within_one_cluster(const string& foldername) {
    // foldername is the folder of a cluster
    // find all '_out' output sets
    namespace fs = std::filesystem;
    fs::path folder_path = foldername;
    printf("in cluster: %s\n", folder_path.c_str());

    DIR* dirStream = opendir(folder_path.c_str());
    assert(dirStream);
    dirent* dirInfo;
    vector<string> output_set_names;

    while ((dirInfo = readdir(dirStream)) != 0) {
        if (dirInfo->d_name[0] == '.') {
            continue;
        }
        if (strlen(dirInfo->d_name) >= 4 &&
            strcmp(dirInfo->d_name + (int)strlen(dirInfo->d_name) - 4, "_out") == 0 &&
            dirInfo->d_type == 4) {                                 // directory 'xxx_out'
            output_set_names.emplace_back((folder_path / dirInfo->d_name).string());
            printf("output set: %s\n", dirInfo->d_name);
        }
    }
    closedir(dirStream);

    int output_set_num = output_set_names.size();
    int cnt = 0;
    for (int i = 0; i < output_set_num; i++) {
        for (int j = i + 1; j < output_set_num; j++) {
            cnt += compare_one_output_set_pair(output_set_names[i], output_set_names[j]);
        }
    }
    printf_g("find %d output sets in cluster %s\n"
        "compared %d pairs of output sets, %d failed\n",
        output_set_num, folder_path.c_str(), cnt, output_set_num * (output_set_num - 1) / 2 - cnt);

    printf("find %d output files in each output set\n", num_in_ouputsets);
    flag_num_in_ouputsets = true;
}


void run(int argc, char** argv) {
    if (chdir(argv[1]) != 0) {
        printf_r("fail to change directory to %s\n", argv[1]);
        assert(0);
    }
    char* cur_dir = get_current_dir_name();
    printf_g("loading output files from directory %s\n", cur_dir);

    // clear all results
    // equal.csv, inequal.csv, error.csv are in 'input' directory
    // they will be moved to 'output' directory in run.sh
    string record = cur_dir;
    free(cur_dir);
    FILE* fp = fopen((record + "/equal.csv").c_str(), "w");
    assert(fp); fclose(fp);
    fp = fopen((record + "/inequal.csv").c_str(), "w");
    assert(fp); fclose(fp);
    fp = fopen((record + "/error.csv").c_str(), "w");
    assert(fp); fclose(fp);

    vector<string> foldernames = get_all_cluster_names();
    for (const string& foldername : foldernames) {
        compare_output_within_one_cluster(foldername);
    }
}


int main(int argc, char** argv) {
    if (argc <= 1) {
        printf_r("missing arg: targeted directory\n");
        assert(0);
    }
    // base_path == ./input/
    base_path = argv[1];
    run(argc, argv);

    return 0;
}
