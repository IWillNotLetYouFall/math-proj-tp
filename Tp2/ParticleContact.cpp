#include "ParticleContact.h"

void ParticleContact::Resolve(float duration)
{
    //Appliquer l'impulsion et repos
    ResolveVelocity(duration);

    //Résoudre interpénétration (position)
    ResolveInterpenetration();
}

float ParticleContact::CalculateSeparatingVelocity()
{
    Vector3D distRel = particle[0]->velocite;
    if (particle[1])
        distRel -= particle[1]->velocite;
    return distRel.ScalarProduct(contactNormal);
}

void ParticleContact::ResolveVelocity(float duration)
{
    float separationVel = CalculateSeparatingVelocity();
    if (separationVel > 0) return;

    float restiSepVelocity = restitution * -separationVel;
    Vector3D accelerationVel = particle[0]->getAcceleration();
    if (particle[1])
        accelerationVel -= particle[1]->getAcceleration();

    float accVelSeparation = accelerationVel.ScalarProduct(contactNormal) * duration;

    //Si l'accélétation crée une interpolation, retrait de celle-ci
    if (accVelSeparation < 0) {
        restiSepVelocity += accVelSeparation * restitution;

        //Empêche l'inversion de la vélocité par accident
        if (restiSepVelocity < 0)
            restiSepVelocity = 0;
    }

    float velociteDelta = restiSepVelocity - separationVel;

    float masseInverseTotale = particle[0]->InverseMasse();
    if (particle[1]) 
        masseInverseTotale += particle[1]->InverseMasse();
    if (masseInverseTotale <= 0) return; //Gère collisions entre masses infinies

    float impulsion = velociteDelta / masseInverseTotale;
    Vector3D impulsionAvecMasse = contactNormal * impulsion; //IMass??

    particle[0]->velocite = particle[0]->velocite + impulsionAvecMasse * particle[0]->InverseMasse();
    if (particle[1])
        particle[1]->velocite = particle[1]->velocite + impulsionAvecMasse * -particle[1]->InverseMasse();
}

void ParticleContact::ResolveInterpenetration()
{
    if (penetration <= 0) return;

    float masseInverseTotale = particle[0]->InverseMasse();
    if (particle[1])
        masseInverseTotale += particle[1]->InverseMasse();
    if (masseInverseTotale <= 0) return; //Gère collisions entre masses infinies

    Vector3D deltaMouvementIMass = (contactNormal) * (penetration / masseInverseTotale);

    particle[0]->position += deltaMouvementIMass * particle[0]->InverseMasse();
    if (particle[1])
        particle[1]->position += deltaMouvementIMass * -particle[1]->InverseMasse();
}
