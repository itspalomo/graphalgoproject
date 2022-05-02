#ifndef EDGE_W_H_INCLUDED
#define EDGE_W_H_INCLUDED

#include <iostream>
using namespace std;

class edge_w{

private:
    unsigned int v,w;
    double weight;

public:
    edge_w(unsigned int a, unsigned int b, double c);
    // Constructor that takes in a for the starting vertex, b for the ending vertex,
    // and c for the weight.

    unsigned int either();
    // Returns one of the vertices attached to this edge

    unsigned int other(unsigned int a);
    // Returns w if a==v
    // else returns v

    bool operator<(const edge_w& b) const;
    bool operator>(const edge_w& b) const;
    // Greater than and less than operator overloads that compare the weights of
    // this edge versus the edge being passed in.
    // Returns a boolean TRUE if the condition is true

    friend istream& operator>>(istream& is, edge_w& b) {
        is >> b.v >> b.w >> b.weight;
        return is;
    }
    // Overloading the input stream operator to allow an edges properties to be modified
    // from an input stream directly

    friend ostream& operator<<(ostream& os, const edge_w& b) {
        os << b.v << "---" << b.w << "\t" << b.weight;
        return os;
    }
    // Overloading the output stream operator to print out the private data members of a
    // weighted edge

    double getWeight() { return weight; }
};
#endif // EDGE_W_H_INCLUDED
