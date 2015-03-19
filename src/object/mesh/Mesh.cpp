#include "Mesh.h"

#include <iostream>

Mesh::Mesh()
    : isInit(false)
{
}

void Mesh::addVertex(const Eigen::Vector3f &v)
{
  vertices.push_back(Vertex(v));
}

void Mesh::addFaces(const Eigen::Vector3i &f)
{
  faces.push_back(f);
}

void Mesh::drawGeometry(int prg_id, bool usePatch)
{
  if(!isInit)
  {
    isInit = true;
    /*Init buffer object*/
    glGenBuffers(1,&vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices[0])*vertices.size(), vertices[0].position.data(), GL_STATIC_DRAW);

    glGenBuffers(1,&indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(faces[0])*faces.size(), faces[0].data(), GL_STATIC_DRAW);

    glGenVertexArrays(1,&vertexArrayId);
  }
  // bind the vertex array
  glBindVertexArray(vertexArrayId);

  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferId);

  int vertex_loc   = glGetAttribLocation(prg_id, "vPosition");
  int normal_loc   = glGetAttribLocation(prg_id, "vNormal");
  int texcoord_loc = glGetAttribLocation(prg_id, "vTexcoord");
  //
  // specify the vertex data
  if(vertex_loc>=0)
  {
    glVertexAttribPointer(vertex_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(vertex_loc);
  }

  if(normal_loc>=0)
  {
    glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Eigen::Vector3f));
    glEnableVertexAttribArray(normal_loc);
  }

  if(texcoord_loc>=0)
  {
    glVertexAttribPointer(texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2*sizeof(Eigen::Vector3f)));
    glEnableVertexAttribArray(texcoord_loc);
  }

  if(usePatch)
  {
    glPatchParameteri(GL_PATCH_VERTICES, 3);

    // send the geometry
    glDrawElements(GL_PATCHES, 3*faces.size(), GL_UNSIGNED_INT, (void*)0);
  }
  else
  {
    glDrawElements(GL_TRIANGLES, 3*faces.size(), GL_UNSIGNED_INT, (void*)0);
  }
  if(vertex_loc>=0) glDisableVertexAttribArray(vertex_loc);
  if(normal_loc>=0) glDisableVertexAttribArray(normal_loc);
  if(texcoord_loc>=0) glDisableVertexAttribArray(texcoord_loc);
  // release the vertex array
  glBindVertexArray(0);
}

void Mesh::displayInfo()
{
  size_t i;
  std::cout << std::endl;
  std::cout << "Vertex list: " << std::endl;
  for(i=0; i<vertices.size(); i++)
  {
    std::cout << "(" << vertices[i].position[0] << "," << vertices[i].position[1] << "," << vertices[i].position[2] << ")  "; 
  }

  std::cout << std::endl;
  std::cout << "Face list: " << std::endl;
  for(i=0; i<faces.size(); i++)
  {
    std::cout << "(" << faces[i][0] << "," << faces[i][1] << "," << faces[i][2] << ")  "; 
  }
  std::cout << std::endl;

}
