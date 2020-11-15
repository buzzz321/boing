#include "wavefrontreader.h"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

WaveFrontReader::WaveFrontReader(std::string filename) : m_filename(filename) {}

void WaveFrontReader::readVertices(Mesh &obj) {
  std::ifstream myfile(m_filename);
  std::string line;
  uint32_t debug_index{0};

  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      auto vpos = line.find("v ");
      if (vpos == 0) {
        std::stringstream conv{std::move(line.substr(1))};
        float x, y, z;
        conv >> x >> y >> z;
        std::cout << " x " << x << " y " << y << " z " << z << std::endl;
        obj.vertices.push_back(glm::vec3(x, y, z));
      }
      vpos = line.find("f ");
      if (vpos == 0) {
        // f 1/2/3 1/2/3 13/1/2
        // f 11/108/34 13/109/34 7/106/34
        uint64_t currPos = 1;
        auto startpos = currPos;
        char separator = '/'; // first we run utill we get a / then we switch to
                              // space to skip rest of numbers

        std::istringstream splitter{line.substr(2)};
        std::string face;
        uint32_t index;
        // Mesh obj2;
        while (std::getline(splitter, face, ' ')) {
          std::istringstream splitter{face};
          splitter >> index;
          obj.indicies.push_back(index - 1);
          splitter >> index;
          obj.texture_indicies.push_back(index - 1);
          splitter >> index;
          obj.normal_indicies.push_back(index - 1);

          std::cout << "f " << obj.indicies.back() + 1 << "/"
                    << obj.texture_indicies.back() + 1 << "/"
                    << obj.normal_indicies.back() + 1 << std::endl;
        }
      }
    }
    obj.indicies.shrink_to_fit();
    obj.vertices.shrink_to_fit();
    myfile.close();
  } else
    std::cout << "Unable to open file";
}
