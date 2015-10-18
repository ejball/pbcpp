#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

struct PbNoncopyable {
public:
  PbNoncopyable() = default;
  ~PbNoncopyable() = default;
  PbNoncopyable(const PbNoncopyable &) = delete;
  PbNoncopyable & operator=(const PbNoncopyable &) = delete;
};
