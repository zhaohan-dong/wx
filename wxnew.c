#include <stdio.h>
#include <string.h>

#define MAXSTATION 1024

int main(int argc, char **argv) {
    char *stations[MAXSTATION], *report_types[2];

    // check the argument number
    if (argc > 3) {
        printf("Please check input\n");
        return -1;
    }

    // if no report type is given, default to METAR and TAF
    if (argc == 2) {
        report_types[0] = "METAR";
        report_types[1] = "TAF";
    }



    printf("%d\n", argc);
    printf("%s %s\n", report_types[0], report_types[1]);
    return 0;
}