#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define F_PATH "/tmp/count_integral"

double calculate_integral(double a, double b, double rect_width) {
    double x;
    double sum = 0.0;
    for (x = a; x < b; x += rect_width) {
        sum += (4.0 / (x * x + 1.0)) * rect_width;
    }
    return sum;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Three arguments required \n");

        return 1;
    }
    double a = atof(argv[1]);
    double b = atof(argv[2]);
    double rect_width = atof(argv[3]);
    double integral = calculate_integral(a, b, rect_width);
    char str_integral[2048];

    int f = open(F_PATH, O_WRONLY);
    sprintf(str_integral, "%f", integral);
    write(f, str_integral, sizeof(str_integral));
    write(f, " ", sizeof(" "));
    close(f);

    return 0;
}