#include "Mesh.h"

#include <iostream>

Mesh::Mesh()
  : m_isInit(false)
{
}

void
Mesh::addVertex(const Eigen::Vector3f& v)
{
  m_vertices.push_back(Vertex(v));
}

void
Mesh::addFaces(const Eigen::Vector3i& f)
{
  m_faces.push_back(f);
}

void
Mesh::drawGeometry(int prg_id, bool usePatch)
{
  if (!m_isInit)
  {
    m_isInit = true;
    /*Init buffer object*/
    glGenBuffers(1, &m_vertexBufferId);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_vertices[0]) * m_vertices.size(), m_vertices[0].position.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_indexBufferId);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_faces[0]) * m_faces.size(), m_faces[0].data(), GL_STATIC_DRAW);

    glGenVertexArrays(1, &m_vertexArrayId);
  }
  // bind the vertex array
  glBindVertexArray(m_vertexArrayId);

  glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferId);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferId);

  int vertex_loc   = glGetAttribLocation(prg_id, "vPosition");
  int normal_loc   = glGetAttribLocation(prg_id, "vNormal");
  int texcoord_loc = glGetAttribLocation(prg_id, "vTexcoord");
  //
  // specify the vertex data
  if (vertex_loc >= 0)
  {
    glVertexAttribPointer(vertex_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
    glEnableVertexAttribArray(vertex_loc);
  }

  if (normal_loc >= 0)
  {
    glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)sizeof(Eigen::Vector3f));
    glEnableVertexAttribArray(normal_loc);
  }

  if (texcoord_loc >= 0)
  {
    glVertexAttribPointer(texcoord_loc, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)(2*sizeof(Eigen::Vector3f)));
    glEnableVertexAttribArray(texcoord_loc);
  }

  if (usePatch)
  {
    glPatchParameteri(GL_PATCH_VERTICES, 3);

    // send the geometry
    glDrawElements(GL_PATCHES, 3 * m_faces.size(), GL_UNSIGNED_INT, (void*)0);
  }
  else
  {
    glDrawElements(GL_TRIANGLES, 3 * m_faces.size(), GL_UNSIGNED_INT, (void*)0);
  }

  if (vertex_loc >= 0)
    glDisableVertexAttribArray(vertex_loc);

  if (normal_loc >= 0)
    glDisableVertexAttribArray(normal_loc);

  if (texcoord_loc >= 0)
    glDisableVertexAttribArray(texcoord_loc);

  // release the vertex array
  glBindVertexArray(0);
}

void
Mesh::displayInfo()
{
  size_t i;
  std::cout << std::endl;
  std::cout << "Vertex list: " << std::endl;
  for (i = 0; i < m_vertices.size(); i++)
  {
    std::cout << "(" << m_vertices[i].position[0] << "," << m_vertices[i].position[1] << "," << m_vertices[i].position[2] << ")  ";
  }

  std::cout << std::endl;
  std::cout << "Face list: " << std::endl;
  for(i = 0; i < m_faces.size(); i++)
  {
    std::cout << "(" << m_faces[i][0] << "," << m_faces[i][1] << "," << m_faces[i][2] << ")  ";
  }
  std::cout << std::endl;
}
