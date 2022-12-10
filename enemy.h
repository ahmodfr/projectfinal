#ifndef ENEMY_H
#define ENEMY_H

#include <QKeyEvent>
#include <QList>
#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>
#include <map>
#include <QKeyEvent>
#include "lose.h"
using namespace std;

struct Node
{
    int row;
    int col;
    int parentRow;
    int parentCol;
    float gCost; // cost of moving from the starting node to this node
    float hCost; // estimated cost of moving from this node to the final node
    float fCost; // gCost + hCost
    Node() {}
    Node(int _row, int _col, int _parentRow, int _parentCol, float _gCost, float _hCost)
    {
        row = _row;
        col = _col;
        parentRow = _parentRow;
        parentCol = _parentCol;
        gCost = _gCost;
        hCost = _hCost;
        fCost = gCost + hCost;
    }
    bool operator==(const Node& rhs)
    {
        if (row == rhs.row && col == rhs.col)
            return true;
        return false;
    }
};

class Enemy: public QObject, public QGraphicsPixmapItem{
    Q_OBJECT
public:
    Enemy(int boardData[12][12], int rows, int columns, lose *l[1]);
    QVector<Node> path;
    int life=2;
    bool dead = false;
    lose **l;
    int lives =2;
    int row, column;
    pair<int, int> findPath(int, int);

    int getrow();
     int getcolumn();
     void updateAllNodes(Node[12][12], int, int, int, int, float, float);
     void sort(QVector<Node> nodes);
     float getDistance(int x1, int y1, int x2, int y2);
private:

    int data[12][12];

public slots:
    void move();
    void findpath(int, int, int, int);

};

#endif // ENEMY_H
