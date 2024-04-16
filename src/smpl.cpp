#include "smpl.hpp"

#include <fstream>

namespace smpl {

std::vector<std::string> parse(const std::string& str){
    std::vector<std::string> result;
    std::string curr_token;

    for(auto c : str){
        // Seperators
        if(c == ' ' || c == '\n' || c == ';' || c == '\t'){
            if(curr_token != ""){
                result.push_back(curr_token);
                curr_token.clear();
            } else {
                curr_token.clear();
            }
        // Operators
        } else if(c == '(' || c == ')' || c == ','){
            if(curr_token != ""){
                result.push_back(curr_token);
                curr_token.clear();
            }
            result.push_back(std::string(1, c));
        } else {
            curr_token += c;
        }
    }
    if(curr_token != ""){
        result.push_back(curr_token);
    }

    return result;
}

std::string load(const std::string& f_name){
    std::ifstream file(f_name);
    std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    return content;
}

namespace ast {



}

}