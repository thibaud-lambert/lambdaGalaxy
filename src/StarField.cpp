#include "StarField.h"

StarField::StarField()
  : m_chunkGrid(NULL)
  , m_position(0.0f, 0.0f, 0.0f)
{
}


void
StarField::init(const Eigen::Vector3f& pos)
{
  m_position[0] = floor(pos[0] / CHUNK_SIZE) - CHUNK_NUMBER / 2;
  m_position[1] = floor(pos[1] / CHUNK_SIZE) - CHUNK_NUMBER / 2;
  m_position[2] = floor(pos[2] / CHUNK_SIZE) - CHUNK_NUMBER / 2;
  m_chunkGrid = new Chunk***[CHUNK_NUMBER + 3];
  for (int i = 0; i < CHUNK_NUMBER; i++)
  {
    m_chunkGrid[i] = new Chunk**[CHUNK_NUMBER];
    for (int j = 0; j < CHUNK_NUMBER; j++)
    {
      m_chunkGrid[i][j] = new Chunk*[CHUNK_NUMBER];
      for (int k = 0; k < CHUNK_NUMBER; k++)
      {
        m_chunkGrid[i][j][k] = new Chunk(Eigen::Vector3i(m_position[0] + i, m_position[1] + j, m_position[2] + k));
      }
    }
  }
}

void
StarField::updateDelete(const Eigen::Vector3i& pos)
{
  // Update along X
  if (pos[0] < 0)
  {
    for (int i = CHUNK_NUMBER + pos[0]; i < CHUNK_NUMBER; i++)
    {
      for (int j = 0; j < CHUNK_NUMBER; j++)
      {
        for (int k = 0; k < CHUNK_NUMBER; k++)
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
  else if (pos[0] > 0)
  {
    for (int i = 0; i < pos[0]; i++)
    {
      for (int j = 0; j < CHUNK_NUMBER; j++)
      {
        for (int k = 0; k < CHUNK_NUMBER; k++)
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
  if (pos[1] < 0)
  {
    for (int i = 0; i < CHUNK_NUMBER; i++)
    {
      for (int j = CHUNK_NUMBER - pos[1]; j < CHUNK_NUMBER; j++)
      {
        for (int k = 0; k < CHUNK_NUMBER; k++)
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
  else if (pos[1] > 0)
  {
    for (int i = 0; i < CHUNK_NUMBER; i++)
    {
      for (int j = 0; j < pos[1]; j++)
      {
        for (int k = 0; k < CHUNK_NUMBER; k++)
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
  if (pos[2] < 0)
  {
    for (int i = 0; i < CHUNK_NUMBER; i++)
    {
      for (int j = 0; j < CHUNK_NUMBER; j++)
      {
        for (int k = CHUNK_NUMBER + pos[2]; k < CHUNK_NUMBER; k++)
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
  else if (pos[2] > 0)
  {
    for (int i = 0; i < CHUNK_NUMBER; i++)
    {
      for (int j = 0; j < CHUNK_NUMBER; j++)
      {
        for (int k = 0; k < pos[2]; k++)
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
StarField::updateMove(const Eigen::Vector3i& pos)
{
  // Move along x
  if (pos[0] < 0)
  {
    for (int i = CHUNK_NUMBER - 1 + pos[0]; i > 0; i--)
    {
      for (int j = 0; j < CHUNK_NUMBER; j++)
      {
        for (int k = 0; k < CHUNK_NUMBER; k++)
        {
          m_chunkGrid[i - pos[0]][j][k] = m_chunkGrid[i][j][k];
          m_chunkGrid[i][j][k] = NULL;
        }
      }
    }
  }
  else if (pos[0] > 0)
  {
    for (int i = pos[0]; i < CHUNK_NUMBER; i++)
    {
      for (int j = 0; j < CHUNK_NUMBER; j++)
      {
        for (int k = 0; k < CHUNK_NUMBER; k++)
        {
          m_chunkGrid[i - pos[0]][j][k] = m_chunkGrid[i][j][k];
          m_chunkGrid[i][j][k] = NULL;
        }
      }
    }
  }


  // Move along y
  if (pos[1] < 0)
  {
    for (int i = 0; i < CHUNK_NUMBER; i++)
    {
      for (int j = CHUNK_NUMBER - 1 + pos[1]; j > 0; j--)
      {
        for (int k = 0; k < CHUNK_NUMBER; k++)
        {
          m_chunkGrid[i][j - pos[1]][k] = m_chunkGrid[i][j][k];
          m_chunkGrid[i][j][k] = NULL;
        }
      }
    }
  }
  else if (pos[1] > 0)
  {
    for (int i = 0; i < CHUNK_NUMBER; i++)
    {
      for (int j = pos[1]; j < CHUNK_NUMBER; j++)
      {
        for (int k = 0; k < CHUNK_NUMBER; k++)
        {
          m_chunkGrid[i][j - pos[1]][k] = m_chunkGrid[i][j][k];
          m_chunkGrid[i][j][k] = NULL;
        }
      }
    }
  }

  // Move along z
  if (pos[2] < 0)
  {
    for (int i = 0; i < CHUNK_NUMBER; i++)
    {
      for (int j = 0; j < CHUNK_NUMBER; j++)
      {
        for (int k = CHUNK_NUMBER - 1 + pos[2]; k > 0; k--)
        {
          m_chunkGrid[i][j][k - pos[2]] = m_chunkGrid[i][j][k];
          m_chunkGrid[i][j][k] = NULL;
        }
      }
    }
  }
  else if (pos[2] > 0)
  {
    for (int i = 0; i < CHUNK_NUMBER; i++)
    {
      for (int j = 0; j < CHUNK_NUMBER; j++)
      {
        for (int k = pos[2]; k < CHUNK_NUMBER; k++)
        {
          m_chunkGrid[i][j][k - pos[2]] = m_chunkGrid[i][j][k];
          m_chunkGrid[i][j][k] = NULL;
        }
      }
    }
  }
}

void
StarField::updateNew()
{
  for (int i = 0; i < CHUNK_NUMBER; i++)
  {
    for (int j = 0; j < CHUNK_NUMBER; j++)
    {
      for (int k = 0; k < CHUNK_NUMBER; k++)
      {
        if (m_chunkGrid[i][j][k] == NULL)
        {
          m_chunkGrid[i][j][k] = new Chunk(m_position + Eigen::Vector3i(i, j, k));
        }
      }
    }
  }
}

void
StarField::update(const Eigen::Vector3f& pos)
{
  Eigen::Vector3i position(floor(pos[0] / CHUNK_SIZE) - CHUNK_NUMBER / 2,
                           floor(pos[1] / CHUNK_SIZE) - CHUNK_NUMBER / 2,
                           floor(pos[2] / CHUNK_SIZE) - CHUNK_NUMBER / 2);
  position -= m_position;
  m_position += position;

  updateDelete(position);
  updateMove(position);
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

