#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>

int main() {
    DIR *dir;
    struct stat buff;
    struct dirent *file;
    long long totalSize = 0;

    dir = opendir(".");
    while ((file = readdir(dir)) != NULL) {
        stat(file->d_name, &buff);
        if (!S_ISDIR(buff.st_mode)) {
            printf("%s %lld B\n", file->d_name, (long long)buff.st_size);
            totalSize += (long long)buff.st_size;
        }
    }
    printf("Total size %lld B\n", totalSize);
    closedir(dir);
    return 0;
}