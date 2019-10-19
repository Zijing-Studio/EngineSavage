#pragma once
#include<vector>
#include<cstring>
#include<string>
#include<queue>
#include<iostream>
#include<assert.h>
using namespace std;

class LDictIndex
{
public:
	int ch[26];
	int content_index;
	LDictIndex();
};

template<class T>
class LDictionary
{
public:
	vector<LDictIndex> dict;
	vector<T> content_pool;
	LDictionary();
	LDictionary(const LDictionary<T>& source);
	LDictionary<T>& operator= (const LDictionary<T>& source);

	T& Query(const char* index);
	T& operator[](const char* index);
	T& operator[](string index);
	size_t size() const;
	void list_index() const;
};

template<class T>
inline LDictionary<T>::LDictionary()
{
	dict.clear();
	dict.push_back(LDictIndex());
	content_pool.clear();
}

template<class T>
inline LDictionary<T>::LDictionary(const LDictionary<T>& source)
{
	dict.reserve(source.dict.size());
	for (LDictIndex i : source.dict)dict.push_back(i);
	content_pool.reserve(source.content_pool.size());
	for (T i : source.content_pool)content_pool.push_back(i);
}

template<class T>
inline LDictionary<T>& LDictionary<T>::operator=(const LDictionary<T>& source)
{
	dict.resize(source.dict.size());
	for (int i = 0; i < source.dict.size(); i++)dict[i] = source.dict[i];
	content_pool.resize(source.content_pool.size());
	for (int i = 0; i < source.content_pool.size(); i++)content_pool[i] = source.content_pool[i];
	return *this;
}

template<class T>
inline T& LDictionary<T>::Query(const char* index)
{
	int p = 0, len = strlen(index);
	for (int i = 0; i < len; i++)
	{
		int c = index[i] - 'a';
		assert(c >= 0 && c < 26);
		if (!dict[p].ch[c])
		{
			dict[p].ch[c] = dict.size();
			dict.push_back(LDictIndex());
		}
		p = dict[p].ch[c];
	}
	if (!~dict[p].content_index)
	{
		dict[p].content_index = content_pool.size();
		content_pool.push_back(T());
	}
	return content_pool[dict[p].content_index];
}

template<class T>
inline T& LDictionary<T>::operator[](const char* index)
{
	return Query(index);
}

template<class T>
inline T& LDictionary<T>::operator[](string index)
{
	return Query(index.c_str());
}

template<class T>
inline size_t LDictionary<T>::size() const
{
	return content_pool.size();
}

template<class T>
inline void LDictionary<T>::list_index() const
{
	printf("[");
	bool first = 1;
	queue<pair<int, string>> Q;
	Q.push(make_pair(0, string("")));
	while (!Q.empty())
	{
		pair<int, string> p = Q.front(); Q.pop();
		if (~dict[p.first].content_index)
		{
			if (first)first = 0;
			else printf(", ");
			printf("%s", p.second.c_str());
			//cout << ":" << content_pool[dict[p.first].content_index];
		}
		for (int i = 0; i < 26; i++)
		{
			if (dict[p.first].ch[i])
			{
				Q.push(make_pair(dict[p.first].ch[i], p.second + (char)(i + 'a')));
			}
		}
	}
	printf("]");
}
