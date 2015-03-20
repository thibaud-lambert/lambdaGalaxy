#include "StarField.h"

StarField::StarField()
  : m_chunkGrid(NULL)
  , m_position(0.0f, 0.0f, 0.0f)
{
}


void
StarField::init(const Eigen::Vector3f& pos)
{
  int i, j, k;
  m_position[0] = floor(pos[0] / CHUNK_SIZE) - CHUNK_NUMBER / 2;
  m_position[1] = floor(pos[1] / CHUNK_SIZE) - CHUNK_NUMBER / 2;
  m_position[2] = floor(pos[2] / CHUNK_SIZE) - CHUNK_NUMBER / 2;
  m_chunkGrid = new Chunk***[CHUNK_NUMBER + 3];
  for (i = 0; i < CHUNK_NUMBER; i++)
  {
    m_chunkGrid[i] = new Chunk**[CHUNK_NUMBER];
    for (j = 0; j < CHUNK_NUMBER; j++)
    {
      m_chunkGrid[i][j] = new Chunk*[CHUNK_NUMBER];
      for (k = 0; k < CHUNK_NUMBER; k++)
      {
        m_chunkGrid[i][j][k] = new Chunk(m_position[0] + i, m_position[1] + j, m_position[2] + k);
      }
    }
  }
}

void
StarField::updateDelete(int x, int y, int z)
{
  int i, j, k;
  // Update along X
  if (x < 0)
  {
    for (i = CHUNK_NUMBER + x; i < CHUNK_NUMBER; i++)
    {
      for (j = 0; j < CHUNK_NUMBER; j++)
      {
        for (k = 0; k < CHUNK_NUMBER; k++)
        {
          if (m_chunkGrid[i][j][k] != NULL)
          {
            delete m_chunkGrid[i][j][k];
            m_chunkGrid[i][j][k] = NULL;
          }
        }
      }
    }
  }
  else if (x > 0)
  {
    for (i = 0; i < x; i++)
    {
      for (j = 0; j < CHUNK_NUMBER; j++)
      {
        for (k = 0; k < CHUNK_NUMBER; k++)
        {
          if (m_chunkGrid[i][j][k] != NULL)
          {
            delete m_chunkGrid[i][j][k];
            m_chunkGrid[i][j][k] = NULL;
          }
        }
      }
    }
  }

  // Update along Y
  if (y < 0)
  {
    for (i = 0; i < CHUNK_NUMBER; i++)
    {
      for (j = CHUNK_NUMBER - y; j < CHUNK_NUMBER; j++)
      {
        for (k = 0; k < CHUNK_NUMBER; k++)
        {
          if (m_chunkGrid[i][j][k] != NULL)
          {
            delete m_chunkGrid[i][j][k];
            m_chunkGrid[i][j][k] = NULL;
          }
        }
      }
    }
  }
  else if (y > 0)
  {
    for (i = 0; i < CHUNK_NUMBER; i++)
    {
      for (j = 0; j < y; j++)
      {
        for (k = 0; k < CHUNK_NUMBER; k++)
        {
          if (m_chunkGrid[i][j][k] != NULL)
          {
            delete m_chunkGrid[i][j][k];
            m_chunkGrid[i][j][k] = NULL;
          }
        }
      }
    }
  }

  // Update along Z
  if (z < 0)
  {
    for (i = 0; i < CHUNK_NUMBER; i++)
    {
      for (j = 0; j < CHUNK_NUMBER; j++)
      {
        for (k = CHUNK_NUMBER+z; k < CHUNK_NUMBER; k++)
        {
          if (m_chunkGrid[i][j][k] != NULL)
          {
            delete m_chunkGrid[i][j][k];
            m_chunkGrid[i][j][k] = NULL;
          }
        }
      }
    }
  }
  else if (z > 0)
  {
    for (i = 0; i < CHUNK_NUMBER; i++)
    {
      for (j = 0; j < CHUNK_NUMBER; j++)
      {
        for (k = 0; k < z; k++)
        {
          if (m_chunkGrid[i][j][k] != NULL)
          {
            delete m_chunkGrid[i][j][k];
            m_chunkGrid[i][j][k] = NULL;
          }
        }
      }
    }
  }
}

void
StarField::updateMove(int x, int y, int z)
{
  int i, j, k;
  // Move along x
  if (x < 0)
  {
    for (i = CHUNK_NUMBER - 1 + x; i > 0; i--)
    {
      for (j = 0; j < CHUNK_NUMBER; j++)
      {
        for (k = 0; k < CHUNK_NUMBER; k++)
        {
          m_chunkGrid[i - x][j][k] = m_chunkGrid[i][j][k];
          m_chunkGrid[i][j][k] = NULL;
        }
      }
    }
  }
  else if (x > 0)
  {
    for (i = x; i < CHUNK_NUMBER; i++)
    {
      for (j = 0; j < CHUNK_NUMBER; j++)
      {
        for (k = 0; k < CHUNK_NUMBER; k++)
        {
          m_chunkGrid[i - x][j][k] = m_chunkGrid[i][j][k];
          m_chunkGrid[i][j][k] = NULL;
        }
      }
    }
  }


  // Move along y
  if (y < 0)
  {
    for (i = 0; i < CHUNK_NUMBER; i++)
    {
      for (j = CHUNK_NUMBER - 1 + y; j > 0; j--)
      {
        for (k = 0; k < CHUNK_NUMBER; k++)
        {
          m_chunkGrid[i][j - y][k] = m_chunkGrid[i][j][k];
          m_chunkGrid[i][j][k] = NULL;
        }
      }
    }
  }
  else if (y > 0)
  {
    for (i = 0; i < CHUNK_NUMBER; i++)
    {
      for (j = y; j < CHUNK_NUMBER; j++)
      {
        for (k = 0; k < CHUNK_NUMBER; k++)
        {
          m_chunkGrid[i][j - y][k] = m_chunkGrid[i][j][k];
          m_chunkGrid[i][j][k] = NULL;
        }
      }
    }
  }

  // Move along z
  if (z < 0)
  {
    for (i = 0; i < CHUNK_NUMBER; i++)
    {
      for (j = 0; j < CHUNK_NUMBER; j++)
      {
        for (k = CHUNK_NUMBER - 1 + z; k > 0; k--)
        {
          m_chunkGrid[i][j][k - z] = m_chunkGrid[i][j][k];
          m_chunkGrid[i][j][k] = NULL;
        }
      }
    }
  }
  else if (z > 0)
  {
    for (i = 0; i < CHUNK_NUMBER; i++)
    {
      for (j = 0; j < CHUNK_NUMBER; j++)
      {
        for (k =z; k < CHUNK_NUMBER; k++)
        {
          m_chunkGrid[i][j][k - z] = m_chunkGrid[i][j][k];
          m_chunkGrid[i][j][k] = NULL;
        }
      }
    }
  }
}

void
StarField::updateNew()
{
  int i, j, k;
  for (i = 0; i < CHUNK_NUMBER; i++)
  {
    for (j = 0; j < CHUNK_NUMBER; j++)
    {
      for (k = 0; k < CHUNK_NUMBER; k++)
      {
        if (m_chunkGrid[i][j][k] == NULL)
        {
          m_chunkGrid[i][j][k] = new Chunk(m_position[0] + i, m_position[1] + j, m_position[2] + k);
        }
      }
    }
  }
}

void
StarField::update(const Eigen::Vector3f& pos)
{
  int x, y, z;
  x = floor(pos[0] / CHUNK_SIZE) - CHUNK_NUMBER / 2 - m_position[0];
  y = floor(pos[1] / CHUNK_SIZE) - CHUNK_NUMBER / 2 - m_position[1];
  z = floor(pos[2] / CHUNK_SIZE) - CHUNK_NUMBER / 2 - m_position[2];

  m_position[0] += x;
  m_position[1] += y;
  m_position[2] += z;

  updateDelete(x, y, z);
  updateMove(x, y, z);
  updateNew();
}

void
StarField::draw(Camera& cam)
{
  int i, j, k;
  for (i = 0; i < CHUNK_NUMBER; i++)
  {
    for (j = 0; j < CHUNK_NUMBER; j++)
    {
      for (k = 0; k < CHUNK_NUMBER; k++)
      {
        m_chunkGrid[i][j][k]->draw(cam);
      }
    }
  }
}

float
getDist(const Eigen::Vector3f& /*pos*/)
{
  return 0.0f;
}

