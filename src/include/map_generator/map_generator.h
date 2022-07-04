#ifndef MY_IWANNA_SRC_MAP_GENERATOR_H_
#define MY_IWANNA_SRC_MAP_GENERATOR_H_

#include <cstdio>

#include "entity/Barrier.h"
#include "entity/Entity.h"
#include "entity/Player.h"

void GenerateTestMap() {
  char s[10000];
  Player player;
  Barrier block;
  Barrier block2;
  HotArea pha;
  HotArea bha;
  HotArea bha2;
  player.SetPos(150, 300);
  player.SetWidth(25);
  player.SetHeight(21);
  pha.SetType(rectangular);
  pha.SetPointNum(2);
  pha.AddPoint(0, 0);
  pha.AddPoint(25, 21);
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
  block.SetPos(100, 324);
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
  int size = 0;
  sprintf(s, "%8d", -1);
  size += 8;
  sprintf(s + size, "%8d", 3);
  size += 8;
  size += player.SerializeTo(s + size);
  size += block.SerializeTo(s + size);
  size += block2.SerializeTo(s + size);
  sprintf(s + size, "%8d", 5);
  size += 8;
  sprintf(s + size, " a.png");
  size += 6;
  sprintf(s + size, "%8d", 40);
  size += 8;
  FILE *fp = fopen("D:/my_iwanna/about/test_map7.map", "w");
  fwrite(s, 1, size, fp);
  fclose(fp);
}

#endif