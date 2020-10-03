#include <iostream>
#include <string>
#include "../include/type_def.h"

static std::string IdentifierStr;
static double NumVal;
static Token CurTok;

// lexer, recoginze tokens
static void dump_token(Token tok) {
  switch (tok) {
    case tok_eof:
      std::cout << "end of file." << std::endl;
      break;
    case tok_def:
      std::cout << "def" << std::endl;
      break;
    case tok_extern:
      std::cout << "extern" << std::endl;
      break;
    case tok_identifier:
      std::cout << "identifier: " << IdentifierStr << std::endl;
      break;
    case tok_number:
      std::cout << NumVal << std::endl;
      break;
    case tok_nline:
      std::cout << "nline: " << IdentifierStr << std::endl;
      break;
    case tok_comm:
      std::cout << "comment" << std::endl;
      break;
    default:
      std::cout << "Unknown token!" << std::endl;
      break;
  }
}

static Token gettok() {
  static char LastChar = ' ';

  while (isspace(LastChar))
    LastChar = getchar();

  // identifier or keywords (def, extern)
  if (isalpha(LastChar)) {
    IdentifierStr = LastChar;
    while (isalnum((LastChar = getchar())))
      IdentifierStr += LastChar;

    if (IdentifierStr == "def")
      return tok_def;
    if (IdentifierStr == "extern")
      return tok_extern;
    return tok_identifier;
  }

  // numbers
  if (isdigit(LastChar) || LastChar == '.') {
    std::string NumStr;
    do {
      NumStr += LastChar;
      LastChar = getchar();
    } while (isdigit(LastChar) || LastChar == '.');
    NumVal = strtod(NumStr.c_str(), 0);
    return tok_number;
  }

  // eof token
  if (LastChar == EOF)
    return tok_eof;

  // new line
  if (LastChar == '\n' || LastChar == '\r')
    return tok_nline;

  // comments
  if (LastChar == '#') {
    do {
      LastChar = getchar();
    } while (LastChar != EOF && LastChar != '\n' && LastChar != '\r');
    return tok_comm;
  }

  char ThisChar = LastChar;
  LastChar = getchar();
  std::cout << "WARNNING: unknown char : " << ThisChar << std::endl;
  return tok_unknown;
}

static Token getNextToken() {
  return CurTok = gettok();
}

// log function
std::unique_ptr<ExprAST> logError(const char *str) {
  fprintf(stderr, "Logerr: %s\n", str);
  return nullptr;
}

int main() {
  while (getNextToken() != tok_eof) {
    dump_token(CurTok);
  }
}

