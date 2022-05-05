#ifndef vertex_h
#define vertex_h

struct Vertex{
    int ID;                                     // unique vertex identifier
    int d;                                      // min total depth from source
    int p;                                      // predecessor vertex
    int w;                                      // weight from predecessor
    bool c;                                     // vertex 'color' to indicate if visited

    Vertex* adj;

    Vertex() : ID(-1), d(INT_MAX), p(0), w(0), c(0), adj(NULL) {}

    bool operator<(const Vertex v) {return (this->d < v.d);}
    bool operator<(const Vertex* v) {return (this->d < v->d);}
    bool operator>(const Vertex v) {return (this->d > v.d);}
    bool operator>(const Vertex* v) {return (this->d > v->d);}
    bool operator==(const Vertex v) {return (this->ID==v.ID);}
    bool operator==(const Vertex* v) {return (this->ID==v->ID);}
    Vertex& operator=(const Vertex v) {
        this->ID = v.ID;
        this->d = v.d;
        this->p = v.p;
        this->w = v.w;
        this->c = v.c;
        this->adj = v.adj;
        return *this;
    }
    Vertex* operator=(const Vertex* v) {
        this->ID = v->ID;
        this->d = v->d;
        this->p = v->p;
        this->w = v->w;
        this->c = v->c;
        this->adj = v->adj;
        return this;
    }
};

#endif