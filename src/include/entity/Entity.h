//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_ENTITY_ENTITY_H_
#define MY_IWANNA_SRC_ENTITY_ENTITY_H_

#include "hotarea/HotArea.h"

class Entity {
 public:
  explicit Entity() = default;
  HotArea hot_area_;
  int GetX() const;
  int GetY() const;
  void SetPos(int, int);
  bool IsHidden() const;
  void SetHidden(bool);
  enum TypeId { player, barrier, trap, portal };
  bool friend Collide(Entity &en1, Entity &en2);

 private:
  const char *res_;  // picture of entity
  int x_, y_;
  bool hidden_;
  TypeId type_;
  bool can_move_;
};

#endif  // MY_IWANNA_SRC_ENTITY_ENTITY_H_
