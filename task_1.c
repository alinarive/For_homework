#include <stdio.h>
#include <stdlib.h>

void change_size(int *current_size, int position, char **array){
	if (position >= *current_size){
		(*current_size)=(*current_size)*2;
		*array = (char *)realloc(*array, *current_size);
	}
}

int compare(char *first, char *second){
	int i=0;
	while (first[i]){
		if (first[i] > second[i])
			return 1;
		if (first[i] < second[i])
			return 0;
		i++;
	}
	return 0;
}

void sort_bubble(char **destination_array, int length){
	int flag_finished=0;
	if (length>0){
		while (!flag_finished){
			flag_finished=1;
			int i=0;
			for (i=0;i<=length-1;i++){
				if (compare(destination_array[i], 
						destination_array[i+1])){
					char *tmp_line=NULL;
					tmp_line=destination_array[i];
					destination_array[i]=
						destination_array[i+1];
					destination_array[i+1]=tmp_line;
					flag_finished=0;
				}
			}
		}
	}
}

void print_result(char **lines, int lines_count){
	int i=0;
	for (i=0;i<=lines_count;i++)
		printf("%s\n", lines[i]);
	for (i=0;i<=lines_count;i++)
		free(lines[i]);
	free(lines);	
}

void read_string(char **lines, int *lines_count, int array_length){
	char *string;
	int string_length=8, symbol_count=0, flag_empty_line=0;
	char symbol;
	string = (char *)malloc(string_length*sizeof(char));
	while ((symbol=getchar())!=EOF){
		if (symbol!='\n'){
			change_size(&string_length, symbol_count, &string);
			string[symbol_count] = symbol;
			symbol_count++;
		} else {
			if (symbol_count!=0){
				change_size(&string_length, symbol_count, &string);
				string[symbol_count]='\0';
				change_size(&array_length, 
						*lines_count, &(*lines));
				lines[*lines_count]=string;
				(*lines_count)++;
				string_length=8;
				symbol_count=0;
				string = (char *)malloc(string_length*sizeof(char));
			}
		}
	}
	if (symbol_count!=0){
		change_size(&string_length, symbol_count, &string);
		string[symbol_count]='\0';
		change_size(&array_length, *lines_count, &(*lines));
		lines[*lines_count]=string;
	} else flag_empty_line=1;
	if (flag_empty_line) (*lines_count)--;
	printf("\n\n****\n\n");
}


int main(){
	char **lines;
	int lines_count=0, array_length=8;
	lines = (char **)malloc(array_length*sizeof(char*));
	read_string(&(*lines), &lines_count, array_length);
	sort_bubble(&(*lines), lines_count);
	print_result(&(*lines), lines_count);
	return 0;
}
