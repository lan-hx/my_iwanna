//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_ENTITY_ENTITY_H_
#define MY_IWANNA_SRC_ENTITY_ENTITY_H_

#include <cstdint>
#include <string>

#include "include/common/common.h"
#include "include/hotarea/HotArea.h"

class Entity {
 public:
  // explicit Entity() = default;
  explicit Entity(const char *file);
  ~Entity();
  inline int32_t GetX() const { return x_; }
  inline int32_t GetY() const { return y_; }
  void SetPos(const int32_t &x, const int32_t &y);
  void MoveX(const int32_t &dx);
  void MoveY(const int32_t &dy);
  inline bool IsHidden() const { return hidden_ != 0; }
  void SetHidden(bool);
  const char *GetCurPic() const;
  int32_t GetCurState() const;
  int32_t GetDisplayPriority() const;
  int32_t Load(const char *);
  const HotArea &GetHotArea() const;
  EntityTypeId GetType() const;

  bool friend Collide(const Entity &en1, const Entity &en2);

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

#endif  // MY_IWANNA_SRC_ENTITY_ENTITY_H_
