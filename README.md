# C-File-reader

A file for read inside file and find specific value at a given attribute (```category.attribute```)
Support: string, int, float, double, array of int, array of float, array of double

Examples of code:

  Get a string in file:
  ```c
char* returnedString = GetStringInFile(file, "Credits.message");
printf("%s\n", returnedString);
free(returnedString);
  ```

  Get an int in file:
  ```c
int returnedInt = GetIntInFile(file, "Credits.int");
printf("%d\n", returnedInt);
  ```

  Get a float in file:
  ```c
float returnedFloat = GetFloatInFile(file, "Credits.float");
printf("%f\n", returnedFloat);
  ```

  Get a double in file:
  ```c
float returnedDouble = GetDoubleInFile(file, "Credits.double");
printf("%lf\n", returnedDouble);
  ```

  Get an int array in file:
  ```c
int returnedIntsLen = 0;
int* returnedInts = GetIntsArrayInFile(file, "Credits.ints", &returnedIntsLen);
for (int i = 0; i < returnedIntsLen; i++)
{
	printf("%d, ", returnedInts[i]);
}
free(returnedInts);
  ```

  Get a float array in file:
  ```c
int returnedFloatsLen = 0;
float* returnedFloats = GetFloatsArrayInFile(file, "Credits.floats", &returnedFloatsLen);
for (int i = 0; i < returnedFloatsLen; i++)
{
	printf("%f, ", returnedFloats[i]);
}
free(returnedFloats);
  ```

  Get a double array in file:
```c
int returnedDoublesLen = 0;
double* returnedDoubles = GetDoublesArrayInFile(file, "Credits.doubles", &returnedDoublesLen);
for (int i = 0; i < returnedDoublesLen; i++)
{
	printf("%lf, ", returnedDoubles[i]);
}
	free(returnedDoubles);
  ```
  
NOTE: You need to open and close a file to do that

Example of file.txt:

```txt
#Credits
backSprite: "backSpriteCredits.png"
message: "\"Wesh les gens !\""
int: 5
float: 5.555
double: 15.555555555
ints: [1, 2, 3, 4, 5]
floats: [1.9, 2.8, 3.7, 4.6, 5.5]
doubles: [1.12345678910, 2.12345678910, 3.12345678910, 4.12345678910, 5.12345678910]
```
