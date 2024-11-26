#include "essential.h"

char Add(StrStruct* Str1, StrStruct* Str2, StrStruct* Target) {
	if (Str1->Type == 1 || Str2->Type == 1) {
		printf("[!] Error occurred while adding>> %s + %s [!]\n", Str1->Str, Str2->Str);
		printf("Integer와 String을 합칠 수 없습니다(Info. 문자열 간 나눗셈 연산 시, 결괏값은 Integer가 됩니다).\n");
		return 0;
	}
	else {
		sprintf_s(Target->Str, 0x1000, "%s%s", Str1->Str, Str2->Str);
	}

	free(Str1->Str);
	free(Str1);
	free(Str2->Str);
	free(Str2);

	return 1;
}

char Subtract(StrStruct* Str1, StrStruct* Str2, StrStruct* Target) {
	if (Str1->Type == 1 || Str2->Type == 1) {
		printf("[!] Error occurred while subtracting>> %s - %s [!]\n", Str1->Str, Str2->Str);
		printf("Integer와 String을 연산할 수 없습니다(Info. 문자열 간 나눗셈 연산 시, 결괏값은 Integer가 됩니다).\n");
		return 0;
	}

	char* Ptr = strstr(Str1->Str, Str2->Str);
	if (!Ptr) {
		sprintf_s(Target->Str, 0x1000, "%s", Str1->Str);
	}
	else {
		strncpy_s(Target->Str, 0x1000, Str1->Str, Ptr - Str1->Str);
		sprintf_s(Target->Str, 0x1000, "%s%s", Target->Str, Ptr + strlen(Str2->Str));
	}

	free(Str1->Str);
	free(Str1);
	free(Str2->Str);
	free(Str2);

	return 1;
}

char Multiply(StrStruct* Str1, StrStruct* MulNum, StrStruct* Target) {
	for (int i = 0; i < strlen(MulNum->Str); i++) {
		if (!isdigit(MulNum->Str[i])) {
			printf("[!] Error occurred while multiplying>> %s * %s [!]\n", Str1->Str, MulNum->Str);
			printf("String 곱셈 연산 시, 곱할 숫자로는 Integer가 와야 합니다(ex. Hello * 3)\n");
			return 0;
		}
	}
	if (Str1->Type == 1) {
		printf("[!] Error occurred while multiplying>> %s * %s [!]\n", Str1->Str, MulNum->Str);
		printf("이 계산기는 문자열 계산기입니다. Integer와 Integer의 곱셈은 지원하지 않습니다(Info. 문자열 간 나눗셈 연산 시, 결괏값은 Integer가 됩니다)\n");
		return 0;
	}
	if (MulNum->Str[0] == '-') {
		printf("문자열에 음수의 Integer를 곱할 수 없습니다.");
		return 0;
	}

	int Count = strtoull(MulNum->Str, NULL, 10); // 문자열인 MulNum->Str을 uint64 type으로 변환하여 Count에 저장한다.
	if (strlen(Str1->Str) * Count > 0x1000) {
		printf("Str1 * %d를 한 길이가 0x1000보다 큽니다(지원하는 최대 문자열 길이: 0x1000)\n", Count);
		return 0;
	}

	for (int i = 0; i < Count; i++) {
		if (i == 0)
			strcpy_s(Target->Str, 0x1000, Str1->Str);
		else
			strcat_s(Target->Str, 0x1000, Str1->Str);
	}

	free(Str1->Str);
	free(Str1);
	free(MulNum->Str);
	free(MulNum);

	return 1;
}

char Divide(StrStruct* Str1, StrStruct* Str2, StrStruct* Target) {
	if (Str1->Type == 1 || Str2->Type == 1) {
		printf("[!] Error occurred while dividing>> %s / %s [!]\n", Str1->Str, Str2->Str);
		printf("Integer와 String을 연산할 수 없습니다(Info. 문자열 간 나눗셈 연산 시, 결괏값은 Integer가 됩니다).\n");
		return 0;
	}

	int Count = 0;
	char* Ptr = Str1->Str;

	while (1) {
		if (Ptr = strstr(Ptr, Str2->Str)) {
			Ptr += strlen(Str2->Str);
			Count++;
			if (Ptr[0] == 0)
				break;
		}
		else {
			break;
		}
	}

	sprintf_s(Target->Str, 0x1000, "%d", Count);
	Target->Type = 1; // Type을 1(Integer)로 설정해준다.

	free(Str1->Str);
	free(Str1);
	free(Str2->Str);
	free(Str2);

	return 1;
}

void Erase(StrStruct** StrArr, int Index) {
	free(StrArr[Index]->Str);
	StrArr[Index]->Str = NULL;

	free(StrArr[Index]);
	StrArr[Index] = NULL;

	do {
		StrArr[Index] = StrArr[Index + 1];
		Index++;
	} while (StrArr[Index] != NULL);
}