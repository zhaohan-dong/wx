#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>

void queryurl(char *url, char *station, char *report_type);
int gethttps(char *url);