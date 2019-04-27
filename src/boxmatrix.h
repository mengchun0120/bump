#ifndef INCLUDE_BOXMATRIX
#define INCLUDE_BOXMATRIX

namespace bump {

class Box;
class BumpShaderProgram;
class Game;

class BoxMatrix {
public:
    static const unsigned int NUM_ROWS = 5;
    static const unsigned int NUM_COLS = 7;

    static int clampRow(int row);

    static int clampCol(int col);

    BoxMatrix(Game& game);

    virtual ~BoxMatrix();

    void init();

    void clear();

    Box *getBox(int row, int col)
    {
        return m_boxes[row][col];
    }

    void clearBox(int row, int col);

    void draw(BumpShaderProgram& program);

    float left() const
    {
        return m_boxLeft;
    }

    float bottom() const
    {
        return m_boxBottom;
    }

    bool getCoverArea(int& startRow, int& endRow, int& startCol, int& endCol,
                      float left, float bottom, float right, float top);

    int getRow(float y);

    int getCol(float x);

    int boxCount() const
    {
        return m_boxCount;
    }

private:
    Box *m_boxes[NUM_ROWS][NUM_COLS];
    int m_boxCount;
    float m_boxLeft, m_boxBottom, m_boxRight, m_boxTop;
    float m_spacing;
    float m_colWidth, m_rowHeight;
};

} // end of namespace bump

#endif
