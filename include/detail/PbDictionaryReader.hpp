#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbDictionaryReader {
public:
  explicit PbDictionaryReader(PbDictionaryIteratorRef iterator)
    : _iterator(iterator) {}

  class Iterator {
  public:
    Iterator() {}
    explicit Iterator(PbDictionaryIteratorRef iterator) : _current(iterator.readFirst()), _iterator(iterator) {}
    Iterator & operator++() { _current = _iterator.readNext(); return *this; }
    Iterator & operator++(int) { return ++*this; }
    PbTupleRef operator*() { return _current; }
    PbTupleRef * operator->() { return &_current; }
    bool operator==(const Iterator & it) const { return _current == it._current; }
    bool operator!=(const Iterator & it) const { return _current != it._current; }
  private:
    PbTupleRef _current;
    PbDictionaryIteratorRef _iterator;
  };

  Iterator begin() {
    return Iterator(_iterator);
  }

  Iterator end() {
    return Iterator();
  }

private:
  PbDictionaryIteratorRef _iterator;
};
