#include "essential.h"

void PrintTeam() {
	printf("  _____                        ___            ___    _                     ___            _           \n");
	printf(" |_   _|  ___   __ _   _ __   |_  )    o O O / __|  | |_     _ _    o O O / __|  __ _    | |    __    \n");
	printf("   | |   / -_) / _` | | '  \\   / /    o      \\__ \\  |  _|   | '_|  o     | (__  / _` |   | |   / _|   \n");
	printf("  _|_|_  \\___| \\__,_| |_|_|_| /___|  TS__[O] |___/  _\\__|  _|_|_  TS__[O] \\___| \\__,_|  _|_|_  \\__|_  \n");
	printf("_|\"\"\"\"\"_|\"\"\"\"\"_|\"\"\"\"\"_|\"\"\"\"\"_|\"\"\"\"\"|{======_|\"\"\"\"\"_|\"\"\"\"\"_|\"\"\"\"\"|{======_|\"\"\"\"\"_|\"\"\"\"\"_|\"\"\"\"\"_|\"\"\"\"\"| \n");
	printf("\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-./o--000\"`-0-0-\"`-0-0-\"`-0-0-./o--000\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-' \n\n\n");

}

void PrintMenu(char CallType) { // CallType: 0 == Called on starting, 1 == Called by "menu" or 'm', 2 == Called by "clear" or 'c'
	if (CallType == 1)
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("################################################### [이용 방법] ###################################################\n");
	printf("$$$$$$$$$$$$$                           이 계산기는 다항식 String 계산기입니다.                       $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$                               +, -, *, / 연산이 지원됩니다.                             $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$                                                                                         $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$             '\+\': a 문장과 b 문장을 붙인다, \'-\': 앞 문장에서 뒤 문장을 제거한다          $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$        \'*\': a 문장을 b번 반복한다, \'/\': a 문장에서 b 단어가 들어있는 개수를 구한다      $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$                                                                                         $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$            입력 예시: ex. ( \"+ I am inevitable - inevitable + Iron Man.+ \" ) * 3        $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$                                                                                         $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$                     메뉴 출력을 원하시면 \"menu\" 또는 \"m\"을 입력해주세요                 $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$                   콘솔창을 Clear 하시려면 \"clear\" 또는 \"c\"을 입력해주세요               $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$             프로그램을 종료하시려면 \"exit\" 또는 \"quit\" 또는 \"q\"을 입력해주세요          $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$                                                                                         $$$$$$$$$$$$$\n");
	printf("################### Credits: 김정수(팀장), 신채빈(팀원), 이승우(팀원), 어치르수렌호비툭스(팀원) ###################\n\n\n\n");
}

void PrintExitMsg() {
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("    ___                 __ _                                             _  _         \n");
	printf("   | _ \\   _ _   ___   / _` |   _ _  __ _   _ __    ___    ___   __ _   | || |  ___   \n");
	printf("   |  _/  | '_| / _ \\  \\__, |  | '_|/ _` | | '  \\  |___|  (_-<  / _` |   \\_, | (_-<   \n");
	printf("  _|_|_  _|_|_  \\___/  |___/  _|_|_ \\__,_| |_|_|_| _____  /__/_ \\__,_|  _|__/  /__/_  \n");
	printf("_| \"\"\" _|\"\"\"\"\"_|\"\"\"\"\"_|\"\"\"\"\"_|\"\"\"\"\"_|\"\"\"\"\"_|\"\"\"\"\"_|     _|\"\"\"\"\"_|\"\"\"\"\"_| \"\"\"\"_|\"\"\"\"\"| \n");
	printf("\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-' \n");
	printf("   _ _   _       _  _                _       _  _           _     _ _                 \n");
	printf("  ( | ) | |__   | || |  ___    ___  | |__   | || |  ___    | |   ( | )                \n");
	printf("   V V  | '_ \\   \\_, | / -_)  |___| | '_ \\   \\_, | / -_)   |_|    V V                 \n");
	printf("  _____ |_.__/  _|__/  \\___|  _____ |_.__/  _|__/  \\___|  _(_)_  _____                \n");
	printf("_|     _|\"\"\"\"\"_| \"\"\"\"_|\"\"\"\"\"_|     _|\"\"\"\"\"_| \"\"\"\"_|\"\"\"\"\"_| \"\"\" _|     |               \n");
	printf("\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-\"`-0-0-'               \n");
	printf("\n\n\n\n\n");
}

int main() {
	PrintTeam(); // 시작 메세지 출력
	PrintMenu(0); // 메뉴 출력

	char* InitStr = (char*)malloc(INIT_STR_SIZE); // 초기 문자열 계산식을 받을 공간 할당
	if (!InitStr) {
		printf("[Fatal] malloc() failed\n\n");
	}
	memset(InitStr, 0x0, INIT_STR_SIZE); // InitStr 공간 모두 0으로 초기화

	StrStruct** StrArr = (StrStruct**)malloc(sizeof(StrStruct*) * ARRMAX); // 초기 문자열 계산식을 parsing 해서 담아둘 구조체 배열. 원소의 개수는 최대 0x100개이다.
	if (!StrArr) { // StrArr를 위한 malloc()이 fail한 경우 error handling
		printf("[Fatal] malloc() failed\n\n");
		return 0;
	}
	memset(StrArr, 0x0, sizeof(StrStruct*) * ARRMAX); // StrArr 공간 모두 0으로 초기화;

	while (1) { // while문 시작
		printf("문자열 계산식을 입력하세요: ");
		fgets(InitStr, INIT_STR_SIZE, stdin); // fgets()를 통해 사용자에게서 계산식을 string으로 입력 받는다

		if (InitStr[0] == NULL) { // Ctrl+C를 입력 받았을 경우
			break; // 프로세스 종료
		}

		InitStr[strlen(InitStr) - 1] = 0; // fgets()로 입력 받으면, 끝에 있는 '\n'까지 입력 받으므로, 이 '\n'을 NULL로 바꿔준다.

		if (!IsValidInitStr(InitStr)) { // IsValidInitStr()을 통해, 사용자가 입력한 계산식이 올바른지 검사한다.
			goto cleanup;
		}

		if (!strcmp(InitStr, "exit") || !strcmp(InitStr, "quit") || (InitStr[0] == 'q' && InitStr[1] == 0)) { // 사용자가 "exit", "quit", 'q'를 입력했다면 프로세스 종료
			break;
		}

		if (!strcmp(InitStr, "menu") || (InitStr[0] == 'm' && InitStr[1] == 0)) { // 사용자가 "menu", 'm'을 입력했다면 메뉴 출력
			PrintMenu(1);
			continue;
		}

		if (!strcmp(InitStr, "clear") || (InitStr[0] == 'c' && InitStr[1] == 0)) { // 사용자가 "clear", 'c'를 입력했다면 콘솔창 clear
			system("cls");
			PrintMenu(2);
			continue;
		}

		if (!ParseStr(InitStr, StrArr))  // InitStr(사용자가 초기에 입력한 계산식)에서 피연산자와 연산자로 나누어 자른 후, StrStruct* 배열인 StrArr에 담아준다.
			goto cleanup;

		if (!IsValidStrArr(StrArr)) { // 위에서 ParseStr을 통해 StrArr에 문자열들이 담겼으므로, StrArr가 올바른지 검사한다.
			goto cleanup;
		}

		if (!Calc(StrArr)) // StrArr에 담겨있는 연산자와 피연산자들을 토대로 계산 수행 및 결과를 StrArr[0]에 저장
			goto cleanup;

		if (StrArr[0]->Type == 1) // StrArr[0]->Type이 1(Integer)이라면
			printf("Result: %s개\n\n", StrArr[0]->Str); // 몇 개인지 출력
		else
			printf("Result: %s\n\n", StrArr[0]->Str); // StrArr[0]->Type이 0(String)이라면, 결괏값 출력 

	cleanup: // InitStr의 값들 모두 0으로 초기화 && StrArr->Str release && StrArr의 원소들 release하고 NULL로 초기화
		memset(InitStr, 0x0, INIT_STR_SIZE);
		for (uint32 i = 0; StrArr[i] != NULL; i++) {
			if (StrArr[i]->Str)
				free(StrArr[i]->Str);
			free(StrArr[i]);
			StrArr[i] = NULL;
		}
	} // while문 끝

	for (uint32 i = 0; StrArr[i] != NULL; i++) { // 프로세스 종료 전, Heap에 할당했던 resource들 release 해주기 START
		if (StrArr[i]->Str)
			free(StrArr[i]->Str);
		free(StrArr[i]);
	}
	free(StrArr);
	free(InitStr); // 프로세스 종료 전, Heap에 할당했던 resource들 release 해주기 END

	PrintExitMsg(); // 종료 메세지 출력

	return 0; // 프로세스 종료
}