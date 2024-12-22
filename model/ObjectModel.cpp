#include "ObjectModel.h"

#include "PositionGenerator.h"
void ObjectModel::init()
{
    shader.loadShaders("Debug/shaders/program.vert","Debug/shaders/program.frag");
    shader.use();
    std::vector<glm::mat4> models;
    std::vector<glm::vec3> colors;
    colors.resize(numberOfObject);
    models.resize(numberOfObject);
    for (int i = 0; i < numberOfObject; ++i) {
        glm::mat4 model = glm::mat4(1.0f);
        auto [x, y] = generateRandomPosition();
        model = glm::translate(model, glm::vec3(x, y, 0.0f));
        positions.emplace_back(glm::vec3(x, y, 0.0f));
        accelerations.emplace_back(glm::vec3(0.0f, 0.0f, 0.0f));
        models[i] = model;
        colors[i] = generateRandomColor();
    }
    last_positions = positions;
    modelMatrices = models;
    addObject(glm::vec3(0.0f, 0.0f, 0.0f), 0.05f);
    vertexBuffer.init(objects[0].getVertices(), colors ,modelMatrices);
}
float a = 1.0f / 1000.0f;
void ObjectModel::draw()
{
    applyGravity();
    checkCollision();
    applyBoundary();
    update(a);
    vertexBuffer.upload(modelMatrices);
    vertexBuffer.draw();
}

void ObjectModel::update(float dt)
{
    for(int i  = 0; i < numberOfObject; ++i){
        glm::vec3 displacement = positions[i] - last_positions[i];
        last_positions[i] = positions[i];
        positions[i]      = positions[i] + displacement + accelerations[i] * (dt * dt);
        accelerations[i]  = {};
        modelMatrices[i] = glm::mat4(1.0f);
        modelMatrices[i] = glm::translate(modelMatrices[i], positions[i]);
    }
}

void ObjectModel::applyGravity()
{
    for(int i  = 0; i < numberOfObject; ++i){
        accelerations[i] -= gravity;
    }
}

void ObjectModel::applyBoundary()
{
    for(int i  = 0; i < numberOfObject; ++i){
        glm::vec3 r = boundary_center - positions[i];
        float dist = sqrt(r.x * r.x + r.y * r.y);
        if(dist > boundary_radius - 0.05f){
            glm::vec3 n = r / dist;
            glm::vec3 perp = {-n.y, n.x , 0.0f};
            glm::vec3 vel = getVelocity(i);
            positions[i] = boundary_center - n * (boundary_radius - 0.05f);
            setVelocity(i, 2.0f * (vel.x * perp.x + vel.y * perp.y) * perp - vel, 1.0f);
        }
    }
}

void ObjectModel::checkCollision()
{
    for(int i  = 0; i < numberOfObject; ++i){
        for(int j = 0; j < numberOfObject; ++j){
            if(i == j) continue;
            glm::vec3 v = positions[i] - positions[j];
            float dist = sqrt(v.x * v.x + v.y * v.y);
            float min_dist = 0.05f + 0.05f;
            if(dist < min_dist){
                glm::vec3 n = v / dist;
                float total_mass = 0.05f * 0.05f + 0.05f * 0.05f;
                float mass_ratio = (0.05f * 0.05f) / total_mass;
                float delta = 1.0f * (min_dist - dist);
                positions[i] += n * ( 1 - mass_ratio) * delta;
                positions[j] -= n * mass_ratio * delta;
            }
        }
    }
}

void ObjectModel::setVelocity(int i, glm::vec3 v, float dt)
{
    last_positions[i] = positions[i] - (v * dt);
}
