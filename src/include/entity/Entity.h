//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_ENTITY_ENTITY_H_
#define MY_IWANNA_SRC_ENTITY_ENTITY_H_

#include <cstdint>

#include "hotarea/HotArea.h"

class Entity {
 public:
  // explicit Entity() = default;
  explicit Entity(const char *);
  HotArea hot_area_;
  int GetX() const;
  int GetY() const;
  void SetPos(int, int);
  bool IsHidden() const;
  void SetHidden(bool);
  const char *GetCurPic() const;
  int GetCurState() const;
  enum TypeId { player, barrier, trap, portal };
  bool friend Collide(Entity &en1, Entity &en2);

 private:
  // const char *res_;  // picture of entity
  int32_t entity_id_;
  TypeId type_;
  int32_t x_, y_;
  bool hidden_;
  int32_t state_num_;
  const char **state_pics_;
  int32_t cur_state_;
  int32_t refresh_rate_;
  bool can_move_;
};

#endif  // MY_IWANNA_SRC_ENTITY_ENTITY_H_
