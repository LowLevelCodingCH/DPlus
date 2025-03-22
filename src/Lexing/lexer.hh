#ifndef LEXER_H_
#define LEXER_H_

typedef enum {
  STRING_LITERAL,        // "Hello"...
  INTEGER_LITERAL,       // 0...

  KEYWORD,               // return...
  WORD,                  // true, false, null...
  TYPE,                  // int...

  OPEN_BRACE,            // {
  CLOSED_BRACE,          // }

  OPEN_PARENTHESIS,      // (
  CLOSED_PARENTHESIS,    // )

  //OPEN_SQUARE,           // [
  //CLOSED_SQUARE,         // ]

  SEMI_COLON,            // ;
  COMMA,                 // ,
  PERIOD,                // .
  COLON,                 // :

  AT,                    // @
  EQUAL,                 // =

  NONE,                  //

  GREATER,               // >
  LESS,                  // <
  NOT,                   // !
} Token_Kind;

bool IsAssertion(Token_Kind kind1, Token_Kind kind2) {
    if(kind1 == Token_Kind::EQUAL && (
      kind2 == Token_Kind::EQUAL ||
      kind2 == Token_Kind::LESS ||
      kind2 == Token_Kind::GREATER ||
      kind2 == Token_Kind::NOT
    )) return true;
    else return false;
}

std::string TTS(Token_Kind token){
    switch(token){
        case Token_Kind::STRING_LITERAL: return "[STRING_LITERAL]"; break;
        case Token_Kind::INTEGER_LITERAL: return "[INTEGER_LITERAL]"; break;
        case Token_Kind::KEYWORD: return "[KEYWORD]"; break;
        case Token_Kind::WORD: return "[WORD]"; break;
        case Token_Kind::TYPE: return "[TYPE]"; break;
        case Token_Kind::OPEN_BRACE: return "[OPEN_BRACE]"; break;
        case Token_Kind::CLOSED_BRACE: return "[CLOSED_BRACE]"; break;
        case Token_Kind::OPEN_PARENTHESIS: return "[OPEN_PARENTHESIS]"; break;
        case Token_Kind::CLOSED_PARENTHESIS: return "[CLOSED_PARENTHESIS]"; break;
        //case Token_Kind::OPEN_SQUARE: return "[OPEN_SQUARE]"; break;
        //case Token_Kind::CLOSED_SQUARE: return "[CLOSED_SQUARE]"; break;
        case Token_Kind::SEMI_COLON: return "[SEMI_COLON]"; break;
        case Token_Kind::COMMA: return "[COMMA]"; break;
        case Token_Kind::PERIOD: return "[PERIOD]"; break;
        case Token_Kind::COLON: return "[COLON]"; break;
        case Token_Kind::AT: return "[AT]"; break;
        case Token_Kind::EQUAL: return "[EQUAL]"; break;
        case Token_Kind::LESS: return "[LESS]"; break;
        case Token_Kind::GREATER: return "[GREATER]"; break;
        case Token_Kind::NOT: return "[NOT]"; break;
        default: return "[NONE]"; break;
    }
}

typedef struct {
  Token_Kind  kind;
  std::string value;
} Token;

bool IsSpecial (char C) {
  switch (C) {
    case '\n': return true; break;
    case '\t': return true; break;
    case ' ': return true; break;
    //case '[': return true; break;
    //case ']': return true; break;
    case '{': return true; break;
    case '}': return true; break;
    case '(': return true; break;
    case ')': return true; break;
    case '@': return true; break;
    case ',': return true; break;
    case '.': return true; break;
    case ';': return true; break;
    case ':': return true; break;
    case '"': return true; break;
    case '=': return true; break;
    case '!': return true; break;
    case '<': return true; break;
    case '>': return true; break;
    default: return false; break;
  }
}

struct Lexer {
  std::vector<Token> Lex (std::string Code) {
    std::vector<Token> Lexed;
    std::string Buffer;
    std::string String;
    bool InString = false;
    int i = 0;

    std::cout << "[INFO]: Lexing" << std::endl;

    for (char C : Code) {
      if (InString) {
        String.push_back(C);
      }

      if (IsSpecial(C)) {
        try {
          std::stoi(Buffer);
          Token token = {Token_Kind::INTEGER_LITERAL, Buffer};
          Lexed.push_back(token);
          Buffer = "";
        } catch (const std::exception& e) {}
        if(!InString){
          if (Buffer == "proc") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "scope") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "call") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "asm") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "repeat") {
            Lexed.push_back({Token_Kind::WORD, Buffer});
            Buffer = "";
          } else if (Buffer == "do") {
            Lexed.push_back({Token_Kind::WORD, Buffer});
            Buffer = "";
          } else if (Buffer == "loop") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "mexpr") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "poke") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "while") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "endwhile") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "if") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "endif") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "sof") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "endloop") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "times") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "endtimes") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "return") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "external") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "pushptr") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "exit") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
            Buffer = "";
          } else if (Buffer == "Var") {
            Lexed.push_back({Token_Kind::TYPE, Buffer});
          } else if (Buffer == "Int") {
            Lexed.push_back({Token_Kind::TYPE, Buffer});
          } else if (Buffer == "Bool") {
            Lexed.push_back({Token_Kind::TYPE, Buffer});
          } else if (Buffer == "String") {
            Lexed.push_back({Token_Kind::TYPE, Buffer});
          } else if (Buffer == "NString") {
            Lexed.push_back({Token_Kind::TYPE, Buffer});
          } else if (Buffer == "alloc") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
          } else if (Buffer == "push") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
          } else if (Buffer == "pop") {
            Lexed.push_back({Token_Kind::KEYWORD, Buffer});
          } else if (Buffer != "" && Buffer != " " && Buffer != "\t" && Buffer != "\n"){
            Lexed.push_back({Token_Kind::WORD, Buffer});
            Buffer = "";
          }
        }

        if (C == '"') {
          if (InString) {
            InString = false;
            Lexed.push_back({Token_Kind::STRING_LITERAL, '"' + String});
            String = "";
            Buffer = "";
          } else if (!InString) {
            InString = true;
          }
        }

        if (!InString){
          if (C == ';') {
            Lexed.push_back({Token_Kind::SEMI_COLON, ""});
          } else if (C == '(') {
            Lexed.push_back({Token_Kind::OPEN_PARENTHESIS, ""});
          } else if (C == ')') {
            Lexed.push_back({Token_Kind::CLOSED_PARENTHESIS, ""});
          } else if (C == '{') {
            Lexed.push_back({Token_Kind::OPEN_BRACE, ""});
          } else if (C == '}') {
            Lexed.push_back({Token_Kind::CLOSED_BRACE, ""});
          } else if (C == '@') {
            Lexed.push_back({Token_Kind::AT, ""});
          } else if (C == ',') {
            Lexed.push_back({Token_Kind::COMMA, ""});
          } else if (C == '=') {
            Lexed.push_back({Token_Kind::EQUAL, ""});
          } else if (C == '<') {
            Lexed.push_back({Token_Kind::LESS, ""});
          } else if (C == '>') {
            Lexed.push_back({Token_Kind::GREATER, ""});
          } else if (C == '!') {
            Lexed.push_back({Token_Kind::NOT, ""});
          } else if (C == ' ' || C == '\t' || C == '\n') {

          }
          Buffer = "";
        }
      } else if (InString == false){
        Buffer.push_back(C);
      }
      ++i;
    }
    if(InString) {
      std::cerr << "[LEXING-ERROR]: {At: " << i << "} Still inside of a string literal" << std::endl;
      exit(1);
    }
    return Lexed;
  }
};

#endif // LEXER_H_
