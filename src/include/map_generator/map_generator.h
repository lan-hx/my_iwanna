#ifndef MY_IWANNA_SRC_MAP_GENERATOR_H_
#define MY_IWANNA_SRC_MAP_GENERATOR_H_

#include <cstdio>

#include "entity/Barrier.h"
#include "entity/Entity.h"
#include "entity/Player.h"
#include "entity/Trap.h"
#include "entity/Portal.h"

void GenerateTestMap() {
  char s[10000];
  Player player;
  Barrier block;
  Barrier block2;
  Trap trap;
  Portal port;
  HotArea pha;
  HotArea bha;
  HotArea bha2;
  HotArea tha;
  HotArea ptha;
  player.SetPos(150, 250);
  player.SetWidth(25);
  player.SetHeight(21);
  pha.SetType(rectangular);
  pha.SetPointNum(2);
  pha.AddPoint(2, 0);
  pha.AddPoint(23, 21);
  player.SetHotArea(pha);
  player.SetHidden(false);
  player.SetDisplayPriority(0);
  player.SetRefreshRate(1);
  player.SetStateNum(0);
  player.AddStatePic(":/hero/eastFall.png");
  player.AddStatePic(":/hero/eastIdle.gif");
  player.AddStatePic(":/hero/eastJump.png");
  player.AddStatePic(":/hero/eastMoving.gif");
  player.AddStatePic(":/hero/westFall.png");
  player.AddStatePic(":/hero/westIdle.gif");
  player.AddStatePic(":/hero/westJump.png");
  player.AddStatePic(":/hero/westMoving.gif");
  player.SetCurState(0);
  player.SetDrawType(tiled);
  block.SetPos(100, 400);
  block.SetWidth(400);
  block.SetHeight(100);
  bha.SetType(rectangular);
  bha.SetPointNum(2);
  bha.AddPoint(0, 0);
  bha.AddPoint(400, 100);
  block.SetHotArea(bha);
  block.SetHidden(false);
  block.SetDisplayPriority(1);
  block.SetRefreshRate(1);
  block.SetStateNum(0);
  block.AddStatePic(":/platforms/platform1.png");
  block.SetCurState(0);
  block.SetDrawType(tiled);
  block2.SetPos(400, 280);
  block2.SetWidth(100);
  block2.SetHeight(300);
  bha2.SetType(rectangular);
  bha2.SetPointNum(2);
  bha2.AddPoint(0, 0);
  bha2.AddPoint(100, 300);
  block2.SetHotArea(bha2);
  block2.SetHidden(false);
  block2.SetDisplayPriority(1);
  block2.SetRefreshRate(1);
  block2.SetStateNum(0);
  block2.AddStatePic(":/platforms/platform1.png");
  block2.SetCurState(0);
  block2.SetDrawType(tiled);
  trap.SetPos(200, 372);
  trap.SetWidth(28);
  trap.SetHeight(28);
  tha.SetType(triangular);
  tha.SetPointNum(3);
  tha.AddPoint(14, 0);
  tha.AddPoint(0, 28);
  tha.AddPoint(28, 28);
  trap.SetHotArea(tha);
  trap.SetHidden(false);
  trap.SetDisplayPriority(2);
  trap.SetRefreshRate(1);
  trap.SetStateNum(0);
  trap.AddStatePic(":/platforms/trap1.gif");
  trap.SetCurState(0);
  trap.SetDrawType(scaled);
  port.SetPos(440, 230);
  port.SetWidth(30);
  port.SetHeight(30);
  ptha.SetType(rectangular);
  ptha.SetPointNum(2);
  ptha.AddPoint(0, 0);
  ptha.AddPoint(30, 30);
  port.SetHotArea(ptha);
  port.SetHidden(false);
  port.SetDisplayPriority(1);
  port.SetRefreshRate(1);
  port.SetStateNum(0);
  port.AddStatePic(":/platforms/door.png");
  port.SetCurState(0);
  port.SetDrawType(scaled);
  port.SetSuccess(false);
  port.SetMap("test_map10.map");
  int size = 0;
  sprintf(s + size, "%8d", 0);
  size += 8;
  sprintf(s + size, "%8d", 0);
  size += 8;
  sprintf(s + size, "%8d", -1);
  size += 8;
  sprintf(s + size, "%8d", 5);
  size += 8;
  size += player.SerializeTo(s + size);
  size += block.SerializeTo(s + size);
  size += block2.SerializeTo(s + size);
  size += trap.SerializeTo(s + size);
  size += port.SerializeTo(s + size);
  sprintf(s + size, "%8d", 0);
  size += 8;
  sprintf(s + size, "%8d", 40);
  size += 8;
  FILE *fp = fopen("D:/my_iwanna/about/test_map11.map", "w");
  sprintf(s + size, "%8d", 14);
  size += 8;
  sprintf(s + size, " test_map11.map");
  size += 15;
  sprintf(s + size, "%8d", 14);
  size += 8;
  sprintf(s + size, " test_map11.map");
  size += 15;
  sprintf(s + size, "%8d", 14);
  size += 8;
  sprintf(s + size, " test_map11.map");
  size += 15;
  sprintf(s + size, "%8d", 14);
  size += 8;
  sprintf(s + size, " test_map11.map");
  size += 15;
  fwrite(s, 1, size, fp);
  fclose(fp);
}

#endif