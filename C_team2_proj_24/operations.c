#include "essential.h"

char Add(StrStruct* Str1, StrStruct* Str2, StrStruct* Target) { // Str1 + Str2를 수행하고, 결괏값을 Target에 저장한다. 함수 성공 시 1, 실패 시 0을 return
	uint8 reallocFlag = 0; // realloc()이 발생했는지 나타내는 Flag
	uint64 NewSize = 0; // realloc()을 한 경우, realloc() 한 크기를 저장하는 변수

	if (strlen(Str1->Str) + strlen(Str2->Str) >= MAX_STR_SIZE) { // 만약 Str1+Str2의 크기가 Target의 크기(MAX_STR_SIZE)보다 크다면
		NewSize = strlen(Str1->Str) + strlen(Str2->Str) + 1; // 'Str1 + Str2의 길이 + 1'만큼을 NewSize 변수에 저장.( +1은 NULL byte를 위함 ) 
		Target->Str = (char*)realloc(Target->Str, NewSize); // NewSize 크기만큼 realloc() 진행

		if (!Target->Str) { // realloc() 실패 시, 프로세스 종료
			printf("[Fatal] realloc() failed\n\n");
			exit(1); // exit(0): Exit Success <-> exit(1): Exit Failure
		}
		reallocFlag = 1; // realloc()이 발생했으므로, reallofFlag를 1로 set
	}
	if (Str1->Type == 1 || Str2->Type == 1) { // 만약 Str1->Type이 1(Integer)이거나 Str2->Type이 1(Integer)라면, 문자열과 Integer의 연산은 불가하므로 오류 발생
		printf("[!] Error occurred while adding>> \"%s + %s\"\n", Str1->Str, Str2->Str);
		printf("[!] Integer와 String을 합칠 수 없습니다.\n");
		printf("[Info] 문자열 간 나눗셈 연산 시, 결괏값은 Integer가 됩니다.\n\n");
		return 0; // return fail
	}

	if (!reallocFlag) // realloc()이 발생하지 않은 경우, 원래 Target의 크기(MAX_STR_SIZE)만큼 sprintf_s() 진행
		sprintf_s(Target->Str, MAX_STR_SIZE, "%s%s", Str1->Str, Str2->Str);
	else // realloc()이 발생한 경우, NewSize만큼 sprintf_s() 진행
		sprintf_s(Target->Str, NewSize, "%s%s", Str1->Str, Str2->Str);


	return 1; // return success
}

char Subtract(StrStruct* Str1, StrStruct* Str2, StrStruct* Target) { // Str1 - Str2 수행 후, 결괏값을 Target에 저장. 함수 성공 시 1, 실패 시 0 return
	uint8 reallocFlag = 0; // Add 함수와 동일
	uint64 NewSize = 0; // Add 함수와 동일

	if (strlen(Str1->Str) >= MAX_STR_SIZE) { // Str1의 크기가 MAX_STR_SIZE보다 큰 경우
		NewSize = strlen(Str1->Str) + 1;
		Target->Str = (char*)realloc(Target->Str, NewSize); // Target을 NewSize 크기로 realloc

		if (!Target->Str) { // realloc() 실패 시 프로세스 종료
			printf("[Fatal] realloc() failed\n\n");
			exit(1);
		}
		reallocFlag = 1;
	}

	if (Str1->Type == 1 || Str2->Type == 1) { // Add 함수와 동일한 검사
		printf("[!] Error occurred while subtracting>> \"%s - %s\"\n", Str1->Str, Str2->Str);
		printf("[!] Integer와 String을 연산할 수 없습니다.\n");
		printf("[Info] 문자열 간 나눗셈 연산 시, 결괏값은 Integer가 됩니다.\n\n");
		return 0;
	}

	char* Ptr = strstr(Str1->Str, Str2->Str); // Str1에서 Str2를 찾는다. Str1에서 Str2를 찾았을 경우 Ptr는 0이 아니다 <-> 못찾았을 경우 Ptr는 0이다.

	if (!reallocFlag) { // realloc이 발생하지 않은 경우, MAX_STR_SIZE를 토대로 연산 수행
		if (!Ptr) { // Str1에서 Str2를 못찾은 경우.
			sprintf_s(Target->Str, MAX_STR_SIZE, "%s", Str1->Str); // 결괏값은 여전히 Str1이다
		}
		else { // Str1에서 Str2를 찾은 경우
			strncpy_s(Target->Str, MAX_STR_SIZE, Str1->Str, Ptr - Str1->Str); // Str1에서 '찾은 String' 전까지 Target에 복사
			sprintf_s(Target->Str, MAX_STR_SIZE, "%s%s", Target->Str, Ptr + strlen(Str2->Str)); // Str1에서 '찾은 String' 이후 내용 Target에 복사
		}
	}
	else { // realloc이 발생한 경우, NewSize를 토대로 연산 수행
		if (!Ptr) { // Str1에서 Str2를 못찾은 경우
			sprintf_s(Target->Str, NewSize, "%s", Str1->Str); // 결괏값은 여전히 Str1이다.
		}
		else { // Str1에서 Str2를 찾은 경우
			strncpy_s(Target->Str, NewSize, Str1->Str, Ptr - Str1->Str); // Str1에서 '찾은 String' 전까지 Target에 복사
			sprintf_s(Target->Str, NewSize, "%s%s", Target->Str, Ptr + strlen(Str2->Str)); // Str1에서 '찾은 String' 이후 내용 Target에 복사
		}
	}

	return 1; // return success
}

char Multiply(StrStruct* Str1, StrStruct* MulNum, StrStruct* Target) { // Str1을 MulNum만큼 반복하고, 결괏값을 Target에 저장한다.
	uint8 reallocFlag = 0; // Add 함수와 동일
	uint64 NewSize = 0; // Add 함수와 동일

	for (uint32 i = 0; i < strlen(MulNum->Str); i++) {
		if (!isdigit(MulNum->Str[i]) && MulNum->Str[i] != ' ') {
			printf("[!] Error occurred while multiplying>> \"%s * %s\"\n", Str1->Str, MulNum->Str);
			printf("[!] String 곱셈 연산 시, 곱할 숫자로는 Integer가 와야 합니다(ex. Hello * 3)\n\n");
			return 0;
		}
	}
	if (Str1->Type == 1) {
		printf("[!] Error occurred while multiplying>> \"%s * %s\"\n", Str1->Str, MulNum->Str);
		printf("[!] 이 계산기는 문자열 계산기입니다. Integer와 Integer의 곱셈은 지원하지 않습니다.\n");
		printf("[Info] 문자열 간 나눗셈 연산 시, 결괏값은 Integer가 됩니다.\n\n");
		return 0;
	}

	uint64 Count = strtoull(MulNum->Str, NULL, 10); // 문자열인 MulNum->Str을 uint64 type으로 변환하여 Count에 저장한다.

	if (strlen(Str1->Str) * Count >= MAX_STR_SIZE) { // Str1*Count의 길이가 MAX_STR_SIZE보다 긴 경우 realloc 해준다 START
		NewSize = strlen(Str1->Str) * Count; // NewSize는 Str1*Count의 길이 + 1
		Target->Str = (char*)realloc(Target->Str, NewSize + 1);
		if (!Target->Str) {
			printf("[Fatal] realloc() failed\n\n");
			exit(1);
		}
		reallocFlag = 1;
	} // Multiply 한 결괏값의 길이가 MAX_STR_SIZE보다 긴 경우 realloc 해준다 END

	if (!reallocFlag) { // realloc이 발생하지 않은 경우, 원래 Target의 크기인 MAX_STR_SIZE를 토대로 연산 수행
		for (uint64 i = 0; i < Count; i++) {
			if (i == 0)
				strcpy_s(Target->Str, MAX_STR_SIZE, Str1->Str); // i == 0일 때는 strcpy_s()를 통해 Str1->Str의 내용을 Target->Str 공간에 복사한다
			else
				strcat_s(Target->Str, MAX_STR_SIZE, Str1->Str); // i != 0일 때는, strcat_s()를 Count-1번만큼 반복한다.
		}
	}
	else { // realloc이 발생한 경우
		for (uint64 i = 0; i < NewSize; i++) {
			if (i == 0)
				strcpy_s(Target->Str, NewSize + 1, Str1->Str);
			else
				strcat_s(Target->Str, NewSize + 1, Str1->Str);
		}
	}

	return 1;
}

char Divide(StrStruct* Str1, StrStruct* Str2, StrStruct* Target) { // Str1에서 Str2가 몇 개 있는지 센 후, 결괏값을 Target에 저장
	if (Str1->Type == 1 || Str2->Type == 1) { // Add 함수와 동일한 검사
		printf("[!] Error occurred while dividing>> \"%s / %s\"\n", Str1->Str, Str2->Str);
		printf("[!] Integer와 String을 연산할 수 없습니다\n");
		printf("[Info] 문자열 간 나눗셈 연산 시, 결괏값은 Integer가 됩니다.\n\n");
		return 0;
	}

	uint32 Count = 0; // Str1에 Str2가 몇 개 들어있는지를 저장할 변수
	char* Ptr = Str1->Str; // 반복문 순회를 위한 변수. Ptr의 초기값은 Str1->Str의 시작 주소이다

	while (1) { // Str1에서 Str2가 들어있는 개수 찾기 START
		if (Ptr = strstr(Ptr, Str2->Str)) { // Ptr 위치에서부터 Str2를 찾은 경우
			Ptr += strlen(Str2->Str); // Ptr 변수를 Str1에서 Str2가 위치한 위치 바로 뒤를 가리키도록 수정한다.
			Count++; // Count 1 증가
			if (Ptr[0] == 0) // 만약 Ptr가 가리키는 위치의 값이 NULL이라면
				break; // 반복문 break
		}
		else { // Str1에서 Str2를 못찾은 경우
			break; // 반복문 탈출
		}
	} // Str1에서 Str2가 들어있는 개수 찾기 END

	sprintf_s(Target->Str, MAX_STR_SIZE, "%u", Count); // Target에 Count 값을 문자열로 치환하여 저장
	Target->Type = 1; // 나눗셈의 결괏값은 Integer이므로, 결괏값이 담기는 Taret의 Type 멤버를 1(Integer)로 설정해준다.

	return 1; // return success
}