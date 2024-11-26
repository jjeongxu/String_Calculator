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
	printf("################################################### [�̿� ���] ###################################################\n");
	printf("$$$$$$$$$$$$$                           �� ����� ���׽� String �����Դϴ�.                       $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$                               +, -, *, / ������ �����˴ϴ�.                             $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$                                                                                         $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$             '\+\': a ����� b ������ ���δ�, \'-\': �� ���忡�� �� ������ �����Ѵ�          $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$        \'*\': a ������ b�� �ݺ��Ѵ�, \'/\': a ���忡�� b �ܾ ����ִ� ������ ���Ѵ�      $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$                                                                                         $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$            �Է� ����: ex. ( \"+ I am inevitable - inevitable + Iron Man.+ \" ) * 3        $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$                                                                                         $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$                     �޴� ����� ���Ͻø� \"menu\" �Ǵ� \"m\"�� �Է����ּ���                 $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$                   �ܼ�â�� Clear �Ͻ÷��� \"clear\" �Ǵ� \"c\"�� �Է����ּ���               $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$             ���α׷��� �����Ͻ÷��� \"exit\" �Ǵ� \"quit\" �Ǵ� \"q\"�� �Է����ּ���          $$$$$$$$$$$$$\n");
	printf("$$$$$$$$$$$$$                                                                                         $$$$$$$$$$$$$\n");
	printf("################### Credits: ������(����), ��ä��(����), �̽¿�(����), ��ġ������ȣ������(����) ###################\n\n\n\n");
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
	PrintTeam(); // ���� �޼��� ���
	PrintMenu(0); // �޴� ���

	char* InitStr = (char*)malloc(INIT_STR_SIZE); // �ʱ� ���ڿ� ������ ���� ���� �Ҵ�
	if (!InitStr) {
		printf("[Fatal] malloc() failed\n\n");
	}
	memset(InitStr, 0x0, INIT_STR_SIZE); // InitStr ���� ��� 0���� �ʱ�ȭ

	StrStruct** StrArr = (StrStruct**)malloc(sizeof(StrStruct*) * ARRMAX); // �ʱ� ���ڿ� ������ parsing �ؼ� ��Ƶ� ����ü �迭. ������ ������ �ִ� 0x100���̴�.
	if (!StrArr) { // StrArr�� ���� malloc()�� fail�� ��� error handling
		printf("[Fatal] malloc() failed\n\n");
		return 0;
	}
	memset(StrArr, 0x0, sizeof(StrStruct*) * ARRMAX); // StrArr ���� ��� 0���� �ʱ�ȭ;

	while (1) { // while�� ����
		printf("���ڿ� ������ �Է��ϼ���: ");
		fgets(InitStr, INIT_STR_SIZE, stdin); // fgets()�� ���� ����ڿ��Լ� ������ string���� �Է� �޴´�

		if (InitStr[0] == NULL) { // Ctrl+C�� �Է� �޾��� ���
			break; // ���μ��� ����
		}

		InitStr[strlen(InitStr) - 1] = 0; // fgets()�� �Է� ������, ���� �ִ� '\n'���� �Է� �����Ƿ�, �� '\n'�� NULL�� �ٲ��ش�.

		if (!IsValidInitStr(InitStr)) { // IsValidInitStr()�� ����, ����ڰ� �Է��� ������ �ùٸ��� �˻��Ѵ�.
			goto cleanup;
		}

		if (!strcmp(InitStr, "exit") || !strcmp(InitStr, "quit") || (InitStr[0] == 'q' && InitStr[1] == 0)) { // ����ڰ� "exit", "quit", 'q'�� �Է��ߴٸ� ���μ��� ����
			break;
		}

		if (!strcmp(InitStr, "menu") || (InitStr[0] == 'm' && InitStr[1] == 0)) { // ����ڰ� "menu", 'm'�� �Է��ߴٸ� �޴� ���
			PrintMenu(1);
			continue;
		}

		if (!strcmp(InitStr, "clear") || (InitStr[0] == 'c' && InitStr[1] == 0)) { // ����ڰ� "clear", 'c'�� �Է��ߴٸ� �ܼ�â clear
			system("cls");
			PrintMenu(2);
			continue;
		}

		if (!ParseStr(InitStr, StrArr))  // InitStr(����ڰ� �ʱ⿡ �Է��� ����)���� �ǿ����ڿ� �����ڷ� ������ �ڸ� ��, StrStruct* �迭�� StrArr�� ����ش�.
			goto cleanup;

		if (!IsValidStrArr(StrArr)) { // ������ ParseStr�� ���� StrArr�� ���ڿ����� ������Ƿ�, StrArr�� �ùٸ��� �˻��Ѵ�.
			goto cleanup;
		}

		if (!Calc(StrArr)) // StrArr�� ����ִ� �����ڿ� �ǿ����ڵ��� ���� ��� ���� �� ����� StrArr[0]�� ����
			goto cleanup;

		if (StrArr[0]->Type == 1) // StrArr[0]->Type�� 1(Integer)�̶��
			printf("Result: %s��\n\n", StrArr[0]->Str); // �� ������ ���
		else
			printf("Result: %s\n\n", StrArr[0]->Str); // StrArr[0]->Type�� 0(String)�̶��, �ᱣ�� ��� 

	cleanup: // InitStr�� ���� ��� 0���� �ʱ�ȭ && StrArr->Str release && StrArr�� ���ҵ� release�ϰ� NULL�� �ʱ�ȭ
		memset(InitStr, 0x0, INIT_STR_SIZE);
		for (uint32 i = 0; StrArr[i] != NULL; i++) {
			if (StrArr[i]->Str)
				free(StrArr[i]->Str);
			free(StrArr[i]);
			StrArr[i] = NULL;
		}
	} // while�� ��

	for (uint32 i = 0; StrArr[i] != NULL; i++) { // ���μ��� ���� ��, Heap�� �Ҵ��ߴ� resource�� release ���ֱ� START
		if (StrArr[i]->Str)
			free(StrArr[i]->Str);
		free(StrArr[i]);
	}
	free(StrArr);
	free(InitStr); // ���μ��� ���� ��, Heap�� �Ҵ��ߴ� resource�� release ���ֱ� END

	PrintExitMsg(); // ���� �޼��� ���

	return 0; // ���μ��� ����
}