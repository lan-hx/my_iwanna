#ifndef MY_IWANNA_SRC_ENTITY_COMMON_H_ 
#define MY_IWANNA_SRC_ENTITY_COMMON_H_

#include <cstdint>
#include <cctype>
#include <cstring>

enum EntityTypeId { invalid_type = -1, player, barrier, trap, portal };
enum YState { on_ground, first_jump_begin, first_jump_end, second_jump_begin, second_jump_end };
enum XState { idle, moving };
enum HotAreaType { invalid_hotarea_type = -1, rectangular, triangular, point_set };

inline int32_t StringGetInt(const char *s, int32_t &x) {
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

inline int32_t StringGetType(const char *s, EntityTypeId &t) {
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

inline int32_t StringGetString(const char *s, char *str) {
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

inline int64_t CrossProduct(const int32_t &x1, const int32_t &y1, const int32_t &x2, const int32_t &y2){
    return static_cast<int64_t>(x1) * static_cast<int64_t>(y2) - static_cast<int64_t>(x2) * static_cast<int64_t>(y1);
}

inline bool Intersect (const int32_t &x1, const int32_t &y1, const int32_t &x2, const int32_t &y2, const int32_t &x3, const int32_t &y3, const int32_t &x4, const int32_t &y4){
    return (CrossProduct(x3 - x1, y3 - y1, x4 - x1, y4 - y1) * CrossProduct(x3 - x2, y3 - y2, x4 - x2, y4 - y2) <= 0);
}

inline bool InTriangle(const int32_t &x, const int32_t &y, const int32_t &x1, const int32_t &y1, const int32_t &x2, const int32_t &y2, const int32_t &x3, const int32_t &y3){
    return (!Intersect(x, y, x1, y1, x2, y2, x3, y3)) && (!Intersect(x, y, x2, y2, x1, y1, x3, y3)) &&(!Intersect(x, y, x3, y3, x1, y1, x2, y2));
}

#endif