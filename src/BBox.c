/*
 * License: Zlib
 * Copyright (c) Sean Tyler Berryhill (sean.tyler.berryhill@gmail.com)
 */

#include "RadiantPhysics.h"
#include "Internal_Physics.h"

BBoxTypes BBox2D_getType(BBox2D *box) {
    return box->type;
}

int BBox2D_getID(BBox2D *box) {
    return box->id;
}

void BBox2D_getCenter(BBox2D *box, float *output) {
    output[0] = box->center[0];
    output[1] = box->center[1];
}

void BBox2D_getSize(BBox2D *box, float *output) {
    output[0] = box->size[0];
    output[1] = box->size[1];
}

float BBox2D_getMass(BBox2D *box) {
    return box->mass;
}

float BBox2D_getTheta(BBox2D *box) {
    return box->theta;
}

void BBox2D_getVelocity(BBox2D *box, float *output) {
    output[0] = box->velocity[0];
    output[1] = box->velocity[1];
}

void BBox2D_getAcceleration(BBox2D *box, float *output) {
    output[0] = box->acceleration[0];
    output[1] = box->acceleration[1];
}

float BBox2D_getGravityScale(BBox2D *box) {
    return box->gravityScale;
}

void BBox2D_setType(BBox2D *box, BBoxTypes boxType) {
    box->type = boxType;
}

void BBox2D_setCenter(BBox2D *box, float *center) {
    box->center[0] = center[0];
    box->center[1] = center[1];
}

void BBox2D_setSize(BBox2D *box, float *size) {
    box->size[0] = size[0];
    box->size[1] = size[1];

}

void BBox2D_setMass(BBox2D *box, float mass) {
    box->mass = mass;
}

void BBox2D_setTheta(BBox2D *box, float theta) {
    box->theta = theta;
}

void BBox2D_setVelocity(BBox2D *box, float *velocity) {
    box->velocity[0] = velocity[0];
    box->velocity[1] = velocity[1];
}

void BBox2D_setAcceleration(BBox2D *box, float *acceleration) {
    box->acceleration[0] = acceleration[0];
    box->acceleration[1] = acceleration[1];
}

void BBox2D_setGravityScale(BBox2D *box, float gravityScale) {
    box->gravityScale = gravityScale;
}