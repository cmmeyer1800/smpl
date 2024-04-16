#include "smpl.hpp"

#include <fstream>
#include <iostream>

namespace smpl {

std::vector<std::string> parse(const std::string& str){
    std::vector<std::string> result;
    std::string curr_seg;

    for(auto c : str){
        // Seperators
        if(c == ' ' || c == '\n' || c == ';' || c == '\t'){
            if(curr_seg != ""){
                result.push_back(curr_seg);
                curr_seg.clear();
            } else {
                curr_seg.clear();
            }
        // Operators
        } else if(c == '(' || c == ')' || c == ','){
            if(curr_seg != ""){
                result.push_back(curr_seg);
                curr_seg.clear();
            }
            result.push_back(std::string(1, c));
        } else {
            curr_seg += c;
        }
    }
    if(curr_seg != ""){
        result.push_back(curr_seg);
    }

    return result;
}

std::vector<token_t> tokenize(const std::vector<std::string>& segments){
    std::vector<std::string> known_ids;

    auto seen = [](std::vector<std::string> ids, std::string id){
        return std::find(ids.begin(), ids.end(), id) != ids.end();
    };

    std::vector<token_t> tokens;

    for(auto& seg : segments){
        token_t token;
        token.value = seg;

        if(seg == "int"){
            token.type = T_INT;
        } else if(seg == "float"){
            token.type = T_FLOAT;
        } else if(seg == "string"){
            token.type = T_STRING;
        } else if(seg == "bool"){
            token.type = T_BOOL;
        } else if(seg == "void"){
            token.type = T_VOID;
        } else if(seg == "func"){
            token.type = T_FUNC;
        } else if(seg == "if"){
            token.type = T_IF;
        } else if(seg == "else"){
            token.type = T_ELSE;
        } else if(seg == "while"){
            token.type = T_WHILE;
        } else if(seg == "for"){
            token.type = T_FOR;
        } else if(seg == "return"){
            token.type = T_RETURN;
        } else if(seg == "print"){
            token.type = T_PRINT;
        } else if(seg == "("){
            token.type = T_OP;
        } else if(seg == ")"){
            token.type = T_CP;
        } else if(seg == "{"){
            token.type = T_OPEN_CONT;
        } else if(seg == "}"){
            token.type = T_CLOSE_CONT;
        } else if(seg == ","){
            token.type = T_COMMA;
        } else if(seg == ";"){
            token.type = T_SEMICOLON;
        } else if(seg == "+" || seg == "-" || seg == "*" || seg == "/" || seg == "^") {
            token.type = T_OPER;
        } else if(seg == ""){
            token.type = T_EOF;
        } else {
            // Function name identifier
            if(tokens.size() > 0 && tokens.back().type == T_FUNC){
                token.type = T_ID;
            // Argument name identifier
            } else if(tokens.size() > 2 && (
                    (tokens[tokens.size() - 3].type == T_FUNC && 
                    tokens[tokens.size() - 2].type == T_ID && tokens.back().type == T_OP) ||
                    (tokens[tokens.size() - 2].type == T_ID && tokens.back().type == T_COMMA))
                ){
                known_ids.push_back(token.value);
                token.type = T_ID;
            // Function Call Argument ID
            } else if(tokens.size() > 0 && (tokens.back().type == T_OP || tokens.back().type == T_COMMA)){
                if (seen(known_ids, token.value)){
                    token.type = T_ID;
                } else {
                    throw std::runtime_error("Unknown identifier: " + token.value);
                }
                token.type = T_ID;
            } else {
                // throw std::runtime_error("Could not determine token type for: " + token.value);
                token.type = T_UNKNOWN;
            }
        }

        tokens.push_back(token);
    }

    return tokens;
}

std::string load(const std::string& f_name){
    std::ifstream file(f_name);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

namespace ast {



}

}