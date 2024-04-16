#pragma once

#include <vector>
#include <string>

namespace smpl {

typedef enum {
    T_INT,
    T_FLOAT,
    T_STRING,
    T_BOOL,
    T_VOID,
    T_FUNC,
    T_IF,
    T_ELSE,
    T_WHILE,
    T_FOR,
    T_RETURN,
    T_PRINT,
    T_EOF,
    T_UNKNOWN,
    T_OPER,
    T_ID,
    T_OPEN_CONT, T_CLOSE_CONT,
    T_OP, T_CP, T_COMMA, T_SEMICOLON
} token_type_t;

typedef struct token {
    token_type_t type;
    std::string value;
} token_t;

std::vector<std::string> parse(const std::string& str);

std::vector<token_t> tokenize(const std::vector<std::string>& segments);

std::string load(const std::string& f_name);

namespace ast {



}

}