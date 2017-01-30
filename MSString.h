#ifndef MSSTRING_H
#define MSSTRING_H
#include <string.h>
#include <assert.h>

// Base length of string is 16 bytes
const int ALLOC_BASE_BUFFER = 20;

class MSString {
public:
						MSString();
						MSString(const MSString& strText);
						MSString(const char *strText);

						~MSString();

	inline size_t		Length() const;	
	/*char				operator[](int index) const;
	int					Compare(const char *strText) const;
	void				Empty();
	bool				IsEmpty() const;
	void				ToLower();
	void				ToUpper();*/
	void				InitializeBuffer();
	//void				ReAllocateBuffer();
	const char			*GetStringText() const;
	bool				IfNeededMemoryIsAllocated(int amountOfMemory);
	//const char	*c_str() const;
	
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

	assert(sizeof(strData) == ALLOC_BASE_BUFFER);

	// If textString is not null and If the 
	// needed memory is allocated then 
	// copy the string text to strData
	// i.e. the string
	if (strText && IfNeededMemoryIsAllocated(len + 1)) {
		strcpy_s(strData, sizeof(strData), strText);
		length = len;
	}
}

void MSString::InitializeBuffer() {
	length = 0;
	allocatedMemory = ALLOC_BASE_BUFFER;
	strData = initialBufferAllocated;
	strData[0] = '\0';
}

bool MSString::IfNeededMemoryIsAllocated(int amountOfMemory) {
	return true;
}

size_t MSString::Length() const {
	return length;
}

const char *MSString::GetStringText() const {
	return strData;
}

MSString::~MSString() { }

#endif
