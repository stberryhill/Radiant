/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef _INTERNAL_RADIANT2D_H
#define _INTERNAL_RADIANT2D_H

#include "Radiant2D.h"
#include "RadiantTextureAtlas.h"

struct {
  TileID tileId;
  float position[2];
  float scale[2];
} Sprite;

struct {
  float tileSize;
  float position[2];
  float scale[2];
  TileID *ids;
  size_t rows;
  size_t columns;
  TileSet *tileSet;
} TileMap;

struct {
  TileID *ids;
  uint32_t numIds;
  TextureAtlas *atlas;
} TileSet;

#endif
