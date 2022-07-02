//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_HOTAREA_HOTAREA_H_
#define MY_IWANNA_SRC_HOTAREA_HOTAREA_H_

#include <cstdint>
#include <istream>
#include <utility>
#include <vector>

#include "include/common/common.h"

class HotArea {
 public:
  explicit HotArea() { type_ = invalid_hotarea_type; }
  HotAreaType GetType() const;
  int32_t GetX(const size_t &index) const;
  int32_t GetY(const size_t &index) const;
  int32_t GetPointNum() const;

  friend std::istream &operator>>(std::istream &i, HotArea &h);

 private:
  HotAreaType type_;
  int32_t point_num_;
  std::vector<std::pair<int32_t, int32_t> > coordinates_;
};

std::istream &operator>>(std::istream &i, HotArea &h);

#endif  // MY_IWANNA_SRC_HOTAREA_HOTAREA_H_
