#include "input_generator.h"


static void generate_outputfiles_within_folder(const string& foldername) {
    char format_file_addr[64] = "";
    char* cur_dir = get_current_dir_name();
    strcpy(format_file_addr, cur_dir);
    free(cur_dir);
    strcat(format_file_addr, "/");
    strcat(format_file_addr, foldername.c_str());
    strcat(format_file_addr, "/stdin_format.txt");

    string fmt_filename = format_file_addr;
    string ret_filename = format_file_addr;
    for(int i = 0; i < 10; i++) {
        ret_filename.pop_back();
    }
    ret_filename += "random.txt";
    generate_input(fmt_filename, ret_filename);
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


void run(int argc, char** argv) {
    if(chdir(argv[1]) != 0) {
        printf("fail to change directory to %s\n", argv[1]);
        assert(0);
    }
    char* cur_dir = get_current_dir_name();
    printf("loading programs from %s\n", cur_dir);
    free(cur_dir);

    vector<string> foldernames = get_all_foldernames();
    for(const string& foldername : foldernames) {
        generate_outputfiles_within_folder(foldername);
    }
}


int main(int argc, char** argv) {
    if(argc <= 1) {
        printf("name of folder is necessary\n");
        assert(0);
    }
    run(argc, argv);
    return 0;
}
