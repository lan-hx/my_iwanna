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
  HotArea(const HotArea &) = default;
  inline HotArea &operator=(const HotArea &ha) = default;
  HotAreaType GetType() const;
  int32_t GetX(const size_t &index) const;
  int32_t GetY(const size_t &index) const;
  int32_t GetPointNum() const;
  inline void SetType(const HotAreaType &type) { type_ = type; }
  inline void SetPointNum(const int32_t &num) { point_num_ = num; }
  inline void AddPoint(const int32_t &x, const int32_t &y) { coordinates_.emplace_back(std::make_pair(x, y)); }

  int32_t SerializeTo(char *str);

  friend std::istream &operator>>(std::istream &i, HotArea &h);

 private:
  HotAreaType type_;
  int32_t point_num_;
  std::vector<std::pair<int32_t, int32_t> > coordinates_;
};

std::istream &operator>>(std::istream &i, HotArea &h);

#endif  // MY_IWANNA_SRC_HOTAREA_HOTAREA_H_
