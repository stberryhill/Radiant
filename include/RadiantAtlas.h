/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef _RADIANT_ATLAS_H
#define _RADIANT_ATLAS_H

#include "Radiant.h"
#include "RadiantAPIMacro.h"

typedef struct Atlas Atlas;
typedef uint32_t AtlasRegionId;

/* Atlas functions */
RADIANT_API Atlas *Atlas_Create(Texture *texture, const uint16_t cellWidth, const uint16_t cellHeight);
RADIANT_API void Atlas_Destroy(Atlas *atlas);
RADIANT_API AtlasRegionId Atlas_DefineRegion(Atlas *atlas, const uint16_t x, const uint16_t y, const uint16_t width, const uint16_t height);

#endif