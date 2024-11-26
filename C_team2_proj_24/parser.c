#include "essential.h"

char ParseStr(char* InitStr, StrStruct** StrArr) { // [In]: InitStr(사용자가 입력한 계산식 Str), [Out]: StrStruct* StrArr[]. 함수 성공 시 1을, 실패 시 0을 return 한다.
	char* Temp = (char*)malloc(MAX_STR_SIZE); // 피연산자가 임시로 담길 공간 malloc()으로 할당
	if (!Temp) { // malloc() fail시 error handling
		printf("[Fatal] malloc() failed\n\n");
		return 0;
	}
	memset(Temp, 0x0, MAX_STR_SIZE); // Temp 공간의 값들 모두 0으로 초기화
	uint32 StrArrIdx = 0; // StrArr 배열의 원소를 가리키는 인덱스
	uint32 TempIdx = 0; // Temp 문자열의 원소를 가리키는 인덱스
	uint8 CharFlag = 0; // 문자가 오는 순간 1로 바뀐다. Error handling을 위한 변수.

	for (uint32 i = 0; InitStr[i] != 0 && StrArrIdx < ARRMAX; i++) { // (1) For문 START. InitStr을 처음부터 끝까지 읽어, 피연산자와 연산자로 잘라 StrArr 배열에 담는다.
		if (InitStr[i] == '(' || InitStr[i] == ')' || InitStr[i] == '+' || InitStr[i] == '-' || InitStr[i] == '*' || InitStr[i] == '/') { // i가 가리키는 문자열의 현재 원소가 연산자인 경우
			if (Temp[0] != 0) { // Temp가 비어있지 않은 경우
				StrArr[StrArrIdx] = (StrStruct*)malloc(sizeof(StrStruct)); // malloc()으로, StrArr 원소에 StrStruct를 위한 공간 할당
				if (!StrArr[StrArrIdx]) { // malloc() fail시 error handling
					printf("[Fatal] malloc() failed\n\n");
					return 0;
				}
				memset(StrArr[StrArrIdx], 0x0, sizeof(StrStruct)); // StrStruct의 값들을 모두 0으로 초기화.(이때, StrStruct->Type도 0(Str Type)으로 자동으로 초기화 됨)

				StrArr[StrArrIdx]->Str = (char*)malloc(MAX_STR_SIZE); // 문자열이 담길 StrStruct->Str 멤버를 위한 공간 malloc()으로 할당.
				if (!StrArr[StrArrIdx]->Str) { // malloc() fail시 error handling
					printf("[Fatal] malloc() failed\n\n");
					return 0;
				}
				memset(StrArr[StrArrIdx]->Str, 0x0, MAX_STR_SIZE); // StrStruct->Str 공간의 값들 모두 0으로 초기화
				strcpy_s(StrArr[StrArrIdx++]->Str, MAX_STR_SIZE, Temp); // strcpy_s()를 통해 Temp에 저장돼 있는 문자열을 StrArr 배열의 원소에 복사함
			}

			StrArr[StrArrIdx] = (StrStruct*)malloc(sizeof(StrStruct)); // malloc()으로, StrArr 원소에 StrStruct를 위한 공간 할당
			if (!StrArr[StrArrIdx]) { // malloc() fail시 error handling
				printf("[Fatal] malloc() failed\n\n");
				return 0;
			}

			memset(StrArr[StrArrIdx], 0x0, sizeof(StrStruct)); // StrStruct의 값들을 모두 0으로 초기화.(이때, StrStruct->Type도 0(Str Type)으로 자동으로 초기화 됨)
			StrArr[StrArrIdx]->Str = (char*)malloc(MAX_STR_SIZE); // 현재는 연산자가 저장 되지만, 사칙연산 수행 뒤 결괏값이 저장 될 것이므로 똑같이 0x10000(MAX_STR_SIZE)의 큰 공간 할당.
			if (!StrArr[StrArrIdx]->Str) { // malloc() fail시 error handling
				printf("[Fatal] malloc() failed\n\n");
				return 0;
			}
			memset(StrArr[StrArrIdx]->Str, 0x0, MAX_STR_SIZE); // StrStruct->Str의 값들 모두 0으로 초기화
			StrArr[StrArrIdx++]->Str[0] = InitStr[i]; // StrArr 배열의 원소의 Str 멤버에 연산자를 복사함

			memset(Temp, 0x0, MAX_STR_SIZE); // Temp 공간 0으로 초기화
			TempIdx = 0; // TempIdx도 0으로 초기화

			CharFlag = 0; // CharFlag 0으로 초기화
		}
		else { // InitStr[i]가 연산자가 아닌 경우. 즉, 문자인 경우 START
			if (!CharFlag && StrArrIdx && (StrArr[StrArrIdx - 1]->Str[0] == ')' || StrArr[StrArrIdx - 1]->Str[0] == '+' // 괄호, 뺄셈, 곱셈, 나눗셈 뒤에 공백 오면 무시한다 START
				|| StrArr[StrArrIdx - 1]->Str[0] == '-' || StrArr[StrArrIdx - 1]->Str[0] == '*' || StrArr[StrArrIdx - 1]->Str[0] == '/')) { // 이때, StrArr의 0번째라면, StrArrIdx-1에서 Integer Underflow가 발생하므로, StrArrIdx가 0이 아닌지 체크한다
				if (InitStr[i] == ' ') // 문자열 뒤에 공백이 있다면 continue
					continue;
				else
					CharFlag = 1; // 문자가 왔음을 알리기 위한 CharFlag를 1로 set
			} // 괄호, 뺄셈, 곱셈, 나눗셈 뒤에 공백 오면 무시한다 END

			if (TempIdx >= MAX_STR_SIZE) {  // 피연산자의 길이가 MAX_STR_SIZE(0x10000)보다 길면 에러 발생 후, return 0(함수 fail을 가리키는 값)
				printf("[!] 한 피연산자 String의 길이가 %u보다 깁니다(지원하는 한 피연산자의 최대 길이: %u)\n\n", MAX_STR_SIZE, MAX_STR_SIZE);
				return 0;
			}

			Temp[TempIdx++] = InitStr[i]; // 초기 문자열(InitStr)의 각 문자를 Temp 문자열에 이어 붙임
		} // InitStr[i]가 연산자가 아닌 경우. 즉, 문자인 경우 END
	} // (1) For문 END
	if (Temp[0] != 0) { // Temp가 비어있지 않다면 Temp에 남은 데이터 복사하기 START
		StrArr[StrArrIdx] = (StrStruct*)malloc(sizeof(StrStruct));
		if (!StrArr[StrArrIdx]) {
			printf("[Fatal] malloc() failed\n\n");
			return 0;
		}
		memset(StrArr[StrArrIdx], 0x0, sizeof(StrStruct)); // 각 구조체 원소 0으로 초기화.(이때, StrStruct->Type도 0(Str Type)으로 자동으로 초기화 됨)

		StrArr[StrArrIdx]->Str = (char*)malloc(MAX_STR_SIZE);
		if (!StrArr[StrArrIdx]->Str) {
			printf("[Fatal] malloc() failed\n\n");
			free(Temp);
			return 0;
		}
		memset(StrArr[StrArrIdx]->Str, 0x0, MAX_STR_SIZE);

		strcpy_s(StrArr[StrArrIdx]->Str, MAX_STR_SIZE, Temp); // 마지막 남은 Temp 문자열을 StrArr의 원소에 복사
	} // Temp가 비어있지 않다면 Temp에 남은 데이터 복사하기 START

	free(Temp); // Temp 다 썼으므로, Temp에 할당했던 공간 release

	if (StrArrIdx == ARRMAX) { // StrArr의 최대 원소 개수는 0x100개이다. 따라서 원소 개수가 0x101개 이상인 경우 오류를 발생시킨다.
		printf("[!] Error: 입력하신 연산자와 피연산자의 개수의 총합이 %u개 이상입니다(지원하는 최대 연산자와 피연산자의 개수의 총합: %u개)\n\n", ARRMAX, ARRMAX);
		return 0;
	}

	return 1;
}