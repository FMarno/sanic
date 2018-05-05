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
struct Multiply : public Token {
  std::string toString() const override { return "*"; }
};
struct Divide : public Token {
  std::string toString() const override { return "/"; }
};
struct Modulus : public Token {
  std::string toString() const override { return "%"; }
};
struct I : public Token {
  int value;
  I(int v) : value(v){};
  std::string toString() const override {
    return "I(" + std::to_string(value) + ")";
  }
};

int readInt(std::deque<char> &line, char head);

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
  case '*':
    return std::make_unique<Multiply>();
  case '/':
    return std::make_unique<Divide>();
  case '%':
    return std::make_unique<Modulus>();
  }
  if (std::isdigit(c)) {
    return std::make_unique<I>(readInt(line, c));
  }
  throw std::invalid_argument(std::string{c});
}

int readInt(std::deque<char> &line, char head) {
  std::string num{head};
  while (!line.empty() && std::isdigit(line.front())) {
    char next = line.front();
    line.pop_front();
    num += next;
  }
  return std::stoi(num);
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
