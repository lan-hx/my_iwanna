#ifndef MY_IWANNA_SRC_ENTITY_COMMON_H_ 
#define MY_IWANNA_SRC_ENTITY_COMMON_H_

#include <cstdint>
#include <cctype>
#include <cstring>

enum EntityTypeId { invalid_type = -1, player, barrier, trap, portal };

int32_t StringGetInt(const char *s, int32_t &x) {
  int32_t size = 0;
  bool neg = false;
  x = 0;
  while (*(s + size) <= 32) {
    ++size;
  }
  if ((*(s + size) == '-') || (*(s + size) == '+')) {
    neg = (*(s + size) == '-');
    ++size;
  }
  while (isdigit(*(s + size)) != 0) {
    x = x * 10 + *(s + size++) - 48;
  }
  if (neg) {
    x = -x;
  }
  return size;
}

int32_t StringGetType(const char *s, EntityTypeId &t) {
  int32_t tmp;
  int32_t size;
  size = StringGetInt(s, tmp);
  switch (tmp) {
    case 0:
      t = EntityTypeId::player;
      break;
    case 1:
      t = EntityTypeId::barrier;
      break;
    case 2:
      t = EntityTypeId::trap;
      break;
    case 3:
      t = EntityTypeId::portal;
      break;
    default:
      t = EntityTypeId::invalid_type;
      break;
  }
  return size;
}

int32_t StringGetString(const char *s, char *str) {
  int32_t size = 0;
  while (*(s + size) <= 32) {
    ++size;
  }
  while (*(s + size) > 32) {
    *str++ = *(s + size++);
  }
  *str = '\0';
  return size;
}

#endif