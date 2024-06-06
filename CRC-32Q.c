#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define POLYNOM 2168537515 //  1000 0001 0100 0001 0100 0001 1010 1011  -  CRC-32Q
#define MAX_CODE 256
#define BYTE 8

void help(char*);
char* read_file(char*, char*, int*);
void file_error();
int how_many_symbs_in_file(FILE*);
unsigned long crc32Q(char*, int);
void bin(unsigned long, int);

int main()
{
	char FileName[32] = { '\0' };
	char* textFromFile = { '\0' };
	int count_file_symbs = 0;
	help(FileName);
	textFromFile = read_file(FileName, textFromFile, &count_file_symbs);
	//printf("Text from file:\n%s\n", textFromFile);
	unsigned long CRC = crc32Q(textFromFile, count_file_symbs);
	printf("CRC-32Q = DEC - %lu, HEX - 0x%X, ", CRC, CRC);
	bin(CRC, sizeof(int));
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

	textFromFile = (char*)calloc((*count_file_symbs) + 1, sizeof(char));
	if(fin)fread(textFromFile, sizeof(char), *count_file_symbs, fin);

	if(fin)fclose(fin);

	return textFromFile;
}

unsigned long crc32Q(char* textFromFile, int count_file_symbs)
{
	char* buffer = textFromFile;
	unsigned int CRC = 0;
	while (count_file_symbs--)
	{
		CRC = CRC ^ (*buffer << 24);
		for (int i = 0; i < BYTE; i++) 
		{
			CRC = CRC & 0x80000000 ? (CRC << 1) ^ POLYNOM : CRC << 1;
		}
		buffer++;
	}
	CRC = CRC ^ 0;
	return (CRC);
}

void bin(unsigned long k, int size)
{
	printf("BIN - 0b");
	for (int i = size * 8; i > 0; --i) {
		printf("%d", (k & ((unsigned long)1 << (i - 1))) ? 1 : 0);
	}
	printf("\n");
}
