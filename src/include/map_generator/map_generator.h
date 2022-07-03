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
  HotArea pha;
  HotArea bha;
  player.SetPos(0, 500);
  block.SetPos(0, 524);
  player.SetWidth(24);
  player.SetHeight(24);
  block.SetWidth(240);
  block.SetHeight(24);
  pha.SetType(rectangular);
  pha.SetPointNum(2);
  pha.AddPoint(0, 0);
  pha.AddPoint(24, 24);
  bha.SetType(rectangular);
  bha.SetPointNum(2);
  bha.AddPoint(0, 0);
  bha.AddPoint(240, 24);
  player.SetHotArea(pha);
  block.SetHotArea(bha);
  player.SetHidden(false);
  block.SetHidden(false);
  player.SetDisplayPriority(0);
  block.SetDisplayPriority(1);
  player.SetRefreshRate(1);
  block.SetRefreshRate(1);
  player.SetStateNum(0);
  player.AddStatePic(":/hero/eastIdle.gif");
  player.SetCurState(0);
  block.SetStateNum(0);
  block.AddStatePic(":/platforms/platform1.png");
  block.SetCurState(0);
  player.SetDrawType(tiled);
  block.SetDrawType(tiled);
  int size = 0;
  sprintf(s, "%8d", -1);
  size += 8;
  sprintf(s + size, "%8d", 2);
  size += 8;
  size += player.SerializeTo(s + size);
  size += block.SerializeTo(s + size);
  sprintf(s + size, "%8d", 5);
  size += 8;
  sprintf(s + size, " a.png");
  size += 6;
  sprintf(s + size, "%8d", 30);
  size += 8;
  FILE *fp = fopen("D:/my_iwanna/about/test_map4.map", "w");
  fwrite(s, 1, size, fp);
  fclose(fp);
}

#endif