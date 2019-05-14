#include <cstdlib>
#include <ctime>
#include "game.h"
#include "box.h"
#include "boxmatrix.h"
#include "log.h"

namespace bump {

int BoxMatrix::clampRow(int row)
{
    if(row < 0) {
        return 0;
    } else if(row >= (int)NUM_ROWS) {
        return NUM_ROWS - 1;
    }
    return row;
}

int BoxMatrix::clampCol(int col)
{
    if(col < 0) {
        return 0;
    } else if(col >= (int)NUM_COLS) {
        return NUM_COLS - 1;
    }
    return col;
}

BoxMatrix::BoxMatrix(Game& game)
{
    m_spacing = 2.0f;
    m_boxLeft = (game.width() - NUM_COLS * Box::width() -
                 (NUM_COLS - 1) * m_spacing) / 2.0f;
    m_boxBottom = game.height() - 60.0f - NUM_ROWS * Box::height() -
                  (NUM_ROWS - 1) * m_spacing;
    m_boxRight = m_boxLeft + NUM_COLS * Box::width() + 
                 (NUM_COLS - 1) * m_spacing;
    m_boxTop = m_boxBottom + NUM_ROWS * Box::height() +
               (NUM_ROWS - 1) * m_spacing;
    m_colWidth = Box::width() + m_spacing;
    m_rowHeight = Box::height() + m_spacing;
    LOG_INFO("left=%f bottom=%f right=%f top=%f width=%f height=%f",
             m_boxLeft, m_boxBottom, m_boxRight, m_boxTop,
             m_colWidth, m_rowHeight);
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
    const unsigned int TYPE_COUNT = Box::typeCount();

    m_boxCount = 0;
    for(unsigned int row = 0; row < NUM_ROWS; ++row) {
        float x = m_boxLeft;
        for(unsigned int col = 0; col < NUM_COLS; ++col) {
            int type = (int)((double)rand() /
                             (double)RAND_MAX * TYPE_COUNT);
            if(type < TYPE_COUNT) {
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

void BoxMatrix::clearBox(int row, int col)
{
    if(m_boxes[row][col]) {
        delete m_boxes[row][col];
        m_boxes[row][col] = nullptr;
        --m_boxCount;
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

int BoxMatrix::getRow(float y)
{
    return clampRow((int)((y - m_boxBottom) / m_rowHeight));
}

int BoxMatrix::getCol(float x)
{
    return clampCol((int)((x - m_boxLeft) / m_colWidth));
}

bool BoxMatrix::getCoverArea(int& startRow, int& endRow,
                             int& startCol, int& endCol,
                             float left, float bottom,
                             float right, float top)
{
    if(left > m_boxRight || right < m_boxLeft ||
       bottom > m_boxTop || top < m_boxBottom) {
        return false;
    }

    startRow = getRow(bottom);
    endRow = getRow(top);
    startCol = getCol(left);
    endCol = getCol(right);

    return true;
}

} // end of namespace bump

