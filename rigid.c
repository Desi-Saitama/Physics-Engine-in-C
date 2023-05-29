#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#define NUM_RIGID_BODY 1
#define M_PI 3.14

// 2d vector
typedef struct {
    float x;
    float y;
} Vector1;

// Creating a 2d box, we can also create circle, cylinders etc
typedef struct{
    float width;
    float height;
    float mass;
    float momentOfInertia;
}BoxShape;

// Function to calculate inertia of box and store in moment of inertia
void BodyInertia(BoxShape *boxShape){
    float m = boxShape->mass;
    float w = boxShape->width;
    float h = boxShape->height;
    boxShape->momentOfInertia = m*(w*w+h*h) / 12;
}

// Creating a 2d rigid body
typedef struct{
    Vector1 position; // vector of x and Y value
    Vector1 linearVelocity; // vector of x and y
    float angle;
    float angularVelocity; //vector of x and y
    Vector1 Force; // vector of x and y
    float torque;
    BoxShape  shape; // shape in BoxShape
}RigidBody;

//array of bodies
RigidBody rigidBodies[NUM_RIGID_BODY];

//printing position of Rigid bodies
void PrintRigidBodies(){
    for (int i = 0; i < NUM_RIGID_BODY; ++i) {
        RigidBody *rigidBody = &rigidBodies[i];
        printf("body[%i]p = (%0.2f, %0.2f), a = %0.2f\n", i, rigidBody->position.x, rigidBody->position.y, rigidBody->angle);
    }
}

//we will initialize bodies with random variables
void InitializingBodies(){
    for (int i = 0; i<NUM_RIGID_BODY; ++i){
        RigidBody *rigidBody = &rigidBodies[i];
        rigidBody->position = (Vector1){(1 + rand() % 50) , (1 + rand() % 50)};
        rigidBody->angle = (1 + rand() % 360)/360.f * M_PI * 2;
        rigidBody->linearVelocity = (Vector1){0, 0};
        rigidBody->angularVelocity = 0;

        BoxShape shape;
        shape.mass = 10;
        shape.width = 1 + rand() % 2;
        shape.height = 1 + rand() % 2;
        BodyInertia(&shape);
        rigidBody->shape = shape;
    }
}

// Applying force at a point in body and induce torque
void ForceAndTorque(RigidBody *rigidBody){
    Vector1 f = (Vector1){0,100};
    rigidBody->Force = f;
    Vector1 r = (Vector1){(rigidBody->shape.width)/2, (rigidBody->shape.height)/2};
    rigidBody->torque = (r.x * f.y) - (r.y * f.x);
}

void
RunRigidSimulation(){
    float totalSimulationTime = 10;
    float currentTime = 0;
    float dt = 1;

    InitializingBodies();
    PrintRigidBodies();

    while (currentTime < totalSimulationTime){
        sleep(dt);

        for (int i = 0; i<NUM_RIGID_BODY; ++i){
            RigidBody *rigidBody = &rigidBodies[i];
            ForceAndTorque(rigidBody);
            Vector1 linearAcceleration = (Vector1){(rigidBody->Force.x)/(rigidBody->shape.mass), (rigidBody->Force.y)/(rigidBody)->shape.mass};
            rigidBody->linearVelocity.x += linearAcceleration.x * dt;
            rigidBody->linearVelocity.y += linearAcceleration.y * dt;
            rigidBody->position.x += rigidBody->linearVelocity.x * dt;
            rigidBody->position.y += rigidBody->linearVelocity.y * dt;
            float angularAcceleration = rigidBody->torque/rigidBody->shape.momentOfInertia;
            rigidBody->angularVelocity += angularAcceleration*dt;
            rigidBody->angle += rigidBody->angularVelocity*dt;
        }
        PrintRigidBodies();
        currentTime += dt;
    }
}

int main(){
    RunRigidSimulation();
    return 0;
}