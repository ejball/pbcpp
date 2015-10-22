#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbSystem {
public:
  static bool isRound() {
#ifdef PBL_ROUND
    return true;
#else
    return false;
#endif
  }

  static bool is24hStyle() {
    return clock_is_24h_style();
  }

  PbSystem() = delete;
};
