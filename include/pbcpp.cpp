#include "pbcpp.hpp"

void * operator new(size_t size) {
  void * ptr = malloc(size);
  PB_ASSERT(ptr != nullptr);
  return ptr;
}

void operator delete(void * ptr) {
  free(ptr);
}

void * operator new[](size_t size) {
  void * ptr = malloc(size);
  PB_ASSERT(ptr != nullptr);
  return ptr;
}

void operator delete[](void * ptr) {
  free(ptr);
}
