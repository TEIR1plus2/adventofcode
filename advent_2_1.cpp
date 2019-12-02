// advent_2_1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

#define BYTECODE_COUNT 109
#define MAGIC_NUMBER 19690720

DWORD dwBaseByteCode[] = {
	1,0,0,3,1,1,2,3,1,3,4,3,1,5,0,3,2,10,1,19,1,19,9,23,1,23,13,27,1,10,27,31,2,31,13,35,1,10,35,39,2,9,39,43,2,43,9,47,1,6,47,51,1,10,51,55,2,55,13,59,1,59,10,63,2,63,13,67,2,67,9,71,1,6,71,75,2,75,9,79,1,79,5,83,2,83,13,87,1,9,87,91,1,13,91,95,1,2,95,99,1,99,6,0,99,2,14,0,0
};

DWORD RunByteCode(DWORD dwNoun, DWORD dwVerb, DWORD* dwByteCode)
{
	if ((dwNoun < BYTECODE_COUNT) && (dwVerb < BYTECODE_COUNT))
	{
		dwByteCode[1] = dwNoun;
		dwByteCode[2] = dwVerb;
		for (int i = 0; i < BYTECODE_COUNT; i += 4)
		{
			DWORD dwOp = dwByteCode[i];
			if (dwOp == 99)
			{
				//printf("end of code found at %d\n", i);
				break;
			}
			DWORD dwPos1 = dwByteCode[i + 1];
			DWORD dwPos2 = dwByteCode[i + 2];
			DWORD dwPos3 = dwByteCode[i + 3];
			if ((dwPos1 < BYTECODE_COUNT) && (dwPos2 < BYTECODE_COUNT) && (dwPos3 < BYTECODE_COUNT))
			{
				if (dwOp == 1)
					dwByteCode[dwPos3] = dwByteCode[dwPos1] + dwByteCode[dwPos2];
				else if (dwOp == 2)
					dwByteCode[dwPos3] = dwByteCode[dwPos1] * dwByteCode[dwPos2];
				else
					printf("unknown opcode %d at position %d\n", dwOp, i);
			}
			else
			{
				printf("out of bounds, dwPos1: %d, dwPos2: %d, dwPos3: %d\n", dwPos1, dwPos2, dwPos3);
				break;
			}
		}
	}
	return dwByteCode[0];
}

int main()
{
	DWORD* pdwByteCode = (DWORD*)malloc(BYTECODE_COUNT * sizeof(DWORD));
	for (int i = 0; i < BYTECODE_COUNT; i++)
	{
		for (int j = 0; j < BYTECODE_COUNT; j++)
		{
			memcpy(pdwByteCode, dwBaseByteCode, BYTECODE_COUNT * sizeof(DWORD));
			DWORD dwRet = RunByteCode(i, j, pdwByteCode);
			if (dwRet == MAGIC_NUMBER)
			{
				printf("noun: %d, verb: %d, answer: %d\n", i, j, (100 * i) + j);
				i = BYTECODE_COUNT;
				break;
			}
		}
	}
	if (pdwByteCode[0] != MAGIC_NUMBER)
		printf("couldn't find combo\n");
	printf("position 0: %d\n", pdwByteCode[0]);
	free(pdwByteCode);
	system("pause");
    return 0;
}

