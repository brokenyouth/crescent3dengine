#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "../Vertex.h"

std::vector<Vertex> CubeVertices = {
    // 0
    Vertex {
        glm::vec3(0.5, 0.5, -0.5),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec2(1.0f, 1.0f)
    },
    // 1
    Vertex {
        glm::vec3(0.5, -0.5, -0.5),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f)
    },
    // 2
    Vertex {
        glm::vec3(-0.5, -0.5, -0.5),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec2(0.0f, 0.0f)
    },
    // 3
    Vertex {
        glm::vec3(-0.5, 0.5, -0.5),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec2(0.0f, 1.0f)
    },
    // 4
    Vertex {
        glm::vec3(0.5, 0.5, 0.5),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec2(0.0f, 1.0f)
    },
    // 5
    Vertex {
        glm::vec3(0.5, -0.5, 0.5),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec2(0.0f, 0.0f)
    },
    // 6
    Vertex {
        glm::vec3(-0.5, -0.5, 0.5),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f)
    },
    // 7
    Vertex {
        glm::vec3(-0.5, 0.5, 0.5),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec3(1.0f, 0.0f, 0.0f),
        glm::vec2(1.0f, 1.0f)
    }
};

std::vector<glm::vec3> CubeVerticesVec = {
    // VO
    glm::vec3(0.5, 0.5, -0.5),
    // V1
    glm::vec3(0.5, -0.5, -0.5),
    // V2
    glm::vec3(-0.5, -0.5, -0.5),
    // V3
    glm::vec3(-0.5, 0.5, -0.5),
    // V4
    glm::vec3(0.5, 0.5, 0.5),
    // V5
    glm::vec3(0.5, -0.5, 0.5),
    // V6
    glm::vec3(-0.5, -0.5, 0.5),
    // V7
    glm::vec3(-0.5, 0.5, 0.5),
};

std::vector<unsigned int> CubeIndices = {
    // Front
    0, 1, 3,      3, 1, 2,
    // Top
    4, 0, 3,      5, 4, 3,
    // Right
    3, 2, 7,      5, 3, 7,
    // Left
    6, 1, 0,      6, 0, 4,
    // Bottom
    2, 1, 6,      2, 6, 7,
    // Back
    7, 6, 4,      7, 4, 5,

};

std::vector<glm::vec2> cubeUVCoords = {
        glm::vec2(1.0f, 1.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(0.0f, 1.0f),//
        glm::vec2(0.0f, 1.0f),
        glm::vec2(0.0f, 0.0f),
        glm::vec2(1.0f, 0.0f),
        glm::vec2(1.0f, 1.0f),
};