#include <stdio.h>
#include <string.h>

#define MAXSTATION 1024
#define REPORTNUM 2

int main(int argc, char **argv) {
    char *stations[MAXSTATION], *report_types[REPORTNUM];
    int stations_len=0, report_types_len=0;
    int i=1, j=0, k=0;

    // Print usage help
    if (strcmp(argv[i], "-h") == 0) {
        printf("Usage: wx {station names} [-r] report types\n");
        return 0;
    }

    // Check against inputing -r first
    if (strcmp(argv[i], "-r") == 0) {
        printf("Please enter station identifier first before report type\n");
        printf("For usage, use -h\n");
        return -1;
    }

    // Initialize length counts if arguments passed the checks before
    stations_len=0;
    report_types_len=0;

    // While remaining argc is greater than 1 (in case -r flag not given) and haven't read -r flag, assign argv[++i] to station list
    while (--argc > 1 && (strcmp((stations[stations_len++] = argv[++i]), "-r") != 0))
    ;

    // If last item in stations list is not -r (-r not given), use default reports METAR and TAF
    if (strcmp(stations[--stations_len], "-r") != 0) {
        ++stations_len; // Add 1 back to station length that was deducted from comparison

        // Assign default report types
        report_types[0] = "METAR";
        report_types[1] = "TAF";
        report_types_len = 2;
    }
    // Else read report types
    else {
         while (--argc > 1 && k < REPORTNUM) {
            report_types[k++] = argv[++i]; // Use ++i because argv[i] is now at the -r flag
            ++report_types_len;
         }
    }

        // Last string read into stations[] is -r, so we'll delete that
        //stations[--j] = NULL;
        /*while (--argc > 0) {
            argv[i++] = report_types[k++];
        }*/

    /*
    // If first argument is report flag
    else if (argv[i] == "-r") {
        while ((argv[i++] = report_types[k++]) != "-r" && --argc > 0)
        ;
        while (--argc > 0) {
            argv[i++] = stations[j++];
        }
    }

*/
/*
    // if no report type is given, default to METAR and TAF
    if (argc == 2) {
        report_types[0] = "METAR";
        report_types[1] = "TAF";
    }

    // if report type(s) are given, break the third argument into tokens of report type and reduce argc
    else if (argc-- == 3) {
        
        // initiate strtok and get first report type from argument
        report_types[i] = strtok(argv[argc], " ");

        // continue reading string, second check ensures the array is within size
        

        // set argc to 1
        --argc;
    }

    // initiate strtok and get first station from argument
    //i = 0;
    //stations[0] = strtok(argv[argc], " ");
    // continue reading string, second check ensures the array is within size
    while (argv[argc] != NULL) {
        stations[++i] = strtok(NULL, " "); 
    }

*/

    return 0;
}