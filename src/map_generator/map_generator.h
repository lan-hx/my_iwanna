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
  block.SetPos(0, 524);
  player.SetPos(0, 500);
  pha.SetType(rectangular);
  pha.SetPointNum(2);
  pha.AddPoint(0, 0);
  pha.AddPoint(24, 24);
  bha.SetType(rectangular);
  bha.SetPointNum(2);
  bha.AddPoint(0, 0);
  bha.AddPoint(24, 24);
  player.SetHotArea(pha);
  block.SetHotArea(bha);
  int size = 0;
  sprintf(s, "%8d", -1);
  size += 8;
  sprintf(s + size, "%8d", 2);
  size += 8;
  size += player.SerializeTo(s + size);
  size += block.SerializeTo(s + size);
  sprintf(s + size, "%8d", 5);
  size += 8;
  sprintf(s + size, "   a.png");
  size += 8;
  sprintf(s + size, "%8d", 12);
  size += 8;
  FILE *fp = fopen("D:/my_iwanna/about/test_map3.map", "w");
  fwrite(s, 1, size, fp);
  fclose(fp);
}