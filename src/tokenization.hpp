
#include <iostream>
#include <vector>
#include <optional>
#include "./token.hpp"

#pragma once



class Tokenizer {
  public:
      inline explicit Tokenizer(const std::string& src): m_src(std::move(src)) {
      }
      std::vector<Token> tokenize(const std::string& str) {
        std::vector<Token> tokens;
        std::string buf;

        while(peak().has_value()) {
          if(std::isalpha(peak().value())) {
            buf.push_back(consume());
            while(peak().has_value() && std::isalnum(peak().value())) {
              buf.push_back(consume());
            }

            if(buf == "exit") {
              tokens.push_back({.type = TokenType::exit});
              buf.clear();
            } else {
              throw std::runtime_error("You messed up!: " + buf);
              exit(EXIT_FAILURE);
            }
          }

          else if(std::isdigit(peak().value())) {
            buf.push_back(consume());
            while(peak().has_value() && std::isdigit(peak().value())) {
              buf.push_back(consume());
            }
            tokens.push_back({.type = TokenType::int_lit, .value = buf});
            buf.clear();
            continue;
          }

          else if (peak().value() == ';') {
            consume();
            tokens.push_back({.type = TokenType::semi});
          }

          else if (std::isspace(peak().value())) {
            consume();
          }

          else {
            throw std::runtime_error(std::string("You messed up! ") + peak().value());
            exit(EXIT_FAILURE);
          }
        }
        m_index = 0;
        return tokens;
      }

  private:
    [[nodiscard]] inline std::optional<char> peak(const size_t offset = 0) const
    {
        if (m_index + offset >= m_src.length()) {
            return {};
        }
        return m_src.at(m_index + offset);
    }

    inline char consume()
    {
        return m_src.at(m_index++);
    }

    const std::string m_src;
    size_t m_index = 0;
};