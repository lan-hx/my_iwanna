//
// Created by lan on 2022/6/29.
//

#include "include/entityset/EntitySet.h"

void EntitySet::Destroy() {
  for (auto entity_ptr : entities_) {
    delete entity_ptr;
  }
  entities_.clear();
  player_set_.clear();
  barrier_set_.clear();
  trap_set_.clear();
  portal_set_.clear();
  resurrection_set_.clear();
}

int32_t EntitySet::SerializeTo(char *str) {
  int32_t size = 0;
  sprintf(str + size, "%8d", static_cast<int32_t>(entities_.size()));
  size += 8;
  for (auto entity : entities_) {
    size += entity->SerializeTo(str + size);
  }
  return size;
}

Resurrection *EntitySet::GetResurrection(const int32_t &index) {
  if ((index >= 0) && (index < static_cast<int32_t>(resurrection_set_.size()))) {
    return static_cast<Resurrection *>(resurrection_set_[index]);
  }
  return nullptr;
}