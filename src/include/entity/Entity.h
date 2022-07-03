//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_ENTITY_ENTITY_H_
#define MY_IWANNA_SRC_ENTITY_ENTITY_H_

#include <cstdint>
#include <istream>
#include <string>

#include "common/common.h"
#include "hotarea/HotArea.h"

class Entity {
 public:
  explicit Entity(EntityTypeId type);
  ~Entity();
  inline int32_t GetX() const { return x_; }
  inline int32_t GetY() const { return y_; }
  void SetPos(const int32_t &x, const int32_t &y) { x_ = x, y_ = y; }
  inline void MoveByX(const int32_t &dx) { x_ += dx; }
  inline void MoveByY(const int32_t &dy) { y_ += dy; }
  inline void MoveTo(const int32_t &x, const int32_t &y) { x_ = x, y_ = y; }
  int32_t Load(const char *);
  inline bool IsHidden() const { return hidden_ != 0; }
  const char *GetCurPic() const { return state_pics_[cur_state_].c_str(); }
  int32_t GetCurState() const { return cur_state_; }
  int32_t GetDisplayPriority() const { return display_priority_; }
  inline const HotArea &GetHotArea() const { return hot_area_; }
  inline EntityTypeId GetType() const { return type_; }
  inline int32_t GetRefreshRate() const { return refresh_rate_; }
  inline DrawType GetDrawType() const { return draw_type_; }
  inline int32_t GetWidth() const { return width_; }
  inline int32_t GetHeight() const { return height_; }
  void SetHidden(bool hidden) { hidden_ = hidden ? 1 : 0; }
  inline void SetCurState(const int32_t &state) { cur_state_ = state; }
  inline void SetDisplayPriority(const int32_t &priority) { display_priority_ = priority; }
  inline void SetHotArea(const HotArea &ha) { hot_area_ = ha; }
  inline void SetType(const EntityTypeId &type) { type_ = type; }
  inline void SetRefreshRate(const int32_t refresh_rate) { refresh_rate_ = refresh_rate; }
  inline void SetDrawType(const DrawType &draw_type) { draw_type_ = draw_type; }
  inline void SetWidth(const int32_t &w) { width_ = w; }
  inline void SetHeight(const int32_t &h) { height_ = h; }
  inline void SetStateNum(const int32_t &num) { state_num_ = num; }
  inline void AddStatePic(char *pic) { ++state_num_, state_pics_.emplace_back(pic); }

  int32_t SerializeTo(char *str);

  friend int Collide(const Entity &en1, const Entity &en2);
  friend std::istream &operator>>(std::istream &i, Entity &entity);

  //  private:
  // const char *res_;  // picture of entity
  int32_t entity_id_;
  EntityTypeId type_;
  int32_t x_, y_;
  HotArea hot_area_;
  int32_t hidden_;
  int32_t display_priority_;
  int32_t state_num_;
  std::vector<std::string> state_pics_;
  int32_t cur_state_;
  int32_t refresh_rate_;
  int32_t width_;
  int32_t height_;
  DrawType draw_type_;
  bool can_move_;
  static int32_t entity_id_cnt;
};

std::istream &operator>>(std::istream &i, Entity &entity);

#endif  // MY_IWANNA_SRC_ENTITY_ENTITY_H_
