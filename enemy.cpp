#include "enemy.h"
#include "Franklin.h"
#include <QGraphicsScene>
#include <QList>
#include <stdlib.h>
#include <QTimer>
#include <QDebug>
#include <QPair>
#include <map>
#include <set>
#include "bullet.h"
#include "lose.h"

#define ROW 12
#define COL 12
extern rect* r;
using namespace std;



Enemy::Enemy(int boardData[12][12], int r, int c,lose *l[1]){

    // Set Image of the enemy
    QPixmap image("A:\\proj\\project-main\\project-main\\images\\frame-1.png");
        image = image.scaledToWidth(30);
        image = image.scaledToHeight(30);
        setPixmap(image);
  // Set Position
        row = r;
        column =c;
        setPos(50 + column * 50, 50 + row * 50);

        this->l=l ;
 // Set data Array
    for (int i = 0; i < 12; i++)
           for (int j = 0; j < 12; j++)
               data[i][j] = boardData[i][j];
    // calling the move function periodically so it moves every certain amount of time
    QTimer * timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(500);
//    QTimer * timer2 = new QTimer(this);
//    connect(timer2,SIGNAL(timeout()),this,SLOT(findpath(row, column, r->row, r->column)));
//    timer2->start(250);

}

void Enemy::move(){
    // move enemy
    //if((row == r->row && column == r->column))

        QList<QGraphicsItem *> colliding_items_enemy = collidingItems();
        for (int i =0, n=colliding_items_enemy.size(); i<n; i++){
            if (typeid(*(colliding_items_enemy[i]))==typeid(rect)){
                rect * franklin = dynamic_cast<rect*>(colliding_items_enemy[i]);
                           if(franklin->angry)
                           {
                               continue;
                           }
                            else
                           {
                             franklin->life -- ;
                           }
                           if (franklin->life== 0)
                           {
                               scene()->addItem(l[0]);
                               l[0]->setPos(50 + -2 * 50, 50 + -2 * 50);
                           }
            }
        }

    if (!(row == r->row && column == r->column))
    {
        if(path.empty())
            findpath(row, column, r->row, r->column);
        row=path.begin()->row;
        column=path.begin()->col;
        path.pop_front();
        qDebug() << data[row][column];
        setPos(50*column + 50,50*row + 50);
    }




/*
    QList<QGraphicsItem *> colliding_items_enemy = collidingItems();
    for (int i =0, n=colliding_items_enemy.size(); i<n; i++){
        if (typeid(*(colliding_items_enemy[i]))==typeid(rect)){
            rect * franklin = dynamic_cast<rect*>(colliding_items_enemy[i]);
                       if(franklin->angry)
                       {
                           continue;
                       }
                        else
                       {
                         franklin->life -- ;
                       }
                       if (franklin->life== 0)
                       {
                           scene()->addItem(l[0]);
                           l[0]->setPos(50 + -2 * 50, 50 + -2 * 50);
                       }


            data[12][12];







        }
    }
    */


}


void Enemy::findpath(int startingRow, int startingCol, int finalRow, int finalCol)
{
    if( (finalRow == startingRow + 1 && finalCol == startingCol) || (finalRow == startingRow - 1 && finalCol == startingCol) || (finalRow == startingRow && finalCol == startingCol-1) || (finalRow == startingRow && finalCol == startingCol+1) )
    {
        Node point(finalRow, finalCol, -1, -1, 0, 0);
        path.push_front(point);
    }
    else
    {

        Node allNodes[12][12];
        for (int i = 0; i < 12; i++)
            for (int j = 0; j < 12; j++)
                updateAllNodes(allNodes, i, j, -1, -1, INT_MAX, INT_MAX);
        QVector<Node> openNodes;
        QVector<Node> closedNodes;
        Node currentNode(startingRow, startingCol, -1, -1, 0, getDistance(startingRow, startingCol, finalRow, finalCol));   //initializes starting Node that starts from the place of the boss
        updateAllNodes(allNodes, currentNode.row, currentNode.col, currentNode.parentRow, currentNode.parentCol, currentNode.gCost, currentNode.hCost); // updates the starting Node in allNodes with its new parents and such
        openNodes.push_back(currentNode);   // pushes it as the first step for the boss to take (idk if this is useful or not but it was in the main code)

        while (!openNodes.empty())  // works until openNodes is empty (idk where this exactly functions im very sleepy and its 5:47 am)
        {
            sort(openNodes);
            currentNode = openNodes[0];
            openNodes.pop_front();

            if ((currentNode.row == finalRow) && (currentNode.col == finalCol)) //checks if we entered the final target
            {
                while (currentNode.parentRow != -1) // as long as it is not the starting point with -ve parents
                {
                    path.insert(path.begin(), currentNode); // haydakhal el current fi el path
                    currentNode = allNodes[currentNode.parentRow][currentNode.parentCol];   // makes the current node equals to its parents so it could follow the path from target to boss loc
                }
                path.insert(path.begin(), currentNode);
            }


            bool exists = false;    //to check if it already exists in the closedNodes and/or openNodes
            bool flag = false;      //instead of break for sarah
            int neighbourRow = currentNode.row - 1, neighbourCol = currentNode.col;
            if (data[neighbourRow][neighbourCol] >= 0)
                //checks if next step is acceptable or not
            {
                float gCost = getDistance(startingRow, startingCol, currentNode.row, currentNode.col) + getDistance(currentNode.row, currentNode.col, neighbourRow, neighbourCol);
                Node north(neighbourRow, neighbourCol, currentNode.row, currentNode.col, gCost, getDistance(neighbourRow, neighbourCol, finalRow, finalCol));
                for (int i = 0; i < closedNodes.size() && !exists; i++)
                    if (closedNodes[i] == north)
                    {
                        exists = true;
                        //if it exists in closed then we dont want it.
                    }
                for (int i = 0; i < openNodes.size() && !flag; i++)
                    if (openNodes[i] == north)
                    {
                        exists = true;
                        if (openNodes[i].fCost <= north.fCost)
                            flag = true;    //if it already exists in openNodes with a lower value then we dont want it
                        else
                        {
                            openNodes[i].fCost = north.fCost;
                            updateAllNodes(allNodes, north.row, north.col, north.parentRow, north.parentCol, north.gCost, north.hCost); // if this has a less value than the previous we update it
                        }
                    }
                if (!exists)
                {
                    openNodes.push_back(north);
                    updateAllNodes(allNodes, north.row, north.col, north.parentRow, north.parentCol, north.gCost, north.hCost);
                    //if it doesnt exist in either, we add it to the OpenNodes
                }
            }



            exists = false;
            flag = false;
            neighbourRow = currentNode.row, neighbourCol = currentNode.col + 1;
            if (data[neighbourRow][neighbourCol] >= 0)
            {
                float gCost = getDistance(startingRow, startingCol, currentNode.row, currentNode.col) + getDistance(currentNode.row, currentNode.col, neighbourRow, neighbourCol);
                Node east(neighbourRow, neighbourCol, currentNode.row, currentNode.col, gCost, getDistance(neighbourRow, neighbourCol, finalRow, finalCol));
                for (int i = 0; i < closedNodes.size() && !exists; i++)
                    if (closedNodes[i] == east)
                    {
                        exists = true;
                    }
                for (int i = 0; i < openNodes.size() && !flag; i++)
                    if (openNodes[i] == east)
                    {
                        exists = true;
                        if (openNodes[i].fCost <= east.fCost)
                            flag = true;
                        else
                        {
                            openNodes[i].fCost = east.fCost;
                            updateAllNodes(allNodes, east.row, east.col, east.parentRow, east.parentCol, east.gCost, east.hCost);
                        }
                    }
                if (!exists)
                {
                    openNodes.push_back(east);
                    updateAllNodes(allNodes, east.row, east.col, east.parentRow, east.parentCol, east.gCost, east.hCost);
                }
            }

            exists = false;
            flag = false;
            neighbourRow = currentNode.row, neighbourCol = currentNode.col - 1;
            if (data[neighbourRow][neighbourCol] >= 0)
            {
                float gCost = getDistance(startingRow, startingCol, currentNode.row, currentNode.col) + getDistance(currentNode.row, currentNode.col, neighbourRow, neighbourCol);
                Node west(neighbourRow, neighbourCol, currentNode.row, currentNode.col, gCost, getDistance(neighbourRow, neighbourCol, finalRow, finalCol));
                for (int i = 0; i < closedNodes.size() && !exists; i++)
                    if (closedNodes[i] == west)
                    {
                        exists = true;
                    }
                for (int i = 0; i < openNodes.size() && !flag; i++)
                    if (openNodes[i] == west)
                    {
                        exists = true;
                        if (openNodes[i].fCost <= west.fCost)
                            flag = true;
                        else
                        {
                            openNodes[i].fCost = west.fCost;
                            updateAllNodes(allNodes, west.row, west.col, west.parentRow, west.parentCol, west.gCost, west.hCost);
                        }
                    }
                if (!exists)
                {
                    openNodes.push_back(west);
                    updateAllNodes(allNodes, west.row, west.col, west.parentRow, west.parentCol, west.gCost, west.hCost);
                }
            }



            exists = false;
            flag = false;
            neighbourRow = currentNode.row + 1, neighbourCol = currentNode.col;
            if (data[neighbourRow][neighbourCol] >= 0)
            {
                float gCost = getDistance(startingRow, startingCol, currentNode.row, currentNode.col) + getDistance(currentNode.row, currentNode.col, neighbourRow, neighbourCol);
                Node south(neighbourRow, neighbourCol, currentNode.row, currentNode.col, gCost, getDistance(neighbourRow, neighbourCol, finalRow, finalCol));
                for (int i = 0; i < closedNodes.size() && !exists; i++)
                    if (closedNodes[i] == south)
                    {
                        exists = true;
                    }
                for (int i = 0; i < openNodes.size() && !flag; i++)
                    if (openNodes[i] == south)
                    {
                        exists = true;
                        if (openNodes[i].fCost <= south.fCost)
                            flag = true;
                        else
                        {
                            openNodes[i].fCost = south.fCost;
                            updateAllNodes(allNodes, south.row, south.col, south.parentRow, south.parentCol, south.gCost, south.hCost);
                        }
                    }
                if (!exists)
                {
                    openNodes.push_back(south);
                    updateAllNodes(allNodes, south.row, south.col, south.parentRow, south.parentCol, south.gCost, south.hCost);
                }
            }



            closedNodes.push_back(currentNode); //since we already used the currentNode and inputted it, we add it to the closedNodes
        }
    }
}


float Enemy:: getDistance(int x1, int y1, int x2, int y2)
{
    float deltaX = x1 - x2;
    float deltaY = y1 - y2;
    return sqrt((deltaX * deltaX) + (deltaY * deltaY));
}

void Enemy::sort(QVector<Node> nodes)
{
    for (int i = 0; i < nodes.size(); i++)
    {
        for (int j = i + 1; j < nodes.size(); j++)
        {
            if (nodes[j].fCost < nodes[i].fCost){
               Node temp;
               temp= nodes[i];
               nodes[i]=nodes[j];
               nodes[j]=temp;
            }
        }
    }
}

void Enemy::updateAllNodes(Node allNodes[12][12], int row, int col, int pRow, int pCol, float gCost, float hCost)
{
    allNodes[row][col].row = row;
    allNodes[row][col].col = col;
    allNodes[row][col].parentRow = pRow;
    allNodes[row][col].parentCol = pCol;
    allNodes[row][col].gCost = gCost;
    allNodes[row][col].hCost = hCost;
    allNodes[row][col].fCost = gCost + hCost;
}


