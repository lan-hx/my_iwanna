//
// Created by lan on 2022/6/29.
//

#ifndef MY_IWANNA_SRC_ENTITY_PORTAL_H_
#define MY_IWANNA_SRC_ENTITY_PORTAL_H_

#include "entity/Entity.h"

class Portal : public Entity {
 public:
  explicit Portal() : Entity(portal) {}
  inline const std::string GetMap() { return map_; }
  inline bool Success() { return (success_ != 0); }
  inline void SetSuccess(const bool &success) { success_ = static_cast<int32_t>(success); }
  inline void SetMap(const char *file_name) { map_ = file_name; }
  int32_t SerializeTo(char *str);

  friend std::istream &operator>>(std::istream &i, Portal &p);

 private:
  int32_t success_;
  std::string map_;
};

std::istream &operator>>(std::istream &i, Portal &p);

#endif  // MY_IWANNA_SRC_ENTITY_PORTAL_H_
