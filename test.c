#include <stdio.h>
#include <string.h>
#include "gethttps.c"

int main() {
    gethttps("https://aviationweather.gov/adds/dataserver_current/httpparam?dataSource=metars&requestType=retrieve&format=csv&stationString=KDEN&hoursBeforeNow=2");
}