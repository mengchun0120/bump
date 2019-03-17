#include <stdexcept>
#include "log.h"
#include "rectangle.h"

namespace bump {

Rectangle::Rectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
: VertexArray()
{
    GLfloat vertices[] = {
        x, y,
        x, y+height,
        x+width, y+height,
        x+width, y
    };

    unsigned short indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    if(!load(vertices, 4, indices, 6)) {
        throw std::runtime_error("Failed to initialize Rectangle");
    }
}

Rectangle::~Rectangle()
{
}

void Rectangle::draw(BumpShaderProgram& program, const GLfloat *ref, const GLfloat *color)
{
    if(ref != nullptr) {
        program.setUseObjRef(true);
        program.setObjRef(ref);
    } else {
        program.setUseObjRef(false);
    }

    program.setColor(color);
    program.setPosition(*this);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (void *)0);
}

} // end of namespace bump
