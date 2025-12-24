#pragma once

#include <optional>
#include <iostream>


enum class TokenType {
  exit,
  int_lit,
  semi
};


struct Token {
  TokenType type;
  std::optional<std::string> value {};
};  
