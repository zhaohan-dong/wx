#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

struct report {
   char *response;
   size_t size;
 };

void queryurl(char *url, char *station, char *report_type);
int gethttps(char *url, struct report rpt);
int writeresponse(char *url, char *report_str);