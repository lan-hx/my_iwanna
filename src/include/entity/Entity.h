//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_ENTITY_ENTITY_H_
#define MY_IWANNA_SRC_ENTITY_ENTITY_H_

#include <cstdint>
#include <istream>
#include <string>

#include "include/common/common.h"
#include "include/hotarea/HotArea.h"

class Entity {
 public:
  explicit Entity(EntityTypeId type);
  ~Entity();
  inline int32_t GetX() const { return x_; }
  inline int32_t GetY() const { return y_; }
  void SetPos(const int32_t &x, const int32_t &y);
  inline void MoveX(const int32_t &dx) { x_ += dx; }
  inline void MoveY(const int32_t &dy) { y_ += dy; }
  inline bool IsHidden() const { return hidden_ != 0; }
  void SetHidden(bool hidden) { hidden_ = hidden ? 1 : 0; }
  const char *GetCurPic() const;
  int32_t GetCurState() const;
  int32_t GetDisplayPriority() const;
  int32_t Load(const char *);
  inline const HotArea &GetHotArea() const { return hot_area_; }
  inline EntityTypeId GetType() const { return type_; }
  inline void SetType(const EntityTypeId &type) { type_ = type; }
  inline DrawType GetDrawType() const;
  inline int32_t GetWidth() const;
  inline int32_t GetHeight() const;

  friend bool Collide(const Entity &en1, const Entity &en2);
  friend std::istream &operator>>(std::istream &i, Entity &entity);

 private:
  // const char *res_;  // picture of entity
  int32_t entity_id_;
  EntityTypeId type_;
  int32_t x_, y_;
  HotArea hot_area_;
  int32_t hidden_;
  int32_t display_priority_;
  int32_t state_num_;
  std::vector<char *> state_pics_;
  int32_t cur_state_;
  int32_t refresh_rate_;
  bool can_move_;
};

std::istream &operator>>(std::istream &i, Entity &entity);

#endif  // MY_IWANNA_SRC_ENTITY_ENTITY_H_
