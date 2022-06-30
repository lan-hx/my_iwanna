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
  int32_t GetX() const;
  int32_t GetY() const;
  void SetPos(int, int);
  bool IsHidden() const;
  void SetHidden(bool);
  const char *GetCurPic() const;
  int32_t GetCurState() const;
  int32_t GetDisplayPriority() const;
  int32_t Load(const char *);

  bool friend Collide(Entity &en1, Entity &en2);

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
