bool checkIdentical(const string &filename1, const string &filename2) {
    char ch = 0;

    FILE *fp1 = fopen(filename1.c_str(), "r");
    string str1;
    while(fscanf(fp1, "%c", &ch) && !feof(fp1)) {
        str1 += ch;
    }
    fclose(fp1);

    FILE *fp2 = fopen(filename2.c_str(), "r");
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