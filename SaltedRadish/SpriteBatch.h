#pragma once
#include "Vertex.h"

#include <GL/glew.h>

#include <vector>

class SpriteBatch {
public:
     struct Glyph {
        GLuint texture;

        Vertex topLeft;
        Vertex bottomLeft;
        Vertex bottomRight;
        Vertex topRight;
    };

    struct RenderBatch {
        RenderBatch(const GLint Offset, const GLsizei NumVertices, const GLuint Texture):
            offset(Offset),
            numVertices(NumVertices),
            texture(Texture) {}

	    GLint offset;
	    GLsizei numVertices;
	    GLuint texture;
    };

    SpriteBatch();
    ~SpriteBatch();

    void init();
    void clean();
    void add(glm::vec3 destRect, GLuint texture, float size);
    void addGlyph(Glyph* glyph);
    void createBatch();
    void renderBatch() const;

private:
    GLuint _vao{};
    GLuint _vbo{};

    std::vector<Glyph*> _glyphs;
    std::vector<RenderBatch*> _renderBatches;
};
