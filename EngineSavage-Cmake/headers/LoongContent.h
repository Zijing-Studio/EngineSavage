#pragma once
#include"LoongDictionary.h"
#include"LoongVector.h"
#include"LoongDebug.h"
#include"SavageCoordinate.h"
#include<iostream>
#include<cstring>
#include<cstdio>
#include<cmath>
#include<ctime>
#include<queue>
#include<set>
#include<vector>
#include<cstdlib>
using namespace std;

#define LOONG_TYPE_NULL 0
#define LOONG_TYPE_INT 1
#define LOONG_TYPE_DOUBLE 2
#define LOONG_TYPE_POSITION 3
#define LOONG_TYPE_STRING 4
#define LOONG_TYPE_DICTIONARY 5
#define LOONG_TYPE_VECTOR 6
#define LOONG_TYPE_POINTER -1

class IContent;

class LContent
{
public:
	LContent();
	~LContent();
	virtual int type() const;
	virtual bool to_bool() const;
	virtual int to_int() const;
	virtual double to_double() const;
	virtual Pos to_pos() const;
	virtual string to_str() const;
	virtual LDictionary<IContent> to_dict() const;
	virtual LVector<IContent> to_vector() const;
	virtual	LContent* operator + (const LContent* b) const;
	virtual LContent* operator - (const LContent* b) const;
	virtual LContent* operator * (const LContent* b) const;
	virtual LContent* operator / (const LContent* b) const;
	virtual LContent* operator [] (const LContent* b);
	virtual LContent* operator () (const LContent* b);
	virtual LContent* operator ^ (const LContent* b) const;
	virtual	LContent* operator & (const LContent* b) const;
	virtual LContent* operator | (const LContent* b) const;
	virtual LContent* operator && (const LContent* b) const;
	virtual LContent* operator || (const LContent* b) const;
	virtual LContent* operator < (const LContent* b) const;
	virtual LContent* operator <= (const LContent* b) const;
	virtual LContent* operator > (const LContent* b) const;
	virtual LContent* operator >= (const LContent* b) const;
	virtual LContent* operator == (const LContent* b) const;
	virtual void Clone(LContent** pContentTarg) const;
	virtual void Print() const;
	virtual string str() const;
};


class LContentPointer :public LContent
{
	IContent* pIContent;
public:
	LContentPointer(IContent* pSource);
	~LContentPointer();
	virtual int type() const;
	virtual bool to_bool() const;
	virtual int to_int() const;
	virtual double to_double() const;
	virtual Pos to_pos() const;
	virtual string to_str() const;
	virtual LDictionary<IContent> to_dict() const;
	virtual LVector<IContent> to_vector() const;
	virtual	LContent* operator + (const LContent* b) const;
	virtual LContent* operator - (const LContent* b) const;
	virtual LContent* operator * (const LContent* b) const;
	virtual LContent* operator / (const LContent* b) const;
	virtual LContent* operator [] (const LContent* b);
	virtual LContent* operator () (const LContent* b);
	virtual LContent* operator ^ (const LContent* b) const;
	virtual	LContent* operator & (const LContent* b) const;
	virtual LContent* operator | (const LContent* b) const;
	virtual LContent* operator && (const LContent* b) const;
	virtual LContent* operator || (const LContent* b) const;
	virtual LContent* operator < (const LContent* b) const;
	virtual LContent* operator <= (const LContent* b) const;
	virtual LContent* operator > (const LContent* b) const;
	virtual LContent* operator >= (const LContent* b) const;
	virtual LContent* operator == (const LContent* b) const;
	virtual void Clone(LContent** pContentTarg) const;
	virtual void Print() const;
	virtual string str() const;
	void assign(const IContent& source);
	const IContent& GetContent() const;
	IContent* GetContentIndex() const;
};

class LContentInt :public LContent
{
	int x;
public:
	LContentInt();
	LContentInt(int _x);
	LContentInt(const LContent& b);
	LContentInt(const LContent* b);
	~LContentInt();
	virtual int type() const;
	virtual bool to_bool() const;
	virtual int to_int() const;
	virtual double to_double() const;
	virtual Pos to_pos() const;
	virtual string to_str() const;
	virtual LDictionary<IContent> to_dict() const;
	virtual LVector<IContent> to_vector() const;
	virtual	LContent* operator + (const LContent* b) const;
	virtual LContent* operator - (const LContent* b) const;
	virtual LContent* operator * (const LContent* b) const;
	virtual LContent* operator / (const LContent* b) const;
	virtual LContent* operator [] (const LContent* b);
	virtual LContent* operator () (const LContent* b);
	virtual LContent* operator ^ (const LContent* b) const;
	virtual	LContent* operator & (const LContent* b) const;
	virtual LContent* operator | (const LContent* b) const;
	virtual LContent* operator && (const LContent* b) const;
	virtual LContent* operator || (const LContent* b) const;
	virtual LContent* operator < (const LContent* b) const;
	virtual LContent* operator <= (const LContent* b) const;
	virtual LContent* operator > (const LContent* b) const;
	virtual LContent* operator >= (const LContent* b) const;
	virtual LContent* operator == (const LContent* b) const;
	virtual void Clone(LContent** pContentTarg) const;
	virtual void Print() const;
	virtual string str() const;
};


class LContentVector :public LContent
{
	LVector<IContent> vec;
public:
	LContentVector();
	LContentVector(const LVector<IContent>& source_vec);
	LContentVector(const LContent& b);
	LContentVector(const LContent* b);
	~LContentVector();
	virtual int type() const;
	virtual bool to_bool() const;
	virtual int to_int() const;
	virtual double to_double() const;
	virtual Pos to_pos() const;
	virtual string to_str() const;
	virtual LDictionary<IContent> to_dict() const;
	virtual LVector<IContent> to_vector() const;
	virtual	LContent* operator + (const LContent* b) const;
	virtual LContent* operator - (const LContent* b) const;
	virtual LContent* operator * (const LContent* b) const;
	virtual LContent* operator / (const LContent* b) const;
	virtual LContent* operator [] (const LContent* b);
	virtual LContent* operator () (const LContent* b);
	virtual void Clone(LContent** pContentTarg) const;
	virtual void Print() const;
	virtual string str() const;
};

class LContentDouble :public LContent
{
	double x;
public:
	LContentDouble();
	LContentDouble(double _x);
	LContentDouble(const LContent& b);
	LContentDouble(const LContent* b);
	~LContentDouble();
	virtual int type() const;
	virtual bool to_bool() const;
	virtual int to_int() const;
	virtual double to_double() const;
	virtual Pos to_pos() const;
	virtual string to_str() const;
	virtual LDictionary<IContent> to_dict() const;
	virtual LVector<IContent> to_vector() const;
	virtual	LContent* operator + (const LContent* b) const;
	virtual LContent* operator - (const LContent* b) const;
	virtual LContent* operator * (const LContent* b) const;
	virtual LContent* operator / (const LContent* b) const;
	virtual LContent* operator [] (const LContent* b);
	virtual LContent* operator () (const LContent* b);
	virtual void Clone(LContent** pContentTarg) const;
	virtual void Print() const;
	virtual string str() const;
};

class LContentPos :public LContent
{
	Pos pos;
public:
	LContentPos();
	LContentPos(Pos _pos);
	LContentPos(const LContent& b);
	LContentPos(const LContent* b);
	~LContentPos();
	virtual int type() const;
	virtual bool to_bool() const;
	virtual int to_int() const;
	virtual double to_double() const;
	virtual Pos to_pos() const;
	virtual string to_str() const;
	virtual LDictionary<IContent> to_dict() const;
	virtual LVector<IContent> to_vector() const;
	virtual	LContent* operator + (const LContent* b) const;
	virtual LContent* operator - (const LContent* b) const;
	virtual LContent* operator * (const LContent* b) const;
	virtual LContent* operator / (const LContent* b) const;
	virtual LContent* operator [] (const LContent* b);
	virtual LContent* operator () (const LContent* b);
	virtual void Clone(LContent** pContentTarg) const;
	virtual void Print() const;
	virtual string str() const;
};

class LContentString :public LContent
{
	string Str;
public:
	LContentString();
	LContentString(string _str);
	LContentString(const LContent& b);
	LContentString(const LContent* b);
	~LContentString();
	virtual int type() const;
	virtual bool to_bool() const;
	virtual int to_int() const;
	virtual double to_double() const;
	virtual Pos to_pos() const;
	virtual string to_str() const;
	virtual LDictionary<IContent> to_dict() const;
	virtual LVector<IContent> to_vector() const;
	virtual	LContent* operator + (const LContent* b) const;
	virtual LContent* operator - (const LContent* b) const;
	virtual LContent* operator * (const LContent* b) const;
	virtual LContent* operator / (const LContent* b) const;
	virtual LContent* operator [] (const LContent* b);
	virtual LContent* operator () (const LContent* b);
	virtual void Clone(LContent** pContentTarg) const;
	virtual void Print() const;
	virtual string str() const;
};

class LContentDictionary :public LContent
{
	LDictionary<IContent> dict;
public:
	LContentDictionary();
	LContentDictionary(const LDictionary<IContent>& source_dict);
	LContentDictionary(const LContent& b);
	LContentDictionary(const LContent* b);
	~LContentDictionary();
	virtual int type() const;
	virtual bool to_bool() const;
	virtual int to_int() const;
	virtual double to_double() const;
	virtual Pos to_pos() const;
	virtual string to_str() const;
	virtual LDictionary<IContent> to_dict() const;
	virtual LVector<IContent> to_vector() const;
	virtual	LContent* operator + (const LContent* b) const;
	virtual LContent* operator - (const LContent* b) const;
	virtual LContent* operator * (const LContent* b) const;
	virtual LContent* operator / (const LContent* b) const;
	virtual LContent* operator [] (const LContent* b);
	virtual LContent* operator () (const LContent* b);
	virtual void Clone(LContent** pContentTarg) const;
	virtual void Print() const;
	virtual string str() const;
};

class IContent
{
private:
	LContent* pContent=NULL;
public:
	IContent();
	IContent(int x);
	IContent(double x);
	IContent(Pos pos);
	IContent(const char * str);
	IContent(string str);
	IContent(IContent* pIContent);
	IContent(LContent* source);
	IContent(const LDictionary<IContent>& dict);
	IContent(const LVector<IContent>& vec);
	IContent(const IContent &content);
	IContent(const LContent& b);
	~IContent();
	int type() const;
	bool to_bool() const;
	int to_int() const;
	double to_double() const;
	Pos to_pos() const;
	string to_str() const;
	LDictionary<IContent> to_dict() const;
	LVector<IContent> to_vector() const;
	IContent operator + (const IContent& content_b) const;
	IContent operator - (const IContent& content_b) const;
	IContent operator * (const IContent& content_b) const;
	IContent operator / (const IContent& content_b) const;
	IContent operator [] (const IContent& content_b);
	IContent operator () (const IContent& content_b);
	IContent operator ^ (const IContent& content_b) const;
	IContent operator & (const IContent& content_b) const;
	IContent operator | (const IContent& content_b) const;
	IContent operator && (const IContent& content_b) const;
	IContent operator || (const IContent& content_b) const;
	IContent operator < (const IContent& content_b) const;
	IContent operator <= (const IContent& content_b) const;
	IContent operator > (const IContent& content_b) const;
	IContent operator >= (const IContent& content_b) const;
	IContent operator == (const IContent& content_b) const;
	IContent& operator = (const IContent& content_b);
	IContent& operator |= (const IContent& content_b);
	LContent* GetContentPointer() const;
	void Print() const;
	void assign(const IContent& source);
	void clear(int type);
	string str()const;
};