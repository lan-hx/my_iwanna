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
  // explicit EntitySet(std::vector<Entity *> &&entities) : entities_(std::move(entities)) {}
  explicit EntitySet(std::vector<Entity *> &&player_set, std::vector<Entity *> &&barrier_set,
                     std::vector<Entity *> &&trap_set, std::vector<Entity *> &&portal_set)
      : player_set_(std::move(player_set)),
        barrier_set_(std::move(barrier_set)),
        trap_set_(std::move(trap_set)),
        portal_set_(std::move(portal_set)) {
    entities_.insert(entities_.end(), player_set_.begin(), player_set_.end());
    entities_.insert(entities_.end(), barrier_set_.begin(), barrier_set_.end());
    entities_.insert(entities_.end(), trap_set_.begin(), trap_set_.end());
    entities_.insert(entities_.end(), portal_set_.begin(), portal_set_.end());
  }
  inline std::vector<Entity *> GetEntitySet() const { return entities_; }
  inline std::vector<Entity *> GetBarrierSet() const { return barrier_set_; }
  inline std::vector<Entity *> GetTrapSet() const { return trap_set_; }
  inline std::vector<Entity *> GetPortalSet() const { return portal_set_; }
  inline Player *GetPlayer() { return player_set_.empty() ? nullptr : static_cast<Player *>(player_set_[0]); }
  void Destroy() {
    for (auto entity_ptr : entities_) {
      delete entity_ptr;
    }
  }

 private:
  std::vector<Entity *> entities_;
  std::vector<Entity *> player_set_;
  std::vector<Entity *> barrier_set_;
  std::vector<Entity *> trap_set_;
  std::vector<Entity *> portal_set_;
};

#endif  // MY_IWANNA_SRC_ENTITYSET_ENTITYSET_H_
