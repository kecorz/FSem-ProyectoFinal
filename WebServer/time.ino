// Get internal server time.
// Input: int [3] array to store data time.
void getServerTime(int *timeArr)
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo))
  {
    Serial.println("Failed to obtain time");
    return;
  }

  int hour = timeinfo.tm_hour;
  int minutes = timeinfo.tm_min;
  int seconds = timeinfo.tm_sec;

  int detail = 0;
  if (hour < 12)
  {
    detail = 0;
  }
  else
  {
    hour -= 12;
    detail = 1;
  }

  timeArr[0] = hour;
  timeArr[1] = minutes;
  timeArr[2] = detail;
}

// Get input time (from string).
// Input: int [3] array to store data time.
//        time string - HH::MM AM
void getSelectedTime(int *timeArr, String timeString)
{
  String hourDelimeter = ":";
  String minutesDelimeter = " ";

  String hour = timeString.substring(0, timeString.indexOf(hourDelimeter));

  timeString.remove(0, timeString.indexOf(hourDelimeter) + 1);

  String minutes = timeString.substring(0, timeString.indexOf(minutesDelimeter));

  timeString.remove(0, timeString.indexOf(minutesDelimeter) + 1);

  int detail;
  if (timeString == "AM")
  {
    detail = 0;
  }
  else
  {
    detail = 1;
  }

  timeArr[0] = hour.toInt();
  timeArr[1] = minutes.toInt();
  timeArr[2] = detail;
}
