#include "essential.h"

char IsValidStrArr(StrStruct** StrArr) {
	uint32 LastIndex = 0; // Parsing ���ִ� ���ڿ��� ��� �迭�� StrArr�� ������ ���Ҹ� ����Ű�� Index
	uint32 NotSpace = 0; // ' '�� �ƴ� ���ڰ� ���� 1�� ��

	for (int i = 0; StrArr[0]->Str[i] != NULL; i++) { // (1) "        (a+b)"�� ����, ���� �ڿ� ���� ��ȣ�� ���� ������ �߻��ϴ� ���� �ذ� START
		if (StrArr[0]->Str[i] != ' ') { // ���� ���� "        (a+b)"�� ���� StrArr[0]->Str: "        ", StrArr[1]->Str: "("�� �ǹǷ� �� ���̿� �����ڰ� ���� ������ �߻��Ѵ�.
			NotSpace = 1; // NotSpace�� 1�� set
			break;
		}
	}
	if (!NotSpace && (StrArr[1]->Str[0] == '(' && StrArr[1]->Str[1] == 0)) { // StrArr[0]->Str: "        ", StrArr[1]->Str: "("�� ���
		Erase(StrArr, 0); // StrArr[0]�� �����, StrArr[1]�� StrArr[0]�� �ȴ�.
	} // (1) "        (a+b)�� ����, ���� �ڿ� ���� ��ȣ�� ���� ������ �߻��ϴ� ���� �ذ� END

	if (StrArr[0]->Str[0] == '-') { // (2) ù �ǿ������� ù ��° ���� '-'���� Ȯ��
		printf("[!} ���ڿ��� ������ �� �����ϴ�.\n\n"); // StrArr[0]->Str[0]�� ���ڿ��� ������� ���̴�. ���ڿ� ���⿡�� ���ڿ��� ������ �� ����.
		return 0; // return fail
	}

	if (StrArr[0]->Str[0] == '+' || StrArr[0]->Str[0] == '*' || StrArr[0]->Str[0] == '/') { // (3) ù ���ڿ��� ù ��° ���ڰ� '+', '*', '-'���� Ȯ��
		printf("[!] ù �ǿ����ڰ� \'%c\' �����ڷ� �����մϴ�. �Է��� �ٽ� �� �� Ȯ�����ּ���.\n\n", StrArr[0]->Str[0]); // ������ �����ڷ� ������ �� �����Ƿ� �Լ� ����
		return 0; // return fail
	}

	for (uint32 i = 0; StrArr[i + 1] != NULL; i++) { // (4) ���� ������ �ذ��ϱ� ���� StrArr�迭 ��ȸ For START
		if (StrArr[i]->Str[0] == '+' || StrArr[i]->Str[0] == '-' || StrArr[i]->Str[0] == '*' || StrArr[i]->Str[0] == '/' || StrArr[i]->Str[0] == '(') { // ���� StrArr[i]->Str�� ���������� Ȯ��
			if ((StrArr[i + 1]->Str[0] == '-')) { // �ǿ����ڰ� �������� Ȯ��(���ڿ� ���� ���� �ǿ����ڴ� ���� �� ����). ex. a+-b
				printf("[!] ������ ���� ���ڿ��� ������ �� �����ϴ�.\n\n");
				return 0; // return fail
			}
			if (StrArr[i + 1]->Str[0] == '+' || StrArr[i + 1]->Str[0] == '-' || StrArr[i + 1]->Str[0] == '*' || StrArr[i + 1]->Str[0] == '/') { // ������ �ڿ� �����ڰ� �̾ ������ Ȯ�� ex. a++b
				printf("[!] ������ �ùٸ��� �ʽ��ϴ�. �Է��� �ٽ� �� �� Ȯ�����ּ���.\n\n");
				return 0; // return fail
			}
		}

		if ((StrArr[i]->Str[0] == '+' || StrArr[i]->Str[0] == '-' || StrArr[i]->Str[0] == '*' || StrArr[i]->Str[0] == '/') && StrArr[i + 1]->Str[0] == ')') { // ��ȣ ���� �����ڷ� �������� Ȯ�� ex. a+(b+)
			printf("[!] ��ȣ �� �����ڿ� ���� �ǿ����ڰ� �������� �ʽ��ϴ�. �Է��� �ٽ� �� �� Ȯ�����ּ���.\n\n");
			return 0;
		}

		if (StrArr[i]->Str[0] == '(' && StrArr[i + 1]->Str[0] == ')') { // "()"�� ���� ��ȣ �ȿ� ��� ���� �Ǵ� ������ �������� �ʴ��� Ȯ��
			printf("[!] ��ȣ �ȿ� ��� ���� �Ǵ� ���ĵ� �������� �ʽ��ϴ�. �Է��� �ٽ� �� �� Ȯ�����ּ���.\n\n");
			return 0;
		}

		LastIndex = i + 1; // LastIndex�� StrArr�� ������ ���Ҹ� ����Ű���� ����
	} // (4) ���� ������ �ذ��ϱ� ���� StrArr�迭 ��ȸ For END

	if ((StrArr[LastIndex]->Str[0] == '+' || StrArr[LastIndex]->Str[0] == '-' || StrArr[LastIndex]->Str[0] == '*' || StrArr[LastIndex]->Str[0] == '/'
		|| StrArr[LastIndex]->Str[0] == '(')) { // (5) ������ �������� ������ �Ǵ� ���� ��ȣ�� �������� Ȯ��. ex1. "a+", ex2. "a+("
		if (StrArr[LastIndex]->Str[0] == '(') {
			printf("[!] ������ ���� ��ȣ�� �����ϴ�. �Է��� �ٽ� �� �� Ȯ�����ּ���.\n\n");
			return 0;
		}

		printf("[!] ������ �����ڿ� ���� �ǿ����ڰ� �������� �ʽ��ϴ�. �Է��� �ٽ� �� �� Ȯ�����ּ���.\n\n");
		return 0;
	}
}

char IsValidInitStr(char* InitStr) { // ���⼭ InitStr�� ����ڰ� �Է��� �����̴�. -> Valid�� �����̶�� 1��, Invalid�� �����̶�� 0�� ��ȯ�Ѵ�.
	char CharFlag = 0; // ' '�� �ƴ� ���ڰ� ���� 1�� �ٲ��.

	for (int i = 0; InitStr[i] != NULL; i++) { // (1) ���Ŀ� Control code(Ctrl+X, Ctrl+O ���...)�� �ִ��� Ȯ���ϰ�, �ִٸ� exception�� �߻���Ų��
		if (iswcntrl(InitStr[i])) { // iswcntrl()�� wchar(2byte)�� ���ڷ� �޾�, ���ڰ� control code�� �ش��ϸ� 0�� �ƴ� ����, control code�� �ƴϸ� 0�� ��ȯ�Ѵ�.
			printf("[!] �ùٸ��� ���� ���ڰ� ���Ŀ� ���� ���ֽ��ϴ�. �Է��� �ٽ� �� �� Ȯ�����ּ���.\n\n");
			return 0;
		}
	}

	for (int i = 0; InitStr[i] != 0; i++) { // (2) ����ڰ� ���� ���� ' '�� �Է��� ��츦 �˻��ϱ� ���� ����
		if (InitStr[i] != ' ') {
			CharFlag = 1; // ' '�� �ƴ� ���ڰ� ���� CharFlag�� 1�� �ٲ��ش�. �� CharFlag ������ ���� if������ ���δ�.
			break;
		}
	}

	if (InitStr[0] == NULL || !CharFlag) { // (a) ����ڰ� �������� �ƹ��͵� �Է����� �ʾҰų� or (b) ����ڰ� �Է��� ���Ŀ� ' '���� ������ ��� -> Exception �߻�
		printf("[!] ������ �Էµ��� �ʾҽ��ϴ�. �Է��� �ٽ� �� �� Ȯ�����ּ���\n\n\n");
		return 0;
	}

	return 1; // Valid�� ������ ��� 1�� ��ȯ���ش�.
}