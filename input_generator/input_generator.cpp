#include "input_generator.h"


static void generate_outputfiles_within_folder(const string& foldername) {
    char format_file_addr[64] = "";
    char* cur_dir = get_current_dir_name();
    strcpy(format_file_addr, cur_dir);
    free(cur_dir);
    strcat(format_file_addr, "/");
    strcat(format_file_addr, foldername.c_str());
    strcat(format_file_addr, "/stdin_format.txt");

    namespace fs = std::filesystem;
    string fmt_filename = format_file_addr;
    fs::path ret_folder = format_file_addr;
    ret_folder = ret_folder.parent_path() / "random_input";

    if (access(ret_folder.c_str(), 0)) {
        // if this folder does not exist, create it
        if(mkdir(ret_folder.c_str(), S_IRWXU) != 0) {
            printf("fail to create directory %s", ret_folder.c_str());
            assert(0);
        }
    }

    for(int i = 0; i < BATCH_SIZE; i++) {
        char tmp[12] = "";
        sprintf(tmp, "%d.txt", i);
        fs::path ret_filename = ret_folder / tmp;
        generate_input(fmt_filename, ret_filename.string());
    }
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
    printf("loading stdin format file from %s\n", cur_dir);
    free(cur_dir);

    vector<string> foldernames = get_all_foldernames();
    for(const string& foldername : foldernames) {
        generate_outputfiles_within_folder(foldername);
    }
}


int main(int argc, char** argv) {
    if(argc <= 1) {
        printf("name of targeted folder is necessary\n");
        assert(0);
    }
    // set seed for `generate_input`
    srand((unsigned)time(0));
    run(argc, argv);
    return 0;
}
