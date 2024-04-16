#include <iostream>

#include "smpl.hpp"

auto main(int argc, char *argv[]) -> int{
  if(argc != 2){
    std::cout << "Usage: " << argv[0] << " <file>" << std::endl;
    return 1;
  }

  std::vector<std::string> tokens = smpl::parse(smpl::load(argv[1]));

  for(auto& token : tokens){
    // std::cout << token << std::endl;
  }
}