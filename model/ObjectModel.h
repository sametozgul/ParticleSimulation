#ifndef OBJECTMODEL_H
#define OBJECTMODEL_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "OGLRenderData.h"
#include "Shader.h"
#include "VertexBuffer.h"

#include <vector>
struct Particle {
    glm::vec3 position;
    float radius = 10.0f;
    int numberOfTriangles = 30;

    OGLMesh vertexData;

    Particle(glm::vec3 position_, float radius_)
        : position{position_},radius{radius_} {
        generateCircle();
    }

    void generateCircle() {
        vertexData.vertices.resize(numberOfTriangles + 2); // Center + outer vertices
        vertexData.indices.clear();
        vertexData.vertices[0].position = position;
        float angleIncrement = 2.0f * M_PI / numberOfTriangles;
        for (int i = 1; i <= numberOfTriangles + 1; ++i) { // +1 to close the circle
            float angle = (i - 1) * angleIncrement;
            float x = position.x + radius * cos(angle);
            float y = position.y + radius * sin(angle);
            float z = position.z;

            vertexData.vertices[i].position = glm::vec3(x, y, z);
            vertexData.indices.push_back(0);        // Center vertex
            vertexData.indices.push_back(i);        // Current vertex
            vertexData.indices.push_back((i % numberOfTriangles) + 1); // Next vertex
        }
    }

    const OGLMesh& getVertices() const { return vertexData; }
};

class ObjectModel
{
public:
    ObjectModel() = default;
    void setObjectCount(const int& objectCount){numberOfObject = objectCount; init();};
    void init();
    void draw();
    Particle& addObject(glm::vec3 position, float radius) {
        Particle newParticle = Particle(position, radius);
        return objects.emplace_back(newParticle);
    }
    VertexBuffer vertexBuffer{};
private:
    std::vector<glm::vec3> positions;
    std::vector<glm::vec3> last_positions;
    std::vector<glm::vec3> accelerations;
    void update(float dt);
    glm::vec3 gravity          = {0.0f, 10.0f, 0.0f};
    glm::vec3 boundary_center = {0.0f, 0.0f, 0.0f};
    float boundary_radius = 1.0f;
    void applyGravity();
    void applyBoundary();
    void checkCollision();

    void setVelocity(int i, glm::vec3 v, float dt);
    glm::vec3 getVelocity(int i){return positions[i] - last_positions[i];}
private:
    int numberOfObject = 0;
    std::vector<Particle>  objects;
    Shader shader{};
    std::vector<glm::mat4> modelMatrices;
};

#endif // OBJECTMODEL_H
