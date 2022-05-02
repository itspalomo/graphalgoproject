#include "edge_w.h"

edge_w::edge_w(unsigned int a, unsigned int b, double c) {
    v = a;
    w = b;
    weight = c;
}
//===========================================================
unsigned int edge_w::either() {
    return v;
}
//===========================================================
unsigned int edge_w::other(unsigned int a) {
    if (a == v) return w;
    else return v;
}
//===========================================================
bool edge_w::operator<(const edge_w& b) const{
    return (this->weight < b.weight);
}
//===========================================================
bool edge_w::operator>(const edge_w& b) const{
    return (this->weight > b.weight);
}
