#ifndef vertex_h
#define vertex_h

struct Vertex{
    int ID;                                     // unique vertex identifier
    int d;                                      // min total depth from source
    int p;                                      // predecessor vertex
    bool c;                                     // vertex 'color' to indicate if visited

    Vertex() : ID(-1), qID(-1), d(INT_MAX), p(0), c(0) {}

    bool operator<(const Vertex v) {return (this->d < v.d);}
    bool operator>(const Vertex v) {return (this->d > v.d);}
    bool operator==(const Vertex v) {return (this->ID==v.ID);}
    Vertex& operator=(const Vertex v) {
        this->ID = v.ID;
        this->qID = v.qID;
        this->d = v.d;
        this->p = v.p;
        this->c = v.c;
        return *this;
    }
};

#endif