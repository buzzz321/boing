#ifndef WAVEFRONTREADER_H
#define WAVEFRONTREADER_H
#include <glm/glm.hpp>
#include <string>
#include <vector>

typedef glm::vec3 Vertex;

struct Mesh {
  std::vector<Vertex> vertices;
  std::vector<uint32_t> indicies;
};

class WaveFrontReader {
public:
  WaveFrontReader(std::string filename);

  void readVertices(Mesh &obj);

private:
  std::string m_filename;
};

#endif // WAVEFRONTREADER_H
