#include "essential.h"

void Erase(StrStruct** StrArr, int Index) { // StrArr �迭���� Ư�� Index�� �����ִ� �Լ� ex. StrArr->Str: {"a", "ab", "b"} => Erase(StrArr, 0) => StrArr->Str: {"ab", "b"}
	free(StrArr[Index]->Str); // StrArr���� ������� Index�� Str ����� ���� release
	StrArr[Index]->Str = NULL; // StrArr[Index]->Str�� NULL�� ����

	free(StrArr[Index]); // StrArr[Index] release
	StrArr[Index] = NULL; // StrArr[Index]�� NULL�� ����

	do { // ���� index ���� ���ҵ��� ��� ������ ��ܿ�. �̶� StrArr[Index]�� NULL�̶�� �ݺ� ����
		StrArr[Index] = StrArr[Index + 1];
		Index++;
	} while (StrArr[Index] != NULL);
	StrArr[Index] = StrArr[Index + 1];
}

char Calc(StrStruct** StrArr) { // StrArr�� ���� ���׿����� �����ϴ� �Լ�. ���� �� 1��, ���� �� 0�� return �Ѵ�.
	int OpenBrack, ClosedBrack; // ��ȣ�� ����ų Index
	char OpenBrackFlag, ClosedBrackFlag; // ���� ��ȣ, ���� ��ȣ�� ã�Ҵ��� ǥ���ϴ� ����. 0: Not found <-> 1: Found
	char BrackOpFlag; // �� ������ ��ȣ ������ �������� ��Ÿ���� flag. 0: Undone, 1: Done

	while (1) { // (1) while() ��ȣ ��� �� ��ȣ ���ֱ� START
		OpenBrack = 0; // ���� ��ȣ�� ����Ű�� Index 0���� �ʱ�ȭ
		ClosedBrack = 0; // ���� ��ȣ�� ����Ű�� Index 0���� �ʱ�ȭ
		OpenBrackFlag = 0; // ���� ��ȣ�� ã�Ҵ��� ��Ÿ���� Flag 0���� �ʱ�ȭ
		ClosedBrackFlag = 0; // ���� ��ȣ�� ã�Ҵ��� ��Ÿ���� Flag 0���� �ʱ�ȭ
		BrackOpFlag = 0; // �� ������ ��ȣ ������ �������� ��Ÿ���� Flag 0���� �ʱ�ȭ

		for (uint32 i = 0; StrArr[i] != NULL; i++) { // ���� �������� �ִ� '(' ã�� START
			if (StrArr[i]->Str[0] == '(') {
				OpenBrack = i;
				OpenBrackFlag = 1;
			}
		} // ���� �ڿ� �ִ� '(' ã�� END

		for (uint32 i = OpenBrack; StrArr[i] != NULL; i++) { // ��� ã�� '('�� �����Ǵ� ���� ��ȣ ã�� START
			if (StrArr[i]->Str[0] == ')') {
				ClosedBrack = i;
				ClosedBrackFlag = 1;
				break;
			}
		} // ��� ã�� '('�� �����Ǵ� ���� ��ȣ ã�� END

		if ((OpenBrackFlag && !ClosedBrackFlag) || (!OpenBrackFlag && ClosedBrackFlag)) { // ��ȣ ¦ �� �´� ��� �Լ� ����
			printf("[!] ��ȣ�� ¦�� ���� �ʽ��ϴ�.\n\n");
			return 0;
		} // ��ȣ ¦ �� �´� ��� Error handling END

		if (!OpenBrackFlag && !ClosedBrackFlag) // StrArr�� ���̻� ��ȣ�� �������� �ʴ� ���, ��ȣ ������ ���� �ݺ��� break
			break;

		for (uint32 i = OpenBrack + 1; i < ClosedBrack; i++) { // (a) ����, ������ ���� for START
			if (ClosedBrack - OpenBrack == 2) { // ��ȣ ���̿� Operand �ϳ��� ���� ���, ��ȣ�� �迭���� ����� break START ex. (ab) -> ab
				Erase(StrArr, OpenBrack); // StrArr���� ���� ��ȣ ����
				ClosedBrack--; // ���� ��ȣ�� �����ϸ�, ���� ��ȣ�� index�� �� ĭ ������Ƿ� �׿� �°� ClosedBrack ����
				Erase(StrArr, ClosedBrack); // ClosedBrack�� StrArr���� ����
				BrackOpFlag = 1; // �� ������ ��ȣ ������ �������Ƿ�, for�� break
				break;
			} // ��ȣ ���̿� Operand �ϳ��� ���� ���, ��ȣ�� �迭���� ����� break END
			if (StrArr[i]->Str[0] == '*' || StrArr[i]->Str[0] == '/') { // ��ȣ �� ����, ���������� �켱������ ���� START
				if (StrArr[i]->Str[0] == '*') { // ������ ��� START
					if (!Multiply(StrArr[i - 1], StrArr[i + 1], StrArr[i])) // ���⼭ i�� �����ڸ� ����Ű�� �ִ�.
						return 0;
					Erase(StrArr, i - 1);
					ClosedBrack--;
					i--; // ���⼭ i�� �ᱣ���� ����Ű�� �ִ�.
					Erase(StrArr, i + 1);
					ClosedBrack--;
				} // ������ ��� END
				else if (StrArr[i]->Str[0] == '/') { // �������� ��� START
					if (!Divide(StrArr[i - 1], StrArr[i + 1], StrArr[i])) // ���⼭ i�� �����ڸ� ����Ű�� �ִ�.
						return 0;
					Erase(StrArr, i - 1);
					ClosedBrack--;
					i--; // ���⼭ i�� �ᱣ���� ����Ű�� �ִ�.
					Erase(StrArr, i + 1);
					ClosedBrack--;
				} // �������� ��� END

				i = OpenBrack; // i�� �ٽ� ���� ��ȣ�� ����Ű�� �Ͽ�, ���� ��ȣ ¦ �ȿ� ���� ������� �����ϰ� �Ѵ�.
			} // ��ȣ �� ����, ���������� �켱������ ���� END
		} // (a) ����, ������ ���� for END
		if (BrackOpFlag) // �� ������ ��ȣ ������ �������� ��Ÿ���� BrackOpFlag�� set ���ִٸ�,
			continue; // while�� �������� ���ư��� ���ο� ��ȣ ¦�� ã�´�.

		for (uint32 i = OpenBrack + 1; i < ClosedBrack; i++) { // (b) ���� ���� ���� for START
			if (ClosedBrack - OpenBrack == 2) { // ��ȣ ���̿� Operand �ϳ��� ���� ��� -> ��ȣ �迭���� �����ϰ� break START
				Erase(StrArr, OpenBrack);
				ClosedBrack--;
				Erase(StrArr, ClosedBrack);
				BrackOpFlag = 1;
				break;
			} // ��ȣ ���̿� Operand �ϳ��� ���� ��� -> ��ȣ �迭���� �����ϰ� break END
			if (StrArr[i]->Str[0] == '+' || StrArr[i]->Str[0] == '-') { // ��ȣ �� ����, ���� ���� START
				if (StrArr[i]->Str[0] == '+') { // ������ ��� START
					if (!Add(StrArr[i - 1], StrArr[i + 1], StrArr[i])) // ���⼭ i�� �����ڸ� ����Ű�� �ε����̴�.
						return 0;
					Erase(StrArr, i - 1);
					ClosedBrack--;
					i--; // ���⼭ i�� �ᱣ���� ����Ű�� �ε����̴�.
					Erase(StrArr, i + 1);
					ClosedBrack--;
				} // ������ ��� END
				else if (StrArr[i]->Str[0] == '-') { // ������ ��� START
					if (!Subtract(StrArr[i - 1], StrArr[i + 1], StrArr[i])) // ���⼭ i�� �����ڸ� ����Ű�� �ε����̴�.
						return 0;
					Erase(StrArr, i - 1);
					ClosedBrack--;
					i--; // ���⼭ i�� �ᱣ���� ����Ű�� �ε����̴�.
					Erase(StrArr, i + 1);
					ClosedBrack--;
				} // ������ ��� END

				i = OpenBrack; // i�� �ٽ� ���� ��ȣ�� ����Ű�� �Ͽ�, ���� ��ȣ ¦ �ȿ� ���� ������� �����ϰ� �Ѵ�.
			} // ��ȣ �� ����, ���� ���� END
		} // (b) ���� ���� ���� for END
	} // (1) while() ��ȣ ��� �� ��ȣ ���ֱ� END

	if (StrArr[1] != NULL) { // StrArr[1] == NULL�̶�� ���� ��ȣ�� ����ϴ� while������ ��ü ������ �ᱣ���� ���� ���̹Ƿ�, return 1�� �ϵ��� �Ѵ�.
		while (1) { // (2) while() ������ ��ȣ ������ ���� ���� START
			if (StrArr[1] == NULL) // StrArr[1] == NULL�̶�� ��ü ������ �ᱣ���� �����س� ���̹Ƿ� while���� break �Ѵ�.
				break;

			for (uint32 i = 0; StrArr[i] != NULL; i++) { // (a) ����, ������ ���� for START
				if (StrArr[i]->Str[0] == '*' || StrArr[i]->Str[0] == '/') { // ��ȣ �� ����, ���������� �켱������ ���� START
					if (StrArr[i]->Str[0] == '*') { // ������ ��� START
						if (!Multiply(StrArr[i - 1], StrArr[i + 1], StrArr[i])) // ���⼭ i�� �����ڸ� ����Ű�� �ε����̴�
							return 0;
						Erase(StrArr, i - 1);
						i--; // ���⼭ i�� �ᱣ���� ����Ű�� �ε����̴�.
						Erase(StrArr, i + 1);

						break; // ���� ������ ���� for�� break
					} // ������ ��� END
					else if (StrArr[i]->Str[0] == '/') { // �������� ��� START
						if (!Divide(StrArr[i - 1], StrArr[i + 1], StrArr[i])) // ���⼭ i�� �����ڸ� ����Ű�� �ε����̴�
							return 0;
						Erase(StrArr, i - 1);
						i--; // ���⼭ i�� �ᱣ���� ����Ű�� �ε����̴�.
						Erase(StrArr, i + 1);

						break; // ���� ������ ���� for�� break
					} // �������� ��� END
				} // ��ȣ �� ����, ���������� �켱������ ���� END
			} // (a) ����, ������ ���� for END

			for (uint32 i = 0; StrArr[i] != NULL; i++) { // (b) ���� ���� ���� for START
				if (StrArr[i]->Str[0] == '+' || StrArr[i]->Str[0] == '-') { // ��ȣ �� ����, ���� ���� START
					if (StrArr[i]->Str[0] == '+') { // ������ ��� START
						if (!Add(StrArr[i - 1], StrArr[i + 1], StrArr[i])) // ���⼭ i�� �����ڸ� ����Ű�� �ε����̴�.
							return 0;
						Erase(StrArr, i - 1);
						i--; // ���⼭ i�� �ᱣ���� ����Ű�� �ε����̴�.
						Erase(StrArr, i + 1);

						break; // ���� ���� ���� for�� break
					} // ������ ��� END

					else if (StrArr[i]->Str[0] == '-') { // ������ ��� START
						if (!Subtract(StrArr[i - 1], StrArr[i + 1], StrArr[i])) // ���⼭ i�� �����ڸ� ����Ű�� �ε����̴�.
							return 0;
						Erase(StrArr, i - 1);
						i--; // ���⼭ i�� �ᱣ���� ����Ű�� �ε����̴�.
						Erase(StrArr, i + 1);

						break; // ���� ���� ���� for�� break
					} // ������ ��� END
				} // ��ȣ �� ����, ���� ���� END
			} // (b) ���� ���� ���� for END
		} // (2) while() ������ ��ȣ ������ ���� ���� END
	}
	return 1; // return success
}