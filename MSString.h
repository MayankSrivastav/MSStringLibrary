#ifndef MSSTRING_H
#define MSSTRING_H

#include <string.h>
#include <assert.h>
//#include <exception>
using namespace std;

// Base length of string is 16 bytes
const int ALLOC_BASE_BUFFER = 0x10;

class MSString {
public:
						MSString();
						MSString(const MSString& strText);	// TODO: Not implemented correctly
						MSString(const char *strText);

						~MSString();	// TODO: Complete implement in the end

	inline size_t		Length() const;	
	const char&			operator[](int index) const;
	//int				Compare() const;
	bool				Equals(const char* strText) const;
	inline void			Empty();
	bool				IsEmpty() const;
	void				ToLower();
	void				ToUpper();
	void				InitializeBuffer();	
	const char			*GetStringText() const;
	void				ReAllocateNeededMemory(int amountOfMemory);
	bool				IfNeededMemoryIsAllocated(int amountOfMemory);
	friend				ostream& operator<<(ostream& os, const MSString& strData);
	
protected:
	size_t				length;
	char				*strData;
	int					allocatedMemory;
	char				initialBufferAllocated[ALLOC_BASE_BUFFER];
};

MSString::MSString() {
	InitializeBuffer();
}

MSString::MSString(const MSString& strText) {
	size_t len;

	InitializeBuffer();
	len = strText.Length();

	// If textString is not null and If the 
	// needed memory is allocated then 
	// copy the string text to strData
	// i.e. the string
	if (IfNeededMemoryIsAllocated(len + 1)) {
		strcpy_s(strData, sizeof(strData), strText.strData);
		length = len;
	}
}

MSString::MSString(const char *strText) {
	size_t len;

	InitializeBuffer();
	len = strlen(strText);

	assert(sizeof(strData) <= ALLOC_BASE_BUFFER);

	// If textString is not null and If the 
	// needed memory is allocated then 
	// copy the string text to strData
	// i.e. the string
	if (strText) {
		if (IfNeededMemoryIsAllocated(len + 1)) {
			strcpy_s(strData, sizeof(initialBufferAllocated), strText);
			length = len;
		} else {
			ReAllocateNeededMemory(len + 1);
			strcpy_s(strData, len + 1, strText);
			length = len;
		}
	}
}

// Checks and returns if the string
// is empty or not
inline bool MSString::IsEmpty() const
{	
	return (strData[0] == NULL);
}

// Makes the string empty
inline void MSString::Empty() {
	if (strData) {
		strData[0] = '\0';
		length = 0;
	}
}

void MSString::InitializeBuffer() {
	length = 0;
	allocatedMemory = ALLOC_BASE_BUFFER;
	strData = initialBufferAllocated;
	strData[0] = '\0';
}

bool MSString::IfNeededMemoryIsAllocated(int amountOfMemory) {
	return (allocatedMemory >= amountOfMemory);
}

size_t MSString::Length() const {
	return length;
}

void MSString::ToLower() {
	if (strData) {
		for (auto i = 0; i < strlen(strData); ++i) {
			if (strData[i] >= 'A' && strData[i] <= 'Z') {
				strData[i] = strData[i] + 32;
			}
		}
	}	
}

void MSString::ToUpper() {
	if (strData) {
		for (auto i = 0; i < strlen(strData); ++i) {
			if (strData[i] >= 'a' && strData[i] <= 'z') {
				strData[i] = strData[i] - 32;
			}
		}
	}	
}

bool MSString::Equals(const char* strText) const {
	if (strlen(strData) != strlen(strText)) return false;

	for (auto i = 0, j = 0; strData[i] && strText[j]; ++i, ++j) {
		if (strData[i] != strText[j]) return false;
	}
	return true;	
}

const char& MSString::operator[](int index) const {
	if (index < 0 || index >= strlen(strData)) {
		throw out_of_range("Index out of range");
	}
	return strData[index];
}

void MSString::ReAllocateNeededMemory(int amountOfMemory) {
	char *buffer = new char[amountOfMemory];
	//delete [] strData;
	allocatedMemory = amountOfMemory;
	strData = buffer;
}

const char *MSString::GetStringText() const {
	return strData;
}

ostream& operator<<(ostream& os, const MSString& strData) {
	os << strData.GetStringText();
	return os;
}

MSString::~MSString() { 
	if (strData != initialBufferAllocated) {
		delete [] strData;
	}
}

#endif
