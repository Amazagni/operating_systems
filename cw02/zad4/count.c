#include <stdio.h>
#include <stdlib.h>
#include <ftw.h>

long long totalSize = 0;
int countFile(const char *path, const struct stat *buff, int flag) {
    if (!S_ISDIR(buff->st_mode)) {
        printf("%s %lld B\n", path, (long long)buff->st_size);
        totalSize += (long long)buff->st_size;
    }
    return 0;
}
int main(int argc, char *argv[]) {
    char* dirPath = argv[1];
    ftw(dirPath, countFile, 1);
    printf("Total size: %lld\n", totalSize);
    return 0;
}