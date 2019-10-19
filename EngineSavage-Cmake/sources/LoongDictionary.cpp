#include "LoongDictionary.h"

LDictIndex::LDictIndex()
{
	memset(ch, 0, sizeof ch);
	content_index = -1;
}
