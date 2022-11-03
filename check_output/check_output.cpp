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

using namespace std;


bool checkIdentical(const string& filename1, const string& filename2) {
    char ch = 0;

    FILE* fp1 = fopen(filename1.c_str(), "r");
    string str1;
    while(fscanf(fp1, "%c", &ch) && !feof(fp1)) {
        str1 += ch;
    }
    fclose(fp1);

    FILE* fp2 = fopen(filename2.c_str(), "r");
    string str2;
    while(fscanf(fp2, "%c", &ch) && !feof(fp2)) {
        str2 += ch;
    }
    fclose(fp2);

    int l1 = str1.length(), l2 = str2.length();
    int i = 0;
    for(i = 0; i < l1 && i < l2; i++) {
        if(str1[i] != str2[i]) return false;
    }
    if(i < l1) return false;
    if(i < l2) return false;

    return true;
}


static vector<string> get_all_foldernames() {
    char* cur_dir = get_current_dir_name();
    DIR* dirStream = opendir(cur_dir);
    free(cur_dir);
    assert(dirStream);
    dirent* dirInfo;
    vector<string> foldername;

    while((dirInfo = readdir(dirStream)) != 0) {
        if(dirInfo->d_name[0] == '.') {
            continue;
        }
        if(dirInfo->d_type == 4) {  // is directory
            foldername.emplace_back(dirInfo->d_name);
            printf("cluster directory: %s\n", foldername.back().c_str());
        }
    }
    closedir(dirStream);
    return foldername;
}


int count_output_files(const string& set_name) {
    DIR* dirStream = opendir(set_name.c_str());
    assert(dirStream);
    dirent* dirInfo;
    int cnt = 0;
    while((dirInfo = readdir(dirStream)) != 0) {
        if(dirInfo->d_name[0] == '.') {
            continue;
        }
        if(strlen(dirInfo->d_name) >= 4 &&
                strcmp(dirInfo->d_name + (int)strlen(dirInfo->d_name) - 4, ".txt") == 0 &&
                dirInfo->d_type == 8) {                                 // file 'xxx.txt'
            cnt++;
        }
    }
    closedir(dirStream);
    return cnt;
}


void compare_output_set_pair(const string& set_name1, const string& set_name2) {
    int cnt1 = count_output_files(set_name1);
    int cnt2 = count_output_files(set_name2);
    if(cnt1 != cnt2) {
        printf("find %d output files in %s, but there are %d output files in %s\n"
               "cannot compare these two output sets\n",
               cnt1, set_name1.c_str(), cnt2, set_name2.c_str());
        assert(0);
    }
    
}



static void compare_output_within_folder(const string& foldername) {
    // foldername is the folder of a cluster
    namespace fs = std::filesystem;
    fs::path folder_path = foldername;
    printf("in cluster: %s\n", folder_path.c_str());

    DIR* dirStream = opendir(folder_path.c_str());
    assert(dirStream);
    dirent* dirInfo;
    vector<string> output_set_names;

    while((dirInfo = readdir(dirStream)) != 0) {
        if(dirInfo->d_name[0] == '.') {
            continue;
        }
        if(strlen(dirInfo->d_name) >= 4 &&
                strcmp(dirInfo->d_name + (int)strlen(dirInfo->d_name) - 4, "_out") == 0 &&
                dirInfo->d_type == 4) {                                 // directory 'xxx_out'
            output_set_names.emplace_back((folder_path / dirInfo->d_name).string());
            printf("output set: %s\n", dirInfo->d_name);
        }
    }
    closedir(dirStream);

    vector<pair<string, string>> output_set_pair;
    int output_set_num = output_set_names.size();
    for(int i = 0; i < output_set_num; i++) {
        for(int j = i + 1; j < output_set_num; j++) {
            compare_output_set_pair(output_set_names[i], output_set_names[j]);
        }
    }
}


void run(int argc, char** argv) {
    if(chdir(argv[1]) != 0) {
        printf("fail to change directory to %s\n", argv[1]);
        assert(0);
    }
    char* cur_dir = get_current_dir_name();
    printf("loading output files from directory %s\n", cur_dir);
    free(cur_dir);

    vector<string> foldernames = get_all_foldernames();
    for(const string& foldername : foldernames) {
        compare_output_within_folder(foldername);
    }
}


int main(int argc, char** argv) {
    if(argc <= 1) {
        printf("missing arg: targeted directory\n");
        assert(0);
    }

    run(argc, argv);

    return 0;
}
