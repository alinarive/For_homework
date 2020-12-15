#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int open_file(FILE *file)
{
	if (file == NULL) {
		fprintf(stdout, "Error opening file\n");
		return 1;
	} else
        printf("OK\n");
	return 0;
}

void sort_strings(FILE *file, FILE *tmp_file, int max_length, int string_length_to_look_for)
{
	char string[max_length];
	int j = 0;
	char symbol;
	fseek(file, 0, SEEK_SET);
	while (!feof(file)) {
		symbol = fgetc(file);
        if (symbol == '\n') {
            if (j == string_length_to_look_for) {
                string[j] = '\n';
                fwrite(string, j + 1, 1, tmp_file);
            }
            j = 0;
            continue;
        } else {
            if (j <= string_length_to_look_for)
                string[j] = symbol;
        }
        j++;
    }
}

int main(int argc, const char *argv[])
{
	int max_length = 0, i = 0, symbol_count = 0;
	char symbol;
	FILE *file = NULL, *tmp_file = NULL;
	if (argc < 3) {
		printf("No arguments in command line\n");
        return -1;
    }
	while (argv[2][i] != '\0') {
		symbol_count += 1;
	    	i++;
	}
	for ( i = 0; i < symbol_count ; i++)
		max_length = max_length*10 + (argv[2][i] - '0');
    file = fopen(argv[1], "r");
	if (open_file(file) == 1)
        return -1;
    tmp_file = fopen("tmp_file.txt", "a");
    if (open_file(tmp_file) == 1)
        return 1;
	for (i = 0; i <= max_length; i++)
		sort_strings(file, tmp_file, max_length, i);
    fclose(file);
    fclose(tmp_file);
	tmp_file = fopen("tmp_file.txt", "r");
    if (open_file(tmp_file) == 1)
        return 1;
	file = fopen(argv[1], "w");
    if (open_file(file) == 1)
        return 1;
	while (!feof(tmp_file)) {
		symbol = fgetc(tmp_file);
   		if (symbol != EOF)
			fwrite(&symbol, sizeof(char), 1, file);
	}
	fclose(file);
    fclose(tmp_file);
	printf ("Delete file tmp_file: ");
	if (remove ("tmp_file.txt") == -1)
        	printf("Error\n");
	else
    		printf("Done\n");
	return 0;
}
