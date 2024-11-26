#include "essential.h"

char IsValidStrArr(StrStruct** StrArr) {
	uint32 LastIndex = 0; // Parsing 돼있는 문자열을 담는 배열인 StrArr의 마지막 원소를 가리키는 Index
	uint32 NotSpace = 0; // ' '이 아닌 문자가 오면 1이 됨

	for (int i = 0; StrArr[0]->Str[i] != NULL; i++) { // (1) "        (a+b)"와 같이, 공백 뒤에 열린 괄호가 오면 오류가 발생하는 것을 해결 START
		if (StrArr[0]->Str[i] != ' ') { // 위와 같이 "        (a+b)"가 오면 StrArr[0]->Str: "        ", StrArr[1]->Str: "("가 되므로 둘 사이에 연산자가 없어 오류가 발생한다.
			NotSpace = 1; // NotSpace를 1로 set
			break;
		}
	}
	if (!NotSpace && (StrArr[1]->Str[0] == '(' && StrArr[1]->Str[1] == 0)) { // StrArr[0]->Str: "        ", StrArr[1]->Str: "("인 경우
		Erase(StrArr, 0); // StrArr[0]을 지우고, StrArr[1]이 StrArr[0]이 된다.
	} // (1) "        (a+b)와 같이, 공백 뒤에 열린 괄호가 오면 오류가 발생하는 것을 해결 END

	if (StrArr[0]->Str[0] == '-') { // (2) 첫 피연산자의 첫 번째 값이 '-'인지 확인
		printf("[!} 문자열은 음수일 수 없습니다.\n\n"); // StrArr[0]->Str[0]은 문자열이 음수라는 뜻이다. 문자열 계산기에서 문자열은 음수일 수 없다.
		return 0; // return fail
	}

	if (StrArr[0]->Str[0] == '+' || StrArr[0]->Str[0] == '*' || StrArr[0]->Str[0] == '/') { // (3) 첫 문자열의 첫 번째 문자가 '+', '*', '-'인지 확인
		printf("[!] 첫 피연산자가 \'%c\' 연산자로 시작합니다. 입력을 다시 한 번 확인해주세요.\n\n", StrArr[0]->Str[0]); // 계산식이 연산자로 시작할 수 없으므로 함수 실패
		return 0; // return fail
	}

	for (uint32 i = 0; StrArr[i + 1] != NULL; i++) { // (4) 여러 오류를 해결하기 위해 StrArr배열 순회 For START
		if (StrArr[i]->Str[0] == '+' || StrArr[i]->Str[0] == '-' || StrArr[i]->Str[0] == '*' || StrArr[i]->Str[0] == '/' || StrArr[i]->Str[0] == '(') { // 현재 StrArr[i]->Str이 연산자인지 확인
			if ((StrArr[i + 1]->Str[0] == '-')) { // 피연산자가 음수인지 확인(문자열 계산시 음수 피연산자는 쓰일 수 없다). ex. a+-b
				printf("[!] 음수의 값을 문자열과 연산할 수 없습니다.\n\n");
				return 0; // return fail
			}
			if (StrArr[i + 1]->Str[0] == '+' || StrArr[i + 1]->Str[0] == '-' || StrArr[i + 1]->Str[0] == '*' || StrArr[i + 1]->Str[0] == '/') { // 연산자 뒤에 연산자가 이어서 오는지 확인 ex. a++b
				printf("[!] 계산식이 올바르지 않습니다. 입력을 다시 한 번 확인해주세요.\n\n");
				return 0; // return fail
			}
		}

		if ((StrArr[i]->Str[0] == '+' || StrArr[i]->Str[0] == '-' || StrArr[i]->Str[0] == '*' || StrArr[i]->Str[0] == '/') && StrArr[i + 1]->Str[0] == ')') { // 괄호 안이 연산자로 끝나는지 확인 ex. a+(b+)
			printf("[!] 괄호 안 연산자에 대한 피연산자가 존재하지 않습니다. 입력을 다시 한 번 확인해주세요.\n\n");
			return 0;
		}

		if (StrArr[i]->Str[0] == '(' && StrArr[i + 1]->Str[0] == ')') { // "()"와 같이 괄호 안에 어떠한 문자 또는 계산식이 존재하지 않는지 확인
			printf("[!] 괄호 안에 어떠한 문자 또는 계산식도 존재하지 않습니다. 입력을 다시 한 번 확인해주세요.\n\n");
			return 0;
		}

		LastIndex = i + 1; // LastIndex가 StrArr의 마지막 원소를 가리키도록 설정
	} // (4) 여러 오류를 해결하기 위해 StrArr배열 순회 For END

	if ((StrArr[LastIndex]->Str[0] == '+' || StrArr[LastIndex]->Str[0] == '-' || StrArr[LastIndex]->Str[0] == '*' || StrArr[LastIndex]->Str[0] == '/'
		|| StrArr[LastIndex]->Str[0] == '(')) { // (5) 계산식의 마지막이 연산자 또는 열린 괄호로 끝나는지 확인. ex1. "a+", ex2. "a+("
		if (StrArr[LastIndex]->Str[0] == '(') {
			printf("[!] 계산식이 열린 괄호로 끝납니다. 입력을 다시 한 번 확인해주세요.\n\n");
			return 0;
		}

		printf("[!] 마지막 연산자에 대한 피연산자가 존재하지 않습니다. 입력을 다시 한 번 확인해주세요.\n\n");
		return 0;
	}
}

char IsValidInitStr(char* InitStr) { // 여기서 InitStr은 사용자가 입력한 계산식이다. -> Valid한 계산식이라면 1을, Invalid한 계산식이라면 0을 반환한다.
	char CharFlag = 0; // ' '이 아닌 문자가 오면 1로 바뀐다.

	for (int i = 0; InitStr[i] != NULL; i++) { // (1) 계산식에 Control code(Ctrl+X, Ctrl+O 등등...)이 있는지 확인하고, 있다면 exception를 발생시킨다
		if (iswcntrl(InitStr[i])) { // iswcntrl()은 wchar(2byte)를 인자로 받아, 인자가 control code에 해당하면 0이 아닌 값을, control code가 아니면 0을 반환한다.
			printf("[!] 올바르지 않은 문자가 계산식에 포함 돼있습니다. 입력을 다시 한 번 확인해주세요.\n\n");
			return 0;
		}
	}

	for (int i = 0; InitStr[i] != 0; i++) { // (2) 사용자가 여러 개의 ' '만 입력한 경우를 검사하기 위한 루프
		if (InitStr[i] != ' ') {
			CharFlag = 1; // ' '이 아닌 문자가 오면 CharFlag를 1로 바꿔준다. 이 CharFlag 변수는 밑의 if문에서 쓰인다.
			break;
		}
	}

	if (InitStr[0] == NULL || !CharFlag) { // (a) 사용자가 계산식으로 아무것도 입력하지 않았거나 or (b) 사용자가 입력한 계산식에 ' '만이 존재할 경우 -> Exception 발생
		printf("[!] 계산식이 입력되지 않았습니다. 입력을 다시 한 번 확인해주세요\n\n\n");
		return 0;
	}

	return 1; // Valid한 계산식일 경우 1을 반환해준다.
}