#include "MeshLoader.h"

#include <iostream>
#include <fstream>
#include <istream>

Mesh * MeshLoader::loadMesh(const std::string& filename)
{
  Mesh * mesh;
  int extOffset = filename.find_last_of('.')+1;  
  std::string ext = filename.substr(extOffset, filename.size()-extOffset);
  if(ext.compare("obj") == 0 || ext.compare("OBJ") == 0)
  {
    mesh = loadObj(filename);
  }
  else
  {
    std::cerr << "MeshLoader: loadMesh: extension not supported : " << ext << std::endl;
  }
  return mesh;
}

Mesh * MeshLoader::loadObj(const std::string& filename)
{
  std::ifstream file(filename.c_str());
  if (!file) 
  { 
    std::cerr << "MeshLoader: loadObj: Cannot open " << filename << std::endl; 
    exit(1); 
  }

  /* Temporary storage */
  std::vector<Eigen::Vector3f> vertices;
  std::vector<Eigen::Vector2f> texCoord;
  std::vector<Eigen::Vector3f> normales;
  std::vector<Eigen::Vector3i> vfaces;
  std::vector<Eigen::Vector3i> nfaces;
  std::vector<Eigen::Vector3i> rfaces;

  Eigen::Vector3f * v;
  Eigen::Vector3f * t;
  Eigen::Vector3f * n;
  Eigen::Vector3i * f;

  std::string line;
  while(!file.eof())
  {
    getline(file, line);
    if(line.size() > 2)
    {
      if(line.substr(0,2).compare("v ") == 0)
      {
        std::stringstream s(line.substr(2));
        v = new Eigen::Vector3f();
        float tmp;
        s >> tmp;
        v[0][0] = tmp;
        s >> tmp;
        v[0][2] = tmp;
        s >> tmp;
        v[0][1] = tmp;
        vertices.push_back(*v);
      }/*
          else if(line.substr(0,3).compare("vt "))
          {
          stringstream s(line.substr(3));
          t = new Eigen::Vector2f();
          s >> t[0]; s >> t[1];
          texCoord.push_back(t);
          }
          else if(line.substr(0,3).compare("vn "))
          {
          stringstream s(line.substr(3));
          n = new Eigen::Vector3f();
          s >> n[0]; s >> n[1]; s >> n[2]; 
          normales.push_back(n);
          }*/
      else if(line.substr(0,2).compare("f ") == 0)
      {
        std::stringstream s(line.substr(2));
        f = new Eigen::Vector3i();
        int tmp;
        s >> tmp;
        f[0][0] = tmp-1;
        s >> tmp;
        f[0][1] = tmp-1;
        s >> tmp;
        f[0][2] = tmp-1;
        vfaces.push_back(*f);
      }
    }
  }

  Mesh * mesh = new Mesh();
  int i;
  for(i=0; i<vertices.size(); i++)
  {
    mesh->addVertex(vertices[i]);
  }
  for(i=0; i<vfaces.size(); i++)
  {
    mesh->addFaces(vfaces[i]);
  }
  return mesh;
}

