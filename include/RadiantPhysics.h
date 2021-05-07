#ifndef _RADIANT_PHYSICS_H
#define _RADIANT_PHYSICS_H

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

void Physics_Initialize();
void Physics_SetGravity(double acceleration);
void Physics_Quit();
void Physics_Update(double t, double dt);
BBox2D *Physics_AddBBox2D(BBoxTypes boxType, PhysicsMaterial *material, float *center, float *size, float theta);
void Physics_RemoveBBox2D(BBox2D *box);
/* void Physics_addForce(float magnitude, float *direction);
void Physics_removeForce(); */

/* 2D BBox functions */
BBoxTypes BBox2D_getType(BBox2D *box);
int BBox2D_getID(BBox2D *box);
void BBox2D_getCenter(BBox2D *box, float *output);
void BBox2D_getSize(BBox2D *box, float *output);
float BBox2D_getMass(BBox2D *box);
float BBox2D_getTheta(BBox2D *box);
void BBox2D_getVelocity(BBox2D *box, float *output);
void BBox2D_getAcceleration(BBox2D *box, float *output);
float BBox2D_getGravityScale(BBox2D *box);
void BBox2D_setType(BBox2D *box, BBoxTypes boxType);
void BBox2D_setCenter(BBox2D *box, float *center);
void BBox2D_setSize(BBox2D *box, float *size);
void BBox2D_setMass(BBox2D *box, float mass);
void BBox2D_setTheta(BBox2D *box, float theta);
void BBox2D_setVelocity(BBox2D *box, float *velocity);
void BBox2D_setAcceleration(BBox2D *box, float *acceleration);
void BBox2D_setGravityScale(BBox2D *box, float gravityScale);

/* 3D BBox functions */
BBoxTypes BBox3D_getType(BBox3D *box);
int BBox3D_getID(BBox3D *box);
void BBox3D_getCenter(BBox3D *box, float *output);
void BBox3D_getSize(BBox3D *box, float *output);
float BBox3D_getMass(BBox3D *box);
float BBox3D_getTheta(BBox3D *box);
void BBox3D_getVelocity(BBox3D *box, float *output);
void BBox3D_getAcceleration(BBox3D *box, float *output);
float BBox3D_getGravityScale(BBox3D *box);
void BBox3D_setType(BBox3D *box, BBoxTypes boxType);
void BBox3D_setCenter(BBox3D *box, float *center);
void BBox3D_setSize(BBox3D *box, float *size);
void BBox3D_setMass(BBox3D *box, float mass);
void BBox3D_setTheta(BBox3D *box, float theta);
void BBox3D_setVelocity(BBox3D *box, float *velocity);
void BBox3D_setAcceleration(BBox3D *box, float *acceleration);
void BBox3D_setGravityScale(BBox3D *box, float gravityScale);

/* Physics material functions */
PhysicsMaterial *PhysicsMaterial_Create(const char *name, float density, float restitution);
void PhysicsMaterial_Destroy(PhysicsMaterial *material);
float PhysicsMaterial_GetDensity(PhysicsMaterial *material);
float PhysicsMaterial_GetRestitution(PhysicsMaterial *material);
void PhysicsMaterial_SetDensity(PhysicsMaterial *material, float density);
void PhysicsMaterial_SetRestitution(PhysicsMaterial *material, float restitution);

void Force_setMagnitude(float magnitude);
void Force_setDirection(float direction);
#endif