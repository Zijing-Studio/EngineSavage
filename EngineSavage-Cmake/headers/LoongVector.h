#pragma once
#include<vector>
using namespace std;

template<class T>
class LVector
{
	vector<T> vec;
public:
	LVector();
	LVector(const LVector& source);
	LVector(const vector<T>& source);
	LVector<T>& operator = (const LVector<T>& source);
	size_t size() const;
	T& operator[](size_t index);
	const T& Query(size_t index) const;
};


template<class T>
inline LVector<T>::LVector()
{
	vec.clear();//vec.reserve(128);
}

template<class T>
inline LVector<T>::LVector(const LVector& source)
{
	//vec.reserve(128);
	vec.resize(source.vec.size());
	for (int i = 0; i < vec.size(); i++)vec[i] = source.vec[i];
}

template<class T>
inline LVector<T>::LVector(const vector<T>& source)
{
	vec = source;
}

template<class T>
inline LVector<T>& LVector<T>::operator=(const LVector<T>& source)
{
	//vec.reserve(128);
	vec.resize(source.vec.size());
	for (int i = 0; i < vec.size(); i++)vec[i] = source.vec[i];
	return *this;
}

template<class T>
inline size_t LVector<T>::size() const
{
	return vec.size();
}

template<class T>
inline T& LVector<T>::operator[](size_t index)
{
	if (size() < index + 1)vec.resize(index + 1);
	return vec[index];
}

template<class T>
inline const T& LVector<T>::Query(size_t index) const
{
	return vec[index];
}
