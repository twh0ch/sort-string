#include  "sumpr4.h"

int main(int argc, char* argv[]) {


	setlocale(LC_ALL, "RUS");
	srand(time(NULL));
	char staticStrings[STRINGS_COUNT][MAX_STRING_SIZE];

	char** dynamicStrings = (char**)malloc(sizeof(char*) * STRINGS_COUNT);

	char filename[] = "outputFileArray.rtf";
	FILE* outputfile = fopen(filename, "w");
	if (outputfile == NULL) {
		printf("Ошибка при открытии output  файла\n");
		exit(1);
	}
	char* str = NULL;
	GenerateRandomStrings(outputfile, str);

	ReadFile(filename, staticStrings, dynamicStrings);
	printf("Исходная запись\n\n");
	PrintStrings(staticStrings, dynamicStrings);
	printf("\n==================================\n\n");

	printf("Сортировка по возрастанию длины\n\n");
	SortStrings(staticStrings, dynamicStrings,SortPlus);
	PrintStrings(staticStrings, dynamicStrings);

	printf("\n==================================\n\n");

	printf("Сортировка по убыванию длины\n\n");
	SortStrings(staticStrings, dynamicStrings, SortMinus);
	PrintStrings(staticStrings, dynamicStrings);

	printf("\n==================================\n\n");

	printf("Сортировка от a до z\n\n");
	SortStrings(staticStrings, dynamicStrings, caseA_Z);
	PrintStrings(staticStrings, dynamicStrings);

	printf("\n==================================\n\n");

	printf("Сортировка от z до a\n\n");
	SortStrings(staticStrings, dynamicStrings, caseZ_A);
	PrintStrings(staticStrings, dynamicStrings);

	return 0;
}

