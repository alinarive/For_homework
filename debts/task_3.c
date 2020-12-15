#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct List {
	char *s;
	struct List *next;
};

char *get_string()
{
	int length = 8, symbols = 0, position = 0;
	char *string = malloc(length * sizeof(char));
	while (fgets(string + position, 8, stdin)) {
		symbols = strlen(string);
		if (string[symbols - 1] != '\n') {
			position = symbols;
			length += 8;
			string = realloc(string, length);
			if(!string) {
				printf("Error with realloc\n");
				break;
			}
		} else {
			string[symbols - 1] = '\0';
			return string;
		}
	}
	free(string);
	return NULL;
}

int compare_string(char *string1, char *string2)
{
	int i = 0;
	while ((string1[i] != '\0') && (string2[i] != '\0')) {
		if(string1[i] < string2[i]) return 0;
		if(string1[i] > string2[i]) return 1;
		++i;
	}
	if(string2[i] == '\0') {return 1;}
	return 0;
}

struct List *sort_list (struct List *head, int string_count)
{
	struct List *tmp_list = head;
	int i, j;
	for(i = 0 ; i < (string_count - 1); i++) {
		j = i;
		head = tmp_list;
    		while(j < string_count && head->next->next != NULL) {
			int first_is_bigger_than_second = compare_string(head->s,
                head->next->s);
			if (first_is_bigger_than_second) {
				char *tmp_string = head->next->s;
				head->next->s = head->s;
				head->s = tmp_string;
			}
			head = head->next;
			j++;
        	}
	}
	head = tmp_list;
	return head;
}

void push_list(struct List **head, char *string)
{
	struct List *tmp_list = (struct List *)malloc(sizeof(struct List *));
	tmp_list->s = string;
	tmp_list->next = (*head);
	(*head) = tmp_list;
}

void print_list(struct List *head)
{
    while (head){
        struct List *tmp = head;
        printf("%s\n", tmp->s);
        free(tmp->s);
        free(tmp);
        head = head->next;
    }
}

int main()
{
	char *string;
	struct List *head;
    int to_execute = 1;
    do {
        int string_count = 0;
        head = (struct List *)malloc(sizeof(struct List *));
        head->next = NULL;
        while ((string = get_string()) != NULL) {
            push_list(&head, string);
            string_count++;
        }
        head = sort_list(head, string_count);
        printf("\n");
        print_list(head);
        printf("\n");
        scanf("%d", &to_execute);
    } while (to_execute)
}

