//
// Created by lan on 2022/6/29.
//

#include "include/hotarea/HotArea.h"

int32_t HotArea::Load(const char *file) {
  int32_t size = 0;
  int32_t type;
  int32_t x;
  int32_t y;
  size += StringGetInt(file + size, type);
  switch (type) {
    case 0:
      type_ = rectangular;
      point_num_ = 2;
      break;
    case 1:
      type_ = triangular;
      point_num_ = 3;
      break;
    case 2:
      type_ = point_set;
      size += StringGetInt(file + size, point_num_);
      break;
    default:
      type_ = invalid_hotarea_type;
      point_num_ = 0;
      break;
  }
  for (int i = 0; i < point_num_; ++i) {
    size += StringGetInt(file + size, x);
    size += StringGetInt(file + size, y);
    coordinates_.emplace_back(std::make_pair(x, y));
  }
  return size;
}

HotAreaType HotArea::GetType()const{
    return type_;
}

int32_t HotArea::GetX(const size_t &index)const{
    return coordinates_[index].first;
}

int32_t HotArea::GetY(const size_t &index)const{
    return coordinates_[index].second;
}

int32_t HotArea::GetPointNum() const{
    return point_num_;
}