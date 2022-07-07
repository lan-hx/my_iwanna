//
// Created by lan on 2022/7/2.
//
#include <gtest/gtest.h>

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
#include "entity/Trap.h"
#include "game/Game.h"
#include "hotarea/HotArea.h"

//TEST(Loadtest, Gametest) {
//  Game game;
//  game.Reset();
//  game.Load("test_map4.map");
//  for (auto entity : game.GetEntitySet()) {
//    EXPECT_EQ(0, entity->type_);
//    EXPECT_EQ(0, entity->x_);
//    EXPECT_EQ(500, entity->y_);
//    EXPECT_EQ(0, entity->hidden_);
//    EXPECT_EQ(0, entity->display_priority_);
//    EXPECT_EQ(1, entity->state_num_);
//    EXPECT_EQ(1, entity->refresh_rate_);
//    EXPECT_EQ(24, entity->width_);
//    EXPECT_EQ(24, entity->height_);
//    EXPECT_EQ(1, entity->draw_type_);
//    EXPECT_EQ(0, entity->entity_id_cnt);
//    break;
//  }
//  game.CloseMap();
//}
TEST(Jumptest, Gametest){
  Game game;
  game.Load("test_map9.map");
  Qt::Key key = Qt::Key_Shift;
  Player* player  = reinterpret_cast<Player*>((game.GetEntitySet())[0]);
  game.Event(key,1);
  game.Step();
  for(int i = 1;i<8;i++){
    EXPECT_EQ(-5,player->GetVy());
    game.Step();
  }
  game.Event(key,0);
  for(int i = 1;i<6;i++){
    EXPECT_EQ(-5+i,player->GetVy());
    game.Step();
  }
  EXPECT_EQ(1,player->GetVy());
  game.Event(key,1);
  EXPECT_EQ(1,player->GetVy());
  game.CloseMap();
}
TEST(Colitest, Gametest){
  Game game;
  game.Load("test_map9.map");
  Qt::Key key = Qt::Key_Shift;
  Player* player  = reinterpret_cast<Player*>((game.GetEntitySet())[0]);
  for(int i = 1;i<56;i++){
    game.Step();
  }
  game.Event(key,1);
  game.Step();
  game.Event(key,0);
  for(int i = 1;i<7;i++){
    game.Step();
  }
  EXPECT_EQ(0,player->GetVy());
  game.CloseMap();
}
int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}