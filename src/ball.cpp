#include <cmath>
#include <ctime>
#include <cstdlib>
#include "ball.h"
#include "box.h"
#include "game.h"
#include "log.h"

namespace bump {

float Ball::k_radius;
VertexArray Ball::k_va;
Texture Ball::k_texture;

bool Ball::init(const Config& cfg)
{
    k_radius = cfg.m_ballRadius;

    if(!VertexArray::loadRectVertexArray(k_va, 2*k_radius, 2*k_radius)) {
        LOG_ERROR("Failed to load VertexArray for Ball");
        return false;
    }

    if(!k_texture.load(cfg.m_ballImage)) {
        LOG_ERROR("Failed to load texture for Ball");
        return false;
    }

    return true;
}

Ball::Ball(Game& game)
: GameObject()
, m_game(game)
{
}

Ball::~Ball()
{
}

void Ball::init(float x, float y, float speed)
{
    m_pos[0] = x;
    m_pos[1] = y;
    m_speed = speed;

    float factor = (float)(sqrt(2.0) / 2.0);
    bool moveLeft = ((float)rand() / (float)RAND_MAX) > 0.5f;
    m_speedX = moveLeft ? -m_speed * factor : m_speed * factor;
    m_speedY = speed * factor;
}

void Ball::draw(BumpShaderProgram& program)
{
    program.setUseObjRef(true);
    program.setObjRef(m_pos);
    program.setPosition(k_va);
    program.setTexture(k_texture.textureId());
    program.setUseColor(false);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0);
}

bool Ball::update(float timeDelta)
{
    CollideImpact finalImpact, impact;
    bool collide = false;

    collide = collideBoundary(finalImpact, timeDelta);

    const Bat& bat = m_game.bat();
    if(collideRect(impact, bat.x(), bat.y(), bat.right(),
                   bat.top(), timeDelta)) {

        if(!collide || impact.m_collideTime < finalImpact.m_collideTime) {
            collide = true;
            finalImpact = impact;
        }
    }

    Box* box = nullptr;
    int row, col;

    if(collideBoxMatrix(impact, box, row, col, timeDelta)) {
        if(!collide || impact.m_collideTime < finalImpact.m_collideTime) {
            collide = true;
            finalImpact = impact;
        }
    }

    if(!collide) {
        m_pos[0] += m_speedX * timeDelta;
        m_pos[1] += m_speedY * timeDelta;
    } else {
        m_pos[0] = finalImpact.m_newCenterX;
        m_pos[1] = finalImpact.m_newCenterY;
        m_speedX = finalImpact.m_newSpeedX;
        m_speedY = finalImpact.m_newSpeedY;

        if(box) {
            if(!box->onHit()) {
                m_game.boxMatrix().clearBox(row, col);
            }
        }
    }

    return m_pos[1] > -k_radius;
}


bool Ball::collideBat(float& newLeft, float targetLeft)
{
    float collideX, collideY;
    const Bat& bat = m_game.bat();
    CollideResult result = rectCollideCircleHorizontal(newLeft,
                                 collideX, collideY,
                                 bat.x(), bat.y(),
                                 bat.x() + bat.width(), bat.y() + bat.height(),
                                 targetLeft,
                                 m_pos[0], m_pos[1], k_radius);

    if(result == COLLIDE_NOTHING) {
        return false;
    }

    getNewSpeed(m_speedX, m_speedY,
                result, m_pos[0], m_pos[1],
                collideX, collideY);

    return true;
}

bool Ball::collideBoundary(CollideImpact& impact, float timeDelta)
{
    float tx = m_pos[0];
    float ty = m_pos[1];
    CollideResult result;

    result = circleCollideLine(impact.m_collideTime,
                               impact.m_newCenterX,
                               tx, k_radius, m_speedX,
                               0, true,
                               timeDelta);

    if(result == COLLIDE_INTIME) {
        impact.m_newCenterY = ty + m_speedY * impact.m_collideTime;
        impact.m_newSpeedX = -m_speedX;
        impact.m_newSpeedY = m_speedY;
        return true;
    }

    result = circleCollideLine(impact.m_collideTime,
                               impact.m_newCenterX,
                               tx, k_radius, m_speedX,
                               m_game.width(), false,
                               timeDelta);

    if(result == COLLIDE_INTIME) {
        impact.m_newCenterY = ty + m_speedY * impact.m_collideTime;
        impact.m_newSpeedX = -m_speedX;
        impact.m_newSpeedY = m_speedY;
        return true;
    }

    result = circleCollideLine(impact.m_collideTime,
                               impact.m_newCenterY,
                               ty, k_radius, m_speedY,
                               m_game.height(), false,
                               timeDelta);

    if(result == COLLIDE_INTIME) {
        impact.m_newCenterX = tx + m_speedX * impact.m_collideTime;
        impact.m_newSpeedX = m_speedX;
        impact.m_newSpeedY = -m_speedY;
        return true;
    }

    return false;
}

bool Ball::collideRect(CollideImpact &impact,
                       float left, float bottom, float right, float top,
                       float timeDelta)
{
    float tx = m_pos[0];
    float ty = m_pos[1];
    CollideResult result;
    float collideX, collideY;

    result = circleCollideRect(impact.m_collideTime,
                               impact.m_newCenterX, impact.m_newCenterY,
                               collideX, collideY,
                               tx, ty, k_radius,
                               m_speedX, m_speedY,
                               left, bottom, right, top,
                               timeDelta);

    if(result == COLLIDE_NOTHING) {
        return false;
    }

    getNewSpeed(impact.m_newSpeedX, impact.m_newSpeedY,
                result, impact.m_newCenterX, impact.m_newCenterY,
                collideX, collideY);

    return true;
}

bool Ball::collideBoxMatrix(CollideImpact& impact, Box*& box,
                            int& row, int& col, float timeDelta)
{
    int startRow, endRow, startCol, endCol;

    if(!getCoveredBox(startRow, endRow, startCol, endCol, timeDelta)) {
        return false;
    }

    bool collide = false, collide1;
    BoxMatrix& matrix = m_game.boxMatrix();
    Box *b;
    CollideImpact impact1;

    for(int r = startRow; r <= endRow; ++r) {
        for(int c = startCol; c <= endCol; ++c) {
            b = matrix.getBox(r, c);
            if(b == nullptr) {
                continue;
            }

            collide1 = collideRect(impact1, b->x(), b->y(),
                                   b->right(), b->top(), timeDelta);

            if(!collide1) {
                continue;
            }

            if(!collide || impact1.m_collideTime < impact.m_collideTime) {
                collide = true;
                box = b;
                row = r;
                col = c;
                impact = impact1;
            }
        }
    }

    return collide;
}

bool Ball::getCoveredBox(int& startRow, int& endRow,
                         int& startCol, int& endCol,
                         float timeDelta)
{
    float newX = m_pos[0] + m_speedX * timeDelta;
    float newY = m_pos[1] + m_speedY * timeDelta;
    float left = std::min(newX, m_pos[0]) - k_radius;
    float right = std::max(newX, m_pos[0]) + k_radius;
    float bottom = std::min(newY, m_pos[1]) - k_radius;
    float top = std::max(newY, m_pos[1]) + k_radius;
    BoxMatrix& matrix = m_game.boxMatrix();

    bool covered = matrix.getCoverArea(startRow, endRow, startCol, endCol,
                                       left, bottom, right, top);

    return covered;
}


void Ball::getNewSpeed(float& speedX, float& speedY,
                       CollideResult result,
                       float centerX, float centerY,
                       float collideX, float collideY)
{
    switch(result) {
    case COLLIDE_HORIZONTAL:
        speedX = m_speedX;
        speedY = -m_speedY;
        break;

    case COLLIDE_VERTICAL:
        speedX = -m_speedX;
        speedY = m_speedY;
        break;

    case COLLIDE_POINT:
        {
            float deltaX = centerX - collideX;
            float deltaY = centerY - collideY;
            float dist = sqrt(deltaX * deltaX + deltaY * deltaY);
            speedX = m_speed * deltaX / dist;
            speedY = m_speed * deltaY / dist;
        }
        break;
    }
}

} // end of namespace bump

