#include "FileReader.h"

//Return the number of elements in file array
int GetNumberOfElement(FILE* _file)
{
	char c = fgetc(_file);
	int number = 0;
	int isInString = 0;

	//Get each char between each array sperator
	while (c != ']')
	{
		if (c == '\"' && !isInString )
		{
			isInString = 1;
		}
		else if (c == '\"' && isInString)
		{
			isInString = 0;
		}
		//If we found a comma, then add a nuber
		if (c == ',' && !isInString )
		{
			c = fgetc(_file);
			number++;
		}
		c = fgetc(_file);
	}

	//Return n + 1 values (Or 0 in nothing)
	return (number > 0 ? number + 1 : 0);
}

//Check if we are reading an escape sequnce
void CheckForEscapeSequence(FILE* _file, char* _c)
{
	//If char is a backslash, define charactere as the good one escape sequence
	if (*_c == '\\')
	{
		//Analysing the next character
		*_c = fgetc(_file);
		switch (*_c)
		{
		case 'a':
			*_c = '\a';
			break;
		case 'b':
			*_c = '\b';
			break;
		case 'n':
			*_c = '\n';
			break;
		case 'r':
			*_c = '\r';
			break;
		case 't':
			*_c = '\t';
			break;
		case '\\':
			*_c = '\\';
			break;
		case '\'':
			*_c = '\'';
			break;
		case '"':
			*_c = '\"';
			break;
		case '?':
			*_c = '\?';
			break;
			//If no escape sequence is found, ignore the backslash
		default:
			break;
		}
	}
}

//Find token in text file (change cursor position)
int FindCategoryNameInFile(FILE* _file, char* _token)
{
	//Set cursor to _file origin
	fseek(_file, 0, SEEK_SET);
	char c = 0;
	char* str[50] = { 0 };
	int hasFoundCategory = 0;

	//Read each line
	while (c != EOF)
	{
		c = fgetc(_file);

		//If character is new line
		if (c == '\n')
		{
			//If scanned line is equals to the given token, break loop
			if (strcmp(str, _token) == 0)
			{
				c = EOF;
				hasFoundCategory = 1;
			}
			//else, reset word and continue
			else
			{
				memset(str, 0, sizeof(str));
			}
		}
		//Concatenate string and readed char
		else
		{
			sprintf(str, "%s%c", str, c);
		}
	}
	if (hasFoundCategory)
	{
		return 1;
	}
	else
	{
		printf("Category not found\n");
		return 0;
	}
}

//Find attribute in text file (change cursor position)
int FindAttributeNameInFile(FILE* _file, char* _token)
{
	char c = 0;
	char* str[50] = { 0 };
	int hasFoundAttribute = 0;

	//Allocate memory for store string we are searching for
	char* target = calloc(strlen(_token + 1), sizeof(char));
	//Define target string form
	sprintf(target, "%s%c", _token, ':');

	//Read each line
	while (c != EOF)
	{
		c = fgetc(_file);

		//If character is new line or attribute / value separator
		if (c == '\n' || c == ':')
		{
			//If its separator, add char to readed string
			if (c == ':')
			{
				sprintf(str, "%s%c", str, c);
			}

			//If scanned line is equals to the given token, break loop
			if (strstr(str, target))
			{
				c = EOF;
				hasFoundAttribute = 1;
			}
			//else, reset word and continue
			else
			{
				memset(str, 0, sizeof(str));
			}
		}
		//Concatenate string and readed char
		else if (c != EOF)
		{
			sprintf(str, "%s%c", str, c);
		}

		//If loop reached another category name flag, nothing was found
		if (c == '#')
		{
			c = EOF;
		}
	}
	if (hasFoundAttribute)
	{
		return 1;
	}
	else
	{
		printf("Attribute not found\n");
		return 0;
	}
}

//Find categoryname in string
char* GetCategoryName(char* _attribute)
{
	char c = 0;
	char* str;
	int strLen = strlen(_attribute);

	//Allocate memory for store string we are searching for
	str = (char*)calloc(strLen + 2, sizeof(char));
	//Catrgory name always start with its flag
	str[0] = '#';

	//Read each char
	for (int i = 0; i < strLen; i++)
	{
		c = _attribute[i];
		//If point is reached, nreak loop, category name is found
		if (c == '.')
		{
			i = strLen;
		}
		//Concatenate string and readed char
		else
		{
			sprintf(str, "%s%c", str, c);
		}
	}
	//Allocate memory for category name
	char* categoryName = (char*)calloc(strlen(str) + 2, sizeof(char));
	//Set category name to readed value
	strcpy(categoryName, str);

	free(str);

	return categoryName;
}

//Get attribute name in string
char* GetAttributeName(char* _attribute)
{
	char c = 0;
	char* str;
	int strLen = strlen(_attribute);
	char* categoryName = GetCategoryName(_attribute);

	str = (char*)calloc(strLen + 1, sizeof(char));

	//Read each char
	for (int i = strlen(categoryName); i < strLen; i++)
	{
		c = _attribute[i];
		//if attribute / file separator is reached, attribute name is found
		if (c == ':')
		{
			i = strLen;
		}
		//Concatenate string and readed char
		else
		{
			sprintf(str, "%s%c", str, c);
		}
	}

	//Allocate just enought spoace for store attribute name
	char* attributeName = (char*)calloc(strlen(str) + 1, sizeof(char));
	//Set attribute name to readed value
	strcpy(attributeName, str);

	free(str);

	return attributeName;
}

//Return the number of character in a string
int CountCharOfStringInFile(FILE* _file)
{
	int len = 0;
	char c = fgetc(_file);

	//While string end is not reached
	while (c != '\"')
	{
		CheckForEscapeSequence(_file, &c);
		len++;
		c = fgetc(_file);
	}

	return len;
}

//Return the string at given attribute
char* GetStringInFile(FILE* _file, char* _attribute)
{
	char c = 0;
	int strLen = strlen(_attribute);
	int curPos = 0;
	int valueLen;
	char* categoryName = GetCategoryName(_attribute);
	char* attributeName = GetAttributeName(_attribute);
	char* valueStr = "";
	char* str = "";

	//Decompose attribute
	if (FindCategoryNameInFile(_file, categoryName)
		&& FindAttributeNameInFile(_file, attributeName))
	{
		//Search for the first '"'
		c = fgetc(_file);
		while (c != '\"')
		{
			c = fgetc(_file);
		}

		//Store current cursor position
		curPos = ftell(_file);
		//Count number of chars of the value to read
		valueLen = CountCharOfStringInFile(_file);
		//Allocate memory for this savlue (+1 for '\0')
		valueStr = (char*)calloc(valueLen + 1, sizeof(char));
		str = (char*)calloc(valueLen + 1, sizeof(char));
		//Re place cursor in file
		fseek(_file, curPos, SEEK_SET);

		//Add each char between current pos ans the next '"' 
		//(except for escape sequence)
		c = fgetc(_file);
		while (c != '\"')
		{
			CheckForEscapeSequence(_file, &c);
			sprintf(str, "%s%c", str, c);
			c = fgetc(_file);
		}

		free(categoryName);
		free(attributeName);

		strcpy(valueStr, str);

		free(str);

		return valueStr;
	}
	else
	{
		free(categoryName);
		free(attributeName);
		return NULL;
	}

	
}

char** GetStringArrayInFile(FILE* _file, char* _attribute, int* _arraySize)
{
	char c = 0;
	char* categoryName = GetCategoryName(_attribute);
	char* attributeName = GetAttributeName(_attribute);
	int curPos = 0;
	char** stringArray = NULL;

	int* value;

	//Decompose attribute
	if (FindCategoryNameInFile(_file, categoryName)
		&& FindAttributeNameInFile(_file, attributeName))
	{
		//Search for the first array delimiter
		c = fgetc(_file);
		while (c != '[')
		{
			c = fgetc(_file);
		}

		//Store current cursor position
		curPos = ftell(_file);
		//Count the number of element in the array
		*_arraySize = GetNumberOfElement(_file);
		//allocate memory for the array
		stringArray = (char**)calloc((*_arraySize) + 1, sizeof(char*));

		//Re place cursor in file
		fseek(_file, curPos, SEEK_SET);

		for (int i = 0; i < *_arraySize; i++)
		{
			char* valueStr = "";
			char* str = "";
			int valueLen;

			//Search for the first '"'
			c = fgetc(_file);
			while (c != '\"')
			{
				c = fgetc(_file);
			}

			//Store current cursor position
			curPos = ftell(_file);
			//Count number of chars of the value to read
			valueLen = CountCharOfStringInFile(_file);
			//Allocate memory for this savlue (+1 for '\0')
			valueStr = (char*)calloc(valueLen + 1, sizeof(char));
			str = (char*)calloc(valueLen + 1, sizeof(char));
			//Re place cursor in file
			fseek(_file, curPos, SEEK_SET);

			//Add each char between current pos ans the next '"' 
			//(except for escape sequence)
			c = fgetc(_file);
			while (c != '\"')
			{
				CheckForEscapeSequence(_file, &c);
				sprintf(str, "%s%c", str, c);
				c = fgetc(_file);
			}

			strcpy(valueStr, str);

			free(str);
			// add string to the array
			stringArray[i] = valueStr;
		}
	}

	//Free returned strings after use
	free(categoryName);
	free(attributeName);
	
	return stringArray;
}

//Return the int at specified attribute
int GetIntInFile(FILE* _file, char* _attribute)
{
	char c = 0;
	char* categoryName = GetCategoryName(_attribute);
	char* attributeName = GetAttributeName(_attribute);

	int value = 0;

	//Decompose attribute
	if (FindCategoryNameInFile(_file, categoryName)
		&& FindAttributeNameInFile(_file, attributeName))
	{
		//Get the integer
		(void)fscanf(_file, "%d", &value);
	}

	//Free returned strings after use
	free(categoryName);
	free(attributeName);

	return value;
}

//Find token in text _file (change cursor position)
int* GetIntsArrayInFile(FILE* _file, char* _attribute, int* _arraySize)
{
	char c = 0;
	char* categoryName = GetCategoryName(_attribute);
	char* attributeName = GetAttributeName(_attribute);
	int curPos = 0;

	int* value = NULL;

	//Decompose attribute
	if (FindCategoryNameInFile(_file, categoryName)
		&& FindAttributeNameInFile(_file, attributeName))
	{
		//Seachr for the first array delimiter
		c = fgetc(_file);
		while (c != '[')
		{
			c = fgetc(_file);
		}

		//Store current cursor position
		curPos = ftell(_file);
		//Count the number of element in the array
		*_arraySize = GetNumberOfElement(_file);
		//Allocate memory to the array 
		value = (int*)calloc(*_arraySize, sizeof(int));

		//Re place cursor in file
		fseek(_file, curPos, SEEK_SET);

		//Get each int of the array
		for (int i = 0; i < *_arraySize; i++)
		{
			(void)fscanf(_file, "%d", &value[i]);
			fseek(_file, 1, SEEK_CUR);
		}
	}

	//Free returned strings after use
	free(categoryName);
	free(attributeName);

	return value;
}

//Find token in text _file (change cursor position)
float GetFloatInFile(FILE* _file, char* _attribute)
{
	char c = 0;
	char* categoryName = GetCategoryName(_attribute);
	char* attributeName = GetAttributeName(_attribute);

	float value = 0.f;

	//Decompose attribute
	if (FindCategoryNameInFile(_file, categoryName)
		&& FindAttributeNameInFile(_file, attributeName))
	{
			(void)fscanf(_file, "%f", &value);
	}

	//Free returned strings after use
	free(categoryName);
	free(attributeName);

	return value;
}

//Find token in text _file (change cursor position)
float* GetFloatsArrayInFile(FILE* _file, char* _attribute, int* _arraySize)
{
	char c = 0;
	char* categoryName = GetCategoryName(_attribute);
	char* attributeName = GetAttributeName(_attribute);
	int curPos = 0;

	float* value = NULL;

	//Decompose attribute
	if (FindCategoryNameInFile(_file, categoryName)
		&& FindAttributeNameInFile(_file, attributeName))
	{
		//Seachr for the first array delimiter
		c = fgetc(_file);
		while (c != '[')
		{
			c = fgetc(_file);
		}

		//Store current cursor position
		curPos = ftell(_file);
		//Count the number of element in the array
		*_arraySize = GetNumberOfElement(_file);
		//Allocate memory to the array 
		value = (float*)calloc(*_arraySize, sizeof(float));

		//Re place cursor in file
		fseek(_file, curPos, SEEK_SET);

		//Get each float of the array
		for (int i = 0; i < *_arraySize; i++)
		{
			(void)fscanf(_file, "%f", &value[i]);
			fseek(_file, 1, SEEK_CUR);
		}
	}

	//Free returned strings after use
	free(categoryName);
	free(attributeName);

	return value;
}

//Find token in text _file (change cursor position)
double GetDoubleInFile(FILE* _file, char* _attribute)
{
	char c = 0;
	char* categoryName = GetCategoryName(_attribute);
	char* attributeName = GetAttributeName(_attribute);

	double value = 0.;

	//Decompose attribute
	if (FindCategoryNameInFile(_file, categoryName)
		&& FindAttributeNameInFile(_file, attributeName))
	{
		(void)fscanf(_file, "%lf", &value);
	}
	//Free returned strings after use
	free(categoryName);
	free(attributeName);

	return value;
}

//Find token in text _file (change cursor position)
double* GetDoublesArrayInFile(FILE* _file, char* _attribute, int* _arraySize)
{
	char c = 0;
	char* categoryName = GetCategoryName(_attribute);
	char* attributeName = GetAttributeName(_attribute);
	int curPos = 0;

	double* value = NULL;

	//Decompose attribute
	if (FindCategoryNameInFile(_file, categoryName)
		&& FindAttributeNameInFile(_file, attributeName))
	{
		//Search for the first array delimiter
		c = fgetc(_file);
		while (c != '[')
		{
			c = fgetc(_file);
		}

		//Store current cursor position
		curPos = ftell(_file);
		//Count the number of element in the array
		*_arraySize = GetNumberOfElement(_file);
		//Allocate memory to the array 
		value = (double*)calloc(*_arraySize, sizeof(double));

		//Re place cursor in file
		fseek(_file, curPos, SEEK_SET);

		//Get each double of the array
		for (int i = 0; i < *_arraySize; i++)
		{
			(void)fscanf(_file, "%lf", &value[i]);
			fseek(_file, 1, SEEK_CUR);
		}
	}

	//Free returned strings after use
	free(categoryName);
	free(attributeName);

	return value;
}