#include <SFML/Graphics.hpp>
#include <vector>
#pragma once

class ParticleSystem {
public:
    struct Particle {
        sf::Vector2f velocity;
        int lifetime=1000;
    };
std::vector<Particle> particles;
sf::VertexArray vertices;

float particleSize=8;

int mx;
int my;

sf::Color color = sf::Color(255, 255, 255, 127);

ParticleSystem(int x, int y) {
    resetParticles();
    mx=x;
    my=y;
}

void resetParticles(int x=-1000, int y=-1000, int count = 20, int size = 4) {
    particles = std::vector<Particle>(count);
    vertices = sf::VertexArray(sf::Quads, count*4);
    particleSize=size; 

    for(int i=0;i<particles.size();i++) {
        resetParticle(i, x, y);
    }
}

void resetParticle(int index, int x, int y) {

    vertices[4*index + 0].position = sf::Vector2f(x, y);
    vertices[4*index + 1].position = sf::Vector2f(x + particleSize, y);
    vertices[4*index + 2].position = sf::Vector2f(x + particleSize, y + particleSize);
    vertices[4*index + 3].position = sf::Vector2f(x, y+particleSize);

    vertices[4*index + 0].color = color;
    vertices[4*index + 1].color = color;
    vertices[4*index + 2].color = color;
    vertices[4*index + 3].color = color;

    float rx = ((float)rand() / RAND_MAX) * 1;
    float ry = ((float)rand() / RAND_MAX) * 1;

    // if(mx-x >= 0) {
    //     rx=-rx;
    // }
    // if(my-y >= 0) {
    //     ry=-ry;
    // }


    particles[index].velocity = sf::Vector2f(rx, ry);

    particles[index].lifetime = 2000 + rand()%1000;

}
void update(int x, int y) {
    for(int i=0;i<particles.size();i++) {

        if(particles[i].lifetime <= 0) {
            resetParticle(i, x, y);
        } else {
            particles[i].lifetime--;
        }

    vertices[4*i + 0].position += particles[i].velocity*gameSpeed;
    vertices[4*i + 1].position += particles[i].velocity*gameSpeed;
    vertices[4*i + 2].position += particles[i].velocity*gameSpeed;
    vertices[4*i + 3].position += particles[i].velocity*gameSpeed;  
    }
}
};