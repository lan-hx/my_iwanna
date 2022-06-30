//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_ENTITYSET_ENTITYSET_H_
#define MY_IWANNA_SRC_ENTITYSET_ENTITYSET_H_

#include <vector>

#include "entity/Entity.h"
#include "entity/Player.h"

class EntitySet {
 public:
  explicit EntitySet(std::vector<Entity *> &&entities) : entities_(std::move(entities)) {}
  explicit EntitySet(std::vector<Entity *> &entities) : entities_(std::move(entities)) {}
  std::vector<Entity *> GetEntitySet() const;
  void Destroy() {
    for (auto entity_ptr : entities_) {
      delete entity_ptr;
    }
  }
  Player *GetPlayer() {
    if (entities_.empty()) {
      return nullptr;
    }
    return reinterpret_cast<Player *>(entities_[0]);
  }

 private:
  std::vector<Entity *> entities_;
};

#endif  // MY_IWANNA_SRC_ENTITYSET_ENTITYSET_H_
