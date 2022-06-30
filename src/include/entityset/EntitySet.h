//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_ENTITYSET_ENTITYSET_H_
#define MY_IWANNA_SRC_ENTITYSET_ENTITYSET_H_

#include <vector>

#include "entity/Entity.h"

class EntitySet {
 public:
  explicit EntitySet(std::vector<Entity *> &&entities) : entities_(std::move(entities)) {}
  std::vector<Entity *> GetEntitySet() const;

 private:
  std::vector<Entity *> entities_;
};

#endif  // MY_IWANNA_SRC_ENTITYSET_ENTITYSET_H_
