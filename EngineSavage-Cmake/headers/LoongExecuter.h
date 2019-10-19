#pragma once
#include"LoongContent.h"
#include<stack>
#include<map>
#include<functional>
using namespace std;

//typedef IContent(*ILoongFunction)(IContent);
typedef std::function<IContent(IContent)> ILoongFunction;

class LoongCode
{
public:
	char code[8 * 1024 * 1024];
	int link[8 * 1024 * 1024];
	LoongCode();
	void LoadFromFile(const char* filename);
	void Analyze();
};

IContent LoongExecuter(const LoongCode& code,const map<string, ILoongFunction>& funcspace, map<string, IContent>& contentspace);
