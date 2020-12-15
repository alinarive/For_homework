#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct List {
	char *string;
	int count;
	struct List *next;
};

int open_file (FILE *file)
{
    if (file == NULL) {
        fprintf(stdout, "Error with opening the file\n");
         return 1;
    } else
        printf("OK\n");
    return 0;
}

char *get_string(FILE *file)
{
	int length = 10, number = 0, position = 0;
	char *string = malloc(length * sizeof(char));
	if (!string) {
   		perror("Error");
   		exit(1);
	}
	while (fgets(string + position, 10, file)) {
		number = strlen(string);
		if (string[number - 1] != '\n') {
			position = number;
			length += 10;
			string = realloc(string, length);
			if (!string) {
   				perror("error");
   				exit(1);
			}
		} else {
			string[number - 1] = '\0';
			return string;
		}
	}
	free(string);
	return NULL;
}

void push_list(struct List **head, char *string)
{
	struct List *tmp_list = (struct List *)malloc(sizeof(struct List));
	tmp_list->string = string;
	tmp_list->count = 1;
	tmp_list->next = *head;
	*head = tmp_list;
}

int are_strings_similar(char *string1, char *string2)
{
	int i = 0;
	while ((string1[i] != '\0') && (string2[i] != '\0')) {
		if (string1[i] < string2[i]) return 0;
		if (string1[i] > string2[i]) return 0;
		i++;
	}
	if ((string1[i] == '\0') && (string2[i] == '\0')) {
		return 1;
	}
	return 0;
}

struct List *if_similar_string_is_in_list(struct List *head, char *string)
{
	int string_is_not_found = 1;
	struct List *tmp_list = head;
	tmp_list = head;
	while (tmp_list->next != NULL) {
		if (are_strings_similar(tmp_list->string, string) == 1) {
			tmp_list->count = tmp_list->count + 1;
			string_is_not_found = 0;
			head = tmp_list;
			break;			
		}
		tmp_list = tmp_list->next;
	}
	if (string_is_not_found) {
		push_list(&head, string);
	}
	return head;
}

int main(int argc, char *argv[])
{
	FILE *file = NULL;
	char *string = NULL;
	char *most_frequent_string = NULL;
	struct List *head, *tmp_list;
	int max_frequency = 0;
	head = (struct List *)malloc(sizeof(struct List));
	head->next = NULL;	
	head->string = NULL;
	head->count = 0;
	if (argc < 2) {
        	printf("No arguments in command line\n");
        	return 0;
    }
	file = fopen(argv[1], "r");
    	if (open_file(file) == 1) return 1;
	while ((string = get_string(file)) != NULL) {
		head = if_similar_string_is_in_list(head, string);
	}
	tmp_list = head;
	while (tmp_list->next != NULL) {
		if (tmp_list->count > max_frequency) {
			max_frequency = tmp_list->count;
			most_frequent_string = tmp_list->string;
		}
		tmp_list = tmp_list->next;
	}
    printf("\n");
    printf("The most common string: ");
	printf("%s\n", most_frequent_string);
   	fclose(file);
    return 0;
}
