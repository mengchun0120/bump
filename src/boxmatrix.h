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

    BoxMatrix(Game& game);

    virtual ~BoxMatrix();

    void init();

    void clear();

    Box *getBox(int row, int col)
    {
        return m_boxes[row][col];
    }

    void draw(BumpShaderProgram& program);

private:
    Box *m_boxes[NUM_ROWS][NUM_COLS];
    int m_boxCount;
    float m_boxLeft, m_boxBottom;
    float m_spacing;
};

} // end of namespace bump

#endif
