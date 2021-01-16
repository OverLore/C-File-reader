#ifndef FILEREADER_H
#define FILEREADER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/// @brief Get a string from an opened file
/// @param _file : Pointer to the opened file to read in
/// @param _attribute : String of what you want ("Category.Attribute")
/// @return The string you are searching for,
///         or NULL is attribute or category is not found
char* GetStringInFile(FILE* _file, char* _attribute);

/// @brief Get an int from an opened file
/// @param _file : Pointer to the opened file to read in
/// @param _attribute : String of what you want ("Category.Attribute")
/// @return The int you are searching for,
///         or 0 is attribute or category is not found
int GetIntInFile(FILE* _file, char* _attribute);

/// @brief Get an int array and its lenght from an opened file
/// @param _file : Pointer to the opened file to read in
/// @param _attribute : String of what you want ("Category.Attribute")
/// @param _arraySize : Pointer to an int to store lenght of returned array
/// @return The array of int you are searching for,
///         or NULL is attribute or category is not found
int* GetIntsArrayInFile(FILE* _file, char* _attribute, int* _arraySize);

/// @brief Get a float from an opened file
/// @param _file : Pointer to the opened file to read in
/// @param _attribute : String of what you want ("Category.Attribute")
/// @return The float you are searching for,
///         or 0.f is attribute or category is not found
float GetFloatInFile(FILE* _file, char* _attribute);

/// @brief Get a float array and its lenght from an opened file
/// @param _file : Pointer to the opened file to read in
/// @param _attribute : String of what you want ("Category.Attribute")
/// @param _arraySize : Pointer to an int to store lenght of returned array
/// @return The array of float you are searching for,
///         or NULL is attribute or category is not found
float* GetFloatsArrayInFile(FILE* _file, char* _attribute, int* _arraySize);

/// @brief Get a double from an opened file
/// @param _file : Pointer to the opened file to read in
/// @param _attribute : String of what you want ("Category.Attribute")
/// @return The double you are searching for,
///         or 0. is attribute or category is not found
double GetDoubleInFile(FILE* _file, char* _attribute);

/// @brief Get a double array and its lenght from an opened file
/// @param _file : Pointer to the opened file to read in
/// @param _attribute : String of what you want ("Category.Attribute")
/// @param _arraySize : Pointer to an int to store lenght of returned array
/// @return The array of double you are searching for,
///         or NULL is attribute or category is not found
double* GetDoublesArrayInFile(FILE* _file, char* _attribute, int* _arraySize);

#endif