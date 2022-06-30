//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_HOTAREA_HOTAREA_H_
#define MY_IWANNA_SRC_HOTAREA_HOTAREA_H_

#include <cstdint>
#include <utility>
#include <vector>

#include "include/common/common.h"

class HotArea {
 public:
  explicit HotArea() { type_ = invalid_hotarea_type; }
  int32_t Load(const char *file);
  enum HotAreaType { invalid_hotarea_type = -1, rectangular, triangular, point_set };

 private:
  HotAreaType type_;
  int32_t point_num_;
  std::vector<std::pair<int32_t, int32_t> > coordinates_;
};

#endif  // MY_IWANNA_SRC_HOTAREA_HOTAREA_H_
