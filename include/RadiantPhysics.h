/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#ifndef _RADIANT_PHYSICS_H
#define _RADIANT_PHYSICS_H

#include "RadiantAPIMacro.h"

typedef enum BBoxTypes {
    BBOX_TYPE_AXIS_ALIGNED,
    BBOX_TYPE_NON_AXIS_ALIGNED
}BBoxTypes;

typedef struct PhysicsState2D PhysicsState2D;
typedef struct PhysicsMaterial PhysicsMaterial;
typedef struct PhysicsObject PhysicsObject;
typedef struct BBox2D BBox2D;
typedef struct BBox3D BBox3D;
typedef struct Force Force;

RADIANT_API void Physics_Initialize();
RADIANT_API void Physics_SetGravity(double acceleration);
RADIANT_API void Physics_Quit();
RADIANT_API void Physics_Update(double t, double dt);
RADIANT_API BBox2D *Physics_AddBBox2D(BBoxTypes boxType, PhysicsMaterial *material, float *center, float *size, float theta);
RADIANT_API void Physics_RemoveBBox2D(BBox2D *box);
/* void Physics_addForce(float magnitude, float *direction);
void Physics_removeForce(); */

/* 2D BBox functions */
RADIANT_API BBoxTypes BBox2D_getType(BBox2D *box);
RADIANT_API int BBox2D_getID(BBox2D *box);
RADIANT_API void BBox2D_getCenter(BBox2D *box, float *output);
RADIANT_API void BBox2D_getSize(BBox2D *box, float *output);
RADIANT_API float BBox2D_getMass(BBox2D *box);
RADIANT_API float BBox2D_getTheta(BBox2D *box);
RADIANT_API void BBox2D_getVelocity(BBox2D *box, float *output);
RADIANT_API void BBox2D_getAcceleration(BBox2D *box, float *output);
RADIANT_API float BBox2D_getGravityScale(BBox2D *box);
RADIANT_API void BBox2D_setType(BBox2D *box, BBoxTypes boxType);
RADIANT_API void BBox2D_setCenter(BBox2D *box, float *center);
RADIANT_API void BBox2D_setSize(BBox2D *box, float *size);
RADIANT_API void BBox2D_setMass(BBox2D *box, float mass);
RADIANT_API void BBox2D_setTheta(BBox2D *box, float theta);
RADIANT_API void BBox2D_setVelocity(BBox2D *box, float *velocity);
RADIANT_API void BBox2D_setAcceleration(BBox2D *box, float *acceleration);
RADIANT_API void BBox2D_setGravityScale(BBox2D *box, float gravityScale);

/* 3D BBox functions */
RADIANT_API BBoxTypes BBox3D_getType(BBox3D *box);
RADIANT_API int BBox3D_getID(BBox3D *box);
RADIANT_API void BBox3D_getCenter(BBox3D *box, float *output);
RADIANT_API void BBox3D_getSize(BBox3D *box, float *output);
RADIANT_API float BBox3D_getMass(BBox3D *box);
RADIANT_API float BBox3D_getTheta(BBox3D *box);
RADIANT_API void BBox3D_getVelocity(BBox3D *box, float *output);
RADIANT_API void BBox3D_getAcceleration(BBox3D *box, float *output);
RADIANT_API float BBox3D_getGravityScale(BBox3D *box);
RADIANT_API void BBox3D_setType(BBox3D *box, BBoxTypes boxType);
RADIANT_API void BBox3D_setCenter(BBox3D *box, float *center);
RADIANT_API void BBox3D_setSize(BBox3D *box, float *size);
RADIANT_API void BBox3D_setMass(BBox3D *box, float mass);
RADIANT_API void BBox3D_setTheta(BBox3D *box, float theta);
RADIANT_API void BBox3D_setVelocity(BBox3D *box, float *velocity);
RADIANT_API void BBox3D_setAcceleration(BBox3D *box, float *acceleration);
RADIANT_API void BBox3D_setGravityScale(BBox3D *box, float gravityScale);

/* Physics material functions */
RADIANT_API PhysicsMaterial *PhysicsMaterial_Create(const char *name, float density, float restitution);
RADIANT_API void PhysicsMaterial_Destroy(PhysicsMaterial *material);
RADIANT_API float PhysicsMaterial_GetDensity(PhysicsMaterial *material);
RADIANT_API float PhysicsMaterial_GetRestitution(PhysicsMaterial *material);
RADIANT_API void PhysicsMaterial_SetDensity(PhysicsMaterial *material, float density);
RADIANT_API void PhysicsMaterial_SetRestitution(PhysicsMaterial *material, float restitution);

RADIANT_API void Force_setMagnitude(float magnitude);
RADIANT_API void Force_setDirection(float direction);

#endif