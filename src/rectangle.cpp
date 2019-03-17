#include <stdexcept>
#include "log.h"
#include "rectangle.h"

namespace bump {

Rectangle::Rectangle(GLfloat x, GLfloat y, GLfloat width, GLfloat height)
: VertexArray()
{
    GLfloat vertices[] = {
        x+width/2.0f, y+height/2.0f,
        x, y,
        x, y+height,
        x+width, y+height,
        x+width, y,
        x, y
    };

    if(!load(vertices, 6, nullptr, 0)) {
        throw std::runtime_error("Failed to initialize Rectangle");
    }
}

Rectangle::~Rectangle()
{
}

void Rectangle::draw(BumpShaderProgram& program, const GLfloat *ref,
                     const GLfloat* fillColor, const GLfloat* borderColor, GLfloat borderWidth)
{
    if(ref != nullptr) {
        program.setUseObjRef(true);
        program.setObjRef(ref);
    } else {
        program.setUseObjRef(false);
    }

    program.setPosition(*this);

    if(fillColor != nullptr) {
        program.setColor(fillColor);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 6);
    }

    if(borderColor != nullptr) {
        glLineWidth(borderWidth);
        program.setColor(borderColor);
        glDrawArrays(GL_LINE_LOOP, 1, 5);
    }
}

} // end of namespace bump
