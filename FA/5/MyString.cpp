#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <memory>
#include <cstring>
#include "exception.h"



#include "MyString.h"

	MyString::MyString(const char* str)
	{
		my_str = new char[length(str) + 1];
		StrCpy(my_str, str);
	};

	MyString::MyString(const MyString& other){
		my_str = new char[length(other.my_str) + 1];
		StrCpy(my_str, other.my_str);
	};
	MyString::MyString( MyString&& other ){
		my_str = new char[length(other.my_str) + 1];
		StrCpy(my_str, other.my_str);
		delete [] other.my_str;
	};

	MyString::~MyString(){
		delete[] my_str;
	};

	void MyString::SetString(char* str){
		delete[] my_str;
		my_str = new char[length(str) + 1];
		StrCpy(my_str, str);
	};

	char* MyString::GetString() const{
		return my_str;
	};
	
	char MyString::at( size_t pos )
	{
		return empty() ? throw string_is_empty("string_is_empty") :*(my_str + pos);
	};
	int MyString::find_first_not_of( const MyString& str, size_t pos ) const
	{
		for (int i = pos; i < length(my_str); ++i)
		{
			for (int j = 0; j < length(str.my_str); ++j)
			{
				if (my_str[i] != str.my_str[j]){
					return i;
				}
			}
		}
		return -1;
	};

	int MyString::find_first_of( const MyString& str, size_t pos ) const
	{
		for (int i = pos; i < length(my_str); ++i)
		{
			for (int j = 0; j < length(str.my_str); ++j)
			{
				if (my_str[i] == str.my_str[j]){
					return i;
				}
			}
		}
		return -1;

	};
	char MyString::operator[]( size_t pos ) const
	{
		return empty() ? throw string_is_empty("string is empty") :*(my_str + pos);
	};
	bool MyString::empty() const
	{
		return length(my_str) == 0 ? true : false;
	};
	size_t MyString::length() const
	{
		size_t counter = 0;
        for( ;my_str[counter] != 0; counter++);
        return counter;
	};

	void MyString::clear()
	{
		if (length(my_str) != 0)
		{
			delete[] my_str;
		}
	};

	MyString& MyString::insert( size_t index, size_t count, char ch )
	{
		char* temp;
		auto size = length(my_str) + count;
		temp = new char[length(my_str) + 1];
		StrCpy(temp, my_str);
		if (length(my_str) != 0)
		{
			delete[] my_str;
		}
		my_str = new char[size + 1];
		for (int i = 0; i < index; ++i)
		{
			my_str[i] = temp[i];
		}
		for (int i = index; i < index + count; ++i)
		{
			my_str[i] = ch;
		}
		for (int i = index + count; i < size; ++i)
		{
			my_str[i] = temp[i - count];
		}
		my_str[size] = '\0';
		delete [] temp;
		return *this;
	}

	MyString& MyString::operator +=( const MyString& other )
	{
		int size = length(my_str) + length(other.my_str);
		char* temp = new char[size + 1];

		for (int i = 0; i < length(my_str); ++i)
		{
			temp[i] = my_str[i];
		}
		for (int i = 0; i < length(other.my_str); ++i)
		{
			temp[length(my_str) + i] = other.my_str[i];
		}
		delete [] my_str;
		my_str = new char[size + 1];
		my_str = temp;
		my_str[size] = '\0'; 
		return *this;
	};

	MyString& MyString::operator +=( const char& symbol )
	{

		char* temp;
		auto size = length(my_str) + 1;
		temp = new char[length(my_str) + 1];
		StrCpy(temp, my_str);
		if (length(my_str) != 0)
		{
			delete[] my_str;
		}
		my_str = new char[size + 1];
		StrCpy( my_str, temp);
		my_str[length(my_str)] = symbol;
		my_str[size] = '\0';
		delete [] temp;
		return *this;
	};

	int MyString::compare( const MyString& str ) const
	{
		if (length(str.my_str) == length(my_str)){
			for (int i = 0; i < length(my_str); ++i)
			{
				if (str.my_str[i] != my_str[i]){
					return i;
				}
			}
			return 0;
		}else{
			return -1;
		}
	};

	char* MyString::substr( size_t count, size_t pos) const
	{
		char* substr = substr = new char[count + 1];
		

		for (int i = pos, j = 0; i < count; ++i, ++j)
		{
			substr[j] = my_str[i];	
		}
		substr[count] = '\0';

		return substr;
	};

	size_t MyString::copy( char*& dest, size_t count, size_t pos)
	{
		int size;
		if(count + pos >= length(my_str)){
			size = length(my_str) - pos;
		}else{
			size = count;
		}
		dest = new char[size + 1];
		for (int i = pos, j = 0; j < size; ++i, ++j)
		{
			dest[j] = my_str[i];
		}
		dest[size] = '\0';
		return size;
	};
	size_t MyString::length(const char* str) const
	{
		size_t counter = 0;
        for( ;str[counter] != 0; counter++);
        return counter;
	};

	MyString& MyString::operator = ( const MyString& other ){
		if (length(my_str) != 0)
		{
			delete[] my_str;
		}
		my_str = new char[length(other.my_str) + 1];
		StrCpy(my_str, other.my_str);
		return *this;
	};


    void MyString::StrCpy(char* in_str, const char* src_str)
	{
		int i;
		for (i = 0; src_str[i] != 0; ++i)
		{
			in_str[i] = src_str[i];
		}
		in_str[i] = '\0';
	}

	MyString operator + ( const MyString& leftOperand, const MyString& rightOperand ){
		MyString temporary = leftOperand;
		temporary += rightOperand;
		return temporary;
	};

    std::ostream& operator << ( std::ostream& stream, const MyString& toOutput ){
    	return stream << toOutput.GetString(); 
    }

    std::istream& operator >> (std::istream& stream, MyString& toInput)
	{
		size_t max_size = 40;
        char *str = new char[max_size];
        stream >> str;
        toInput.SetString(str);
        delete [] str;
        return stream;
	};
