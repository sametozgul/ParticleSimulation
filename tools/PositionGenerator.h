#ifndef POSITIONGENERATOR_H
#define POSITIONGENERATOR_H

#include <glm/glm.hpp>
#include <vector>
#include <random>

std::pair<float, float> generateRandomPosition() {
    static std::random_device rd;  // Seed for random number generator
    static std::mt19937 gen(rd()); // Mersenne Twister generator
    static std::uniform_real_distribution<float> dist(-0.5f, 0.5f); // Range [-1, 1]

    float x = dist(gen);
    float y = dist(gen);
    return {x, y};
}
glm::vec3 generateRandomColor() {
    static std::random_device rd;  // Seed for random number generator
    static std::mt19937 gen(rd()); // Mersenne Twister generator
    static std::uniform_real_distribution<float> dist(0.0f, 1.0f); // Range [-1, 1]

    float x = dist(gen);
    float y = dist(gen);
    float z = dist(gen);
    glm::vec3 color = {x, y ,z };
    return color;
}

float generateRandomSize() {
    static std::random_device rd;  // Seed for random number generator
    static std::mt19937 gen(rd()); // Mersenne Twister generator
    static std::uniform_real_distribution<float> dist(0.05f, 0.1f); // Range [-1, 1]

    float x = dist(gen);
    return x;
}
#endif // POSITIONGENERATOR_H
