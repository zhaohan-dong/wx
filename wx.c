/* Retrieve aviation weather reports using "wx.sh StationID ReportType"
    Created by Zhaohan Dong on 2022/10/23
    Station_ID is the airport ICAO code
    Reports is report type
*/

#include <stdio.h>
#include <string.h>
#include "gethttps.h"

void parse_report(char *station_id, char *report_type, float query_hours_before);
char *filter_csv(char *res, int row);


int main(int argc, char **argv) {
    int i;
    char *rest;
    
    for (i = 1; i < argc; ++i) {
        parse_report(argv[i], "METAR", 4);
        //printf("Hello\n");
        printf("%d\n", rest);
        //printf("%s\n", argv[i]);
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
    response = get_https_response(url);
    // filter_csv(response, 7);
    //return report;
}

char *filter_csv(char *res, int row) {
    // i is nth char in res, j is nth char in ret_str, r is row counter
    int i, j, r;
    char *token;
    const char s[2] = ",";
    
    token = strtok(res, s);
   
   /* walk through other tokens */
   while( token != NULL ) {
      printf( " %s\n\n", token );
      printf("Hello!\n");
      token = strtok(NULL, s);
   }
    return token;
}