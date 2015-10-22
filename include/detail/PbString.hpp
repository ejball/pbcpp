#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbString {
public:
  PbString() {
    init();
  }

  explicit PbString(const char * text) {
    init();
    append(text);
  }

  PbString(const char * text, size_t length) {
    init();
    append(text, length);
  }

  PbString(PbString && text) {
    init();
    swap(text);
  }

  PbString & operator =(PbString && text) {
    if (this != &text) {
      destroy();
      init();
      swap(text);
    }
    return *this;
  }

  ~PbString() {
    destroy();
  }

  PbString & append(const PbString & text) {
    append(text._text, text._length);
    return *this;
  }

  PbString & append(const char * text) {
    append(text, strlen(text));
    return *this;
  }

  PbString & append(const char * text, size_t length) {
    if (length != 0) {
      reserve(_length + length);
      strncpy(_text + _length, text, length);
      _length += static_cast<uint16_t>(length);
      _text[_length] = '\0';
    }
    return *this;
  }

  template <typename... Args> PbString & appendFormat(const char * format, Args... args) {
    int available = _capacity - _length;
    int needed = snprintf(_text + _length, available + 1, format, args...);
    if (needed > available) {
      reserve(_length + needed);
      needed = snprintf(_text + _length, needed + 1, format, args...);
    }
    _length += needed;
    return *this;
  }

  PbString & appendDateTimeFormat(size_t max, const char * format, const PbDateTimeInfo & dateTimeInfo) {
    reserve(_length + max);
    _length += strftime(_text + _length, max + 1, format, &dateTimeInfo);
    _text[_length] = '\0';
    return *this;
  }

  PbString & assign(const PbString & text) {
    clear();
    append(text);
    return *this;
  }

  PbString & assign(const char * text) {
    clear();
    append(text);
    return *this;
  }

  PbString & assign(const char * text, size_t length) {
    clear();
    append(text, length);
    return *this;
  }

  template <typename... Args> PbString & assignFormat(const char * format, Args... args) {
    clear();
    appendFormat(format, args...);
    return *this;
  }

  PbString & assignDateTimeFormat(size_t max, const char * format, const PbDateTimeInfo & dateTimeInfo) {
    clear();
    appendDateTimeFormat(max, format, dateTimeInfo);
    return *this;
  }

  const char * c_str() const {
    return _text;
  }

  PbString & clear() {
    if (_length != 0) {
      _text[0] = '\0';
      _length = 0;
    }
    return *this;
  }

  PbString clone() {
    PbString text;
    text.append(*this);
    return text;
  }

  int compare(const PbString & text) {
    return strcmp(_text, text._text);
  }

  int compare(const char * text) {
    return strcmp(_text, text);
  }

  int compare(size_t length, const PbString & text) {
    return strncmp(_text, text._text, length);
  }

  int compare(size_t length, const char * text) {
    return strncmp(_text, text, length);
  }

  bool empty() const {
    return _length == 0;
  }

  bool equals(const PbString & text) {
    return strcmp(_text, text._text) == 0;
  }

  bool equals(const char * text) {
    return strcmp(_text, text) == 0;
  }

  bool equals(size_t length, const PbString & text) {
    return strncmp(_text, text._text, length) == 0;
  }

  bool equals(size_t length, const char * text) {
    return strncmp(_text, text, length) == 0;
  }

  size_t length() const {
    return _length;
  }

  PbString & reserve(size_t capacity) {
    if (capacity > _capacity) {
      if (_capacity == 0) {
        ++capacity;
        _text = reinterpret_cast<char *>(malloc(capacity));
        _text[0] = '\0';
      }
      else {
        ++capacity;
        capacity = capacity + (capacity >> 3) + (capacity < 9 ? 3 : 6);
        _text = reinterpret_cast<char *>(realloc(_text, capacity));
      }
      _capacity = static_cast<uint16_t>(capacity - 1);
    }
    return *this;
  }

  void swap(PbString & text) {
    std::swap(_text, text._text);
    std::swap(_length, text._length);
    std::swap(_capacity, text._capacity);
  }

  static const size_t maxLength = 65535;

private:
  PbString(char * text, uint16_t length, uint16_t capacity) {
    init(text, length, capacity);
  }

  void init() {
    _text = const_cast<char *>("");
    _length = 0;
    _capacity = 0;
  }

  void init(char * text, uint16_t length, uint16_t capacity) {
    _text = text;
    _length = length;
    _capacity = capacity;
  }

  void destroy() {
    if (_capacity != 0) {
      free(_text);
    }
  }

  char * _text;
  uint16_t _length;
  uint16_t _capacity;
};
