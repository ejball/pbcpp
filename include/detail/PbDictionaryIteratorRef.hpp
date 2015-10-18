#ifndef PBCPP_HPP
#error Include pbcpp.hpp instead.
#endif

class PbDictionaryIteratorRef : public PbHandleRef<DictionaryIterator *> {
public:
  PbDictionaryIteratorRef() {}

  explicit PbDictionaryIteratorRef(DictionaryIterator * handle)
    : PbHandleRef(handle) {}

  uint32_t size() {
    return dict_size(_handle);
  }

  PbTupleRef readFirst() {
    return PbTupleRef(dict_read_first(_handle));
  }

  PbTupleRef readNext() {
    return PbTupleRef(dict_read_next(_handle));
  }

  DictionaryResult writeData(const uint32_t key, const uint8_t * const data, const uint16_t size) {
    return dict_write_data(_handle, key, data, size);
  }

  DictionaryResult writeString(const uint32_t key, const char * const cstring) {
    return dict_write_cstring(_handle, key, cstring);
  }

  DictionaryResult writeUInt8(const uint32_t key, const uint8_t value) {
    return dict_write_uint8(_handle, key, value);
  }

  DictionaryResult writeUInt16(const uint32_t key, const uint16_t value) {
    return dict_write_uint16(_handle, key, value);
  }

  DictionaryResult writeUInt32(const uint32_t key, const uint32_t value) {
    return dict_write_uint32(_handle, key, value);
  }

  DictionaryResult writeInt8(const uint32_t key, const int8_t value) {
    return dict_write_int8(_handle, key, value);
  }

  DictionaryResult writeInt16(const uint32_t key, const int16_t value) {
    return dict_write_int16(_handle, key, value);
  }

  DictionaryResult writeInt32(const uint32_t key, const int32_t value) {
    return dict_write_int32(_handle, key, value);
  }
};
