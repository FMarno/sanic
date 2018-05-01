#include "tokeniser.hpp"
#include <iostream>

int main() {
  std::string input = "1+2*(4-1)";
  std::cout << input << '\n';

  std::deque<char> line;
  for (char c : input) {
    line.push_back(c);
  }

  auto tokens = tokenise(line);

  for (const auto &token : tokens) {
    std::cout << token->toString() << ' ';
  }
  std::cout << '\n';
}
