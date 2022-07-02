//
// Created by lan on 2022/6/29.
//

#include "include/hotarea/HotArea.h"

HotAreaType HotArea::GetType() const { return type_; }

int32_t HotArea::GetX(const size_t &index) const { return coordinates_[index].first; }

int32_t HotArea::GetY(const size_t &index) const { return coordinates_[index].second; }

int32_t HotArea::GetPointNum() const { return point_num_; }

std::istream &operator>>(std::istream &i, HotArea &h) {
  int32_t type;
  int32_t x;
  int32_t y;
  i >> type;
  switch (type) {
    case 0:
      h.type_ = rectangular;
      h.point_num_ = 2;
      break;
    case 1:
      h.type_ = triangular;
      h.point_num_ = 3;
      break;
    case 2:
      h.type_ = point_set;
      i >> h.point_num_;
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
