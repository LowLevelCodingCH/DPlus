#ifndef AGEN_H_
#define AGEN_H_

struct Agen {
  std::string Generate(std::vector<Scope> scopes) {
  std::cout << "[INFO]: Generating" << std::endl;

	std::stringstream output;

	output << "section .text\n";
  output << "  global _start\n";

	std::stringstream secdata;

	secdata << "section .data\n";

	int label_num = 0;
  int tnum = 0;
 
 	std::string label = "SV" + std::to_string(label_num);
  std::string labellen = "SL" + std::to_string(label_num);
 
 	label = "SV" + std::to_string(label_num);

	std::string ctl;
  std::string times = "0";

	secdata << "ten equ 10\n";
    secdata << "hundred equ 100\n";
    secdata << "thosand equ 1000\n";
    secdata << "Hello_World db \"Hello, World!\"\n";
    secdata << "MARK_SIGN db \"D PLUS EXECUTABLE: https://github.com/lowlevelcodingch/dplus\",0xa,0\n";

    for(Scope scope : scopes) {
        std::stringstream current;
        labellen = "SL" + std::to_string(label_num);

        if(scope.permisee != "main")current << "global " << scope.permisee << "\n" << scope.permisee << ":\n";
        else current << "_start:\n";
        std::vector<Token> tokens = scope.tokens;

        for(int i = 0; i < scope.tokens.size(); i++) {
            label = "SV" + std::to_string(label_num);
            labellen = "SL" + std::to_string(label_num);
            ctl = "BL" + std::to_string(tnum);
            if(tokens[i].kind == Token_Kind::KEYWORD) {
                if(tokens[i].value == "while") {
                    current << "\n   ; WHILE\n";
                    current << "jmp " << ctl << "K\n";
                    current << "B" << ctl << ":\n";
                }
                if(tokens[i].value == "endwhile") {
                    current << "\n   ; ENDWHILE\n";
                    current << ctl << "K:\n";
                    current << "  mov r8, " << tokens[i+1].value << "\n";
                    current << "  mov r9, " << tokens[i+4].value << "\n";
                    current << "  cmp r8, r9\n";
                    if(tokens[i+2].kind == Token_Kind::EQUAL &&
                    tokens[i+3].kind == Token_Kind::EQUAL)
                      current << "  je B" << ctl << "\n";
                    else if(tokens[i+3].kind == Token_Kind::EQUAL &&
                    tokens[i+2].kind == Token_Kind::NOT)
                      current << "  jne B" << ctl << "\n";
                    else if(tokens[i+3].kind == Token_Kind::EQUAL &&
                    tokens[i+2].kind == Token_Kind::GREATER)
                      current << "  jg B" << ctl << "\n";
                    else if(tokens[i+3].kind == Token_Kind::EQUAL &&
                    tokens[i+2].kind == Token_Kind::LESS)
                      current << "  jl B" << ctl << "\n";
                    current << "  jmp E" << ctl << "\n";
                    current << "E" << ctl << ":\n";
                    tnum++;
                }
                if(tokens[i].value == "if") {
                    current << "\n   ; IF\n";
                    current << "jmp " << ctl << "K\n";
                    current << "B" << ctl << ":\n";
                }
                if(tokens[i].value == "endif") {
                    current << "\n   ; ENDIF\n";
                    current << "  jmp E" << ctl << "\n";
                    current << ctl << "K:\n";
                    current << "  mov r8, " << tokens[i+1].value << "\n";
                    current << "  mov r9, " << tokens[i+4].value << "\n";
                    current << "  cmp r8, r9\n";
                    if(tokens[i+2].kind == Token_Kind::EQUAL &&
                    tokens[i+3].kind == Token_Kind::EQUAL) {
                      current << "  je B" << ctl << "\n";
                    }
                    else if(tokens[i+3].kind == Token_Kind::EQUAL &&
                    tokens[i+2].kind == Token_Kind::NOT) {
                      current << "  jne B" << ctl << "\n";
                    }
                    else if(tokens[i+3].kind == Token_Kind::EQUAL &&
                    tokens[i+2].kind == Token_Kind::GREATER) {
                      current << "  jg B" << ctl << "\n";
                    }
                    else if(tokens[i+3].kind == Token_Kind::EQUAL &&
                    tokens[i+2].kind == Token_Kind::LESS) {
                      current << "  jl B" << ctl << "\n";
                    }
                    current << "  jmp E" << ctl << "\n";
                    current << "E" << ctl << ":\n";
                    tnum++;
                }
                if(tokens[i].value == "external") {
                    current << "\n   ; EXTERNAL\n";
                    current << "extern " << tokens[i+1].value << "\n";
                }
                if(tokens[i].value == "loop") {
                    current << "\n   ; LOOP\n";
                    current << "loop:\n";
                }
                if(tokens[i].value == "endloop") {
                    current << "\n   ; ENDLOOP\n";
                    current << "jmp loop\n";
                }
                if(tokens[i].value == "times") {
                    times = tokens[i+1].value;
                    current << "\n  ; TIMES\n";
                    current << ctl << ":\n";
                    current << "  add r8, 1\n";
                }
                if(tokens[i].value == "endtimes") {
                    current << "\n  ; ENDTIMES\n";
                    current << "cmp r8, " << times << "\n";
                    current << "jne " << ctl << "\n";
                    current << "mov r8, 0\n";
                    tnum++;
                }
                if(tokens[i].value == "pop") {
                    current << "\n  ; POP\n";
                    current << "  pop rax\n";
                }
                if(tokens[i].value == "push") {
                    current << "\n  ; PUSH\n";
                    current << "  mov rax, " << tokens[i+2].value << "\n";
                    current << "  push QWORD rax" << "\n";
                }
                if(tokens[i].value == "pushptr") {
                    current << "\n  ; PUSHPTR\n";
                    current << "  push " << tokens[i+2].value << "\n";
                }
                if(tokens[i].value == "exit") {
                    current << "\n  ; EXIT\n";
                    current << "  mov rax, 60\n";
                    current << "  mov rdi, " << tokens[i+2].value << "\n";
                    current << "  syscall\n";
                    current << "  ret\n";
                }
                if(tokens[i].value == "sof") {
                    current << "\n  ; SOF\n";
                    secdata << tokens[i+2].value << " equ $ - " << tokens[i+4].value << "\n";
                }
                if(tokens[i].value == "call") {
                    current << "\n  ; CALL\n";
                    current << "  call " << tokens[i+2].value << "\n";
                }
                if(tokens[i].value == "return") {
                    current << "\n  ; RETURN\n";
                    current << "  ret\n";
                }
                if(tokens[i].value == "alloc") {
                    current << "\n  ; ALLOC\n";
                    current << "  xor rdi, rdi\n";
                    current << "  mov rsi, " << tokens[i+2].value << "\n";
                    current << "  mov rdi, 7\n";
                    current << "  mov r10, 34\n";
                    current << "  xor r8, r8\n";
                    current << "  xor r9, r9\n";
                    current << "  mov rax, 9\n";
                    current << "  syscall\n";
                }
            }
            if(tokens[i].kind == Token_Kind::WORD) {
                if(tokens[i].value == "write") {
                    current << "\n  ; WRITE\n";
                    current << "  mov rax, 1\n";
                    current << "  mov rdi, 1\n";
                    if(tokens[i+2].kind == Token_Kind::STRING_LITERAL){
                      current << "  mov rsi, " << label << "\n";
                      current << "  mov rdx, " << labellen << "\n";
                      current << "  syscall\n";

                      secdata << label << ": db " << tokens[i+2].value << ", 0xa\n";
                      secdata << labellen << " equ $ - " << label << "\n";
                      label_num++;
                    } else if (tokens[i+2].kind == Token_Kind::WORD &&
                               tokens[i+3].kind == Token_Kind::COMMA &&
                               (tokens[i+4].kind == Token_Kind::INTEGER_LITERAL ||
                                tokens[i+4].kind == Token_Kind::WORD)) {
                        current << "  mov rsi, " << tokens[i+2].value << "\n";
                        current << "  mov rdx, " << tokens[i+4].value << "\n";
                        current << "  syscall\n";
                    }
                }
                if(tokens[i].value == "fwrite") {
                    current << "\n  ; FWRITE\n";
                    current << "  mov rdi, rax\n";
                    current << "  mov rax, 1\n";
                    current << "  mov rdi, rdi\n";
                    if(tokens[i+2].kind == Token_Kind::STRING_LITERAL){
                      current << "  mov rsi, " << label << "\n";
                      current << "  mov rdx, " << labellen << "\n";
                      current << "  syscall\n";

                      secdata << label << ": db " << tokens[i+2].value << ", 0xa\n";
                      secdata << labellen << " equ $ - " << label << "\n";
                      label_num++;
                    } else if (tokens[i+2].kind == Token_Kind::WORD &&
                               tokens[i+3].kind == Token_Kind::COMMA &&
                               (tokens[i+4].kind == Token_Kind::INTEGER_LITERAL ||
                                tokens[i+4].kind == Token_Kind::WORD)) {
                        current << "  mov rsi, " << tokens[i+2].value << "\n";
                        current << "  mov rdx, " << tokens[i+4].value << "\n";
                        current << "  syscall\n";
                    }
                }
                if(tokens[i].value == "read") {
                    if(tokens[i+2].kind == Token_Kind::WORD &&
                               tokens[i+3].kind == Token_Kind::COMMA &&
                               (tokens[i+4].kind == Token_Kind::INTEGER_LITERAL ||
                                tokens[i+4].kind == Token_Kind::WORD)){
                        current << "\n  ; READ\n";
                        current << "  mov rax, 0\n";
                        current << "  mov rsi, " << tokens[i+2].value << "\n";
                        current << "  mov rdx, " << tokens[i+4].value << "\n";
                        current << "  syscall\n";
                    }
                }
                if(tokens[i].value == "fread") {
                    if(tokens[i+2].kind == Token_Kind::WORD &&
                               tokens[i+3].kind == Token_Kind::COMMA &&
                               (tokens[i+4].kind == Token_Kind::INTEGER_LITERAL ||
                                tokens[i+4].kind == Token_Kind::WORD)){
                        current << "\n  ; FREAD\n";
                        current << "  mov rdi, rax\n";
                        current << "  mov rax, 0\n";
                        current << "  mov rdi, rdi\n";
                        current << "  mov rsi, " << tokens[i+2].value << "\n";
                        current << "  mov rdx, " << tokens[i+4].value << "\n";
                        current << "  syscall\n";
                    }
                }
                if(tokens[i].value == "mexpr") {
                    if(tokens[i+1].kind == Token_Kind::OPEN_BRACE &&
			   tokens[i+2].kind == Token_Kind::WORD &&
                               tokens[i+3].kind == Token_Kind::COMMA &&
                               (tokens[i+4].kind == Token_Kind::INTEGER_LITERAL ||
                                tokens[i+4].kind == Token_Kind::WORD)){
                        current << "\n  ; MEXPR\n";
                        secdata << tokens[i+2].value << " equ " << tokens[i+4].value << "\n";
                    } else {exit(2);}
                }
                if(tokens[i].value == "close"){
                    current << "\n  ; CLOSE\n";
                    current << "  mov rax, 3\n";
                    current << "  mov rdi, rax\n";
                    current << "  syscall\n";
                }
                if(tokens[i].value == "open") {
                    if(tokens[i+2].kind == Token_Kind::WORD) {
                        current << "\n  ; OPEN\n";
                        current << "  mov rax, 2\n";
                        current << "  mov rdi, " << tokens[i+2].value << "\n";
                        current << "  mov rsi, 110\n";
                        current << "  mov rdx, 0777\n";
                        current << "  syscall";
                    }
                }
            }
            if(tokens[i].kind == Token_Kind::TYPE) {
                if(tokens[i].value == "String") {
                    secdata << tokens[i+1].value << ": db " << tokens[i+3].value << ", 0" << "\n";
                }
                if(tokens[i].value == "NString") {
                    secdata << tokens[i+1].value << ": db " << tokens[i+3].value << ", 0xa, 0" << "\n";
                }
                if(tokens[i].value == "Int") {
                    secdata << tokens[i+1].value << " equ " << tokens[i+3].value << "\n";
                }
                if(tokens[i].value == "Bool") {
                    if(tokens[i+3].value == "true") secdata << tokens[i+1].value << " equ 1\n";
                    else secdata << tokens[i+1].value << " equ 0\n";
                }
            }
        }


        output << "\n" << current.str() << "\n";
    }

    output << "\n" << secdata.str();
    return output.str();
    }
};

#endif // AGEN_H_
