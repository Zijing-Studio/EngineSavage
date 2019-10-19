#include "LoongContent.h"

LContent::LContent()
{
#ifdef LOONG_DEBUG
	LoongDebug("LContent constructing TYPE:%d",type());
#endif 

}

LContent::~LContent()
{
#ifdef LOONG_DEBUG
	LoongDebug("LContent destructing TYPE:%d", type());
#endif
}

int LContent::type() const
{
	return LOONG_TYPE_NULL;
}

bool LContent::to_bool() const
{
	return false;
}

int LContent::to_int() const
{
	return 0;
}

double LContent::to_double() const
{
	return 0.0;
}

Pos LContent::to_pos() const
{
	return Pos();
}

string LContent::to_str() const
{
	return string("");
}

LDictionary<IContent> LContent::to_dict() const
{
	return LDictionary<IContent>();
}

LVector<IContent> LContent::to_vector() const
{
	return LVector<IContent>();
}

LContent* LContent::operator+(const LContent* b) const
{
#ifdef LOONG_DEBUG
	LoongDebug("Error: Content type null participated operating.");
#endif
	return new LContent;
}

LContent* LContent::operator-(const LContent* b) const
{
#ifdef LOONG_DEBUG
	LoongDebug("Error: Content type null participated operating.");
#endif
	return new LContent;
}

LContent* LContent::operator*(const LContent* b) const
{
#ifdef LOONG_DEBUG
	LoongDebug("Error: Content type null participated operating.");
#endif
	return new LContent;
}

LContent* LContent::operator/(const LContent* b) const
{
#ifdef LOONG_DEBUG
	LoongDebug("Error: Content type null participated operating.");
#endif
	return new LContent;
}

LContent* LContent::operator[](const LContent* b)
{
#ifdef LOONG_DEBUG
	LoongDebug("Error: Content type null participated operating.");
#endif
	return new LContent;
}

LContent* LContent::operator()(const LContent* b)
{
#ifdef LOONG_DEBUG
	LoongDebug("Error: Content type null participated operating.");
#endif
	return new LContent;
}

LContent* LContent::operator^(const LContent* b) const
{
	LoongDebug("Error: Operator ^ doesn't exist.");
	return new LContent;
}

LContent* LContent::operator&(const LContent* b) const
{
	LoongDebug("Error: Operator & doesn't exist.");
	return new LContent;
}

LContent* LContent::operator|(const LContent* b) const
{
	LoongDebug("Error: Operator | doesn't exist.");
	return new LContent;
}

LContent* LContent::operator&&(const LContent* b) const
{
	LoongDebug("Error: Operator && doesn't exist.");
	return new LContent;
}

LContent* LContent::operator||(const LContent* b) const
{
	LoongDebug("Error: Operator || doesn't exist.");
	return new LContent;
}

LContent* LContent::operator<(const LContent* b) const
{
	LoongDebug("Error: Operator < doesn't exist.");
	return new LContent;
}

LContent* LContent::operator<=(const LContent* b) const
{
	LoongDebug("Error: Operator <= doesn't exist.");
	return new LContent;
}

LContent* LContent::operator>(const LContent* b) const
{
	LoongDebug("Error: Operator > doesn't exist.");
	return new LContent;
}

LContent* LContent::operator>=(const LContent* b) const
{
	LoongDebug("Error: Operator >= doesn't exist.");
	return new LContent;
}

LContent* LContent::operator==(const LContent* b) const
{
	LoongDebug("Error: Operator == doesn't exist.");
	return new LContent;
}

IContent::IContent()
{
	pContent = new LContent;
}

IContent::IContent(int x)
{
	pContent = new LContentInt(x);
}

IContent::IContent(double x)
{
	pContent = new LContentDouble(x);
}

IContent::IContent(Pos pos)
{
	pContent = new LContentPos(pos);
}

IContent::IContent(const char* str)
{
	pContent = new LContentString(str);
}

IContent::IContent(string str)
{
	pContent = new LContentString(str);
}

IContent::IContent(IContent* pIContent)
{
	pContent = new LContentPointer(pIContent);
}

IContent::IContent(LContent* source)
{
	pContent = source;
}

IContent::IContent(const LDictionary<IContent>& dict)
{
	pContent = new LContentDictionary(dict);
}

IContent::IContent(const LVector<IContent>& vec)
{
	pContent = new LContentVector(vec);
}

IContent::IContent(const IContent& content)
{
	content.pContent->Clone(&pContent);
}

IContent::IContent(const LContent& b)
{
	b.Clone(&pContent);
}

IContent::~IContent()
{
	if (pContent)delete pContent;
}

int IContent::type() const
{
	return pContent->type();
}

bool IContent::to_bool() const
{
	return pContent->to_bool();
}

int IContent::to_int() const
{
	return pContent->to_int();
}

double IContent::to_double() const
{
	return pContent->to_double();
}

Pos IContent::to_pos() const
{
	return pContent->to_pos();
}

string IContent::to_str() const
{
	return pContent->to_str();
}

LDictionary<IContent> IContent::to_dict() const
{
	return pContent->to_dict();
}

LVector<IContent> IContent::to_vector() const
{
	return pContent->to_vector();
}

IContent IContent::operator+(const IContent& content_b) const
{
	return IContent(pContent->operator+(content_b.pContent));
}

IContent IContent::operator-(const IContent& content_b) const
{
	return IContent(pContent->operator-(content_b.pContent));
}

IContent IContent::operator*(const IContent& content_b) const
{
	return IContent(pContent->operator*(content_b.pContent));
}

IContent IContent::operator/(const IContent& content_b) const
{
	return IContent(pContent->operator/(content_b.pContent));
}

IContent IContent::operator[](const IContent& content_b)
{
	if (type() == LOONG_TYPE_NULL)
	{
		if (content_b.type() == LOONG_TYPE_STRING)clear(LOONG_TYPE_DICTIONARY);
		else if (content_b.type() == LOONG_TYPE_INT)clear(LOONG_TYPE_VECTOR);
	}
	else if (type() == LOONG_TYPE_POINTER)
	{
		LContentPointer* ppContent = static_cast<LContentPointer*>(pContent);
		if(ppContent->GetContentIndex()->type()==LOONG_TYPE_NULL)
			if (content_b.type() == LOONG_TYPE_STRING)ppContent->GetContentIndex()->clear(LOONG_TYPE_DICTIONARY);
			else if (content_b.type() == LOONG_TYPE_INT)ppContent->GetContentIndex()->clear(LOONG_TYPE_VECTOR);
	}
	return IContent(pContent->operator[](content_b.pContent));
}

IContent IContent::operator()(const IContent& content_b)
{
	return IContent(pContent->operator()(content_b.pContent));
}

IContent IContent::operator^(const IContent& content_b) const
{
	return IContent(pContent->operator^(content_b.pContent));
}

IContent IContent::operator&(const IContent& content_b) const
{
	return IContent(pContent->operator&(content_b.pContent));
}

IContent IContent::operator|(const IContent& content_b) const
{
	return IContent(pContent->operator|(content_b.pContent));
}

IContent IContent::operator&&(const IContent& content_b) const
{
	return IContent(pContent->operator&&(content_b.pContent));
}

IContent IContent::operator||(const IContent& content_b) const
{
	return IContent(pContent->operator||(content_b.pContent));
}

IContent IContent::operator<(const IContent& content_b) const
{
	return IContent(pContent->operator<(content_b.pContent));
}

IContent IContent::operator<=(const IContent& content_b) const
{
	return IContent(pContent->operator<=(content_b.pContent));
}

IContent IContent::operator>(const IContent& content_b) const
{
	return IContent(pContent->operator>(content_b.pContent));
}

IContent IContent::operator>=(const IContent& content_b) const
{
	return IContent(pContent->operator>=(content_b.pContent));
}

IContent IContent::operator==(const IContent& content_b) const
{
	return IContent(pContent->operator==(content_b.pContent));
}

IContent& IContent::operator=(const IContent& content_b)
{
	content_b.pContent->Clone(&pContent);
	return *this;
}

IContent& IContent::operator|=(const IContent& content_b)
{
	assign(content_b);
	return *this;
}

LContent* IContent::GetContentPointer() const
{
	return pContent;
}

void IContent::Print() const
{
//	LoongDebug("Printing type:%p", pContent);
	pContent->Print();
}

void IContent::assign(const IContent& source)
{
	if (type() == LOONG_TYPE_POINTER)
	{
		LContentPointer* ppContent = static_cast<LContentPointer*>(pContent);
		ppContent->assign(source);
	}
	else if (source.type() == LOONG_TYPE_POINTER)
	{
		LContentPointer* ppContent = static_cast<LContentPointer*>(source.pContent);
		assign(ppContent->GetContent());
	}
	else
	{
		source.pContent->Clone(&pContent);
	}
}

void IContent::clear(int type)
{
	if (pContent)delete pContent;
	switch (type)
	{
	case LOONG_TYPE_INT:
		pContent = new LContentInt;
		break;
	case LOONG_TYPE_VECTOR:
		pContent = new LContentVector;
		break;
	case LOONG_TYPE_DICTIONARY:
		pContent = new LContentDictionary;
		break;
	case LOONG_TYPE_STRING:
		pContent = new LContentString;
		break;
	case LOONG_TYPE_DOUBLE:
		pContent = new LContentDouble;
		break;
	default:
		pContent = new LContent;
		break;
	}
}

string IContent::str() const
{
	return pContent->str();
}

void LContent::Clone(LContent** pContentTarg) const
{
	if (*pContentTarg)delete* pContentTarg;
	*pContentTarg = new LContent;
}

void LContent::Print() const
{
	printf("null");
}

string LContent::str() const
{
	return string("null");
}
