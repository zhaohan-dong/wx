/* Retrieve aviation weather reports using "wx.sh StationID ReportType"
    Created by Zhaohan Dong on 2022/10/23
    Station_ID is the airport ICAO code
    Reports is report type
*/
// use -lcurl to link curl library when compiling

#include <stdio.h>
#include <string.h>
#include "query.h"

#define MAXSTATION 1024
#define REPORTNUM 2

int main(int argc, char **argv) {
    char *stations[MAXSTATION], *report_types[REPORTNUM], *report_types_query[REPORTNUM];
    int stations_len=0, report_types_len=0;
    int i=1;

    // Return error if no argument is parsed
    if (argc < 2) {
        printf("Usage: wx {station names} [-r] report types\n");
        return -1;
    }

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

    // While remaining argc is greater than 1 (in case -r flag not given) and haven't read -r flag, assign argv[i++] to station list
    while (argc-- > 1 && (strcmp(stations[stations_len++] = argv[i++], "-r") != 0))
    ;

    // If last item in stations list is not -r (-r not given), use default reports METAR and TAF
    if (strcmp(stations[stations_len-1], "-r") != 0) {
        // Assign default report types
        report_types[0] = "METAR";
        report_types[1] = "TAF";
        report_types_len = 2;
    }
    // Else if -r is used to specify report types, read report types
    else {
        --stations_len; // Subtract 1 from stations_len to exclude -r from length
         while (argc-- > 1 && report_types_len < REPORTNUM) {
            report_types[report_types_len++] = argv[i++]; // Use i++ because argv[i] is now at the first report type
         }
    }



    // Retrieve data and print
    int j,k;

    for (j=0; j<stations_len; j++) {
        for (k=0; k<report_types_len; k++) {
            // Create memory in heap for URL string
            char *url = malloc(MAXQUERYLENGTH);
            //struct report rpt;
            // Complete the URL string in the heap
            queryurl(url, stations[j], report_types[k]);
            // Do something with the URL
            printf("%s\n", url);
            //gethttps(url, rpt);         // segmentation fault here
            //printf("%s\n", rpt.response);
            // Free memory in heap for URL string
            free(url);
        }
    }

    return 0;
}

/* Parse station_id (airport id) and report_type (metar/taf) to url string
 * then use get_https_response to 
 */
void parse_report(char *station_id, char *report_type, float query_hours_before) {
    char *response, *report;
    char url[150];
    snprintf(url, sizeof(url), "https://aviationweather.gov/adds/dataserver_current/httpparam?dataSource=%ss&requestType=retrieve&format=csv&stationString=%s&hoursBeforeNow=%2.2f", report_type, station_id, query_hours_before);
    //printf("%d\n", get_https_response(url));
    //filter_csv(response, 7);
    //return report;
}

/*
char *filter_csv(char *res, int row) {
    // i is nth char in res, j is nth char in ret_str, r is row counter
    int i, j, r;
    char *token;
    const char s[2] = ",";
    
    token = strtok(res, s);
   
   // walk through other tokens
   while( token != NULL ) {
      printf( " %s\n\n", token );
      printf("Hello!\n");
      token = strtok(NULL, s);
   }
    return token;
}*/