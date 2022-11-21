#include <curl/curl.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAXQUERYLENGTH 1024

struct ReportStruct {
  char *reportstr;
  size_t size;
};

void queryurl(char *url, char *station, char *report_type, float hours_before_now);
void print_report(char **stations, int stations_len, char **report_types, int report_types_len);
char *filter_csv(char *csv_string, int row, int col);
int WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
int gethttps(char *url, struct ReportStruct report);