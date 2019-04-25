#include <cstdlib>
#include <ctime>
#include "game.h"
#include "box.h"
#include "boxmatrix.h"

namespace bump {

BoxMatrix::BoxMatrix(Game& game)
{
    m_boxLeft = (game.width() - NUM_COLS * Box::width() -
                 (NUM_COLS - 1) * m_spacing) / 2.0f;
    m_boxBottom = game.height() - 60.0f - NUM_ROWS * Box::height() -
                  (NUM_ROWS - 1) * m_spacing;
    m_spacing = 2.0f;
    init();
}

BoxMatrix::~BoxMatrix()
{
    clear();
}

void BoxMatrix::init()
{
    srand(time(nullptr));

    float y = m_boxBottom;
    m_boxCount = 0;
    for(unsigned int row = 0; row < NUM_ROWS; ++row) {
        float x = m_boxLeft;
        for(unsigned int col = 0; col < NUM_COLS; ++col) {
            int type = (int)((double)rand() / (double)RAND_MAX * Box::TYPE_COUNT);
            if(type < Box::TYPE_COUNT) {
                m_boxes[row][col] = new Box(x, y, type);
                m_boxCount++;
            } else {
                m_boxes[row][col] = nullptr;
            }
            x += Box::width() + m_spacing;;
        }
        y += Box::height() + m_spacing;
    }
}

void BoxMatrix::clear()
{
    for(unsigned int row = 0; row < NUM_ROWS; ++row) {
        for(unsigned int col = 0; col < NUM_COLS; ++col) {
            if(m_boxes[row][col]) {
                delete m_boxes[row][col];
            }
        }
    }
    m_boxCount = 0;
}

void BoxMatrix::draw(BumpShaderProgram& program)
{
    for(unsigned int row = 0; row < NUM_ROWS; ++row) {
        for(unsigned int col = 0; col < NUM_COLS; ++col) {
            if(m_boxes[row][col]) {
                m_boxes[row][col]->draw(program);
            }
        }
    }
}

} // end of namespace bump

