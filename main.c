#define NUM_PARTTICLE 1
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

// two dimenional vector
typedef struct {
    float x;
    float y;
} Vector1;

// every particle to have one vector for position and one vector for position of particle

typedef struct {
    Vector1 position;
    Vector1 velocity;
    float mass;
} Particle;

int getRandomNumber() {
    return 1 + rand() % 50;  // Generates a random number between 1 and 50
}
// Array of particle
Particle particles[NUM_PARTTICLE];

// Printing particles on output screen
//  function uses a loop to iterate over each particle in the particles array and retrieves its address using the & operator. Then it the particle's index along with its x and y position values.
void Printparticles(){
    for (int i=0; i<NUM_PARTTICLE; ++i){
        Particle *particle = &particles[i];
        printf("particle[%i](%0.2f, %0.2f)\n", i, particle->position.x, particle->position.y);
    }
}

// intializing all particles
void intializeParticle(){
    for (int i=0; i<NUM_PARTTICLE; i++){
        particles[i].position = (Vector1){getRandomNumber(), getRandomNumber()};
        particles[i].velocity = (Vector1){0,0};
        particles[i].mass = 1;
    }
}

// we will apply gravitanional force of earth i.e. 9.81 meter per second square.

Vector1 Gravity(Particle *particle){
    return (Vector1){0, particle->mass*9.81};
}

void StartphysicsEngine(){
    float totaltime = 10;
    float currenttime = 0;
    float dt = 1;

    intializeParticle();
    Printparticles();

    while(currenttime < totaltime){
        sleep(dt);
        for (int i = 0; i<NUM_PARTTICLE; ++i){
            Particle *particle = &particles[i];
            Vector1 force = Gravity(particle);
            Vector1 acceleration = (Vector1){force.x/particle->mass, force.y/particle->mass};
            particle->velocity.x += acceleration.x * dt;
            particle->velocity.y += acceleration.y * dt;
            particle->position.x += particle->velocity.x * dt;
            particle->position.y += particle->velocity.y * dt;
        }
        Printparticles();
        currenttime += dt;
    }
}

int main(){
    StartphysicsEngine();
    return 0;
}