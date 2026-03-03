/* Завдання створити алгоритм який приймає рядок з букв та цифр (ascii 0-9, A-Z, a-z),
 - та повертає інший рядок, за певними правилами:
 - 1. Цифри що зустрічаються більше 1 разу пропадають;
 - 2. Пари літер, що йдуть підряд пропадають (aa, AA);
 - 3. Всі символи відсортовані згідно з ascii кодами в порядку зростання; */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#include "charList.h"

typedef struct {
	char key;
	int value;
} dictItem;

typedef struct {
	dictItem *items;
	int size;
} dict;

static int charToIndex(char c) {
	if (isdigit(c))
		return c - '0';

	if (isupper(c))
		return c - 'A' + 10;

	if (islower(c))
		return c - 'a' + 36;

	return -1;
}

static void inalgorithm__load_prevLetter(dict *dict, int isLetterOdd, char prevLetter) {
	if (isLetterOdd) {
		int charIndex = charToIndex(prevLetter);
		if (charIndex == -1)
			return;

		((dict->items)[charIndex]).value++;
	}
}

static void inalgorithm__iter(dict *dict, int *isLetterOdd, char *prevLetter, char current_char)
{
	if (current_char == *prevLetter) {
		*isLetterOdd = !(*isLetterOdd);
	} else {
		inalgorithm__load_prevLetter(dict, *isLetterOdd, *prevLetter);

		if (isdigit(current_char)) {
			int charIndex = charToIndex(current_char);
			((dict->items)[charIndex]).value++;
			*isLetterOdd = 0;
		} else {
			*isLetterOdd = 1;
			*prevLetter = current_char;
		}
	}
}

char *algorithm(char *word) {
	dictItem dictCharsItems[] = DICT_CHARS_LIST;
	dict dictChars = {dictCharsItems, sizeof(dictCharsItems) / sizeof(dictCharsItems[0])};
	int wordLen = strlen(word);
	char *ret = calloc(1, wordLen + 1);
	int isLetterOdd = 0;
	int retPtr = 0;
	char prevLetter = 0;

	if (wordLen > 0) {
		for (int i = 0; i < wordLen; i++) {
			inalgorithm__iter(&dictChars, &isLetterOdd, &prevLetter, word[i]);
		}

		inalgorithm__load_prevLetter(&dictChars, isLetterOdd, prevLetter);

		for (int i = 0; i < 10; i++) {
			if (((dictChars.items)[i]).value == 1)
				ret[retPtr++] = i + '0';
		}

		for (int p = 10; p < dictChars.size; p++) {
			for (int q = 0; q < ((dictChars.items)[p]).value; q++) {
				ret[retPtr++] = dictChars.items[p].key;
			}
		}
	}

	return ret;
}

int main() {
	printf("%s\n", algorithm("adawd"));
	return 0;
}
