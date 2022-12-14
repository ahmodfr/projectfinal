#include "node.h"

/// Do not use. This is just here so Nodes can be stored in Maps. // TODO: find a way to make it work w/o this useless constructor.
Node::Node(){

}

/// Constructs a Node with the specified x and y values.
Node::Node( int x,  int y): x_(x), y_(y){

}

/// Returns the x value of the Node.
int Node::x() const{
    return x_;
}

/// Returns the y value of the Node.
int Node::y() const{
    return y_;
}

/// Sets the x value of the Node.
void Node::setX( int x){
    x_ = x;
}

/// Sets the y value of the Node.
void Node::setY( int y){
    y_ = y;
}

/// Returns true if both Nodes have the same x and y values.
bool operator==(const Node &lhs, const Node &rhs){
    return (lhs.x() == rhs.x()) && (lhs.y() == rhs.y());
}
