/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef _RADIANT_GRAPHICS_2D_H
#define _RADIANT_GRAPHICS_2D_H

#include "Radiant.h"
#include "RadiantAPIMacro.h"

#include <stdint.h>
#include <stdbool.h>

typedef struct Sprite Sprite;
typedef struct TileMap TileMap;
typedef struct TileSet TiletSet;
typedef uint32_t TileID;

/* TileMap functions */
RADIANT_API TileMap *TileMap_Create(TileSet *tileSet);
RADIANT_API void TileMap_Destroy(TileMap *tileMap);
RADIANT_API void TileMap_PlaceTile(TileMap *tileMap, TileID tile, const uint32_t x, const uin32_t y);
RADIANT_API void TileMap_RemoveTile(TileMap *tileMap, const uint32_t x, const uint32_t y);

/* TileSet functions */
RADIANT_API TileSet *TileSet_Create(Atlas *atlas);
RADIANT_API void TileSet_Destroy(TileSet *tileSet);
RADIANT_API TileID TilSet_DefineTile(TileSet *tileSet, const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height, bool collidable);
RADIANT_API void TilSet_UndefineTile(TileSet *tileSet, TileID tile);

#endif