#pragma once

#include "SpriteBatch.h"
#include <glm/fwd.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

inline void XQuad(const glm::vec2 destRect, float yOffset, const GLuint texture, const float size, SpriteBatch* batch) {
    const glm::vec3 one(destRect.x - size/2, destRect.y - size/2, destRect.y + size/2);
    auto* glyph = new SpriteBatch::Glyph;
    glyph->texture = texture;

    glyph->topLeft.position = glm::vec3(one.x, yOffset, one.z);
    glyph->topLeft.uv = glm::vec2(0.0f, 1.0f);

    glyph->bottomLeft.position = glm::vec3(one.x, yOffset, one.y);
    glyph->bottomLeft.uv = glm::vec2(0.0f, 0.0f);

    glyph->bottomRight.position = glm::vec3(one.x, yOffset + std::abs(size), one.y);
    glyph->bottomRight.uv = glm::vec2(1.0f, 0.0f);

    glyph->topRight.position = glm::vec3(one.x, yOffset + std::abs(size), one.z);
    glyph->topRight.uv = glm::vec2(1.0f, 1.0f);

    batch->addGlyph(glyph);
}

inline void YQuad(const glm::vec2 destRect, float yOffset, const GLuint texture, const float size, SpriteBatch* batch) {
    const glm::vec2 plus(destRect.x + size/2, destRect.y + size/2);
    const glm::vec2 minus(destRect.x - size/2, destRect.y - size/2);
    auto* glyph = new SpriteBatch::Glyph;
    glyph->texture = texture;

    glyph->topLeft.position = glm::vec3(minus.x, yOffset + (std::abs(size/2) - size/2), plus.y);
    glyph->topLeft.uv = glm::vec2(0.0f, 1.0f);

    glyph->bottomLeft.position = glm::vec3(minus.x, yOffset + (std::abs(size/2) - size/2), minus.y);
    glyph->bottomLeft.uv = glm::vec2(0.0f, 0.0f);

    glyph->bottomRight.position = glm::vec3(plus.x, yOffset + (std::abs(size/2) - size/2), minus.y);
    glyph->bottomRight.uv = glm::vec2(1.0f, 0.0f);

    glyph->topRight.position = glm::vec3(plus.x, yOffset + (std::abs(size/2) - size/2), plus.y);
    glyph->topRight.uv = glm::vec2(1.0f, 1.0f);

    batch->addGlyph(glyph);
}

inline void ZQuad(const glm::vec2 destRect, float yOffset, const GLuint texture, const float size, SpriteBatch* batch) {
    const glm::vec3 one(destRect.x - size/2, destRect.y - size/2, destRect.x + size/2);
    auto* glyph = new SpriteBatch::Glyph;
    glyph->texture = texture;

    glyph->topLeft.position = glm::vec3(one.x, yOffset + std::abs(size), one.y);
    glyph->topLeft.uv = glm::vec2(0.0f, 1.0f);

    glyph->bottomLeft.position = glm::vec3(one.x, yOffset, one.y);
    glyph->bottomLeft.uv = glm::vec2(0.0f, 0.0f);

    glyph->bottomRight.position = glm::vec3(one.z, yOffset, one.y);
    glyph->bottomRight.uv = glm::vec2(1.0f, 0.0f);

    glyph->topRight.position = glm::vec3(one.z, yOffset + std::abs(size), one.y);
    glyph->topRight.uv = glm::vec2(1.0f, 1.0f);

    batch->addGlyph(glyph);
}
