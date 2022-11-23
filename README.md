# Unix Utility to Fetch Aviation Weather Reports from NOAA
As a nerdy pilot, I wish to check my weather reports while I'm at office, without getting my iPad EFB out and using Foreflight.<br />
The usage is `wx station_names (optional) -r report_types <br />
Station names are four capital letters according to ICAO, e.g. KJFK for JFK, EGLL for Heathrow.
Report types can be entered either in all cap or lower case, and are currently limited to METAR or TAF report types.<br />

If you're not a pilot, here are the Wikipedia pages on METAR and TAF:<br />
https://en.wikipedia.org/wiki/METAR<br />
https://en.wikipedia.org/wiki/Terminal_aerodrome_forecast<br />

The data is fetched using API from https://aviationweather.gov

The executable `wx` is compiled for MacOS aarch64 using GCC 12. The shell script `wx.sh` is also provided.
