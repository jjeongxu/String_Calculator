#include "essential.h"

char Add(StrStruct* Str1, StrStruct* Str2, StrStruct* Target) { // Str1 + Str2�� �����ϰ�, �ᱣ���� Target�� �����Ѵ�. �Լ� ���� �� 1, ���� �� 0�� return
	uint8 reallocFlag = 0; // realloc()�� �߻��ߴ��� ��Ÿ���� Flag
	uint64 NewSize = 0; // realloc()�� �� ���, realloc() �� ũ�⸦ �����ϴ� ����

	if (strlen(Str1->Str) + strlen(Str2->Str) >= MAX_STR_SIZE) { // ���� Str1+Str2�� ũ�Ⱑ Target�� ũ��(MAX_STR_SIZE)���� ũ�ٸ�
		NewSize = strlen(Str1->Str) + strlen(Str2->Str) + 1; // 'Str1 + Str2�� ���� + 1'��ŭ�� NewSize ������ ����.( +1�� NULL byte�� ���� ) 
		Target->Str = (char*)realloc(Target->Str, NewSize); // NewSize ũ�⸸ŭ realloc() ����

		if (!Target->Str) { // realloc() ���� ��, ���μ��� ����
			printf("[Fatal] realloc() failed\n\n");
			exit(1); // exit(0): Exit Success <-> exit(1): Exit Failure
		}
		reallocFlag = 1; // realloc()�� �߻������Ƿ�, reallofFlag�� 1�� set
	}
	if (Str1->Type == 1 || Str2->Type == 1) { // ���� Str1->Type�� 1(Integer)�̰ų� Str2->Type�� 1(Integer)���, ���ڿ��� Integer�� ������ �Ұ��ϹǷ� ���� �߻�
		printf("[!] Error occurred while adding>> \"%s + %s\"\n", Str1->Str, Str2->Str);
		printf("[!] Integer�� String�� ��ĥ �� �����ϴ�.\n");
		printf("[Info] ���ڿ� �� ������ ���� ��, �ᱣ���� Integer�� �˴ϴ�.\n\n");
		return 0; // return fail
	}

	if (!reallocFlag) // realloc()�� �߻����� ���� ���, ���� Target�� ũ��(MAX_STR_SIZE)��ŭ sprintf_s() ����
		sprintf_s(Target->Str, MAX_STR_SIZE, "%s%s", Str1->Str, Str2->Str);
	else // realloc()�� �߻��� ���, NewSize��ŭ sprintf_s() ����
		sprintf_s(Target->Str, NewSize, "%s%s", Str1->Str, Str2->Str);


	return 1; // return success
}

char Subtract(StrStruct* Str1, StrStruct* Str2, StrStruct* Target) { // Str1 - Str2 ���� ��, �ᱣ���� Target�� ����. �Լ� ���� �� 1, ���� �� 0 return
	uint8 reallocFlag = 0; // Add �Լ��� ����
	uint64 NewSize = 0; // Add �Լ��� ����

	if (strlen(Str1->Str) >= MAX_STR_SIZE) { // Str1�� ũ�Ⱑ MAX_STR_SIZE���� ū ���
		NewSize = strlen(Str1->Str) + 1;
		Target->Str = (char*)realloc(Target->Str, NewSize); // Target�� NewSize ũ��� realloc

		if (!Target->Str) { // realloc() ���� �� ���μ��� ����
			printf("[Fatal] realloc() failed\n\n");
			exit(1);
		}
		reallocFlag = 1;
	}

	if (Str1->Type == 1 || Str2->Type == 1) { // Add �Լ��� ������ �˻�
		printf("[!] Error occurred while subtracting>> \"%s - %s\"\n", Str1->Str, Str2->Str);
		printf("[!] Integer�� String�� ������ �� �����ϴ�.\n");
		printf("[Info] ���ڿ� �� ������ ���� ��, �ᱣ���� Integer�� �˴ϴ�.\n\n");
		return 0;
	}

	char* Ptr = strstr(Str1->Str, Str2->Str); // Str1���� Str2�� ã�´�. Str1���� Str2�� ã���� ��� Ptr�� 0�� �ƴϴ� <-> ��ã���� ��� Ptr�� 0�̴�.

	if (!reallocFlag) { // realloc�� �߻����� ���� ���, MAX_STR_SIZE�� ���� ���� ����
		if (!Ptr) { // Str1���� Str2�� ��ã�� ���.
			sprintf_s(Target->Str, MAX_STR_SIZE, "%s", Str1->Str); // �ᱣ���� ������ Str1�̴�
		}
		else { // Str1���� Str2�� ã�� ���
			strncpy_s(Target->Str, MAX_STR_SIZE, Str1->Str, Ptr - Str1->Str); // Str1���� 'ã�� String' ������ Target�� ����
			sprintf_s(Target->Str, MAX_STR_SIZE, "%s%s", Target->Str, Ptr + strlen(Str2->Str)); // Str1���� 'ã�� String' ���� ���� Target�� ����
		}
	}
	else { // realloc�� �߻��� ���, NewSize�� ���� ���� ����
		if (!Ptr) { // Str1���� Str2�� ��ã�� ���
			sprintf_s(Target->Str, NewSize, "%s", Str1->Str); // �ᱣ���� ������ Str1�̴�.
		}
		else { // Str1���� Str2�� ã�� ���
			strncpy_s(Target->Str, NewSize, Str1->Str, Ptr - Str1->Str); // Str1���� 'ã�� String' ������ Target�� ����
			sprintf_s(Target->Str, NewSize, "%s%s", Target->Str, Ptr + strlen(Str2->Str)); // Str1���� 'ã�� String' ���� ���� Target�� ����
		}
	}

	return 1; // return success
}

char Multiply(StrStruct* Str1, StrStruct* MulNum, StrStruct* Target) { // Str1�� MulNum��ŭ �ݺ��ϰ�, �ᱣ���� Target�� �����Ѵ�.
	uint8 reallocFlag = 0; // Add �Լ��� ����
	uint64 NewSize = 0; // Add �Լ��� ����

	for (uint32 i = 0; i < strlen(MulNum->Str); i++) {
		if (!isdigit(MulNum->Str[i]) && MulNum->Str[i] != ' ') {
			printf("[!] Error occurred while multiplying>> \"%s * %s\"\n", Str1->Str, MulNum->Str);
			printf("[!] String ���� ���� ��, ���� ���ڷδ� Integer�� �;� �մϴ�(ex. Hello * 3)\n\n");
			return 0;
		}
	}
	if (Str1->Type == 1) {
		printf("[!] Error occurred while multiplying>> \"%s * %s\"\n", Str1->Str, MulNum->Str);
		printf("[!] �� ����� ���ڿ� �����Դϴ�. Integer�� Integer�� ������ �������� �ʽ��ϴ�.\n");
		printf("[Info] ���ڿ� �� ������ ���� ��, �ᱣ���� Integer�� �˴ϴ�.\n\n");
		return 0;
	}

	uint64 Count = strtoull(MulNum->Str, NULL, 10); // ���ڿ��� MulNum->Str�� uint64 type���� ��ȯ�Ͽ� Count�� �����Ѵ�.

	if (strlen(Str1->Str) * Count >= MAX_STR_SIZE) { // Str1*Count�� ���̰� MAX_STR_SIZE���� �� ��� realloc ���ش� START
		NewSize = strlen(Str1->Str) * Count; // NewSize�� Str1*Count�� ���� + 1
		Target->Str = (char*)realloc(Target->Str, NewSize + 1);
		if (!Target->Str) {
			printf("[Fatal] realloc() failed\n\n");
			exit(1);
		}
		reallocFlag = 1;
	} // Multiply �� �ᱣ���� ���̰� MAX_STR_SIZE���� �� ��� realloc ���ش� END

	if (!reallocFlag) { // realloc�� �߻����� ���� ���, ���� Target�� ũ���� MAX_STR_SIZE�� ���� ���� ����
		for (uint64 i = 0; i < Count; i++) {
			if (i == 0)
				strcpy_s(Target->Str, MAX_STR_SIZE, Str1->Str); // i == 0�� ���� strcpy_s()�� ���� Str1->Str�� ������ Target->Str ������ �����Ѵ�
			else
				strcat_s(Target->Str, MAX_STR_SIZE, Str1->Str); // i != 0�� ����, strcat_s()�� Count-1����ŭ �ݺ��Ѵ�.
		}
	}
	else { // realloc�� �߻��� ���
		for (uint64 i = 0; i < NewSize; i++) {
			if (i == 0)
				strcpy_s(Target->Str, NewSize + 1, Str1->Str);
			else
				strcat_s(Target->Str, NewSize + 1, Str1->Str);
		}
	}

	return 1;
}

char Divide(StrStruct* Str1, StrStruct* Str2, StrStruct* Target) { // Str1���� Str2�� �� �� �ִ��� �� ��, �ᱣ���� Target�� ����
	if (Str1->Type == 1 || Str2->Type == 1) { // Add �Լ��� ������ �˻�
		printf("[!] Error occurred while dividing>> \"%s / %s\"\n", Str1->Str, Str2->Str);
		printf("[!] Integer�� String�� ������ �� �����ϴ�\n");
		printf("[Info] ���ڿ� �� ������ ���� ��, �ᱣ���� Integer�� �˴ϴ�.\n\n");
		return 0;
	}

	uint32 Count = 0; // Str1�� Str2�� �� �� ����ִ����� ������ ����
	char* Ptr = Str1->Str; // �ݺ��� ��ȸ�� ���� ����. Ptr�� �ʱⰪ�� Str1->Str�� ���� �ּ��̴�

	while (1) { // Str1���� Str2�� ����ִ� ���� ã�� START
		if (Ptr = strstr(Ptr, Str2->Str)) { // Ptr ��ġ�������� Str2�� ã�� ���
			Ptr += strlen(Str2->Str); // Ptr ������ Str1���� Str2�� ��ġ�� ��ġ �ٷ� �ڸ� ����Ű���� �����Ѵ�.
			Count++; // Count 1 ����
			if (Ptr[0] == 0) // ���� Ptr�� ����Ű�� ��ġ�� ���� NULL�̶��
				break; // �ݺ��� break
		}
		else { // Str1���� Str2�� ��ã�� ���
			break; // �ݺ��� Ż��
		}
	} // Str1���� Str2�� ����ִ� ���� ã�� END

	sprintf_s(Target->Str, MAX_STR_SIZE, "%u", Count); // Target�� Count ���� ���ڿ��� ġȯ�Ͽ� ����
	Target->Type = 1; // �������� �ᱣ���� Integer�̹Ƿ�, �ᱣ���� ���� Taret�� Type ����� 1(Integer)�� �������ش�.

	return 1; // return success
}