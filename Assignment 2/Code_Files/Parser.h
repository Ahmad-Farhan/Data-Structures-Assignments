#pragma once
#include "Header.h"
#include "ObjectSeperate.h"

//string RevString(const string&);
bool IsNumber(const char);
bool IsLetter(const char);
bool IsOperand(const char);
bool IsOperator(const char);
bool IsOperatorPM(const char);
bool IsOperatorMD(const char);
bool IsWithinTag(const char&);
bool IsClosingPara(const char&);
bool IsOpeningPara(const char&);
bool IsParenthesis(const char&);

template <typename data>
data CreateToken(Stack<data>& , const char );
template <typename data>
data CreatePostToken(Stack<data>& , char );
template <typename data>
data CreatePreToken(Stack<data>& , char );
template <typename data>
data Concatenate(const data& , const data& );

//bool IsExpression(const string& );
const char TestToken(string& );
bool MatchTags(const string& , const string& );
//bool CompareStr(const string& , const string& );
bool CheckBrackets(string );
bool ValidExpression(const string& );
string ImageDetected(const string& );
string ApplyTag(const string& , const string& );
//------------------Conversion Algorithms------------------//
bool prcd(const char , const char );
string ConvertToPostfix(const string& );
string ConvertToPrefix(const string& );
string EvaluatePostfix(const string& );
string EvaluatePrefix(const string& );
bool EvaluateExpression(const string& );
//--------------------Parser Control Functions--------------------//
template <typename data>
void ReadFile(Stack<data>& , const string& );
template <typename data>
void CompileCode(Stack<data>& , Stack<char>& );
void ExtractErrors(const Stack<string>& );
template <typename data>
void ExecuteCode(Stack<data>& , data& );
void ConsoleOutput(const string& , const string& );

string Parse(const string&, const string&);