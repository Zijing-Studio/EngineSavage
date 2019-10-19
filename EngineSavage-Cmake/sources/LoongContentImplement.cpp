#include "LoongContentImplement.h"

LContentInt::LContentInt()
{
	x = 0;
	LoongDebug("Constructing Int:%d", x);
}

LContentInt::LContentInt(int _x)
{
	x = _x;
	LoongDebug("Constructing Int by int:%d", x);
}

LContentInt::LContentInt(const LContent& b)
{
	x = b.to_int();
	LoongDebug("Constructing Int by const LContent&:%d", x);
}

LContentInt::LContentInt(const LContent* b)
{
	x = b->to_int();
	LoongDebug("Constructing Int by const LContent*:%d", x);
}

LContentInt::~LContentInt()
{
	x = 0;
	LoongDebug("Destructing Int", x);
}

int LContentInt::type() const
{
	return LOONG_TYPE_INT;
}

bool LContentInt::to_bool() const
{
	return x;
}

int LContentInt::to_int() const
{
	return x;
}

double LContentInt::to_double() const
{
	return x;
}

Pos LContentInt::to_pos() const
{
	return Pos(x, 0, 0);
}

string LContentInt::to_str() const
{
	char str[32];
	sprintf_s(str, "%d", x);
	return string(str);
}

LDictionary<IContent> LContentInt::to_dict() const
{
#ifdef LOONG_DEBUG
	LoongDebug("Error: Transforming Int to Dictionary");
#endif // LOONG_DEBUG

	return LDictionary<IContent>();
}

LVector<IContent> LContentInt::to_vector() const
{
	LVector<IContent> ret;
	ret[0] = IContent(*this);
	return ret;
}

LContent* LContentInt::operator+(const LContent* b) const
{
	LContentInt* result;
	switch (b->type())
	{
	case LOONG_TYPE_NULL:
#ifdef LOONG_DEBUG
		LoongDebug("Error: Content type null participated operating.");
#endif // LOONG_DEBUG
		return new LContent;
		break;
	case LOONG_TYPE_INT:
		result = new LContentInt(x + b->to_int());
		return result;
		break;
	default:
#ifdef LOONG_DEBUG
		LoongDebug("Warning: Content type doesn't fit.");
#endif // LOONG_DEBUG
		result = new LContentInt(x + b->to_int());
		return result;
		break;
	}
}

LContent* LContentInt::operator-(const LContent* b) const
{
	LContentInt* result;
	switch (b->type())
	{
	case LOONG_TYPE_NULL:
#ifdef LOONG_DEBUG
		LoongDebug("Error: Content type null participated operating.");
#endif // LOONG_DEBUG
		return new LContent;
		break;
	case LOONG_TYPE_INT:
		result = new LContentInt(x - b->to_int());
		return result;
		break;
	default:
#ifdef LOONG_DEBUG
		LoongDebug("Warning: Content type doesn't fit.");
#endif // LOONG_DEBUG
		result = new LContentInt(x - b->to_int());
		return result;
		break;
	}
}

LContent* LContentInt::operator*(const LContent* b) const
{
	LContentInt* result;
	switch (b->type())
	{
	case LOONG_TYPE_NULL:
#ifdef LOONG_DEBUG
		LoongDebug("Error: Content type null participated operating.");
#endif // LOONG_DEBUG
		return new LContent;
		break;
	case LOONG_TYPE_INT:
		result = new LContentInt(x * b->to_int());
		return result;
		break;
	default:
#ifdef LOONG_DEBUG
		LoongDebug("Warning: Content type doesn't fit.");
#endif // LOONG_DEBUG
		result = new LContentInt(x * b->to_int());
		return result;
		break;
	}
}

LContent* LContentInt::operator/(const LContent* b) const
{
	LContent* result;
	int y;
	switch (b->type())
	{
	case LOONG_TYPE_NULL:
#ifdef LOONG_DEBUG
		LoongDebug("Error: Content type null participated operating.");
#endif // LOONG_DEBUG
		return new LContent;
		break;
	case LOONG_TYPE_INT:
		y = b->to_int();
		if (!y)
		{
#ifdef LOONG_DEBUG
			LoongDebug("Error: Divisor 0 detected!");
#endif // LOONG_DEBUG
			result = new LContent;
		}
		else result = new LContentInt(x / y);
		return result;
		break;
	default:
		LoongDebug("Warning: Content type doesn't fit.");
		y = b->to_int();
		if (!y)
		{
			LoongDebug("Error: Divisor 0 detected!");
			result = new LContent;
		}
		else result = new LContentInt(x / y);
		return result;
		break;
	}
}

LContent* LContentInt::operator[](const LContent* b)
{
	LoongDebug("Error: type Int doesn't have operator []");
	return new LContent;
}

LContent* LContentInt::operator()(const LContent* b)
{
	LoongDebug("Error: type Int doesn't have operator ()");
	return new LContent;
}

LContent* LContentInt::operator^(const LContent* b) const
{
	if (b->type() == LOONG_TYPE_INT)return new LContentInt(x ^ b->to_int());
	return new LContent;
}

LContent* LContentInt::operator&(const LContent* b) const
{
	if (b->type() == LOONG_TYPE_INT)return new LContentInt(x & b->to_int());
	return new LContent;
}

LContent* LContentInt::operator|(const LContent* b) const
{
	if (b->type() == LOONG_TYPE_INT)return new LContentInt(x | b->to_int());
	return new LContent;
}

LContent* LContentInt::operator&&(const LContent* b) const
{
	if (b->type() == LOONG_TYPE_INT)return new LContentInt(x && b->to_int());
	return new LContent;
}

LContent* LContentInt::operator||(const LContent* b) const
{
	if (b->type() == LOONG_TYPE_INT)return new LContentInt(x || b->to_int());
	return new LContent;
}

LContent* LContentInt::operator<(const LContent* b) const
{
	if (b->type() == LOONG_TYPE_INT)return new LContentInt(x < b->to_int());
	return new LContent;
}

LContent* LContentInt::operator<=(const LContent* b) const
{
	if (b->type() == LOONG_TYPE_INT)return new LContentInt(x <= b->to_int());
	return new LContent;
}

LContent* LContentInt::operator>(const LContent* b) const
{
	if (b->type() == LOONG_TYPE_INT)return new LContentInt(x > b->to_int());
	return new LContent;
}

LContent* LContentInt::operator>=(const LContent* b) const
{
	if (b->type() == LOONG_TYPE_INT)return new LContentInt(x >= b->to_int());
	return new LContent;
}

LContent* LContentInt::operator==(const LContent* b) const
{
	if (b->type() == LOONG_TYPE_INT)return new LContentInt(x == b->to_int());
	return new LContent;
}

void LContentInt::Clone(LContent** pContentTarg) const
{
	if (*pContentTarg)delete *pContentTarg;
	*pContentTarg = new LContentInt(x);
}

void LContentInt::Print() const
{
	printf("%d", x);
}

string LContentInt::str() const
{
	char str[32];
	sprintf_s(str, "%d", x);
	return string(str);
}

LContentVector::LContentVector()
{
	LoongDebug("Constructing Vector Initialy.");
}

LContentVector::LContentVector(const LVector<IContent>& source_vec)
{
	vec = source_vec;
	LoongDebug("Constructing Vector by LVector<IContent>.");
	/*printf("[");
	for (int i = 0; i < source_vec.size(); i++)
	{
		if (i)printf(", ");
		source_vec.Query(i).Print();
	}
	printf("]\n");//*/
}

LContentVector::LContentVector(const LContent& b)
{
	vec = b.to_vector();
	LoongDebug("Constructing Vector by LContent&.");
}

LContentVector::LContentVector(const LContent* b)
{
	vec = b->to_vector();
	LoongDebug("Constructing Vector by LContent*.");
}

LContentVector::~LContentVector()
{
	LoongDebug("Destructing Vector");
}

int LContentVector::type() const
{
	return LOONG_TYPE_VECTOR;
}

bool LContentVector::to_bool() const
{
	return vec.size();
}

int LContentVector::to_int() const
{
	return vec.size();
}

double LContentVector::to_double() const
{
	LoongDebug("Error: Converting Vector to Double");
	return 0.0;
}

Pos LContentVector::to_pos() const
{
	LoongDebug("Error: Converting Vector to Pos");
	return Pos();
}

string LContentVector::to_str() const
{
	LoongDebug("Error: Converting Vector to string");
	return string();
}

LDictionary<IContent> LContentVector::to_dict() const
{
	LoongDebug("Error: Converting Vector to Dictionary");
	return LDictionary<IContent>();
}

LVector<IContent> LContentVector::to_vector() const
{
	return vec;
}

LContent* LContentVector::operator+(const LContent* b) const
{
	LContentVector* pResult;
	pResult = new LContentVector(vec);
	int index = vec.size();
	IContent iContent = IContent(*b);
	pResult->vec[index] = iContent;
	/*LoongDebug("New Finished.");
	int index = vec.size();
	IContent pNewNode(pResult->operator[](&LContentInt(index)));
	LoongDebug("IContent constructed.");
	IContent ib = IContent(*b);
	LoongDebug("ib constructed.");
	pNewNode.assign(ib);
	LoongDebug("Assigned");//*/
	
	return pResult;
}

LContent* LContentVector::operator-(const LContent* b) const
{
	LoongDebug("Error: No operator - for Vector.");
	return new LContent;
}

LContent* LContentVector::operator*(const LContent* b) const
{
	if (b->type() != LOONG_TYPE_INT)
	{
		LoongDebug("Error: No operator * for Vector and non-Int.");
		return new LContent;
	}
	int scale = b->to_int();
	if (scale < 0)
	{
		LoongDebug("Error: Can't multiply Vector with an negative number.");
		return new LContent;
	}
	LContentVector* pResult = new LContentVector();
	for (int x = 0; x < scale; x++)
	{
		for (int y = 0; y < vec.size(); y++)
		{
			pResult->vec[x * vec.size() + y] = vec.Query(y);
		}
	}
	return pResult;
}

LContent* LContentVector::operator/(const LContent* b) const
{
	LoongDebug("Error: No operator / for Vector.");
	return new LContent;
}

LContentPointer::LContentPointer(IContent* pSource)
{
	LoongDebug("Constructing Pointer:%p", pSource);
	pIContent = pSource;
}

LContentPointer::~LContentPointer()
{
	LoongDebug("Destructing Pointer:%p", pIContent);
}

int LContentPointer::type() const
{
	return LOONG_TYPE_POINTER;
}

bool LContentPointer::to_bool() const
{
	return pIContent->to_bool();
}

int LContentPointer::to_int() const
{
	return pIContent->to_int();
}

double LContentPointer::to_double() const
{
	return pIContent->to_double();
}

Pos LContentPointer::to_pos() const
{
	return pIContent->to_pos();
}

string LContentPointer::to_str() const
{
	return pIContent->to_str();
}

LDictionary<IContent> LContentPointer::to_dict() const
{
	return pIContent->to_dict();
}

LVector<IContent> LContentPointer::to_vector() const
{
	return pIContent->to_vector();
}

LContent* LContentPointer::operator+(const LContent* b) const
{
	return pIContent->GetContentPointer()->operator+(b);
}

LContent* LContentPointer::operator-(const LContent* b) const
{
	return pIContent->GetContentPointer()->operator-(b);
}

LContent* LContentPointer::operator*(const LContent* b) const
{
	return pIContent->GetContentPointer()->operator*(b);
}

LContent* LContentPointer::operator/(const LContent* b) const
{
	return pIContent->GetContentPointer()->operator/(b);
}

LContent* LContentPointer::operator[](const LContent* b)
{
	return pIContent->GetContentPointer()->operator[](b);
}

LContent* LContentPointer::operator()(const LContent* b)
{
	return pIContent->GetContentPointer()->operator()(b);
}

LContent* LContentPointer::operator^(const LContent* b) const
{
	return pIContent->GetContentPointer()->operator^(b);
}

LContent* LContentPointer::operator&(const LContent* b) const
{
	return pIContent->GetContentPointer()->operator&(b);
}

LContent* LContentPointer::operator|(const LContent* b) const
{
	return pIContent->GetContentPointer()->operator|(b);
}

LContent* LContentPointer::operator&&(const LContent* b) const
{
	return pIContent->GetContentPointer()->operator&&(b);
}

LContent* LContentPointer::operator||(const LContent* b) const
{
	return pIContent->GetContentPointer()->operator||(b);
}

LContent* LContentPointer::operator<(const LContent* b) const
{
	return pIContent->GetContentPointer()->operator<(b);
}

LContent* LContentPointer::operator<=(const LContent* b) const
{
	return pIContent->GetContentPointer()->operator<=(b);
}

LContent* LContentPointer::operator>(const LContent* b) const
{
	return pIContent->GetContentPointer()->operator>(b);
}

LContent* LContentPointer::operator>=(const LContent* b) const
{
	return pIContent->GetContentPointer()->operator>=(b);
}

LContent* LContentPointer::operator==(const LContent* b) const
{
	return pIContent->GetContentPointer()->operator==(b);
}

void LContentPointer::Clone(LContent** pContentTarg) const
{
	if (*pContentTarg)delete* pContentTarg;
	*pContentTarg = new LContentPointer(pIContent);
}

void LContentPointer::Print() const
{
	pIContent->Print();
}

string LContentPointer::str() const
{
	return pIContent->str();
}

void LContentPointer::assign(const IContent& source)
{
	pIContent->assign(source);
}

const IContent& LContentPointer::GetContent() const
{
	return *pIContent;
}

IContent* LContentPointer::GetContentIndex() const
{
	return pIContent;
}

LContent* LContentVector::operator[](const LContent* b)
{
	//LoongDebug("Here");
	if (b->type() != LOONG_TYPE_INT)
	{
		LoongDebug("Vector index is not int.");
		return new LContent;
	}
	int index = b->to_int();
	//LoongDebug("index:%d", index);
	if (index < 0)
	{
		LoongDebug("Error:Vector access index is negative. %d", index);
		return new LContent;
	}
	IContent* pIContent = &vec[index];
	LoongDebug("Pointer fetched! %p", pIContent);
	return new LContentPointer(pIContent);
}

LContent* LContentVector::operator()(const LContent* b)
{
	LoongDebug("Error: No operator () for Vector.");
	return new LContent;
}

void LContentVector::Clone(LContent** pContentTarg) const
{
	if (*pContentTarg)delete *pContentTarg;
	LContentVector* pContentVector = new LContentVector(vec);
	*pContentTarg = pContentVector;
}

void LContentVector::Print() const
{
	printf("[");
	for (int i = 0; i < vec.size(); i++)
	{
		if(i)printf(", ");
		vec.Query(i).Print();
	}
	printf("]");
}

string LContentVector::str() const
{
	string result = "[";
	for (int i = 0; i < vec.size(); i++)
	{
		if (i)result += ", ";
		result += vec.Query(i).str();
	}
	result += ']';
	return result;
}

LContentDouble::LContentDouble()
{
	x = 0;
}

LContentDouble::LContentDouble(double _x)
{
	x = _x;
}

LContentDouble::LContentDouble(const LContent& b)
{
	x = b.to_double();
}

LContentDouble::LContentDouble(const LContent* b)
{
	x = b->to_double();
}

LContentDouble::~LContentDouble()
{
}

int LContentDouble::type() const
{
	return LOONG_TYPE_DOUBLE;
}

bool LContentDouble::to_bool() const
{
	return x;
}

int LContentDouble::to_int() const
{
	return x;
}

double LContentDouble::to_double() const
{
	return x;
}

Pos LContentDouble::to_pos() const
{
	LoongDebug("Error: Converting Double to Pos.");
	return Pos();
}

string LContentDouble::to_str() const
{
	char str[32];
	sprintf_s(str, "%lf", x);
	return string(str);
}

LDictionary<IContent> LContentDouble::to_dict() const
{
	LoongDebug("Error: Converting Double to Dictionary.");
	return LDictionary<IContent>();
}

LVector<IContent> LContentDouble::to_vector() const
{
	LoongDebug("Error: Converting Double to Vector.");
	return LVector<IContent>();
}

LContent* LContentDouble::operator+(const LContent* b) const
{
	LContent* pResult;
	switch (b->type())
	{
	case LOONG_TYPE_INT:
		pResult = new LContentDouble(x + b->to_int());
		break;
	case LOONG_TYPE_DOUBLE:
		pResult = new LContentDouble(x + b->to_double());
		break;
	default:
		LoongDebug("Error: No operator + for Double and type %d.", b->type());
		pResult = new LContent;
		break;
	}
	return pResult;
}

LContent* LContentDouble::operator-(const LContent* b) const
{
	LContent* pResult;
	switch (b->type())
	{
	case LOONG_TYPE_INT:
		pResult = new LContentDouble(x - b->to_int());
		break;
	case LOONG_TYPE_DOUBLE:
		pResult = new LContentDouble(x - b->to_double());
		break;
	default:
		LoongDebug("Error: No operator - for Double and type %d.", b->type());
		pResult = new LContent;
		break;
	}
	return pResult;
}

LContent* LContentDouble::operator*(const LContent* b) const
{
	LContent* pResult;
	switch (b->type())
	{
	case LOONG_TYPE_INT:
		pResult = new LContentDouble(x * b->to_int());
		break;
	case LOONG_TYPE_DOUBLE:
		pResult = new LContentDouble(x * b->to_double());
		break;
	default:
		LoongDebug("Error: No operator * for Double and type %d.", b->type());
		pResult = new LContent;
		break;
	}
	return pResult;
}

LContent* LContentDouble::operator/(const LContent* b) const
{
	LContent* pResult;
	int divisor_i;
	double result;
	switch (b->type())
	{
	case LOONG_TYPE_INT:
		divisor_i = b->to_int();
		if (!divisor_i)
		{
			LoongDebug("Error: Divisor 0 detected.");
			return new LContent;
		}
		pResult = new LContentDouble(x / divisor_i);
		break;
	case LOONG_TYPE_DOUBLE:
		result = x / b->to_double();
		if (!isfinite(result))
		{
			LoongDebug("Error: Division result is not finite.");
			return new LContent;
		}
		pResult = new LContentDouble(result);
		break;
	default:
		LoongDebug("Error: No operator / for Double and type %d.", b->type());
		pResult = new LContent;
		break;
	}
	return pResult;
}

LContent* LContentDouble::operator[](const LContent* b)
{
	LoongDebug("Error: No operator[] for Double.");
	return new LContent;
}

LContent* LContentDouble::operator()(const LContent* b)
{
	LoongDebug("Error: No operator() for Double.");
	return new LContent;
}

void LContentDouble::Clone(LContent** pContentTarg) const
{
	if (*pContentTarg)delete* pContentTarg;
	*pContentTarg = new LContentDouble(x);
}

void LContentDouble::Print() const
{
	printf("%lf", x);
}

string LContentDouble::str() const
{
	char str[32];
	sprintf_s(str, "%lf", x);
	return string(str);
}

LContentString::LContentString()
{
	Str = "";
}

LContentString::LContentString(string _str)
{
	Str = _str;
}

LContentString::LContentString(const LContent& b)
{
	Str = b.to_str();
}

LContentString::LContentString(const LContent* b)
{
	Str = b->to_str();
}

LContentString::~LContentString()
{
}

int LContentString::type() const
{
	return LOONG_TYPE_STRING;
}

bool LContentString::to_bool() const
{
	return Str.length();
}

int LContentString::to_int() const
{
	LoongDebug("Error: Can't Convert string to int.");
	return 0;
}

double LContentString::to_double() const
{
	LoongDebug("Error: Can't Convert string to double.");
	return 0.0;
}

Pos LContentString::to_pos() const
{
	LoongDebug("Error: Can't Convert string to Pos.");
	return Pos();
}

string LContentString::to_str() const
{
	return Str;
}

LDictionary<IContent> LContentString::to_dict() const
{
	LoongDebug("Error: Can't Convert string to Dictionary.");
	return LDictionary<IContent>();
}

LVector<IContent> LContentString::to_vector() const
{
	LoongDebug("Error: Can't Convert string to Vector.");
	return LVector<IContent>();
}

LContent* LContentString::operator+(const LContent* b) const
{
	string result= Str,str2;
	int c;
	switch(b->type())
	{
	case LOONG_TYPE_INT:
		c = b->to_int();
		if (c<0||c>255)
		{
			LoongDebug("Error: String can't add an non-character.");
			return new LContent;
		}
		result += (char)c;
		break;
	case LOONG_TYPE_STRING:
		str2 = b->to_str();
		result += str2;
		break;
	default:
		return new LContent;
	}
	return new LContentString(result);
}

LContent* LContentString::operator-(const LContent* b) const
{
	LoongDebug("Error: No operator - for string.");
	return new LContent;
}

LContent* LContentString::operator*(const LContent* b) const
{
	string result, str2;
	int round;
	switch (b->type())
	{
	case LOONG_TYPE_INT:
		round = b->to_int();
		if (round < 0)
		{
			LoongDebug("Error: String can't multiply a negative number.");
			return new LContent;
		}
		result = "";
		for (int i = 0; i < round; i++)result += Str;
		break;
	default:
		return new LContent;
	}
	return new LContentString(result);
}

LContent* LContentString::operator/(const LContent* b) const
{
	LoongDebug("Error: No operator / for string.");
	return new LContent;
}

LContent* LContentString::operator[](const LContent* b)
{
	int index;
	switch (b->type())
	{
	case LOONG_TYPE_INT:
		index = b->to_int();
		if (index < 0 || index >= Str.size())
		{
			LoongDebug("Error: Index for string out of range.");
			return new LContent;
		}
		return new LContentInt(Str[index]);
	default:
		return new LContent;
	}
}

LContent* LContentString::operator()(const LContent* b)
{
	LoongDebug("Error: No operator () for string.");
	return new LContent;
}

void LContentString::Clone(LContent** pContentTarg) const
{
	if (*pContentTarg)delete* pContentTarg;
	*pContentTarg = new LContentString(Str);
}

void LContentString::Print() const
{
	printf("\"%s\"", Str.c_str());
}

string LContentString::str() const
{
	return "\""+Str+"\"";
}

LContentDictionary::LContentDictionary()
{
}

LContentDictionary::LContentDictionary(const LDictionary<IContent>& source_dict)
{
	dict = source_dict;
}

LContentDictionary::LContentDictionary(const LContent& b)
{
	dict = b.to_dict();
}

LContentDictionary::LContentDictionary(const LContent* b)
{
	dict = b->to_dict();
}

LContentDictionary::~LContentDictionary()
{
}

int LContentDictionary::type() const
{
	return LOONG_TYPE_DICTIONARY;
}

bool LContentDictionary::to_bool() const
{
	return dict.size();
}

int LContentDictionary::to_int() const
{
	return dict.size();
}

double LContentDictionary::to_double() const
{
	return dict.size();
}

Pos LContentDictionary::to_pos() const
{
	LoongDebug("Error: Dictionary can't convert to Pos");
	return Pos();
}

string LContentDictionary::to_str() const
{
	LoongDebug("Error: Dictionary can't convert to string");
	return string();
}

LDictionary<IContent> LContentDictionary::to_dict() const
{
	return dict;
}

LVector<IContent> LContentDictionary::to_vector() const
{
	return LVector<IContent>(dict.content_pool);
}

LContent* LContentDictionary::operator+(const LContent* b) const
{
	LoongDebug("Error: No operator + for Dictionary.");
	return new LContent;
}

LContent* LContentDictionary::operator-(const LContent* b) const
{
	LoongDebug("Error: No operator - for Dictionary.");
	return new LContent;
}

LContent* LContentDictionary::operator*(const LContent* b) const
{
	LoongDebug("Error: No operator * for Dictionary.");
	return new LContent;
}

LContent* LContentDictionary::operator/(const LContent* b) const
{
	LoongDebug("Error: No operator / for Dictionary.");
	return new LContent;
}

LContent* LContentDictionary::operator[](const LContent* b)
{
	string index;
	LContentPointer* pointer;
	if (b->type() == LOONG_TYPE_STRING)
	{
		index = b->to_str();
		bool legal = 1;
		for (char c : index)
		{
			if (c < 'a' || c>'z')legal = 0;
		}
		if (!legal)
		{
			LoongDebug("Error: Illegal index for dictionary.");
			return new LContent;
		}
		pointer = new LContentPointer(&dict[index.c_str()]);
		return pointer;
	}
	else
	{
		return new LContent;
	}
}

LContent* LContentDictionary::operator()(const LContent* b)
{
	LoongDebug("Error: No operator () for Dictionary.");
	return new LContent;
}

void LContentDictionary::Clone(LContent** pContentTarg) const
{
	if (*pContentTarg)delete* pContentTarg;
	*pContentTarg = new LContentDictionary(dict);
}

void LContentDictionary::Print() const
{
	printf("[");
	bool first = 1;
	queue<pair<int, string>> Q;
	Q.push(make_pair(0, string("")));
	while (!Q.empty())
	{
		pair<int, string> p = Q.front(); Q.pop();
		if (~dict.dict[p.first].content_index)
		{
			if (first)first = 0;
			else printf(", ");
			printf("%s:", p.second.c_str());
			dict.content_pool[dict.dict[p.first].content_index].Print();
			//cout << ":" << content_pool[dict[p.first].content_index];
		}
		for (int i = 0; i < 26; i++)
		{
			if (dict.dict[p.first].ch[i])
			{
				Q.push(make_pair(dict.dict[p.first].ch[i], p.second + (char)(i + 'a')));
			}
		}
	}
	printf("]");
}

string LContentDictionary::str() const
{
	string result = "[";
	bool first = 1;
	queue<pair<int, string>> Q;
	Q.push(make_pair(0, string("")));
	while (!Q.empty())
	{
		pair<int, string> p = Q.front(); Q.pop();
		if (~dict.dict[p.first].content_index)
		{
			if (first)first = 0;
			else result += ", ";
			result += p.second;
			result += ":";
			result += dict.content_pool[dict.dict[p.first].content_index].str();
			//cout << ":" << content_pool[dict[p.first].content_index];
		}
		for (int i = 0; i < 26; i++)
		{
			if (dict.dict[p.first].ch[i])
			{
				Q.push(make_pair(dict.dict[p.first].ch[i], p.second + (char)(i + 'a')));
			}
		}
	}
	result += ']';
	return result;
}

LContentPos::LContentPos()
{
	pos = Pos();
}

LContentPos::LContentPos(Pos _pos)
{
	pos = _pos;
}

LContentPos::LContentPos(const LContent& b)
{
	pos = b.to_pos();
}

LContentPos::LContentPos(const LContent* b)
{
	pos = b->to_pos();
}

LContentPos::~LContentPos()
{
}

int LContentPos::type() const
{
	return LOONG_TYPE_POSITION;
}

bool LContentPos::to_bool() const
{
	return pos.Length();
}

int LContentPos::to_int() const
{
	return pos.Length();
}

double LContentPos::to_double() const
{
	return pos.Length();
}

Pos LContentPos::to_pos() const
{
	return pos;
}

string LContentPos::to_str() const
{
	string result;
	char str[32];
	result = "(";
	sprintf_s(str, 32, "%d", pos.x);
	result += string(str) + ", ";
	sprintf_s(str, 32, "%d", pos.y);
	result += string(str) + ", ";
	sprintf_s(str, 32, "%d", pos.z);
	result += string(str) + ")";
	return result;
}

LDictionary<IContent> LContentPos::to_dict() const
{
	LoongDebug("Error: Pos can't convert to Dictionary.");
	return LDictionary<IContent>();
}

LVector<IContent> LContentPos::to_vector() const
{
	LoongDebug("Error: Pos can't convert to Vector.");
	return LVector<IContent>();
}

LContent* LContentPos::operator+(const LContent* b) const
{
	if (b->type() == LOONG_TYPE_POSITION)return new LContentPos(pos + b->to_pos());
	else return new LContent;
}

LContent* LContentPos::operator-(const LContent* b) const
{
	if (b->type() == LOONG_TYPE_POSITION)return new LContentPos(pos - b->to_pos());
	else return new LContent;
}

LContent* LContentPos::operator*(const LContent* b) const
{
	if (b->type() == LOONG_TYPE_INT)return new LContentPos(pos * b->to_int());
	else return new LContent;
}

LContent* LContentPos::operator/(const LContent* b) const
{
	return new LContent;
}

LContent* LContentPos::operator[](const LContent* b)
{
	if (b->type() == LOONG_TYPE_INT)
	{
		int index = b->to_int();
		if (index < 0 || index>2)return new LContent;
		LoongDebug("Index Check Passed. %d", index);
		if (index == 0)return new LContentInt(pos.x);
		if (index == 1)return new LContentInt(pos.y);
		if (index == 2)return new LContentInt(pos.z);
	}
	else if (b->type() == LOONG_TYPE_STRING)
	{
		string index = b->to_str();
		if (index == "x")return new LContentInt(pos.x);
		else if (index == "y")return new LContentInt(pos.y);
		else if (index == "z")return new LContentInt(pos.z);
		else if (index == "EliminateX")return new LContentPos(pos.EliminateX());
		else if (index == "EliminateY")return new LContentPos(pos.EliminateY());
		else if (index == "EliminateZ")return new LContentPos(pos.EliminateZ());
		else if (index == "Balance")return new LContentPos(pos.Balance());
		else if (index == "Length")return new LContentInt(pos.Length());
	}
	return new LContent;
}

LContent* LContentPos::operator()(const LContent* b)
{
	return new LContent;
}

void LContentPos::Clone(LContent** pContentTarg) const
{
	if (*pContentTarg)delete* pContentTarg;
	*pContentTarg = new LContentPos(pos);
}

void LContentPos::Print() const
{
	printf("(%d, %d, %d)", pos.x, pos.y, pos.z);
}

string LContentPos::str() const
{
	string result;
	char str[32];
	result = "(";
	sprintf_s(str, 32, "%d", pos.x);
	result += string(str) + ", ";
	sprintf_s(str, 32, "%d", pos.y);
	result += string(str) + ", ";
	sprintf_s(str, 32, "%d", pos.z);
	result += string(str) + ")";
	return result;
}
