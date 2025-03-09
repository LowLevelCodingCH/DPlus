#ifndef PARSER_H_
#define PARSER_H_

struct Node{
	Token token;
};

struct INode : Node{
	Token token;
	Node  left;
	Node  right;
};

INode Tree = {
	.token = {
		.kind  = Token_Kind::INTEGER_LITERAL,
		.value = "20"
	},
	.left  = {
		.token = {
			.kind  = Token_Kind::NONE,
			.value = ""
		},
	},
	.right  = {
		.token = {
			.kind  = Token_Kind::NONE,
			.value = ""
		},
	},
};

struct Parser {
	//...
};

#endif // PARSER_H_
