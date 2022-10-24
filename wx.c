/* Retrieve aviation weather reports using "wx.sh StationID ReportType"
    Created by Zhaohan Dong on 2022/10/23
    Station_ID is the airport ICAO code
    Reports is report type
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gethttps.h"

void parse_report(char *station_id, char *report_type, float query_hours_before);
char *filter_csv(char *res, int row);


int main(int argc, char **argv) {
    int i, j;
    char res[2048], station_ids[16][5], report_types[4][6];
    int station_idsc, report_typesc;

    // Handle input flags and return station_ids and report_types
    i = 1;
    while (i < argc) {

        // If argument is flag is -s, then we parse station ids
        if (strcmp(argv[i], "-s") == 0) {
            ++i;
            for (j = 0; argv[i] && (argv[i][0] != '-'); ++j) {
                strcpy(station_ids[j], argv[i++]);
                station_idsc = j + 1;
            }
        } else if (strcmp(argv[i], "-r") == 0) {

            // Else if argument is flag -r, we parse report types
            ++i;
            for (j = 0; argv[i] && (argv[i][0] != '-'); ++j) {
                strcpy(report_types[j], argv[i++]);
                report_typesc = j + 1;
            }
        } else {
            
            // Else advance to next argument
            ++i;
        }
    }
    for (i = 0; i < station_idsc; ++i) {
        printf("%s\n", station_ids[i]);
    }
    for (i = 0; i < report_typesc; ++i) {
        printf("%s\n", report_types[i]);
    }
            //parse_report(argv[i], "METAR", 4);
        //printf("%s\n", argv[i]);
    return 0;
}

/* Parse station_id (airport id) and report_type (metar/taf) to url string
 * then use get_https_response to 
 */
void parse_report(char *station_id, char *report_type, float query_hours_before) {
    char *response, *report;
    char url[150];
    snprintf(url, sizeof(url), "https://aviationweather.gov/adds/dataserver_current/httpparam?dataSource=%ss&requestType=retrieve&format=csv&stationString=%s&hoursBeforeNow=%2.2f", report_type, station_id, query_hours_before);
    printf("%d\n", get_https_response(url));
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