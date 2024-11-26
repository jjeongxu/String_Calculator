#include "essential.h"

char ParseStr(char* InitStr, StrStruct** StrArr) { // [In]: InitStr(����ڰ� �Է��� ���� Str), [Out]: StrStruct* StrArr[]. �Լ� ���� �� 1��, ���� �� 0�� return �Ѵ�.
	char* Temp = (char*)malloc(MAX_STR_SIZE); // �ǿ����ڰ� �ӽ÷� ��� ���� malloc()���� �Ҵ�
	if (!Temp) { // malloc() fail�� error handling
		printf("[Fatal] malloc() failed\n\n");
		return 0;
	}
	memset(Temp, 0x0, MAX_STR_SIZE); // Temp ������ ���� ��� 0���� �ʱ�ȭ
	uint32 StrArrIdx = 0; // StrArr �迭�� ���Ҹ� ����Ű�� �ε���
	uint32 TempIdx = 0; // Temp ���ڿ��� ���Ҹ� ����Ű�� �ε���
	uint8 CharFlag = 0; // ���ڰ� ���� ���� 1�� �ٲ��. Error handling�� ���� ����.

	for (uint32 i = 0; InitStr[i] != 0 && StrArrIdx < ARRMAX; i++) { // (1) For�� START. InitStr�� ó������ ������ �о�, �ǿ����ڿ� �����ڷ� �߶� StrArr �迭�� ��´�.
		if (InitStr[i] == '(' || InitStr[i] == ')' || InitStr[i] == '+' || InitStr[i] == '-' || InitStr[i] == '*' || InitStr[i] == '/') { // i�� ����Ű�� ���ڿ��� ���� ���Ұ� �������� ���
			if (Temp[0] != 0) { // Temp�� ������� ���� ���
				StrArr[StrArrIdx] = (StrStruct*)malloc(sizeof(StrStruct)); // malloc()����, StrArr ���ҿ� StrStruct�� ���� ���� �Ҵ�
				if (!StrArr[StrArrIdx]) { // malloc() fail�� error handling
					printf("[Fatal] malloc() failed\n\n");
					return 0;
				}
				memset(StrArr[StrArrIdx], 0x0, sizeof(StrStruct)); // StrStruct�� ������ ��� 0���� �ʱ�ȭ.(�̶�, StrStruct->Type�� 0(Str Type)���� �ڵ����� �ʱ�ȭ ��)

				StrArr[StrArrIdx]->Str = (char*)malloc(MAX_STR_SIZE); // ���ڿ��� ��� StrStruct->Str ����� ���� ���� malloc()���� �Ҵ�.
				if (!StrArr[StrArrIdx]->Str) { // malloc() fail�� error handling
					printf("[Fatal] malloc() failed\n\n");
					return 0;
				}
				memset(StrArr[StrArrIdx]->Str, 0x0, MAX_STR_SIZE); // StrStruct->Str ������ ���� ��� 0���� �ʱ�ȭ
				strcpy_s(StrArr[StrArrIdx++]->Str, MAX_STR_SIZE, Temp); // strcpy_s()�� ���� Temp�� ����� �ִ� ���ڿ��� StrArr �迭�� ���ҿ� ������
			}

			StrArr[StrArrIdx] = (StrStruct*)malloc(sizeof(StrStruct)); // malloc()����, StrArr ���ҿ� StrStruct�� ���� ���� �Ҵ�
			if (!StrArr[StrArrIdx]) { // malloc() fail�� error handling
				printf("[Fatal] malloc() failed\n\n");
				return 0;
			}

			memset(StrArr[StrArrIdx], 0x0, sizeof(StrStruct)); // StrStruct�� ������ ��� 0���� �ʱ�ȭ.(�̶�, StrStruct->Type�� 0(Str Type)���� �ڵ����� �ʱ�ȭ ��)
			StrArr[StrArrIdx]->Str = (char*)malloc(MAX_STR_SIZE); // ����� �����ڰ� ���� ������, ��Ģ���� ���� �� �ᱣ���� ���� �� ���̹Ƿ� �Ȱ��� 0x10000(MAX_STR_SIZE)�� ū ���� �Ҵ�.
			if (!StrArr[StrArrIdx]->Str) { // malloc() fail�� error handling
				printf("[Fatal] malloc() failed\n\n");
				return 0;
			}
			memset(StrArr[StrArrIdx]->Str, 0x0, MAX_STR_SIZE); // StrStruct->Str�� ���� ��� 0���� �ʱ�ȭ
			StrArr[StrArrIdx++]->Str[0] = InitStr[i]; // StrArr �迭�� ������ Str ����� �����ڸ� ������

			memset(Temp, 0x0, MAX_STR_SIZE); // Temp ���� 0���� �ʱ�ȭ
			TempIdx = 0; // TempIdx�� 0���� �ʱ�ȭ

			CharFlag = 0; // CharFlag 0���� �ʱ�ȭ
		}
		else { // InitStr[i]�� �����ڰ� �ƴ� ���. ��, ������ ��� START
			if (!CharFlag && StrArrIdx && (StrArr[StrArrIdx - 1]->Str[0] == ')' || StrArr[StrArrIdx - 1]->Str[0] == '+' // ��ȣ, ����, ����, ������ �ڿ� ���� ���� �����Ѵ� START
				|| StrArr[StrArrIdx - 1]->Str[0] == '-' || StrArr[StrArrIdx - 1]->Str[0] == '*' || StrArr[StrArrIdx - 1]->Str[0] == '/')) { // �̶�, StrArr�� 0��°���, StrArrIdx-1���� Integer Underflow�� �߻��ϹǷ�, StrArrIdx�� 0�� �ƴ��� üũ�Ѵ�
				if (InitStr[i] == ' ') // ���ڿ� �ڿ� ������ �ִٸ� continue
					continue;
				else
					CharFlag = 1; // ���ڰ� ������ �˸��� ���� CharFlag�� 1�� set
			} // ��ȣ, ����, ����, ������ �ڿ� ���� ���� �����Ѵ� END

			if (TempIdx >= MAX_STR_SIZE) {  // �ǿ������� ���̰� MAX_STR_SIZE(0x10000)���� ��� ���� �߻� ��, return 0(�Լ� fail�� ����Ű�� ��)
				printf("[!] �� �ǿ����� String�� ���̰� %u���� ��ϴ�(�����ϴ� �� �ǿ������� �ִ� ����: %u)\n\n", MAX_STR_SIZE, MAX_STR_SIZE);
				return 0;
			}

			Temp[TempIdx++] = InitStr[i]; // �ʱ� ���ڿ�(InitStr)�� �� ���ڸ� Temp ���ڿ��� �̾� ����
		} // InitStr[i]�� �����ڰ� �ƴ� ���. ��, ������ ��� END
	} // (1) For�� END
	if (Temp[0] != 0) { // Temp�� ������� �ʴٸ� Temp�� ���� ������ �����ϱ� START
		StrArr[StrArrIdx] = (StrStruct*)malloc(sizeof(StrStruct));
		if (!StrArr[StrArrIdx]) {
			printf("[Fatal] malloc() failed\n\n");
			return 0;
		}
		memset(StrArr[StrArrIdx], 0x0, sizeof(StrStruct)); // �� ����ü ���� 0���� �ʱ�ȭ.(�̶�, StrStruct->Type�� 0(Str Type)���� �ڵ����� �ʱ�ȭ ��)

		StrArr[StrArrIdx]->Str = (char*)malloc(MAX_STR_SIZE);
		if (!StrArr[StrArrIdx]->Str) {
			printf("[Fatal] malloc() failed\n\n");
			free(Temp);
			return 0;
		}
		memset(StrArr[StrArrIdx]->Str, 0x0, MAX_STR_SIZE);

		strcpy_s(StrArr[StrArrIdx]->Str, MAX_STR_SIZE, Temp); // ������ ���� Temp ���ڿ��� StrArr�� ���ҿ� ����
	} // Temp�� ������� �ʴٸ� Temp�� ���� ������ �����ϱ� START

	free(Temp); // Temp �� �����Ƿ�, Temp�� �Ҵ��ߴ� ���� release

	if (StrArrIdx == ARRMAX) { // StrArr�� �ִ� ���� ������ 0x100���̴�. ���� ���� ������ 0x101�� �̻��� ��� ������ �߻���Ų��.
		printf("[!] Error: �Է��Ͻ� �����ڿ� �ǿ������� ������ ������ %u�� �̻��Դϴ�(�����ϴ� �ִ� �����ڿ� �ǿ������� ������ ����: %u��)\n\n", ARRMAX, ARRMAX);
		return 0;
	}

	return 1;
}