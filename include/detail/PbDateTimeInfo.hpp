#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbDateTimeInfo : public tm {
public:
  PbDateTimeInfo(const tm & tm) {
    memcpy(this, &tm, sizeof(tm));
  }

  int year() const {
    return tm_year + 1900;
  }

  int month() const {
    return tm_mon + 1;
  }

  int day() const {
    return tm_mday;
  }

  int hour() const {
    return tm_hour;
  }

  int minute() const {
    return tm_min;
  }

  int second() const {
    return tm_sec;
  }

  int hour12() const {
    return tm_hour > 12 ? tm_hour - 12 : tm_hour != 0 ? tm_hour : 12;
  }

  bool isPM() const {
    return tm_hour >= 12;
  }

  int weekday() const {
    return tm_wday + 1;
  }

  int yearday() const {
    return tm_yday + 1;
  }
};
