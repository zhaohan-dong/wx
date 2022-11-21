/* Get https response in csv file format from aviationweather.gov
 * Example URL: https://aviationweather.gov/adds/dataserver_current/httpparam?dataSource=metars&requestType=retrieve&format=csv&stationString=KDEN&hoursBeforeNow=2
 * Using example from official curl example: https://curl.se/libcurl/c/https.html and curl.h
*/

#include "query.h"

void queryurl(char *url, char *station, char *report_type) {

  // Temp fix for lowercase METAR and TAF (API only takes lowercase)
  if (strcmp(report_type, "METAR") == 0) {
            report_type = "metar";
        } else if (strcmp(report_type, "TAF") == 0) {
            report_type = "taf";
        }
  
  snprintf(url, MAXQUERYLENGTH, "https://aviationweather.gov/adds/dataserver_current/httpparam?dataSource=%ss&requestType=retrieve&format=csv&stationString=%s&hoursBeforeNow=6.25", report_type, station);
}

int gethttps(char *url, struct report rpt) {
  CURL *curl;
  CURLcode res;
 
  curl_global_init(CURL_GLOBAL_DEFAULT);
 
  curl = curl_easy_init();

  if(curl) {
    curl_easy_setopt(curl, CURLOPT_URL, url);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&rpt);
 
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