#include "sumpr4.h"

char* GenerateRandomString(unsigned int max_size) {

	char alpha[] = "abcdefghijklmnopqrstuvwxyz";

	unsigned int size = rand() % max_size + 1;

	char* string = (char*)malloc((size + 1) * sizeof(char));

	// генерация одной случайной строки
	for (int i = 0; i < size; i++) {
		string[i] = alpha[rand() % strlen(alpha)];

	}
	string[size] = '\0';

	return string;
}

void GenerateRandomStrings(FILE* outputfile, char* str) {

	for (int i = 0; i < STRINGS_COUNT; i++) {

		char* str = GenerateRandomString(MAX);

		fputs(str, outputfile);
		fputs("\n", outputfile);
	}
	fseek(outputfile, 0, 0);
}

void ReadFile(char* filename, char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("Ошибка при открытия файла\n");
		exit(1);
	}
	int count = 0;
	char tmp;
	int k = 0, flag = 0, space = 0;

	for (int j = 0; j < STRINGS_COUNT; j++) {

		dynamicStrings[j] = (char*)malloc(sizeof(char));

		for (int i = 0; ; i++) {

			tmp = fgetc(file);

			if (count < MAX_STRING_SIZE && tmp == '\n') {

				dynamicStrings[j] = NULL;
				staticStrings[j][i] = '\0';
				count = 0;
				break;
			}

			if (tmp == '\n')
			{
				if (space == 0) { //если у меня всё влезло в static 
					dynamicStrings[j][0] = '\0';
				}
				else { // если не влезло в static
					dynamicStrings[j][i] = '\0';
				}
				flag = 1; //флаг для того, чтобы,когда переходил на след строки, у меня index динамического массива каждый раз обнулялся..
							//на случай того,если что-то не влезет в static
							
				count = 0;
				space = 0;

				break;
			}
			if (count < MAX_STRING_SIZE && tmp != '\n') {
				staticStrings[j][i] = tmp;
				count++;
			}

			else if (count == MAX_STRING_SIZE) { //если количество букв уже равно максимальному количеству разрешенных символов в static,то идем сюда и записываем в dynamic
				if (space == 0) {
					space = 1;
				}
				if (flag == 1) {
					k = 0; flag = 0;
				}

				if (k == 0) {
					i = 0; // для обнуления индеса в dynamic string
					k = 1;
				}
				dynamicStrings[j] = (char*)realloc(dynamicStrings[j], sizeof(char) * (i + 1));
				dynamicStrings[j][i] = tmp;
			}
		}
	}
}

void PrintStrings(char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings) {

	int flag = 0;

	for (int j = 0; j < STRINGS_COUNT; j++) {
		for (int i = 0; i < MAX_STRING_SIZE; i++) {
			if (staticStrings[j][i] == '\0') {
				flag = 1;
				break;
			}
			printf("%c", staticStrings[j][i]);
		}
		if (flag == 0) {
			printf("%s", dynamicStrings[j]);
		}
		printf("\n");
		flag = 0;
	}
}

//STRINGS_COUNT  10/
//MAX_STRING_SIZE 10
//MAX 12
//int length(char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings, int index, int index1, int len1, int len2, int indef) {
//
//	int flag = 0;
//	len1 = 0;
//	for (int i = 0; i < MAX_STRING_SIZE; i++) {
//		if (staticStrings[index][i] == '\0') {
//			flag = 1;
//			break;
//		}
//		len1++;
//	}
//	if (flag == 0) {
//		len1 += strlen(dynamicStrings);
//	}
//	flag = 0;
//	len2 = 0;
//
//	for (int i = 0; i < MAX_STRING_SIZE; i++) {
//		if (staticStrings[index1][i] == '\0') {
//			flag = 1;
//			break;
//		}
//		len2++;
//	}
//	if (flag == 0) {
//		len2 += strlen(dynamicStrings);
//	}
//	flag = 0;
//	if (indef == 1) {
//
//		if (len1 == len2) {
//			return 0;
//		}
//		else if (len1 > len2) {
//			return 1;
//		}
//		else {
//			return 2;
//		}
//	}
//	else if (indef == 0) {
//		if (len1 == len2) {
//			return 0;
//		}
//		else if (len1 > len2) {
//			return 2;
//		}
//		else {
//			return 1;
//		}
//	}
//}

int SortPlus(char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings, int index, int index1) {
	/*int len1 = 0, len2 = 0;
	length(staticStrings, dynamicStrings, index, index1, len1, len2, 1);*/

	int flag = 0;
	int len1 = 0;

	for (int i = 0; i < MAX_STRING_SIZE; i++) {
		if (staticStrings[index][i] == '\0') { //включаю флаг, для того, чтобы узнать, есть ли символы которые пойдут в dynamic или нет
			flag = 1;
			break;
		}
		len1++;
	}
	if (flag == 0) { 
		len1 += strlen(dynamicStrings[index]);
	}
	flag = 0;
	int len2 = 0;

	for (int i = 0; i < MAX_STRING_SIZE; i++) {
		if (staticStrings[index1][i] == '\0') {
			flag = 1;
			break;
		}
		len2++;
	}
	if (flag == 0) {
		len2 += strlen(dynamicStrings[index1]);
	}
	flag = 0;

	if (len1 == len2) {
		return 0;
	}
	else if (len1 > len2) {
		return 1;
	}
	else {
		return 2;
	}
}

int SortMinus(char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings, int index, int index1) {
	/*int len1 = 0, len2 = 0;
	length(staticStrings, dynamicStrings, index, index1, len1, len2, 0);*/

	int flag = 0;
	int len1 = 0;

	for (int i = 0; i < MAX_STRING_SIZE; i++) {
		if (staticStrings[index][i] == '\0') {
			flag = 1;
			break;
		}
		len1++;
	}
	if (flag == 0) {
		len1 += strlen(dynamicStrings[index]);
	}
	flag = 0;
	int len2 = 0;

	for (int i = 0; i < MAX_STRING_SIZE; i++) {
		if (staticStrings[index1][i] == '\0') {
			flag = 1;
			break;
		}
		len2++;
	}
	if (flag == 0) {
		len2 += strlen(dynamicStrings[index1]);
	}
	flag = 0;

	if (len1 == len2) {
		return 0;
	}
	else if (len1 > len2) {
		return 2;
	}
	else {
		return 1;
	}
}

int caseA_Z(char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings, int index, int index1) {

	for (int j = 0; j < MAX_STRING_SIZE; j++) {

		if (staticStrings[index][j] == '\0') {
			return 2;
		}

		if (staticStrings[index1][j] == '\0') {
			return 1;
		}
		if (staticStrings[index][j] > staticStrings[index1][j]) {
			return 1;
		}
		else if (staticStrings[index][j] < staticStrings[index1][j]) {
			return 2;
		}
	}
	if (strcmp(dynamicStrings[index], dynamicStrings[index1]) > 0) {
		return 1;
	}
	else if (strcmp(dynamicStrings[index], dynamicStrings[index1]) < 0) {
		return 2;
	}
	else {
		return 2;
	}
    return 0;
}
int caseZ_A(char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings, int index, int index1) {


	for (int j = 0; j < MAX_STRING_SIZE; j++) {

		if (staticStrings[index][j] == '\0') {
			return 1;
		}

		if (staticStrings[index1][j] == '\0') {
			return 2;
		}
		if (staticStrings[index][j] > staticStrings[index1][j]) {
			return 2;
		}
		else if (staticStrings[index][j] < staticStrings[index1][j]) {
			return 1;
		}
	}
	if (strcmp(dynamicStrings[index], dynamicStrings[index1]) > 0) {
		return 2;
	}
	else if (strcmp(dynamicStrings[index], dynamicStrings[index1]) < 0) {
		return 1;
	}
	else {
		return 2;
	}
}

void SortStrings(char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings, int (*compareStringsFunction)(char staticStrings[][MAX_STRING_SIZE], char** dynamicStrings, int, int)) {

	for (int j = 0; j < STRINGS_COUNT; j++) {
		for (int i = 0; i < STRINGS_COUNT - 1; i++) {

			//если == 1 , то значит, что-то отличается, и нужно будет поменять,захожу меняю посимвольно строки  местами статического массива
			if ((compareStringsFunction(staticStrings, dynamicStrings, i, i + 1)) == 1) {

				char tmp[MAX_STRING_SIZE];

				for (int k = 0; k < MAX_STRING_SIZE; k++) {

					if (staticStrings[i][k] == '\0') {
						tmp[k] = '\0';
						break;
					}

					tmp[k] = staticStrings[i][k];
				}
				for (int k = 0; k < MAX_STRING_SIZE; k++) {

					if (staticStrings[i + 1][k] == '\0') {
						staticStrings[i][k] = '\0';
						break;
					}
					staticStrings[i][k] = staticStrings[i + 1][k];
				}

				for (int k = 0; k < MAX_STRING_SIZE; k++) {
					if (tmp[k] == '\0') {
						staticStrings[i + 1][k] = '\0';
						break;
					}
					staticStrings[i + 1][k] = tmp[k];
				}
				//меняем оставшиеся
				char* tmpD = dynamicStrings[i];
				dynamicStrings[i] = dynamicStrings[i + 1];
				dynamicStrings[i + 1] = tmpD;
			}

		}
	}

}