#ifndef FILEREADER_H
#define FILEREADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief Get a string from an opened file
/// @param _file : Pointer to the opened file to read in
/// @param _attribute : String of what you want ("Category.Attribute")
/// @return The string you are searching for
char* GetStringInFile(FILE* _file, char* _attribute);

/// @brief Get an int from an opened file
/// @param _file : Pointer to the opened file to read in
/// @param _attribute : String of what you want ("Category.Attribute")
/// @return The int you are searching for
int GetIntInFile(FILE* _file, char* _attribute);

/// @brief Get an int array and its lenght from an opened file
/// @param _file : Pointer to the opened file to read in
/// @param _attribute : String of what you want ("Category.Attribute")
/// @param _arraySize : Pointer to an int to store lenght of returned array
/// @return The array of int you are searching for
int* GetIntsArrayInFile(FILE* _file, char* _attribute, int* _arraySize);

/// @brief Get a float from an opened file
/// @param _file : Pointer to the opened file to read in
/// @param _attribute : String of what you want ("Category.Attribute")
/// @return The float you are searching for
float GetFloatInFile(FILE* _file, char* _attribute);

/// @brief Get a float array and its lenght from an opened file
/// @param _file : Pointer to the opened file to read in
/// @param _attribute : String of what you want ("Category.Attribute")
/// @param _arraySize : Pointer to an int to store lenght of returned array
/// @return The array of float you are searching for
float* GetFloatsArrayInFile(FILE* _file, char* _attribute, int* _arraySize);

/// @brief Get a double from an opened file
/// @param _file : Pointer to the opened file to read in
/// @param _attribute : String of what you want ("Category.Attribute")
/// @return The double you are searching for
double GetDoubleInFile(FILE* _file, char* _attribute);

/// @brief Get a double array and its lenght from an opened file
/// @param _file : Pointer to the opened file to read in
/// @param _attribute : String of what you want ("Category.Attribute")
/// @param _arraySize : Pointer to an int to store lenght of returned array
/// @return The array of double you are searching for
double* GetDoublesArrayInFile(FILE* _file, char* _attribute, int* _arraySize);

#endif