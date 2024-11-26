#include "essential.h"

void Erase(StrStruct** StrArr, int Index) { // StrArr 배열에서 특정 Index를 지워주는 함수 ex. StrArr->Str: {"a", "ab", "b"} => Erase(StrArr, 0) => StrArr->Str: {"ab", "b"}
	free(StrArr[Index]->Str); // StrArr에서 지우려는 Index의 Str 멤버의 공간 release
	StrArr[Index]->Str = NULL; // StrArr[Index]->Str을 NULL로 설정

	free(StrArr[Index]); // StrArr[Index] release
	StrArr[Index] = NULL; // StrArr[Index]를 NULL로 설정

	do { // 지운 index 뒤의 원소들을 모두 앞으로 당겨옴. 이때 StrArr[Index]가 NULL이라면 반복 종료
		StrArr[Index] = StrArr[Index + 1];
		Index++;
	} while (StrArr[Index] != NULL);
	StrArr[Index] = StrArr[Index + 1];
}

char Calc(StrStruct** StrArr) { // StrArr를 토대로 다항연산을 수행하는 함수. 성공 시 1을, 실패 시 0을 return 한다.
	int OpenBrack, ClosedBrack; // 괄호를 가리킬 Index
	char OpenBrackFlag, ClosedBrackFlag; // 열린 괄호, 닫힌 괄호를 찾았는지 표시하는 변수. 0: Not found <-> 1: Found
	char BrackOpFlag; // 한 단위의 괄호 연산이 끝났음을 나타내는 flag. 0: Undone, 1: Done

	while (1) { // (1) while() 괄호 계산 및 괄호 없애기 START
		OpenBrack = 0; // 열린 괄호를 가리키는 Index 0으로 초기화
		ClosedBrack = 0; // 닫힌 괄호를 가리키는 Index 0으로 초기화
		OpenBrackFlag = 0; // 열린 괄호를 찾았는지 나타내는 Flag 0으로 초기화
		ClosedBrackFlag = 0; // 닫힌 괄호를 찾았는지 나타내는 Flag 0으로 초기화
		BrackOpFlag = 0; // 한 단위의 괄호 연산이 끝났음을 나타내는 Flag 0으로 초기화

		for (uint32 i = 0; StrArr[i] != NULL; i++) { // 가장 마지막에 있는 '(' 찾기 START
			if (StrArr[i]->Str[0] == '(') {
				OpenBrack = i;
				OpenBrackFlag = 1;
			}
		} // 가장 뒤에 있는 '(' 찾기 END

		for (uint32 i = OpenBrack; StrArr[i] != NULL; i++) { // 방금 찾은 '('에 대응되는 닫힌 괄호 찾기 START
			if (StrArr[i]->Str[0] == ')') {
				ClosedBrack = i;
				ClosedBrackFlag = 1;
				break;
			}
		} // 방금 찾은 '('에 대응되는 닫힌 괄호 찾기 END

		if ((OpenBrackFlag && !ClosedBrackFlag) || (!OpenBrackFlag && ClosedBrackFlag)) { // 괄호 짝 안 맞는 경우 함수 실패
			printf("[!] 괄호의 짝이 맞지 않습니다.\n\n");
			return 0;
		} // 괄호 짝 안 맞는 경우 Error handling END

		if (!OpenBrackFlag && !ClosedBrackFlag) // StrArr에 더이상 괄호가 존재하지 않는 경우, 괄호 연산을 위한 반복문 break
			break;

		for (uint32 i = OpenBrack + 1; i < ClosedBrack; i++) { // (a) 곱셈, 나눗셈 위한 for START
			if (ClosedBrack - OpenBrack == 2) { // 괄호 사이에 Operand 하나만 남은 경우, 괄호를 배열에서 지우고 break START ex. (ab) -> ab
				Erase(StrArr, OpenBrack); // StrArr에서 열린 괄호 삭제
				ClosedBrack--; // 열린 괄호를 삭제하면, 닫힌 괄호의 index는 한 칸 당겨지므로 그에 맞게 ClosedBrack 수정
				Erase(StrArr, ClosedBrack); // ClosedBrack도 StrArr에서 삭제
				BrackOpFlag = 1; // 한 단위의 괄호 연산이 끝났으므로, for문 break
				break;
			} // 괄호 사이에 Operand 하나만 남은 경우, 괄호를 배열에서 지우고 break END
			if (StrArr[i]->Str[0] == '*' || StrArr[i]->Str[0] == '/') { // 괄호 안 곱셈, 나눗셈부터 우선적으로 연산 START
				if (StrArr[i]->Str[0] == '*') { // 곱셈인 경우 START
					if (!Multiply(StrArr[i - 1], StrArr[i + 1], StrArr[i])) // 여기서 i는 연산자를 가리키고 있다.
						return 0;
					Erase(StrArr, i - 1);
					ClosedBrack--;
					i--; // 여기서 i는 결괏값을 가리키고 있다.
					Erase(StrArr, i + 1);
					ClosedBrack--;
				} // 곱셈인 경우 END
				else if (StrArr[i]->Str[0] == '/') { // 나눗셈인 경우 START
					if (!Divide(StrArr[i - 1], StrArr[i + 1], StrArr[i])) // 여기서 i는 연산자를 가리키고 있다.
						return 0;
					Erase(StrArr, i - 1);
					ClosedBrack--;
					i--; // 여기서 i는 결괏값을 가리키고 있다.
					Erase(StrArr, i + 1);
					ClosedBrack--;
				} // 나눗셈인 경우 END

				i = OpenBrack; // i를 다시 열린 괄호를 가리키게 하여, 현재 괄호 짝 안에 남은 연산들을 수행하게 한다.
			} // 괄호 안 곱셈, 나눗셈부터 우선적으로 연산 END
		} // (a) 곱셈, 나눗셈 위한 for END
		if (BrackOpFlag) // 한 단위의 괄호 연산이 끝났음을 나타내는 BrackOpFlag가 set 돼있다면,
			continue; // while의 시작으로 돌아가서 새로운 괄호 짝을 찾는다.

		for (uint32 i = OpenBrack + 1; i < ClosedBrack; i++) { // (b) 덧셈 뺄셈 위한 for START
			if (ClosedBrack - OpenBrack == 2) { // 괄호 사이에 Operand 하나만 남은 경우 -> 괄호 배열에서 삭제하고 break START
				Erase(StrArr, OpenBrack);
				ClosedBrack--;
				Erase(StrArr, ClosedBrack);
				BrackOpFlag = 1;
				break;
			} // 괄호 사이에 Operand 하나만 남은 경우 -> 괄호 배열에서 삭제하고 break END
			if (StrArr[i]->Str[0] == '+' || StrArr[i]->Str[0] == '-') { // 괄호 안 덧셈, 뺄셈 연산 START
				if (StrArr[i]->Str[0] == '+') { // 덧셈인 경우 START
					if (!Add(StrArr[i - 1], StrArr[i + 1], StrArr[i])) // 여기서 i는 연산자를 가리키는 인덱스이다.
						return 0;
					Erase(StrArr, i - 1);
					ClosedBrack--;
					i--; // 여기서 i는 결괏값을 가리키는 인덱스이다.
					Erase(StrArr, i + 1);
					ClosedBrack--;
				} // 덧셈인 경우 END
				else if (StrArr[i]->Str[0] == '-') { // 뺄셈인 경우 START
					if (!Subtract(StrArr[i - 1], StrArr[i + 1], StrArr[i])) // 여기서 i는 연산자를 가리키는 인덱스이다.
						return 0;
					Erase(StrArr, i - 1);
					ClosedBrack--;
					i--; // 여기서 i는 결괏값을 가리키는 인덱스이다.
					Erase(StrArr, i + 1);
					ClosedBrack--;
				} // 뺄셈인 경우 END

				i = OpenBrack; // i를 다시 열린 괄호를 가리키게 하여, 현재 괄호 짝 안에 남은 연산들을 수행하게 한다.
			} // 괄호 안 덧셈, 뺄셈 연산 END
		} // (b) 덧셈 뺄셈 위한 for END
	} // (1) while() 괄호 계산 및 괄호 없애기 END

	if (StrArr[1] != NULL) { // StrArr[1] == NULL이라면 위의 괄호를 계산하는 while문에서 전체 계산식의 결괏값이 나온 것이므로, return 1을 하도록 한다.
		while (1) { // (2) while() 위에서 괄호 없어진 계산식 연산 START
			if (StrArr[1] == NULL) // StrArr[1] == NULL이라면 전체 계산식의 결괏값을 도출해낸 것이므로 while에서 break 한다.
				break;

			for (uint32 i = 0; StrArr[i] != NULL; i++) { // (a) 곱셈, 나눗셈 위한 for START
				if (StrArr[i]->Str[0] == '*' || StrArr[i]->Str[0] == '/') { // 괄호 안 곱셈, 나눗셈부터 우선적으로 연산 START
					if (StrArr[i]->Str[0] == '*') { // 곱셈인 경우 START
						if (!Multiply(StrArr[i - 1], StrArr[i + 1], StrArr[i])) // 여기서 i는 연산자를 가리키는 인덱스이다
							return 0;
						Erase(StrArr, i - 1);
						i--; // 여기서 i는 결괏값을 가리키는 인덱스이다.
						Erase(StrArr, i + 1);

						break; // 곱셈 나눗셈 위한 for문 break
					} // 곱셈인 경우 END
					else if (StrArr[i]->Str[0] == '/') { // 나눗셈인 경우 START
						if (!Divide(StrArr[i - 1], StrArr[i + 1], StrArr[i])) // 여기서 i는 연산자를 가리키는 인덱스이다
							return 0;
						Erase(StrArr, i - 1);
						i--; // 여기서 i는 결괏값을 가리키는 인덱스이다.
						Erase(StrArr, i + 1);

						break; // 곱셈 나눗셈 위한 for문 break
					} // 나눗셈인 경우 END
				} // 괄호 안 곱셈, 나눗셈부터 우선적으로 연산 END
			} // (a) 곱셈, 나눗셈 위한 for END

			for (uint32 i = 0; StrArr[i] != NULL; i++) { // (b) 덧셈 뺄셈 위한 for START
				if (StrArr[i]->Str[0] == '+' || StrArr[i]->Str[0] == '-') { // 괄호 안 덧셈, 뺄셈 연산 START
					if (StrArr[i]->Str[0] == '+') { // 덧셈인 경우 START
						if (!Add(StrArr[i - 1], StrArr[i + 1], StrArr[i])) // 여기서 i는 연산자를 가리키는 인덱스이다.
							return 0;
						Erase(StrArr, i - 1);
						i--; // 여기서 i는 결괏값을 가리키는 인덱스이다.
						Erase(StrArr, i + 1);

						break; // 덧셈 뺄셈 위한 for문 break
					} // 덧셈인 경우 END

					else if (StrArr[i]->Str[0] == '-') { // 뺄셈인 경우 START
						if (!Subtract(StrArr[i - 1], StrArr[i + 1], StrArr[i])) // 여기서 i는 연산자를 가리키는 인덱스이다.
							return 0;
						Erase(StrArr, i - 1);
						i--; // 여기서 i는 결괏값을 가리키는 인덱스이다.
						Erase(StrArr, i + 1);

						break; // 덧셈 뺄셈 위한 for문 break
					} // 뺄셈인 경우 END
				} // 괄호 안 덧셈, 뺄셈 연산 END
			} // (b) 덧셈 뺄셈 위한 for END
		} // (2) while() 위에서 괄호 없어진 계산식 연산 END
	}
	return 1; // return success
}