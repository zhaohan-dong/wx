/* Get https response in csv file format from aviationweather.gov
 * Example URL: https://aviationweather.gov/adds/dataserver_current/httpparam?dataSource=metars&requestType=retrieve&format=csv&stationString=KDEN&hoursBeforeNow=2
 * Using example from official curl example: https://curl.se/libcurl/c/getinmemory.html and curl.h
*/

#include "query.h"

// Function to get query URL
void queryurl(char *url, char *station, char *report_type) {

  // Temp fix for lowercase METAR and TAF (API only takes lowercase)
  if (strcmp(report_type, "METAR") == 0) {
            report_type = "metar";
        } else if (strcmp(report_type, "TAF") == 0) {
            report_type = "taf";
        }
  
  snprintf(url, MAXQUERYLENGTH, "https://aviationweather.gov/adds/dataserver_current/httpparam?dataSource=%ss&requestType=retrieve&format=csv&stationString=%s&hoursBeforeNow=6.25", report_type, station);
}

// Fuction to print report
void print_report(char **stations, int stations_len, char **report_types, int report_types_len) {
    //printf("%d\n", get_https_response(url));
    //filter_csv(response, 7);
    //return report;
    int j,k;

    for (j=0; j<stations_len; j++) {
        for (k=0; k<report_types_len; k++) {

            // Create memory in heap for URL string
            char *url = calloc(1, MAXQUERYLENGTH);

            struct ReportStruct report;
            // Create a new struct called report defined in query.h to get curl result
            report.reportstr = calloc(4, 8192);
            report.size = 0;

            // Complete the URL string in the heap
            queryurl(url, stations[j], report_types[k]);
            // Debug: print query URL to check
            // printf("%s\n", url);
            // Get report from url
            gethttps(url, report);

            // Free URL from memory since it has been used
            free(url);
            url = NULL;

            printf("%s\n", report.reportstr);
            // Free memory in heap for URL string
            free(report.reportstr);

        }
    }
}

// Callback function for curl https request, wrapped in gethttps
int WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
  size_t realsize = size * nmemb;
  struct ReportStruct *mem = (struct ReportStruct *)userp;
 
  char *ptr = realloc(mem->reportstr, mem->size + realsize + 1);
  if(!ptr) {
    /* out of memory! */
    printf("not enough memory (realloc returned NULL)\n");
    return 0;
  }
 
  mem->reportstr = ptr;
  memcpy(&(mem->reportstr[mem->size]), contents, realsize);
  mem->size += realsize;
  mem->reportstr[mem->size] = 0;

  return realsize;
}

// Curl get https
int gethttps(char *url, struct ReportStruct report) {
  CURL *curl;
  CURLcode res;
 
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  curl = curl_easy_init();

  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    /* send all data to this function  */
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
 
    /* we pass our 'chunk' struct to the callback function */
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&report);
 
#ifdef SKIP_PEER_VERIFICATION
    /*
     * If you want to connect to a site who is not using a certificate that is
     * signed by one of the certs in the CA bundle you have, you can skip the
     * verification of the server's certificate. This makes the connection
     * A LOT LESS SECURE.
     *
     * If you have a CA cert for the server stored someplace else than in the
     * default bundle, then the CURLOPT_CAPATH option might come handy for
     * you.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
#endif
 
#ifdef SKIP_HOSTNAME_VERIFICATION
    /*
     * If the site you are connecting to uses a different host name that what
     * they have mentioned in their server certificate's commonName (or
     * subjectAltName) fields, libcurl will refuse to connect. You can skip
     * this check, but this will make the connection less secure.
     */
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 0L);
#endif
 
    /* Perform the request, res will get the return code */
    res = curl_easy_perform(curl);
    /* Check for errors */
    if(res != CURLE_OK)
      fprintf(stderr, "curl_easy_perform() failed: %s\n",
              curl_easy_strerror(res));
    /* always cleanup */
    curl_easy_cleanup(curl);
  }
 
  curl_global_cleanup();

  return res;
}