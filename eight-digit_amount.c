#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CODE 255

void help(char*);
char* read_file(char*, char*, int*);
void file_error();
int how_many_symbs_in_file(FILE*);
int control_sum(char*, int);

int main()
{
	char FileName[32] = {'\0'};
	char* textFromFile = { '\0' };
	int count_file_symbs = 0;
	int ControlSum = 0;
	help(FileName);
	textFromFile = read_file(FileName, textFromFile, &count_file_symbs);
	ControlSum = control_sum(textFromFile, count_file_symbs);
	printf("ControlSum = %d\n", ControlSum);
	return 0;
}

void help(char* FileName)
{
	printf("Enter name of file:\n");
	(void)scanf("%s", FileName);
}
void file_error()
{
	perror("Error: file not open");
	exit(-1);
}
int how_many_symbs_in_file(FILE* fin)
{
	fseek(fin, 0x00, SEEK_END);
	int count = ftell(fin);
	rewind(fin);
	return count;
}
char* read_file(char* FileName, char* textFromFile, int* count_file_symbs)
{
	FILE* fin = fopen(FileName, "rb");
	if (fin == NULL)file_error();

	*count_file_symbs = how_many_symbs_in_file(fin);

	textFromFile = (char*)calloc((*count_file_symbs)+1, sizeof(char));
	if(fin)fread(textFromFile, sizeof(char), *count_file_symbs, fin);

	if(fin)fclose(fin);

	return textFromFile;
}
int control_sum(char *textFromFile, int count_file_symbs)
{
	int C = 0, T = 0, M = MAX_CODE;
	for (int i = 0; i < count_file_symbs; i++)
	{
		T += textFromFile[i];
	}
	C = T % (M + 1);
	return C;
} 
