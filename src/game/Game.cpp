//
// Created by lan on 2022/7/4.
//

#include "game/Game.h"

#include <cctype>
#include <cmath>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <exception>
#include <fstream>
#include <unordered_set>
#include <vector>

#include "common/common.h"
#include "entity/Barrier.h"
#include "entity/Player.h"
#include "entity/Portal.h"
#include "entity/Resurrection.h"
#include "entity/Trap.h"
#include "hotarea/HotArea.h"

std::vector<Entity *> Game::GetEntitySet() const { return entities_->GetEntitySet(); }

Game::Game() {
  key_command_map_[Qt::Key_Left] = "Left";
  key_command_map_[Qt::Key_Right] = "Right";
  key_command_map_[Qt::Key_Shift] = "Jump";
  key_command_map_[Qt::Key_Z] = "Shoot";
  key_command_map_[Qt::Key_A] = "Left";
  key_command_map_[Qt::Key_D] = "Right";
  Init();
}

void Game::Init() {
  command_state_["Left"] = 0;
  command_state_["Right"] = 0;
  command_state_["Jump"] = 0;
  command_state_["Shoot"] = 0;
}

const char *Game::GetDebugOutput() {
  static std::string output;
  output.clear();
  Player *player = entities_->GetPlayer();
  output = "x:" + std::to_string(player->GetX()) + " y:" + std::to_string(player->GetY());
  return output.c_str();
}

void Game::Die() {
  if (dead_) {
    return;
  }
  dead_ = true;
  ++death_cnt_;
}

void Game::Save(const int32_t &resurrection_index) {
  // to be implemented
  char s[10000];
  int size = 0;
  sprintf(s + size, "%8d", death_cnt_);
  size += 8;
  sprintf(s + size, "%8d", step_cnt_);
  size += 8;
  sprintf(s + size, "%8d", resurrection_index);
  size += 8;
  size += entities_->SerializeTo(s + size);
  sprintf(s + size, "%8d", static_cast<int32_t>(background_pic_.length()));
  size += 8;
  if (background_pic_.length() > 0) {
    sprintf(s + size, " %s", background_pic_.c_str());
    size += static_cast<int32_t>(background_pic_.length()) + 1;
  }
  sprintf(s + size, "%8d", frame_rate_);
  size += 8;
  sprintf(s + size, "%8d", static_cast<int32_t>(left_map_.length()));
  size += 8;
  if (left_map_.length() > 0) {
    sprintf(s + size, " %s", left_map_.c_str());
    size += static_cast<int32_t>(left_map_.length()) + 1;
  }
  sprintf(s + size, "%8d", static_cast<int32_t>(right_map_.length()));
  size += 8;
  if (right_map_.length() > 0) {
    sprintf(s + size, " %s", right_map_.c_str());
    size += static_cast<int32_t>(right_map_.length()) + 1;
  }
  sprintf(s + size, "%8d", static_cast<int32_t>(up_map_.length()));
  size += 8;
  if (up_map_.length() > 0) {
    sprintf(s + size, " %s", up_map_.c_str());
    size += static_cast<int32_t>(up_map_.length()) + 1;
  }
  sprintf(s + size, "%8d", static_cast<int32_t>(down_map_.length()));
  size += 8;
  if (down_map_.length() > 0) {
    sprintf(s + size, " %s", down_map_.c_str());
    size += static_cast<int32_t>(down_map_.length()) + 1;
  }
  FILE *fp = fopen(cur_map_.c_str(), "w");
  fwrite(s, 1, size, fp);
  fclose(fp);
}

void Game::Load(const char *file_name) {
  if (strcmp(file_name, "") == 0) {
    in_game_ = false;
    emit LoadedCallBack(1);
  }
  std::ifstream ifs(file_name);
  if (!ifs.is_open()) {
    in_game_ = false;
    emit LoadedCallBack(1);
  }
  cur_map_ = file_name;
  int32_t entity_num;
  int32_t entity_size;
  EntityTypeId entity_type;
  std::vector<Entity *> entity_vec;
  std::vector<Entity *> player_vec;
  std::vector<Entity *> barrier_vec;
  std::vector<Entity *> trap_vec;
  std::vector<Entity *> portal_vec;
  std::vector<Entity *> resurrection_vec;
  int32_t background_len;
  int32_t left_map_len;
  int32_t right_map_len;
  int32_t up_map_len;
  int32_t down_map_len;
  dead_ = false;
  death_cnt_ = 0;
  step_cnt_ = 0LL;
  ifs >> death_cnt_ >> step_cnt_;
  ifs >> cur_resurrection_;
  ifs >> entity_num;
  for (int i = 0; i < entity_num; ++i) {
    ifs >> entity_size >> entity_type;
    Entity *e = nullptr;
    switch (entity_type) {
      case EntityTypeId::player:
        assert((player_vec.empty()) && ("Multiple Player Info"));
        e = player_vec.emplace_back(new Player());
        ifs >> *static_cast<Player *>(e);
        break;
      case EntityTypeId::barrier:
        e = barrier_vec.emplace_back(new Barrier());
        ifs >> *static_cast<Barrier *>(e);
        break;
      case EntityTypeId::trap:
        e = trap_vec.emplace_back(new Trap());
        ifs >> *static_cast<Trap *>(e);
        break;
      case EntityTypeId::portal:
        e = portal_vec.emplace_back(new Portal());
        ifs >> *static_cast<Portal *>(e);
        break;
      case EntityTypeId::resurrection:
        e = resurrection_vec.emplace_back(new Resurrection());
        ifs >> *static_cast<Resurrection *>(e);
        break;
      case EntityTypeId::invalid_type:
        assert(true && ("Invalid Entity"));
        break;
      default:;
    }
  }
  // entities_ = new EntitySet(std::move(entity_vec));
  entities_ = new EntitySet(std::move(player_vec), std::move(barrier_vec), std::move(trap_vec), std::move(portal_vec),
                            std::move(resurrection_vec));
  ifs >> background_len;
  if (background_len > 0) {
    ifs >> background_pic_;
    assert((static_cast<int32_t>(background_pic_.length()) == background_len) && ("background picture path error"));
  }
  ifs >> frame_rate_;
  ifs >> left_map_len;
  if (left_map_len > 0) {
    ifs >> left_map_;
    assert((static_cast<int32_t>(left_map_.length()) == left_map_len) && ("path error"));
  }
  ifs >> right_map_len;
  if (right_map_len > 0) {
    ifs >> right_map_;
    assert((static_cast<int32_t>(right_map_.length()) == right_map_len) && ("path error"));
  }
  ifs >> up_map_len;
  if (up_map_len > 0) {
    ifs >> up_map_;
    assert((static_cast<int32_t>(up_map_.length()) == up_map_len) && ("path error"));
  }
  ifs >> down_map_len;
  if (down_map_len > 0) {
    ifs >> down_map_;
    assert((static_cast<int32_t>(down_map_.length()) == down_map_len) && ("path error"));
  }
  Init();
  if (cur_resurrection_ >= 0) {
    // to be implemented
    entities_->GetPlayer()->MoveTo(entities_->GetResurrection(cur_resurrection_)->GetX(),
                                   entities_->GetResurrection(cur_resurrection_)->GetY());
  }
  if (ifs.eof()) {
    ifs.close();
    in_game_ = true;
    emit LoadedCallBack(0);
  } else {
    ifs.close();
    in_game_ = false;
    emit LoadedCallBack(1);
  }
}

void Game::CloseMap() {
  dead_ = false;
  death_cnt_ = 0;
  step_cnt_ = 0LL;
  cur_map_.clear();
  entities_->Destroy();
  delete entities_;
  entities_ = nullptr;
  background_pic_.clear();
  left_map_.clear();
  right_map_.clear();
  up_map_.clear();
  down_map_.clear();
  in_game_ = false;
  frame_rate_ = 60;
}

void Game::ChangeMap(const char *file_name) {
  Player *cur_player = new Player(*(entities_->GetPlayer()));
  dead_ = false;
  entities_->Destroy();
  delete entities_;
  entities_ = nullptr;
  background_pic_.clear();
  left_map_.clear();
  right_map_.clear();
  up_map_.clear();
  down_map_.clear();
  if (strcmp(file_name, "") == 0) {
    in_game_ = false;
    emit LoadedCallBack(1);
  }
  std::ifstream ifs(file_name);
  if (!ifs.is_open()) {
    in_game_ = false;
    emit LoadedCallBack(1);
  }
  int32_t temp;
  int32_t entity_num;
  int32_t entity_size;
  EntityTypeId entity_type;
  std::vector<Entity *> entity_vec;
  std::vector<Entity *> player_vec;
  std::vector<Entity *> barrier_vec;
  std::vector<Entity *> trap_vec;
  std::vector<Entity *> portal_vec;
  std::vector<Entity *> resurrection_vec;
  int32_t background_len;
  int32_t left_map_len;
  int32_t right_map_len;
  int32_t up_map_len;
  int32_t down_map_len;
  ifs >> temp >> temp;
  ifs >> cur_resurrection_;
  ifs >> entity_num;
  for (int i = 0; i < entity_num; ++i) {
    ifs >> entity_size >> entity_type;
    Entity *e = nullptr;
    switch (entity_type) {
      case EntityTypeId::player:
        assert((player_vec.empty()) && ("Multiple Player Info"));
        e = player_vec.emplace_back(new Player());
        ifs >> *static_cast<Player *>(e);
        break;
      case EntityTypeId::barrier:
        e = barrier_vec.emplace_back(new Barrier());
        ifs >> *static_cast<Barrier *>(e);
        break;
      case EntityTypeId::trap:
        e = trap_vec.emplace_back(new Trap());
        ifs >> *static_cast<Trap *>(e);
        break;
      case EntityTypeId::portal:
        e = portal_vec.emplace_back(new Portal());
        ifs >> *static_cast<Portal *>(e);
        break;
      case EntityTypeId::resurrection:
        e = resurrection_vec.emplace_back(new Resurrection());
        ifs >> *static_cast<Resurrection *>(e);
      case EntityTypeId::invalid_type:
        assert(true && ("Invalid Entity"));
        break;
      default:;
    }
  }
  // entities_ = new EntitySet(std::move(entity_vec));
  entities_ = new EntitySet(std::move(player_vec), std::move(barrier_vec), std::move(trap_vec), std::move(portal_vec),
                            std::move(resurrection_vec));
  int32_t default_x = entities_->GetPlayer()->GetX();
  int32_t default_y = entities_->GetPlayer()->GetY();
  *(entities_->GetPlayer()) = *cur_player;
  delete cur_player;
  entities_->GetPlayer()->MoveTo(default_x, default_y);
  ifs >> background_len;
  if (background_len > 0) {
    ifs >> background_pic_;
    assert((static_cast<int32_t>(background_pic_.length()) == background_len) && ("background picture path error"));
  }
  ifs >> frame_rate_;
  ifs >> left_map_len;
  if (left_map_len > 0) {
    ifs >> left_map_;
    assert((static_cast<int32_t>(left_map_.length()) == left_map_len) && ("path error"));
  }
  ifs >> right_map_len;
  if (right_map_len > 0) {
    ifs >> right_map_;
    assert((static_cast<int32_t>(right_map_.length()) == right_map_len) && ("path error"));
  }
  ifs >> up_map_len;
  if (up_map_len > 0) {
    ifs >> up_map_;
    assert((static_cast<int32_t>(up_map_.length()) == up_map_len) && ("path error"));
  }
  ifs >> down_map_len;
  if (down_map_len > 0) {
    ifs >> down_map_;
    assert((static_cast<int32_t>(down_map_.length()) == down_map_len) && ("path error"));
  }
  if (cur_resurrection_ >= 0) {
    entities_->GetPlayer()->MoveTo(entities_->GetResurrection(cur_resurrection_)->GetX(),
                                   entities_->GetResurrection(cur_resurrection_)->GetY());
  }
  if (ifs.eof()) {
    ifs.close();
    in_game_ = true;
    emit LoadedCallBack(0);
  } else {
    ifs.close();
    in_game_ = false;
    emit LoadedCallBack(1);
  }
}

void Game::Restart() {
  if (!dead_) {
    Die();
  }
  int32_t death_cnt = death_cnt_;
  int32_t step_cnt = step_cnt_;
  Load(cur_map_.c_str());
  death_cnt_ = death_cnt;
  step_cnt_ = step_cnt;
}

void Game::Event(const Qt::Key &key, bool is_pressed) {
  std::unordered_map<Qt::Key, std::string>::iterator find_res = key_command_map_.find(key);
  if (find_res != key_command_map_.end()) {
    if ((*find_res).second == "Jump") {
      if (is_pressed) {
        if ((command_state_["Jump"] & 1) == 0) {
          command_state_["Jump"] |= 4;
        }
      } else {
        if ((command_state_["Jump"] & 1) == 1) {
          command_state_["Jump"] |= 2;
        }
      }
    }
    if (is_pressed) {
      command_state_[(*find_res).second] |= 1;
    } else {
      command_state_[(*find_res).second] &= 0xFFFFFFFE;
    }
  }
}

void Game::Step() {
  // for all tracks
  // if activated
  //     move the corresponding entity

  // update vx
  // update vy

  // dx = vx
  // dy = vy

  // while (dx || dy)
  //     if (abs((dx - 1) * vy - vx * dy) < abs(dx * vy - vx * (dy - 1)))
  //         move x by 1 pixel
  //         decrease dx
  //         check death
  //         check track activations
  //         if collide with barrier
  //             rollback x
  //             dx = 0
  //     else
  //         similar
  ++step_cnt_;
  Player *player = entities_->GetPlayer();
  for (auto entity : entities_->GetEntitySet()) {
    switch (entity->GetType()) {
      case barrier:
      case trap:
      case portal:
        entity->SetCurState((entity->GetCurState() + 1) % entity->GetStateNum());
        break;
      default:
        break;
    }
  }
  std::unordered_set<Entity *> entity_set;
  int32_t left = command_state_["Left"];
  int32_t right = command_state_["Right"];
  int32_t jump = command_state_["Jump"];
  bool interrupt_jump = false;
  bool break_jump = false;
  bool land = false;
  bool can_jump;
  //   bool shoot = command_state_["Shoot"];
  if ((left != 0) || (right != 0)) {
    if (left != 0) {
      player->PrepareLeft();
    }
    if (right != 0) {
      player->PrepareRight();
    }
  } else {
    player->HorizontalIdle();
  }
  if ((jump & 4) != 0) {
    player->BreakJump();
  }
  can_jump = player->CanJump();
  if ((jump & 1) != 0 || (jump & 2) != 0) {
    if (can_jump) {
      player->PrepareJump();
    }
  }
  if ((jump & 1) == 0) {
    break_jump = true;
  }
  int32_t vx = player->GetVx();
  int32_t vy = player->GetVy();
  if (vy < 6) {
    ++vy;
    player->SetVy(vy);
  }
  int32_t dx = vx;
  int32_t dy = vy;
  player->MoveTo(player->GetX(), player->GetY() + dy);
  for (auto entity : entities_->GetBarrierSet()) {
    if (!entity->IsHidden()) {
      switch (Collide(*player, *entity)) {
        case 1:
          entity_set.emplace(entity);
          if (vy > 0) {
            land = true;
          }
          if (vy < 0) {
            interrupt_jump = true;
          }
          break;
        default:
          break;
      }
    }
  }
  while (!entity_set.empty()) {
    if (dy == 0) {
      Die();
    }
    if (vy > 0) {
      player->MoveByY(-1);
      --dy;
    } else {
      player->MoveByY(1);
      ++dy;
    }
    for (auto entity : entity_set) {
      switch (Collide(*player, *entity)) {
        case 0:
          entity_set.erase(entity);
          break;
        default:
          break;
      }
    }
  }
  player->MoveTo(player->GetX() + dx, player->GetY());
  for (auto entity : entities_->GetBarrierSet()) {
    if (!entity->IsHidden()) {
      switch (Collide(*player, *entity)) {
        case 1:
          entity_set.emplace(entity);
          break;
        default:
          break;
      }
    }
  }
  while (!entity_set.empty()) {
    if (dx == 0) {
      Die();
    }
    if (vx > 0) {
      player->MoveByX(-1);
      --dx;
    } else {
      player->MoveByX(1);
      ++dx;
    }
    for (auto entity : entity_set) {
      switch (Collide(*player, *entity)) {
        case 0:
          entity_set.erase(entity);
          break;
        default:
          break;
      }
    }
  }
  if (can_jump && interrupt_jump) {
    player->InteruptJump();
  }
  if (break_jump) {
    player->BreakJump();
  }
  if (land) {
    player->SetYState(landed);
  } else {
    if (jump == 0) {
      if (player->GetYState() == on_ground) {
        player->SetYState(drifting);
      }
    }
  }

  switch (player->GetYState()) {
    case on_ground:
    case landed:
      if (player->GetXState() == idle) {
        if (player->GetFacing() == 1) {
          player->SetCurState(1);
        } else {
          player->SetCurState(5);
        }
      } else {
        if (player->GetFacing() == 1) {
          player->SetCurState(3);
        } else {
          player->SetCurState(7);
        }
      }
      break;
    default:
      if (player->GetVy() < 0) {
        if (player->GetFacing() == 1) {
          player->SetCurState(2);
        } else {
          player->SetCurState(6);
        }
      } else {
        if (player->GetFacing() == 1) {
          player->SetCurState(0);
        } else {
          player->SetCurState(4);
        }
      }
  }

  for (auto entity : entities_->GetTrapSet()) {
    if (!entity->IsHidden()) {
      if (Collide(*player, *entity) != 0) {
        Die();
      }
    }
  }

  for (auto entity : entities_->GetPortalSet()) {
    if (!entity->IsHidden()) {
      if (Collide(*player, *entity) != 0) {
        ChangeMap(GeneratePath(cur_map_, (reinterpret_cast<Portal *>(entity))->GetMap()).c_str());
        player = entities_->GetPlayer();
      }
    }
  }

  for (int32_t i = 0; i < static_cast<int32_t>(entities_->GetResurrectionSet().size()); ++i) {
    if (!entities_->GetResurrection(i)->IsHidden()) {
      if (Collide(*player, *(entities_->GetResurrection(i))) != 0) {
        Save(i);
        for (auto resur : entities_->GetResurrectionSet()) {
          resur->SetCurState(0);
        }
        entities_->GetResurrection(i)->SetCurState(1);
        cur_resurrection_ = i;
      }
    }
  }

  command_state_["Jump"] = command_state_["Jump"] & 1;

  int32_t cur_x = player->GetX();
  int32_t cur_y = player->GetY();
  if (cur_y < 0) {
    if (!up_map_.empty()) {
      ChangeMap(GeneratePath(cur_map_, up_map_).c_str());
      player = entities_->GetPlayer();
      player->MoveTo(cur_x, cur_y + 600);
    } else {
      player->MoveTo(cur_x, 0);
    }
  }
  if (cur_y >= 600) {
    if (!down_map_.empty()) {
      ChangeMap(GeneratePath(cur_map_, down_map_).c_str());
      player = entities_->GetPlayer();
      player->MoveTo(cur_x, cur_y - 600);
    } else {
      player->MoveTo(cur_x, 599);
    }
  }
  if (cur_x < 0) {
    if (!left_map_.empty()) {
      ChangeMap(GeneratePath(cur_map_, left_map_).c_str());
      player = entities_->GetPlayer();
      player->MoveTo(cur_x + 800, cur_y);
    } else {
      player->MoveTo(0, cur_y);
    }
  }
  if (cur_x >= 800) {
    if (!right_map_.empty()) {
      ChangeMap(GeneratePath(cur_map_, right_map_).c_str());
      player = entities_->GetPlayer();
      player->MoveTo(cur_x - 800, cur_y);
    } else {
      player->MoveTo(799, cur_y);
    }
  }
  if (IsDead()) {
    emit DieSignal();
  }
  emit StepCallBack();
  emit UpdateFrame();
  emit UpdateInfo(DeathCount(), PlayTime(), GetDebugOutput());
}

int32_t Collide(const Entity &en1, const Entity &en2) {
  const HotArea &ha1 = en1.GetHotArea();
  const HotArea &ha2 = en2.GetHotArea();
  if (en1.GetType() != player) {
    return 0;
  }
  int32_t minx = en1.GetX() + ha1.GetX(0);
  int32_t maxx = en1.GetX() + ha1.GetX(1);
  int32_t miny = en1.GetY() + ha1.GetY(0);
  int32_t maxy = en1.GetY() + ha1.GetY(1);
  int32_t ret = 0;
  switch (ha2.GetType()) {
    case rectangular:
      if ((maxx > en2.GetX() + ha2.GetX(0)) && (en2.GetX() + ha2.GetX(1) > minx) && (maxy > en2.GetY() + ha2.GetY(0)) &&
          (en2.GetY() + ha2.GetY(1) > miny)) {
        ret |= 1;
      }
      return ret;
    case triangular: {
      int32_t x1 = en2.GetX() + ha2.GetX(0);
      int32_t y1 = en2.GetY() + ha2.GetY(0);
      int32_t x2 = en2.GetX() + ha2.GetX(1);
      int32_t y2 = en2.GetY() + ha2.GetY(1);
      int32_t x3 = en2.GetX() + ha2.GetX(2);
      int32_t y3 = en2.GetY() + ha2.GetY(2);
      if ((x1 > minx) && (x1 < maxx) && (y1 > miny) && (y1 < maxy)) {
        return 1;
      }
      if ((x2 > minx) && (x2 < maxx) && (y2 > miny) && (y2 < maxy)) {
        return 1;
      }
      if ((x3 > minx) && (x3 < maxx) && (y3 > miny) && (y3 < maxy)) {
        return 1;
      }
      if (InTriangle(minx, miny, x1, y1, x2, y2, x3, y3)) {
        return 1;
      }
      if (InTriangle(minx, maxy, x1, y1, x2, y2, x3, y3)) {
        return 1;
      }
      if (InTriangle(maxx, miny, x1, y1, x2, y2, x3, y3)) {
        return 1;
      }
      if (InTriangle(maxx, maxy, x1, y1, x2, y2, x3, y3)) {
        return 1;
      }
      return 0;
    }
    case point_set:
      for (int i = 0; i < ha2.GetPointNum(); ++i) {
        int32_t x = en2.GetX() + ha2.GetX(i);
        int32_t y = en2.GetY() + ha2.GetY(i);
        if ((x >= minx) && (x <= maxx) && (y >= miny) && (y <= maxy)) {
          return 1;
        }
      }
      return 0;
    case invalid_hotarea_type:
      return 0;
    default:
      return 0;
  }
}
