//
// Created by lan on 2022/6/29.
//

#include "include/hotarea/HotArea.h"

#include <cassert>

HotAreaType HotArea::GetType() const { return type_; }

int32_t HotArea::GetX(const size_t &index) const { return coordinates_[index].first; }

int32_t HotArea::GetY(const size_t &index) const { return coordinates_[index].second; }

int32_t HotArea::GetPointNum() const { return point_num_; }

std::istream &operator>>(std::istream &i, HotArea &h) {
  int32_t type;
  int32_t x;
  int32_t y;
  i >> type;
  i >> h.point_num_;
  switch (type) {
    case 0:
      h.type_ = rectangular;
      assert((h.point_num_ == 2) && ("wrong rectangle type"));
      //      h.point_num_ = 2;
      break;
    case 1:
      h.type_ = triangular;
      assert((h.point_num_ == 3) && ("wrong triangle type"));
      //      h.point_num_ = 3;
      break;
    case 2:
      h.type_ = point_set;
      break;
    default:
      h.type_ = invalid_hotarea_type;
      h.point_num_ = 0;
  }
  for (int j = 0; j < h.point_num_; ++j) {
    i >> x >> y;
    h.coordinates_.emplace_back(x, y);
  }
  return i;
}

int32_t HotArea::SerializeTo(char *str) {
  int32_t size = 0;
  sprintf(str + size, "%8d", type_);
  size += 8;
  sprintf(str + size, "%8d", point_num_);
  size += 8;
  for (int i = 0; i < point_num_; ++i) {
    sprintf(str + size, "%8d", coordinates_[i].first);
    size += 8;
    sprintf(str + size, "%8d", coordinates_[i].second);
    size += 8;
  }
  return size;
}