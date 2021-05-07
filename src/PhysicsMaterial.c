#include "RadiantPhysics.h"
#include "Internal_Physics.h"

#include <stdlib.h>
#include <string.h>

PhysicsMaterial *PhysicsMaterial_Create(const char *name, float density, float restitution) {
    PhysicsMaterial *material = malloc(sizeof *material);
    material->name = malloc(strlen(name) + 1);
    strcpy(material->name, name);

    material->density = density;
    material->restitution = restitution;

    return material;
}

void PhysicsMaterial_Destroy(PhysicsMaterial *material) {
    free(material->name);
    free(material);
}

float PhysicsMaterial_GetDensity(PhysicsMaterial *material) {
    return material->density;
}

float PhysicsMaterial_GetRestitution(PhysicsMaterial *material) {
    return material->restitution;
}

void PhysicsMaterial_SetDensity(PhysicsMaterial *material, float density) {
    material->density = density;
}
void PhysicsMaterial_SetRestitution(PhysicsMaterial *material, float restitution) {
    material->restitution = restitution;
}