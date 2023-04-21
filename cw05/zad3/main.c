#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <fcntl.h>

#define F_PATH "/tmp/count_integral"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Two arguments required \n");
        return 1;
    }
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);
    int n = atoi(argv[2]);
    double segment_width = 1.0 / n;

    char a_buff[2048];
    char b_buff[2048];

    mkfifo(F_PATH, 0666);

    for (int i = 0; i < n; i++) {
        if (!fork()) {
            sprintf(a_buff, "%f", i * segment_width);
            sprintf(b_buff, "%f", (i + 1) * segment_width);
            execl("./counter", "counter", a_buff, b_buff, argv[1], NULL);
        }
    }

    int f = open(F_PATH, O_RDONLY);


    double total_integral = 0.0;

    char buff[2048];

    int already_got = 0;
    while (already_got < n) {
        read(f, buff, 2048);
        char delim[] = " ";
        char* token;
        token = strtok(buff, delim);

        while (token != NULL) {
            total_integral += strtod(token, NULL);
            already_got += 1;
            token = strtok(NULL, delim);
        }
    }
    close(f);
    remove(F_PATH);

    printf("Value of the integral: %lf\n", total_integral);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Time using %d processes: %lus\n", n, end.tv_sec - start.tv_sec);
    return 0;
}