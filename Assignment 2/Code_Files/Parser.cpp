#pragma once
#include "Header.h"
#include "ObjectSeperate.h"
#include "Parser.h"

bool IsNumber(const char ch)
{
	return (ch >= '0' && ch <= '9');
}
bool IsLetter(const char ch)
{
	return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}
bool IsOperand(const char ch)
{
	return IsNumber(ch) || IsLetter(ch);
}
bool IsOperatorPM(const char ch)
{
	return (ch == '+') || (ch == '-') || (ch == '–');
}
bool IsOperatorMD(const char ch)
{
	return (ch == '*') || (ch == '/');
}
bool IsOperandRP(const char ch)
{
	return (ch == '^') || (ch == '$');
}
bool IsOperator(const char ch)
{
	return (ch == '/' || ch == '*' || ch == '+' || ch == '-' || ch == '^' || ch == '–' || ch == '$');
}
bool IsClosingPara(const char& ch)
{
	return (ch == ')' || ch == '}' || ch == ']');
}
bool IsOpeningPara(const char& ch)
{
	return (ch == '(' || ch == '{' || ch == '[');
}
bool IsParenthesis(const char& ch)
{
	return IsOpeningPara(ch) || IsClosingPara(ch);
}
bool IsWithinTag(const char& ch)
{
	return (ch != '\t' && ch != '\n' && ch != ' ');
}
bool IsOperatorStr(const string& str)
{
	return (str.length() == 1 && IsOperator(str[0]));
}
bool IsOperandStr(const string& str)
{
	bool neg = false;
	if (str.length() == 1 && (str[0] == ' ' || str[0] == '-')) return false;
	else if (!str.length()) return false;
	//else if (str.length() == 1 && IsParenthesis(str[0])) return false;
	
	for (int i = 0; str[i] != '\0'; i++)
		if (str[i] == '-' && !neg)
			neg = true;
		else if (IsOperator(str[i]) || IsParenthesis(str[i]))
			return false;
		else if ((!IsOperand(str[i]) && str[i] != ' ') && neg)
			return false;
	return true;
}
template <typename data>
data CreateToken(Stack<data>& TStack, const char Operator)
{
	data t2 = TStack.PopR(), res = Operator  + TStack.PopR()  + t2;
	return res;
}
template <typename data>
data CreatePostToken(Stack<data>& TokenStack, char Operator)
{
	data res = "(" + TokenStack.PopR() + Operator + TokenStack.PopR() + ")";
	return res;
}
template <typename data>
data CreatePreToken(Stack<data>& TokenStack, char Operator)
{
	data t2 = TokenStack.PopR();
	data res = "(" + t2 + Operator + TokenStack.PopR() + ")";
	return res;
}
template <typename data>
data Concatenate(const data& str1, const data& str2)
{
	return str1 + str2;
}

string RevString(const string& str)
{
	string res;
	for (int i = str.length() - 1; i >= 0; i--)
		res += str[i];
	return res;
}
bool CompareStr(const string& str1, const string& str2)
{
	if (str1.length() != str2.length())
		return false;

	for (int i = 0; i < str1.length(); i++)
		if (str1[i] != str2[i])
			return false;

	return true;
}
string ExtractVar(const string& str, int& index)
{
	string token;
	for (; IsOperand(str[index]); index++)
		token += str[index];
	index--;
	return token + " ";
}

//Returns Multi-character Operators and Operands
string SeperateVar(const string& str, int& index)
{
	string token;
	while (str[index] == ' ' && index < str.length()) index++;
	if (index >= str.length()) { index = str.length() - 1; return ""; }
	else if (str[index] == '-' && IsOperand(str[index + 1])) { token += '-'; index++; };

	if (IsOperator(str[index])) token += str[index++];
	else if (IsOpeningPara(str[index])) token += str[index++];
	else if (IsClosingPara(str[index])) token += str[index++];
	else for (; str[index] != ' ' && !IsOperator(str[index]) && !IsParenthesis(str[index]); index++)
		token += str[index];

	index--;
	return token;
}

//------------------Conversion Algorithms------------------//

//Operator Precedence
bool prcd(const char ch1, const char ch2)
{
	if (IsOperatorMD(ch1) && IsOperatorMD(ch2))
		return true;
	else if (IsOperatorPM(ch1) && IsOperatorPM(ch2))
		return true;
	else if (IsOperatorPM(ch1) && IsOperatorMD(ch2))
		return false;
	else if (IsOperatorMD(ch1) && IsOperatorPM(ch2))
		return true;
	else if (IsOperandRP(ch2) && IsOperatorMD(ch1))
		return false;
	else if (IsOperandRP(ch2) && IsOperatorPM(ch1))
		return false;
	else if (IsOperandRP(ch1) && IsOperatorMD(ch2))
		return true;
	else if (IsOperandRP(ch1) && IsOperatorPM(ch2))
		return true;
	else if (IsOpeningPara(ch1) && IsClosingPara(ch2))
		return false;
	else if (IsOperandRP(ch1) && IsOperandRP(ch2))
		return false;
	else if (IsOperator(ch1) && IsClosingPara(ch2))
		return true;
	else if (IsOpeningPara(ch1) && IsOperator(ch2))
		return false;
	else if (IsOperator(ch1) && IsOpeningPara(ch2))
		return false;
	else return false;
}
//Converts Infix to Postfix String
string ConvertToPostfix(const string& Expression)
{
	string token, res;
	Stack<string> opstack;

	for (int i = 0; Expression[i] != '\0'; i++)
	{
		token = SeperateVar(Expression , i);
		if (IsOperandStr(token))
			res += token;
		else if (IsOperator(token[0]) || IsParenthesis(token[0]))
		{
			while (!opstack.IsEmpty() && prcd(opstack.Peek()[0], token[0]))
				res += opstack.PopR();

			if (opstack.IsEmpty() || token[0] != ')')
				opstack.Push(token);
			else
				opstack.Pop();
		}
	}
	while (!opstack.IsEmpty())
		res += opstack.PopR();
	return res;
}
//Converts Infix to Prefix String
string ConvertToPrefix(const string& Expression)
{
	Stack<char> OpStack;
	Stack<string> TokenStack;
	string res, token;

	for (int i = 0; Expression[i] != '\0'; i++)
	{
		token = Expression[i];

		if (IsOperand(Expression[i]))
			TokenStack.Push(ExtractVar(Expression, i));
		else if (IsOperator(Expression[i]) || IsParenthesis(Expression[i]))
		{
			while (!OpStack.IsEmpty() && prcd(OpStack.Peek(), token[0]))
				TokenStack.Push(CreateToken(TokenStack, OpStack.PopR()));

			if (OpStack.IsEmpty() || token[0] != ')')
				OpStack.Push(token[0]);
			else
				OpStack.Pop();
		}
	}
	while (!OpStack.IsEmpty())
		TokenStack.Push(CreateToken(TokenStack, OpStack.PopR()));

	return TokenStack.PopR();
}

//string ConvertToPostfix(const string& Expression)
//{
//	char token;
//	string res;
//	Stack<char> opstack;
//
//	for (int i = 0; Expression[i] != '\0'; i++)
//	{
//		token = Expression[i];
//		if (IsOperand(ExtractVar(Expression, i))
//			res += Expression[i];
//		else if (token != ' ')
//		{
//			while (!opstack.IsEmpty() && prcd(opstack.Peek(), token))
//				res += opstack.PopR();
//
//			if (opstack.IsEmpty() || token != ')')
//				opstack.Push(token);
//			else
//				opstack.Pop();
//		}
//	}
//	while (!opstack.IsEmpty())
//		res += opstack.PopR();
//	return res;
//}
//string ConvertToPrefix(const string& Expression)
//{
//	Stack<char> OpStack;
//	Stack<string> TokenStack;
//	string res, token;
//
//	for (int i = 0; Expression[i] != '\0'; i++)
//	{
//		token = SeperateVar(Expression, i);
//
//		if (IsOperandStr(token))
//			TokenStack.Push(token + " ");
//		else if (IsOperator(token[0]))
//		{
//			while (!OpStack.IsEmpty() && prcd(OpStack.Peek(), token[0]))
//				TokenStack.Push(CreateToken(TokenStack, OpStack.PopR()));
//
//			if (OpStack.IsEmpty() || token[0] != ')')
//				OpStack.Push(token[0]);
//			else
//				OpStack.Pop();
//		}
//	}
//	while (!OpStack.IsEmpty())
//		TokenStack.Push(CreateToken(TokenStack, OpStack.PopR()));
//
//	return TokenStack.PopR();
//}

//------------------Evaluation Algorithms------------------//

//Apply Arithematic Operation 
string ApplyOperation(const int Op1, const int Op2, const char Op)
{
	if (Op == '+')
		return NumToStr(Op1 + Op2);
	else if (Op == '-')
		return NumToStr(Op1 - Op2);
	else if (Op == '*')
		return NumToStr(Op1 * Op2);
	else if (Op == '/')
		return NumToStr(Op1 / Op2);
	else if (Op == '%')
		return NumToStr(Op1 % Op2);
	else if (Op == '^')
		return NumToStr(Op1 ^ Op2);
	else if (Op == '$')
		return NumToStr(Op1 ^ Op2);

	return "0";
}
//Solves Postfix Expression
string EvaluatePostNExp(const string& Postfix)
{
	Stack<string> TokenStack;
	string token;

	for (int i = 0; i < Postfix.length() - 1; i++)
	{
		token = SeperateVar(Postfix, i);

		if (IsOperatorStr(token))
			TokenStack.Push(ApplyOperation(StrToNum(TokenStack.PopR()), StrToNum(TokenStack.PopR()), token[0]));
		else if (IsOperandStr(token))
			TokenStack.Push(token);
	}
	return TokenStack.PopR();
}
//Solves Prefix Expression
string EvaluatePreNExp(const string& Prefix)
{
	Stack<string> TokenStack;
	string token, Express = RevString(Prefix);

	for (int i = 0; i < Express.length() - 1; i++)
	{
		token = SeperateVar(Express, i);

		if (IsOperatorStr(token))
			TokenStack.Push(ApplyOperation(StrToNum(TokenStack.PopR()), StrToNum(TokenStack.PopR()), token[0]));
		else if (IsOperandStr(token))
			TokenStack.Push(token);
	}
	return TokenStack.PopR();
}
//Converts Postfix to Infix String
string EvaluatePostfix(const string& Postfix)
{
	string token;
	Stack<string> TokenStack;

	for (int i = 0; Postfix[i] != '\0'; i++)
	{
		token = SeperateVar(Postfix, i);

		if (IsOperandStr(token))
			TokenStack.Push(token);
		else if (IsOperator(token[0]))
			TokenStack.Push(CreatePostToken(TokenStack, token[0]));
	}
	return TokenStack.PopR();
}
//Converts Prefix to Infix String
string EvaluatePrefix(const string& Prefix)
{
	Stack<string> TokenStack;
	string token, Express = RevString(Prefix);

	for (int i = 0; Prefix[i] != '\0'; i++)
	{
		token = SeperateVar(Express, i);
		if (IsOperator(token[0]))
			TokenStack.Push(CreatePreToken(TokenStack, token[0]));
		else if (IsOperandStr(token))
			TokenStack.Push(token);
	}
	return TokenStack.PopR();
}

//string EvaluatePostfix(const string& Postfix)
//{
//	string token;
//	Stack<string> TokenStack;
//
//	for (int i = 0; Postfix[i] != '\0'; i++)
//	{
//		//token = Postfix[i];
//		token = SeperateVar(Postfix, i);
//
//		if (IsNumber(token[0]))
//			return EvaluateNumberExp(TokenStack, Postfix);
//		else if (IsOperand(token[0]))
//			TokenStack.Push(token);
//		else if (IsOperator(token[0]))
//			TokenStack.Push(CreatePostToken(TokenStack, token[0]));
//	}
//	return TokenStack.PopR();
//}
//string EvaluatePrefix(const string& Prefix)
//{
//	Stack<string> TokenStack;
//	string token, Express = RevString(Prefix);
//
//	for (int i = 0; Prefix[i] != '\0'; i++)
//	{
//		//token = Express[i];
//		token = SeperateVar(Express, i);
//		if (IsOperator(token[0]))
//			TokenStack.Push(CreatePreToken(TokenStack, token[0]));
//		else if (IsOperandStr(token))
//			TokenStack.Push(token);
//		/*else if (token[0] != ' ')
//			TokenStack.Push(CreatePreToken(TokenStack, token[0]));*/
//	}
//	return TokenStack.PopR();
//}
//bool IsExpression(const string& str)
//{
//	bool Operator = false, Operand1 = false, Operand2 = false;
//
//	for (int i = 0; i < str.length() && i < 10 && (!Operator || !Operand1 || !Operand2); i++)
//		if (IsOperator(str[i]) && Operator == false)
//			Operator = true;
//		else if (IsOperand(str[i]) && Operand1 == false)
//			Operand1 = true;
//		else if (IsOperand(str[i]) && Operand2 == false)
//			Operand2 = true;
//
//	return (Operator && Operand1 && Operand2);
//}

//Validates Postfix/Prefix Expressions
bool EvaluateExpression(const string& str)
{
	string token;
	int Operators = 0, Operands = 0;

	for (int i = 0; str[i] != '\0'; i++)
		if (IsParenthesis(str[i]) || (!IsOperator(str[i]) && !IsOperand(str[i]) && str[i] != ' '))
			return false;

	for (int i = 0; i < str.length(); i++)
	{
		token = SeperateVar(str, i);
		if (IsOperandStr(token))
			Operands++;
		else if (IsOperator(token[0]))
			Operators++;
	}
	return (Operators == Operands - 1);
}

//--------------------Syntax Error Detection--------------------//

//Determines if Token is Opening/Closing Tag or Data
const char TestToken(string& tag)
{
	if (tag[0] == '|' && tag[1] != '\\')	return 'o';
	else if (tag[0] == '|' && tag[1] == '\\')	return 'c';
	else	return 'n';
}

//Matches Opening Tag with Closing Tag
bool MatchTags(const string& str1, const string& str2)
{
	if (str1.length() != str2.length() - 1)
		return false;

	for (int i = 1; i < str1.length(); i++)
		if (str1[i] != str2[i + 1])
			return false;

	return true;
}

//Determines Balanced Brackets
bool CheckBrackets(string line)
{
	char check;
	Stack<char> PStack;
	for (int i = 0; line[i] != '\0'; i++)
	{
		if (IsOpeningPara(line[i]))
			PStack.Push(line[i]);

		else if (IsClosingPara(line[i]))
		{
			check = PStack.Peek();

			if (PStack.IsEmpty())
				return false;
			else if (check == '(' && line[i] == ')')
				PStack.Pop();
			else if (check == '{' && line[i] == '}')
				PStack.Pop();
			else if (check == '[' && line[i] == ']')
				PStack.Pop();
		}
	}
	return (PStack.IsEmpty());
}

//Validates infix Expression
//True condition: One Operator between Two Operands
bool ValidExpression(const string& str)
{
	bool Flip = false;
	string token;
	int Operators = 0, Operands = 0;

	for (int i = 0; str[i] != '\0'; i++)
	{
		token = SeperateVar(str, i);
		if (IsParenthesis(token[0]))
			continue;
		else if (IsOperandStr(token) && !Flip)
		{Operands++; Flip = true;}
		else if (IsOperatorStr(token) && Flip)
		{Operators++; Flip = false;}
		else if(str[i] != ' ' && !IsParenthesis(str[i]))
			return false;
	}
		//if (IsOperand(str[i]) && Flip == false)
		//{
		//	Operands++;
		//	Flip = true;
		//}
		//else if (IsOperator(str[i]) && Flip == true)
		//{
		//	Operators++;
		//	Flip = false;
		//}
		//else if (str[i] != ' ' && !IsParanthesis(str[i]))
		//	return false;

	return CheckBrackets(str) && (Operands == Operators + 1);
}

//Determines which type of |sol_exp| is intended
//Returns 'a' EvaluatePostNExp to solve a Postfix string
//Returns 'b' EvaluatePreNExp to solve a Prefix string
//Returns 'o' EvaluatePostfix to convert Postfix to Infix
//Returns 'r' EvaluatePostfix to convert Prefix to Infix
const char CheckExp(const string& str)
{
	int index = 0;
	while (!IsOperand(str[index]) && !IsOperator(str[index])) index++;
	if (IsLetter(str[index])) return 'o';
	else if (IsNumber(str[index])) return 'a';

	index = str.length() - 1;
	while (!IsOperand(str[index]) && !IsOperator(str[index])) index--;
	if (IsLetter(str[index])) return 'r';
	else if (IsNumber(str[index])) return 'b';
	return 'n';
}

//--------------------Image File Path Conversion--------------------//

//Returns Number of distinct objects detected in image
string ImageDetected(const string& str)
{
	ifstream Test;
	string BasePath = "";
	bool Started = false;

	for (int i = 0; i < str.length(); i++)
		if (str[i] == '\\' && !Started)
			Started = true;
		else if (str[i] == '\\' && Started)
			BasePath += '/';
		else if (str[i] == 'i')
			BasePath += 'I';
		else if (str[i] != ' ')
			BasePath += str[i];

	BasePath += ".png";

	Test.open(BasePath);
	if (!Test.is_open()) 
		 return " Image not Found "; 
	Test.close();

	Mat Img = imread(BasePath, CV_8UC1);
	Image<unsigned char> PNG(Img);
	return SeperateObjects<unsigned char>(PNG);
}

//---------------------Parser Control Functions--------------------//

//Control Function: Calls Functions Based on Tags
string ApplyTag(const string& Data, const string& Tag)
{
	if (CompareStr(Tag, "|head|"))
	return (Data);

	else if (CompareStr(Tag, "|priorty|"))
		return "";

	else if (CompareStr(Tag, "|tab|"))
		return (Data + '\t');

	else if (CompareStr(Tag, "|paragraph|"))
		return (Data + '\n');

	else if (CompareStr(Tag, "|src|"))
		return ImageDetected(Data);

	else if (CompareStr(Tag, "|pre_exp|"))
		if (ValidExpression(Data))
			return ConvertToPrefix(Data);
		else
			return "Invalid Expression";

	else if (CompareStr(Tag, "|post_exp|"))
		if (ValidExpression(Data))
			return ConvertToPostfix(Data);
		else
			return "Invalid Expression";

	else if (CompareStr(Tag, "|In_exp|"))
		if (ValidExpression(Data))
			return ConvertToPostfix(Data);
		else
			return "Invalid Expression";

	else if (CompareStr(Tag, "|sol_exp|"))
		if (!EvaluateExpression(Data))
			return "Invalid Expression";
		else
		{
			char control = CheckExp(Data);
			if (control == 'o')
				return EvaluatePostfix(Data);
			else if (control == 'a')
				return EvaluatePostNExp(Data);
			else if (control == 'r')
				return EvaluatePrefix(Data);
			else if(control == 'b')
				return EvaluatePreNExp(Data);
		}

	return Data;
}

//Reads entire file into a Character type Stack
template <typename data>
void ReadFile(Stack<data>& CharStack, const string& filename)
{
	char ch, prev = '|';
	ifstream file(filename, ios::in);
	while (!file.eof())
	{
		file.get(ch);
		if (!((prev == '|' || prev == '\t') && ch == '\n') && ch != '\t')
			CharStack.Push(ch);

		if (IsWithinTag(ch))
			prev = ch;
	}
	file.close();
	CharStack.Pop();
}

//Converts a Character stack into String type token Stack
template <typename data>
void CompileCode(Stack<data>& TokenStack, Stack<char>& CharStack)
{
	char ch;
	data token;
	bool TagOpen = false;

	while (!CharStack.IsEmpty())
	{
		ch = CharStack.PopR();

		if (ch == '|' && TagOpen == false)
		{
			if (token.length() > 1)
				TokenStack.Push(RevString(token));
			token = ch;
			TagOpen = true;
		}
		else if (ch == '|' && TagOpen == true)
		{
			token += ch;
			TokenStack.Push(RevString(token));
			token = "";
			TagOpen = false;
		}
		else token += ch;
	}
}

//Extracts Syntax Error
bool ExtractErrors(const Stack<string>& TokenStack, const string& File)
{
	string token;
	Stack<string> TokenStackCopy(TokenStack);
	Stack<string> Tags;

	while (!TokenStackCopy.IsEmpty())
	{
		token = TokenStackCopy.PopR();

		if (TestToken(token) == 'o')
			Tags.Push(token);
		else if (TestToken(token) == 'c')
		{
			if (!MatchTags(Tags.PopR(), token))
			{
				cout << "Syntax Error : " << File << endl;
				return true;
			}
		}
	}
	return false;
}

//Converts Code from Tokens to a single string
template <typename data>
void ExecuteCode(Stack<data>& TokenStack, data& result)
{
	string token;
	Stack<data> TagStack;
	Stack<data> DataStack;

	//DataStack.Push("");
	while (!TokenStack.IsEmpty())
	{
		token = TokenStack.PopR();
		if (TestToken(token) == 'o')
			TagStack.Push(token);
		else if (TestToken(token) == 'c')
		{
			if (MatchTags(TagStack.Peek(), token))
				DataStack.Push(ApplyTag(DataStack.PopR(), TagStack.PopR()));
			//	DataStack.Push(Concatenate(DataStack.PopR(), ApplyTag(DataStack.PopR(), TagStack.PopR())));
			//	cout << DataStack.Peek() << endl;
			else return;
		}
		else if (TestToken(token) == 'n')
			DataStack.Push(token);
	}

	for (int length = DataStack.Size(); length > 1; length--)
		DataStack.Push(Concatenate(DataStack.PopR(), DataStack.PopR()));

	result = DataStack.PopR();
}

//Output String to File
void ConsoleOutput(const string& Output, const string& Filename)
{
	ofstream File(Filename, ios::app);
	for (int i = 0; Output[i] != '\0'; i++)
		File << Output[i];
	File.close();
}

//Returns Executed Code as String
string Parse(const string& filename, const string& FName)
{
	Stack<char> Codetxt;
	Stack<string> CodeObj;
	string CodeExe;

	ReadFile<char>(Codetxt, filename);
	CompileCode<string>(CodeObj, Codetxt);
	
	if (ExtractErrors(CodeObj, filename))
		CodeExe = "\nSyntax Error : " + FName + "\n\n";
	else
		ExecuteCode(CodeObj, CodeExe);

	return CodeExe;
}