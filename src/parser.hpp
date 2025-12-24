#include <iostream>
#include <vector>
#include <optional>



#pragma once


  struct NodeExpr {
    Token int_lit;
  };
  struct NodeExit {
    NodeExpr expr;
  };




class Parser {
  public:
  inline explicit Parser(std::vector<Token> tokens): m_tokens(std::move(tokens)) {
   
  }

  std::optional<NodeExpr> parse_expr() {
      if (peak().has_value() && peak().value().type == TokenType::int_lit) {
        return NodeExpr{.int_lit = consume()};
      } else {
        return {};
      }
  }

  std::optional<NodeExit> parse() {
    std::optional<NodeExit> exit_node;

      while(peak().has_value()) {
         if (peak().value().type == TokenType::exit) {
          consume();
          if(auto node_expr = parse_expr()) {
            exit_node = NodeExit { .expr = node_expr.value()};
          } else {
            std::cerr << "Invalid expression"<< std::endl;
            exit(EXIT_FAILURE);
          }
          if(peak().has_value() && peak().value().type == TokenType::semi) {
             consume();
          } else {
            std::cerr << "Invalid expression"<< std::endl;
            exit(EXIT_FAILURE);
          }
         }
      }
      m_index = 0;
      return exit_node;
  };


  private:
  [[nodiscard]] inline std::optional<Token> peak(const size_t offset = 0) const
    {
        if (m_index + offset >= m_tokens.size()) {
            return {};
        }
        return m_tokens.at(m_index + offset);
    }

    inline Token consume()
    {
        return m_tokens.at(m_index++);
    }


  const std::vector<Token> m_tokens;
  size_t m_index = 0;
};

