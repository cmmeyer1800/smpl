#include <catch2/catch_test_macros.hpp>

#include "smpl.hpp"

TEST_CASE("Simple space parse test", "[parser]"){
  std::vector<std::string> tokens;

  tokens = smpl::parse("1 2 3");

  REQUIRE(tokens.size() == 3);

  REQUIRE(tokens[0] == "1");
  REQUIRE(tokens[1] == "2");
  REQUIRE(tokens[2] == "3");
}

TEST_CASE("Simple newline parse test", "[parser]"){
  std::vector<std::string> tokens;

  tokens = smpl::parse("1\n2\n3");

  REQUIRE(tokens.size() == 3);

  REQUIRE(tokens[0] == "1");
  REQUIRE(tokens[1] == "2");
  REQUIRE(tokens[2] == "3");
}

TEST_CASE("Simple semi-colon parse test", "[parser]"){
  std::vector<std::string> tokens;

  tokens = smpl::parse("1;2;3");

  REQUIRE(tokens.size() == 3);

  REQUIRE(tokens[0] == "1");
  REQUIRE(tokens[1] == "2");
  REQUIRE(tokens[2] == "3");
}

TEST_CASE("Simple cross testing", "[parser]"){
  std::vector<std::string> tokens;

  tokens = smpl::parse("1 2 3;\n4 5 6;\n7 8 9");

  REQUIRE(tokens.size() == 9);

  for(auto i = 1; i < 10; i++){
    REQUIRE(tokens[i-1] == std::to_string(i));
  }
}

TEST_CASE("Simple file load test", "[other]"){
  std::string content;

  content = smpl::load("test/data/basic.smpl");

  REQUIRE(content == "func test(arg1, arg2){\n    print(arg1)\n    print(arg2)\n}");
}

TEST_CASE("Simple parse file", "[parser]"){
  std::vector<std::string> tokens;

  tokens = smpl::parse(smpl::load("test/data/basic.smpl"));

  REQUIRE(tokens.size() == 17);

  REQUIRE(tokens[0] == "func");
  REQUIRE(tokens[1] == "test");
  REQUIRE(tokens[2] == "(");
  REQUIRE(tokens[3] == "arg1");
  REQUIRE(tokens[4] == ",");
  REQUIRE(tokens[5] == "arg2");
  REQUIRE(tokens[6] == ")");
  REQUIRE(tokens[7] == "{");
  REQUIRE(tokens[8] == "print");
  REQUIRE(tokens[9] == "(");
  REQUIRE(tokens[10] == "arg1");
  REQUIRE(tokens[11] == ")");
  REQUIRE(tokens[12] == "print");
  REQUIRE(tokens[13] == "(");
  REQUIRE(tokens[14] == "arg2");
  REQUIRE(tokens[15] == ")");
  REQUIRE(tokens[16] == "}");
}

TEST_CASE("Simple tokenization", "[tokenizer]"){
  std::vector<std::string> tokens;
  std::vector<smpl::token_t> tokenized;

  tokens = smpl::parse(smpl::load("test/data/basic.smpl"));
  tokenized = smpl::tokenize(tokens);

  REQUIRE(tokenized.size() == 17);

  REQUIRE(tokenized[0].type == smpl::T_FUNC);
  REQUIRE(tokenized[1].type == smpl::T_ID);
  REQUIRE(tokenized[2].type == smpl::T_OP);
  REQUIRE(tokenized[3].type == smpl::T_ID);
  REQUIRE(tokenized[4].type == smpl::T_COMMA);
  REQUIRE(tokenized[5].type == smpl::T_ID);
  REQUIRE(tokenized[6].type == smpl::T_CP);
  REQUIRE(tokenized[7].type == smpl::T_OPEN_CONT);
  REQUIRE(tokenized[8].type == smpl::T_PRINT);
  REQUIRE(tokenized[9].type == smpl::T_OP);
  REQUIRE(tokenized[10].type == smpl::T_ID);
  REQUIRE(tokenized[11].type == smpl::T_CP);
  REQUIRE(tokenized[12].type == smpl::T_PRINT);
  REQUIRE(tokenized[13].type == smpl::T_OP);
  REQUIRE(tokenized[14].type == smpl::T_ID);
  REQUIRE(tokenized[15].type == smpl::T_CP);
  REQUIRE(tokenized[16].type == smpl::T_CLOSE_CONT);
}