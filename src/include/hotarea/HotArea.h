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
  HotAreaType GetType() const;
  int32_t GetX(const size_t &index)const;
  int32_t GetY(const size_t &index)const;
  int32_t GetPointNum() const;

 private:
  HotAreaType type_;
  int32_t point_num_;
  std::vector<std::pair<int32_t, int32_t> > coordinates_;
};

#endif  // MY_IWANNA_SRC_HOTAREA_HOTAREA_H_
