#!/bin/sh

# Retrieve aviation weather reports using "wx.sh StationID ReportType"
# Created by Zhaohan Dong on 2022/10/22
# Station_ID is the airport ICAO code
# Reports is report type
# Example URL: https://aviationweather.gov/adds/dataserver_current/httpparam?dataSource=metars&requestType=retrieve&format=csv&stationString=KDEN&hoursBeforeNow=2

STATION_IDS=${1}
REPORTS="${2:-"METAR" "TAF"}"

echo ---START---
echo `date -u +"%y/%m/%d %T"`

for STATION_ID in ${STATION_IDS}
do
	echo
	for REPORT in ${REPORTS}
	do
		echo ${STATION_ID} ${REPORT}
		echo "https://aviationweather.gov/adds/dataserver_current/httpparam?dataSource=${REPORT}s&requestType=retrieve&format=csv&stationString=${STATION_ID}&hoursBeforeNow=6.15" |
		tr '[:upper:]' '[:lower:]' |
		xargs curl -s |
		awk -F "," 'FNR == 7 {print $1}'
	done
done

echo ----END----