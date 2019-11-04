#include "kf/kf_mesh.h"

void mesh::dump(std::ostream &os)
{
   int vcount,ecount,fcount;
   vcount=vertices.size();
   ecount=edges.size();
   fcount=faces.size();
   int i;

   /*
   createNode mesh -n "testmesh" -p "testtrans";
   setAttr -k off ".v";
   setAttr -s 4 ".vt";
   setAttr ".vt[0:3]"  0.0 0.0 0.0   0.0 1.0 0.0  1.0 1.0 0.0   1.0 0.0 0.0;
   setAttr -s 6 ".ed";
   setAttr ".ed[0:5]"  0 1 0  1 2 0  2 0 0  2 3 0  3 0 0  2 0 0;
   setAttr -s 2 ".fc";
   setAttr ".fc[0:1]" -type "polyFaces" 
      f 3 0 1 2
      f 3 3 4 5;
      */
   os<<"createNode mesh -n \""<<name<<"\";\n";
   os<<"   setAttr -k off \".v\";\n";
   os<<"   setAttr -s "<<vcount<<" \".vt\";\n";
   os<<"   setAttr \".vt[0:"<<vcount-1<<"]\"\n";
   for(i=0;i<vcount;i++)
   {
      os<<"      "<<vertices[i].pos.x<<" "<<vertices[i].pos.z<<" "<<-vertices[i].pos.y;
      if(i!=vcount-1)
      {
         os<<"\n";
      }
   }
   os<<";\n";
   os<<"   setAttr -s "<<ecount<<" \".ed\";\n";
   os<<"   setAttr \".ed[0:"<<ecount-1<<"]\"\n";
   for(i=0;i<ecount;i++)
   {
      os<<"      "<<edges[i].v[0]<<" "<<edges[i].v[1]<<" 0";
      if(i!=ecount-1)
      {
         os<<"\n";
      }
   }
   os<<";\n";
   os<<"   setAttr -s "<<fcount<<" \".fc\";\n";
   os<<"   setAttr \".fc[0:"<<fcount-1<<"]\" -type \"polyFaces\"\n";
   for(i=0;i<fcount;i++)
   {
      os<<"      f 3 "<<faces[i].e[0]<<" "<<faces[i].e[1]<<" "<<faces[i].e[2];
      if(i!=fcount-1)
      {
         os<<"\n";
      }
   }
   os<<";\n";
}

bool compare_edges(const edge &e1, const edge &e2)
{
   if( ((e1.v[0] == e2.v[0]) && (e1.v[1] == e2.v[1])) || ((e1.v[0] == e2.v[1]) && (e1.v[1] == e2.v[0])))
   {
      return true;
   }
   return false;
}

void mesh::add_face(int v1,int v2, int v3)
{
   int e1,e2,e3;
   e1=-1;
   e2=-1;
   e3=-1;
   
   std::vector<edge>::iterator it;
   int i=0;
   for(it=edges.begin();it!=edges.end();it++,i++)
   {
      
      if(compare_edges(*it,edge(v1,v2)))
      {
         e1 = i;
      }
      if(compare_edges(*it,edge(v2,v3)))
      {
         e2 = i;
      }
      if(compare_edges(*it,edge(v3,v1)))
      {
         e3 = i;
      }
   }
   if(e1<0)
   {
      edges.push_back(edge(v1,v2));
      e1=edges.size()-1;
   }
   if(e2<0)
   {
      edges.push_back(edge(v2,v3));
      e2=edges.size()-1;
   }
   if(e3<0)
   {
      edges.push_back(edge(v3,v1));
      e3=edges.size()-1;
   }
   faces.push_back(face(e1,e2,e3));
}

void mesh::add_vertex(const vector3 &v)
{
   vertex v1;
   v1.pos=v;
   vertices.push_back(v1);
}

