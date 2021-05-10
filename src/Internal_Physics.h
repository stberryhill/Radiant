/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef _RADIANT_INTERNAL_PHYSICS_H
#define _RADIANT_INTERNAL_PHYSICS_H

#include "RadiantPhysics.h"

typedef struct BBox2DList {
    struct BBox2DListNode *head;
    int size;
} BBox2DList;

typedef struct BBox2DListNode {
    struct BBox2DListNode *next;
    struct BBox2DListNode *prev;
    BBox2D *data;
} BBox2DListNode;

struct PhysicsState2D {
    double t;
    double dt;
    double gravityAcceleration;
    BBox2DList *boxes;
};

struct PhysicsMaterial {
    char *name;
    float density;
    float restitution;
};

struct BBox2D {
    int type;
    int id;
    float center[2];
    float size[2];
    float mass;
    float theta;
    float velocity[2];
    float acceleration[2];
    float gravityScale;
    PhysicsMaterial *material;
};

BBox2DList *BBoxList_create();
void BBoxList_destroy(BBox2DList *list);
BBox2DListNode *BBoxList_getHead(BBox2DList *list);
int BBoxList_getSize(BBox2DList *list);
BBox2D *BBoxList_addBBox(BBox2DList *list, const BBox2D box); /* add bbox and return pointer to it. */
void BBoxList_removeNode(BBox2DList *list, BBox2DListNode *node);
void BBoxList_removeNodeByIndex(BBox2DList *list, int indexOfNode);

#endif