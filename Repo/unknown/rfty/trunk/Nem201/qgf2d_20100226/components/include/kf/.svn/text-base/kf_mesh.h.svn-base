#ifndef KF_MESH_H
#define KF_MESH_H
#include "kf/kf_types.h"
#include "kf/kf_vector.h"
#include "kf/kgl_colour.h"
#include <vector>
#include <ostream>

class vertex
{
public:
   vector3 pos;
};

class edge
{
public:
   edge(int v1,int v2) {v[0]=v1; v[1]=v2;}
   int v[2];
};

class face
{
public:
   face(int e1, int e2, int e3) {e[0]=e1; e[1]=e2; e[2]=e3;}
   int e[3];
};

class mesh
{
public:
   mesh(const std::string &n) {name=n;}
   std::string name;
   std::vector<vertex> vertices;
   std::vector<edge> edges;
   std::vector<face> faces;
   void dump(std::ostream &os);
   void add_face(int v1,int v2, int v3);
   void add_vertex(const vector3 &v);
};




#endif