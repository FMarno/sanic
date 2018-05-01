#pragma once
#include <cctype>
#include <deque>
#include <memory>
#include <optional>
#include <ostream>

struct Token {
  virtual ~Token() = default;
  virtual std::string toString() const = 0;
};

struct LParen : public Token {
  std::string toString() const override { return "("; }
};
struct RParen : public Token {
  std::string toString() const override { return ")"; }
};
struct Plus : public Token {
  std::string toString() const override { return "+"; }
};
struct Minus : public Token {
  std::string toString() const override { return "-"; }
};
struct I : public Token {
  int value;
  I(int v) : value(v){};
  std::string toString() const override {
    return "I(" + std::to_string(value) + ")";
  }
};

std::optional<std::unique_ptr<Token>> nextToken(std::deque<char> &line) {
  if (line.empty()) {
    return {};
  }
  char c = line.front();
  line.pop_front();
  while (std::isspace(c)) {
    if (line.empty()) {
      return {};
    }
    c = line.front();
    line.pop_front();
  }
  switch (c) {
  case '(':
    return std::make_unique<LParen>();
  case ')':
    return std::make_unique<RParen>();
  case '+':
    return std::make_unique<Plus>();
  case '-':
    return std::make_unique<Minus>();
  }
  return std::make_unique<I>(c - '0');
}

std::deque<std::unique_ptr<Token>> tokenise(std::deque<char> line) {
  std::deque<std::unique_ptr<Token>> tokens;
  while (true) {
    auto next = nextToken(line);
    if (next) {
      tokens.push_back(std::move(next.value()));
    } else {
      break;
    }
  }
  return tokens;
}
