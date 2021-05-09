#include "RadiantPhysics.h"
#include "Internal_Physics.h"

#include "RadiantMath.h"
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

static PhysicsState2D *physicsState;

void Physics_Initialize() {
    physicsState = malloc(sizeof *physicsState);
    physicsState->t = 0;
    physicsState->dt = 0;
    physicsState->boxes = BBoxList_create();
}

void Physics_Quit() {
    BBoxList_destroy(physicsState->boxes);
    free(physicsState);
}

void Physics_SetGravity(double acceleration) {
    physicsState->gravityAcceleration = acceleration;
}

void Physics_Update(double t, double dt) {
    float newCenter[2];
    float newVelocity[2];
    float temp[2];
    float regionOfCollision[2];
    float distance[2];
    float absDistance[2];
    float collisionNormal[2];

    BBox2DListNode *nA, *nB;
    nA = BBoxList_getHead(physicsState->boxes);

    int i, j;
    const int numBoxes = BBoxList_getSize(physicsState->boxes);
    for (i = 0; i < numBoxes; i++) {
        BBox2D *a = nA->data;
        nA = nA->next;

        Vector2f_Scale(a->acceleration, dt, temp);
        Vector2f_Add(a->velocity, temp, a->velocity);
        Vector2f_Scale(a->velocity, dt, temp);
        Vector2f_Add(a->center, temp, a->center);

        nB = BBoxList_getHead(physicsState->boxes);

        /* check for & handle collisions */
        for (j = 0; j < i; j++) {
            BBox2D *b = nB->data;
            nB = nB->next;
            Vector2f_Subtract(b->center, a->center, distance);
            Vector2f_AbsoluteValue(distance, absDistance);
            Vector2f_Add(a->size, b->size, regionOfCollision);

            if (absDistance[0] > regionOfCollision[0]) {
                return;
            }

            if (absDistance[1] > regionOfCollision[1]){
                return;
            }

            /* Collision has happened, deal with it. */

            float vAB[2];
            Vector2f_Subtract(b->velocity, a->velocity, vAB);
/*             // Vector2f_Normalize(distance, collisionNormal); //distance from a to b normalized */
            

            if (absDistance[0] >= absDistance[1]) {
                collisionNormal[0] = -1.0;
                collisionNormal[1] = 0.0;

                temp[0] = regionOfCollision[0] - absDistance[0];
                temp[1] = 0;
                if (distance[0] < 0) {
                    collisionNormal[0] = 1.0;
                    temp[0] = -temp[0];
                }

            } else {
                collisionNormal[0] = 0.0;
                collisionNormal[1] = -1.0;

                temp[0] = 0;
                temp[1] = regionOfCollision[1] - absDistance[1];
                if (distance[1] < 0) {
                    collisionNormal[1] = 1.0;
                    temp[1] = -temp[1];
                }

            }

            printf("\ncollision normal: %f, %f\n", collisionNormal[0], collisionNormal[1]);

            Vector2f_Add(b->center, temp, b->center); /* Push collider min distance to ensure no overlap. */

            /* Vector2f_Normalize(collisionNormal, collisionNormal); */
            float velocityAlongNormal = Vector2f_DotProduct(vAB, collisionNormal);

            if ((velocityAlongNormal > 0 && distance[0] < 0) || (velocityAlongNormal < 0 && distance[0] > 0)) {
                float epsilon = MinFloat(a->material->restitution, b->material->restitution); /* Use min restitution for best results */
                float impulseCoefficient = -(1 + epsilon) * velocityAlongNormal;
                impulseCoefficient /= (1/a->mass) + (1/b->mass);

                printf("impulse coefficient=%f\n", impulseCoefficient);
                float impulse[2];
                Vector2f_Scale(collisionNormal, impulseCoefficient, impulse);
                Vector2f_Scale(impulse, 1 / a->mass, temp);
                Vector2f_Subtract(a->velocity, temp, a->velocity);

                Vector2f_Scale(impulse, 1 / b->mass, temp);
                Vector2f_Add(b->velocity, temp, b->velocity);
            }
        }
    }
}

BBox2D *Physics_AddBBox2D(BBoxTypes boxType, PhysicsMaterial *material, float *center, float *size, float theta) {
    BBox2D box;
    box.type = boxType;
    box.id = BBoxList_getSize(physicsState->boxes);
    box.center[0] = center[0];
    box.center[1] = center[1];
    box.size[0] = size[0];
    box.size[1] = size[1];
    box.velocity[0] = 0.0;
    box.velocity[1] = 0.0;
    box.acceleration[0] = 0.0;
    box.acceleration[1] = 0.0;
    box.theta = theta;
    box.material = material;
    box.mass = (box.size[0] * box.size[1]) * material->density;
    box.gravityScale = 1.0;

    return BBoxList_addBBox(physicsState->boxes, box);
}

void Physics_RemoveBBox2D(BBox2D *box);
