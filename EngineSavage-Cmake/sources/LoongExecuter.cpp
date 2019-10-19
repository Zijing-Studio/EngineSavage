#include "LoongExecuter.h"

LoongCode::LoongCode()
{
	memset(code, 0, sizeof code);
	memset(link, -1, sizeof link);
}

void LoongCode::LoadFromFile(const char* filename)
{
	memset(code, 0, sizeof code);
	memset(link, -1, sizeof link);
	int p = 0;
	FILE* file;
#ifdef _MSC_VER
	fopen_s(&file, filename, "r");
#else
	file = fopen(filename, "r");
#endif
	if (!file)return;
	int c;
	while (~(c = fgetc(file)))
	{
		code[p++] = c;
	}
	fclose(file);
	Analyze();
}

void LoongCode::Analyze()
{
	stack<pair<char, int>> S;
	int len = strlen(code);
	for (int i = 0; i < len; i++)
	{
		char status = 0; int front = 0;
		if (!S.empty())status = S.top().first, front = S.top().second;
		if (status=='\"')
		{
			if (code[i] == '\\')
			{
				i++;
			}
			else if (code[i] == '\"')
			{
				link[front] = i;
				link[i] = front;
				S.pop();
			}
		}
		else 
		{
			if (code[i] == '(' || code[i] == '[' || code[i] == '{' || code[i] == '\"')S.push(make_pair(code[i], i));
			else if (status)
				if (status == '(' && code[i] == ')')
				{
					link[front] = i;
					link[i] = front;
					S.pop();
				}
				else if (status == '[' && code[i] == ']')
				{
					link[front] = i;
					link[i] = front;
					S.pop();
				}
				else if (status == '{' && code[i] == '}')
				{
					link[front] = i;
					link[i] = front;
					S.pop();
				}
		}
	}
}

IContent LoongExecuter(const LoongCode& code, const map<string, ILoongFunction>& funcspace, map<string, IContent>& contentspace, int L, int R);

IContent LoongExecuter(const LoongCode& code, const map<string, ILoongFunction>& funcspace, map<string, IContent>& contentspace)
{
	return LoongExecuter(code, funcspace, contentspace, 0, strlen(code.code) - 1);
}

#define LOONG_CHAR_NULL 0
#define LOONG_CHAR_NAME 1
#define LOONG_CHAR_OPERATOR 2
#define LOONG_CHAR_SEPARATOR 3

int CharType(char c)
{
	if (c == '+')return LOONG_CHAR_OPERATOR;
	if (c == '-')return LOONG_CHAR_OPERATOR;
	if (c == '*')return LOONG_CHAR_OPERATOR;
	if (c == '/')return LOONG_CHAR_OPERATOR;
	if (c == '|')return LOONG_CHAR_OPERATOR;
	if (c == '&')return LOONG_CHAR_OPERATOR;
	if (c == '^')return LOONG_CHAR_OPERATOR;
	if (c == '<')return LOONG_CHAR_OPERATOR;
	if (c == '>')return LOONG_CHAR_OPERATOR;
	if (c == '=')return LOONG_CHAR_OPERATOR;

	if (c == ',')return LOONG_CHAR_SEPARATOR;
	if (c == ';')return LOONG_CHAR_SEPARATOR;

	if (isdigit(c))return LOONG_CHAR_NAME;
	if (isalpha(c))return LOONG_CHAR_NAME;
	if (c == '_')return LOONG_CHAR_NAME;
	if (c == '.')return LOONG_CHAR_NAME;

	return LOONG_CHAR_NULL;
}

int OpLevel(string op)
{
	if (op == "=")return 10;
	if (op == "||")return 9;
	if (op == "&&")return 8;
	if (op == "|")return 7;
	if (op == "^")return 6;
	if (op == "&")return 5;
	if (op == "==")return 4;
	if (op == "<=" || op == ">=" || op == "<" || op == ">")return 3;
	if (op == "+" || op == "-")return 2;
	if (op == "*" || op == "/")return 1;
	return 0;
}

IContent StringToNumber(string x)
{
	bool illegal = 0;
	bool dot = 0;
	for (int i = 0; i < x.size(); i++)
	{
		if (isdigit(x[i]));
		else if (x[i] == '.')
			if (dot)illegal = 1;
			else dot = 1;
		else illegal = 1;
	}
	if (illegal)return IContent();
	else if (dot)
	{
		double res = 0.0, unit = 1.0;
		bool after_dot = 0;
		for (int i = 0; i < x.size(); i++)
		{
			int c = x[i];
			if (isdigit(c))
			{
				if (!after_dot)res = res * 10 + ((long long)c - '0');
				else res = res + ((long long)c - '0') * unit;
			}
			else if (c == '.')after_dot = 1, unit = 1.0;
			unit *= 0.1;
		}
		return LContentDouble(res);
	}
	else
	{
		int res = 0;
		for (int i = 0; i < x.size(); i++)
		{
			int c = x[i];
			res = res * 10 + ((long long)c - '0');
		}
		return LContentInt(res);
	}
}

bool IsBlank(int c)
{
	if (c == ' ')return true;
	if (c == '\t')return true;
	if (c == '\n')return true;
	if (c == '\r')return true;
	if (c == 10)return true;
	return false;
}//*/

IContent LoongExecuter(const LoongCode& code, const map<string, ILoongFunction>& funcspace, map<string, IContent>& contentspace, int L, int R)
{
	while (L <= R)
	{
		int c = code.code[L];
		if (c == ' ' || c == '\t' || c == '\n' || c == '\r')L++;
		else break;
	}
	while (L <= R)
	{
		int c = code.code[R];
		if (c == ' ' || c == '\t' || c == '\n' || c == '\r')R--;
		else break;
	}
	if (L > R) return IContent();

	int type = 0;
	bool block=0;
	for (int i = L; i <= R; i++)
	{
		if (~code.link[i])i = code.link[i];
		else type = max(type, CharType(code.code[i]));
		if (code.code[i] == '}')
		{
			if (block)type = LOONG_CHAR_SEPARATOR;
			block = 1;
		}
	}
	/*printf("Code Type:%d %d %d\n", type, L, R);
	for (int i = L; i <= R; i++)
	{
		putchar(code.code[i]);
	}
	putchar('\n');
	putchar('\n');//*/

	if (type == LOONG_CHAR_SEPARATOR)
	{
		type = 0;
		for (int i = L; i <= R; i++)
		{
			if (code.code[i] == '{')type = 1;
			if (~code.link[i])i = code.link[i];
			else if (code.code[i] == ';')type = 1;
		}
		int last = L;
		if (type)
		{
			for (int i = L; i <= R; i++)
			{
				if (~code.link[i])i = code.link[i];
				else if (code.code[i] == ';')
				{
					IContent res = LoongExecuter(code, funcspace, contentspace, last, i - 1);
					last = i + 1;
				}

				if (code.code[i] == '}')
				{
					IContent res = LoongExecuter(code, funcspace, contentspace, last, i);
					last = i + 1;
				}//*/
			}
			IContent res = LoongExecuter(code, funcspace, contentspace, last, R);
			return IContent();
		}
		else
		{
			int index = 0;
			IContent res;
			for (int i = L; i <= R; i++)
			{
				if (~code.link[i])i = code.link[i];
				else if (code.code[i] == ',')
				{
					res[index].assign(LoongExecuter(code, funcspace, contentspace, last, i - 1));
					last = i + 1;
					index++;
				}
			}
			res[index].assign(LoongExecuter(code, funcspace, contentspace, last, R));
			return res;
		}
	}
	else if (type == LOONG_CHAR_OPERATOR)
	{
		string op = ""; type = 0;
		for (int i = L; i <= R; i++)
		{
			if (~code.link[i])i = code.link[i];
			if (CharType(code.code[i]) == LOONG_CHAR_OPERATOR)
			{
				op += code.code[i];
			}
			else
			{
				type = max(type, OpLevel(op));
				op = "";
			}
		}
		if (!type)
		{
			LoongDebug("Error: Undefined Operator.");
			return IContent();
		}
		else
		{
			//return IContent();
			int last = L;
			for (int i = L; i <= R; i++)
			{
				//printf("Here:%d\n",i);
				if (CharType(code.code[i]) == LOONG_CHAR_OPERATOR)
				{
					op += code.code[i];
				}
				else
				{
					int ttype = OpLevel(op);
					if (ttype == type)
					{
						IContent a, b, c;
						//printf("Op:%s a:[%d,%d] b:[%d,%d]\n", op.c_str(), L, i - 1 - op.length(), i, R);
						b.assign(LoongExecuter(code, funcspace, contentspace, i, R));
						a = LoongExecuter(code, funcspace, contentspace, L, i - 1 - op.length());
						//printf("op:%s a:%d,%s b:%d,%s\n",op.c_str(), a.type(), a.str().c_str(), b.type(), b.str().c_str());
						if (op == "=")
						{
							a.assign(b);
							return a;
						}
						else if (op == "+")
						{
							return a + b;
						}
						else if (op == "-")
						{
							return a - b;
						}
						else if (op == "*")
						{
							return a * b;
						}
						else if (op == "/")
						{
							return a / b;
						}
						else if (op == "<")
						{
							return a < b;
						}
						else if (op == ">")
						{
							return a > b;
						}
						else if (op == "<=")
						{
							return a <= b;
						}
						else if (op == ">=")
						{
							return a >= b;
						}
						else if (op == "|")
						{
							return a | b;
						}
						else if (op == "&")
						{
							return a & b;
						}
						else if (op == "^")
						{
							return a ^ b;
						}
						else if (op == "||")
						{
							return a || b;
						}
						else if (op == "&&")
						{
							return a && b;
						}
						else if (op == "==")
						{
							return a == b;
						}
					}
					op = "";
				}
				if (~code.link[i])i = code.link[i];
			}
			return IContent();
		}
	}
	else
	{
		IContent res;
		string object_name="";
		int p = L;
		while (p <= R)
		{
			object_name = "";
			while (IsBlank(code.code[p]))p++;
			if (p > R)break;
			while (CharType(code.code[p]) == LOONG_CHAR_NAME)
			{
				object_name += code.code[p];
				p++;
			}
			if (object_name == "")
			{
				if (code.code[p] == '\"')
				{
					string str = "";
					p++;
					while (p <= R && code.code[p] != '\"')
					{
						if (code.code[p] == '\\')
						{
							p++;
							if (code.code[p] == 'n')str += '\n';
							else if (code.code[p] == 't')str += '\t';
							else if (code.code[p] == '\"')str += '\"';
							else if (code.code[p] == '\\"')str += '\\';
							else str += code.code[p];
						}
						else str += code.code[p];
						p++;
					}
					res = str;
				}
				else if (code.code[p] == '('|| code.code[p] == '{')
				{
					//printf("Code:%c [%d,%d] %d %d\n", code.code[p], p + 1, code.link[p] - 1, L, R);
					res = LoongExecuter(code, funcspace, contentspace, p + 1, code.link[p] - 1);
					p = code.link[p];
				}
				else if (code.code[p] == '[')
				{
					IContent index;
					index.assign(LoongExecuter(code, funcspace, contentspace, p + 1, code.link[p] - 1));
					IContent res2;
					//printf("res:%d,%s ", res.type(), res.str().c_str());
					if (res.type() == LOONG_TYPE_POINTER || res.type() == LOONG_TYPE_POSITION)res2 = res[index], res = res2;
					else res2.assign(res[index]), res.assign(res2);
					//printf("[] index:%d,%s res_after:%d,%s\n", index.type(), index.str().c_str(), res.type(), res.str().c_str());
					p = code.link[p];
				}
				p++;
			}
			else
			{
				//printf("Obj:%s %d %d %d\n", object_name.c_str(), L, R, p);
				IContent numres = StringToNumber(object_name);
				if (numres.type())
				{
					res = numres;
				}
				else
				{
					if (object_name == "if")
					{
						while (IsBlank(code.code[p]))p++;
						if (p > R)
						{
							LoongDebug("Error: Illegal if structure.", object_name.c_str());
							return IContent();
						}
						if (code.code[p] == '(')
						{
							int statementL = p + 1, statementR = code.link[p] - 1;
							p = code.link[p] + 1;
							while (IsBlank(code.code[p]))p++;
							if (p > R)
							{
								LoongDebug("Error: Illegal if structure.", object_name.c_str());
								return IContent();
							}
							if (code.code[p] == '{')
							{
								int codeL = p, codeR = code.link[p] - 1;
								p = code.link[p] + 1;
								{
									IContent state;
									state.assign(LoongExecuter(code, funcspace, contentspace, statementL, statementR));
									//printf("If statement:%d %s\n", state.type(), state.str().c_str());
									if (state.to_bool())
									{
										state = LoongExecuter(code, funcspace, contentspace, codeL, codeR);
									}
								}
							}
							else
							{
								LoongDebug("Error: Illegal if structure.", object_name.c_str());
								return IContent();
							}
							return IContent();
						}
						else
						{
							LoongDebug("Error: Illegal if structure.", object_name.c_str());
							return IContent();
						}
					}
					else if (object_name == "while")
					{
						//printf("In while\n");
						while (IsBlank(code.code[p]))p++;
						if (p > R)
						{
							LoongDebug("Error: Illegal while structure.", object_name.c_str());
							return IContent();
						}
						//printf("code.code[p]=%c\n", code.code[p]);
						if (code.code[p] == '(')
						{
							int statementL = p + 1, statementR = code.link[p] - 1;
							//printf("while statement:[%d, %d]\n", statementL, statementR);
							p = code.link[p] + 1;
							while (IsBlank(code.code[p]))p++;
							//printf("after statement code.code[%d]=%c %d\n",p, code.code[p], (int)code.code[p]);
							if (p > R)
							{
								LoongDebug("Error: Illegal while structure.", object_name.c_str());
								return IContent();
							}
							if (code.code[p] == '{')
							{
								int codeL = p, codeR = code.link[p] - 1;
								p = code.link[p] + 1;
								//printf("while:[%d, %d]\n", codeL, codeR);
								while(true)
								{
									IContent state;
									state.assign(LoongExecuter(code, funcspace, contentspace, statementL, statementR));
									if (!state.to_bool())break;
									state = LoongExecuter(code, funcspace, contentspace, codeL, codeR);
								}
							}
							else
							{
								LoongDebug("Error: Illegal while structure.", object_name.c_str());
								return IContent();
							}
							return IContent();
						}
						else
						{
							LoongDebug("Error: Illegal while structure.", object_name.c_str());
							return IContent();
						}
					}
					else if (funcspace.count(object_name))
					{
						while (IsBlank(code.code[p]))p++;
						if (p > R)
						{
							LoongDebug("Error: Wrong Function Call. %s", object_name.c_str());
							return IContent();
						}
						if (code.code[p] == '(')
						{
							IContent var;
							var.assign(LoongExecuter(code, funcspace, contentspace, p + 1, code.link[p] - 1));
							res = funcspace.at(object_name)(var), p = code.link[p] + 1;
						}
						else
						{
							LoongDebug("Error: Wrong Function Call. %s", object_name.c_str());
							return IContent();
						}
					}
					else
					{
						res = IContent(&contentspace[object_name]);
					}
				}
			}
		}
		return res;
	}
	return IContent();
}

//+-*/|&^<>=,

//0-9 a-z A-Z _ .

//()[]{}""
