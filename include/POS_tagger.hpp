#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include "json.hpp"

using json = nlohmann::json;

namespace POS_tagger {

inline json getPOS(const std::string& sentence) {
  std::string command = "./python/dist/spacy_wrapper \"" + sentence + "\"";
  if (system(command.c_str())) {
    std::cerr << "Python script failed\n";
  }

  std::ifstream inputFile("output.json");
  if (!inputFile) {
    std::cerr << "Failed to open output.json\n";
  }

  json parsed;
  inputFile >> parsed;

  std::remove("output.json");

  return parsed;
}

}

