#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <time.h>


double calculate_integral(double a, double b, double rect_width) {
    double x;
    double sum = 0.0;
    for (x = a; x < b; x += rect_width) {
        sum += (4.0 / (x * x + 1.0)) * rect_width;
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Two arguments required \n");
        return 1;
    }
    struct timespec start, end;
    clock_gettime(CLOCK_REALTIME, &start);

    double rect_width = atof(argv[1]);
    int n = atoi(argv[2]);
    double a = 0.0;
    double b = 1.0;
    double segment_width = (b - a) / n;
    int fd[n][2];

    for (int i = 0; i < n; i++) {
        if (pipe(fd[i]) == -1) {
            perror("pipe");
            return 1;
        };

        if (fork() == 0) {
            close(fd[i][0]);

            double tmp_a = a + i * segment_width;
            double tmp_b = tmp_a + segment_width;
            double integral = calculate_integral(tmp_a, tmp_b, rect_width);

            write(fd[i][1], &integral, sizeof(integral));

            close(fd[i][1]);
            return 0;
        }
        else {
            close(fd[i][1]);
        }
    }

    double total_integral = 0.0;
    double tmp_integral;

    for (int i = 0; i < n; i++) {
        read(fd[i][0], &tmp_integral, sizeof(tmp_integral));

        total_integral += tmp_integral;
        close(fd[i][0]);
    }

    printf("Value of the integral: %lf\n", total_integral);
    clock_gettime(CLOCK_REALTIME, &end);
    printf("Time using %d processes: %lus\n", n, end.tv_sec - start.tv_sec);
    return 0;
}