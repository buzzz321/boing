#include "wavefrontreader.h"

#include <fstream>
#include <iostream>
#include <sstream>

WaveFrontReader::WaveFrontReader(std::string filename) : m_filename(filename) {}

void WaveFrontReader::readVertices(Mesh &obj) {
  std::ifstream myfile(m_filename);
  std::string line;

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
        uint64_t currPos = 1;
        auto startpos = currPos;
        char separator = '/'; // first we run utill we get a / then we switch to
                              // space to skip rest of numbers
        while (currPos < line.size()) {
          if (line[currPos] == separator) {
            if (separator == ' ') {
              separator = '/'; // go back to search for slashes
              startpos = currPos;
              continue; // skip rest of loop
            }
            std::stringstream conv{line.substr(startpos, (currPos - startpos))};
            uint32_t face;
            conv >> face;
            std::cout << " face index " << face << std::endl;
            obj.indicies.push_back(face);
            startpos = currPos + 1;
            separator = ' '; // skip until next space
          }
          currPos++;
        }
      }
    }
    myfile.close();
  } else
    std::cout << "Unable to open file";
}
