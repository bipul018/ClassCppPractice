
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


#include "Source1.h"

int main1() {

	g_min_len = 3;
	g_max_len = 8;


	//Read files 
	FILE* file = fopen("data.txt", "r");
	if (!file)
		return -1;
	char* buffer = malloc(g_max_len + 1);
	if (!buffer) {
		fclose(file);
		return -2;
	}
	memset(buffer, 0, g_max_len + 1);
	//Create nodes  and tree
	Node* root = NULL;
	while (!feof(file)) {
		fscanf(file, "%s", buffer);
		Node* temp = NULL;
		temp = create_node(buffer);
		insert_node(&root, temp);
	}
	
	fclose(file);
	free(buffer);


	//Print in inorder 
	//in_order_print(root);
	//printf("\n");

	//Read file
	file = fopen("delete.txt", "r");
	if (!file) {
		free_tree(&root);
		return -3;
	}
	buffer = malloc(g_max_len + 1);
	if (!buffer) {
		fclose(file);
		free_tree(&root);
		return -4;
	}
	memset(buffer, 0, g_max_len + 1);
	//Remove one by one, also print deleted values
	while (!feof(file)) {
		fscanf(file, "%s", buffer);
		Node* temp = remove_node(&root, buffer);
		//printf("%s\t", buffer);
		free_node(&temp);
	}
	//printf("\n");
	fclose(file);
	free(buffer);

	//In order print
	//in_order_print(root);
	//printf("\n");

	//Open file
	file = fopen("search.txt", "r");
	if (!file) {
		free_tree(&root);
		return -5;
	}
	buffer = malloc(g_max_len + 1);
	if (!buffer) {
		fclose(file);
		free_tree(&root);
		return -6;
	}
	memset(buffer, 0, g_max_len + 1);

	//Print string to search, search, print Found if found, Not Found otherwise
	FILE* out_file = fopen("result.txt", "w");
	if (!out_file) {
		fclose(file);
		free(buffer);
		free_tree(&root);
		return -7;
	}

	int first_done = 0;	//For printing new line
	while (!feof(file)) {
		fscanf(file, "%s", buffer);

		if (first_done)
			fprintf(out_file, "\n");
		else
			first_done = 1;

		//printf("%s : ", buffer);
		Node** f_node = find_node(&root, buffer);
		if (f_node)
			fprintf(out_file, "Found");
		else
			fprintf(out_file, "Not Found");
	}
	fclose(out_file);
	fclose(file);
	free(buffer);

	free_tree(&root);

	return 0;

}


int main2() {

	int gen_count = 0;

	printf("Enter number of words to generate : ");
	scanf("%d", &gen_count);

	int min_len, max_len;
	printf("Enter minimum length and maximum length : ");
	scanf("%d%d", &min_len, &max_len);


	g_min_len = 3;
	g_max_len = 8;

	max_len = g_max_len;
	min_len = g_min_len;

	int unit_len = max_len + 1;
	char* words = malloc(gen_count* unit_len * sizeof * words);
	memset(words, 0, gen_count * unit_len * sizeof * words);

	srand((unsigned int)time(NULL));


	//generate words

	for (int i = 0; i < gen_count; ++i) {

		int len = min_len + rand() % (max_len + 1 - min_len );

		for (int j = 0; j < len; ++j) {

			const int nums = 0 + '9' - '0' + 1;
			const int lows = nums + 'z' - 'a' + 1;

			int rnd = rand() % lows;
			if (rnd < nums)
				words[j + unit_len * i] = (char)('0' + rnd);
			else
				words[j + unit_len * i] = (char)('a' + rnd - nums);
		}

	}

	printf("The generated words are now written in files \n");


	//Now write in files
	FILE* file = fopen("data.txt", "w");

	for (int i = 0; i < gen_count; ++i) {
		fprintf(file,"%s", words + i * unit_len);
		if (i != gen_count - 1)
			fprintf(file, "\n");
	}

	fclose(file);

	//find a subset 
	printf("Enter the probability for selection : ");
	float prob_factor = 0.5f;
	scanf("%f", &prob_factor);

	//Create a bit array for marking if selected or not

	//Calculate the upper bit boundary
	int up_bound = (gen_count + 7) & ~7;
	
	char* bit_arr = malloc(up_bound >> 3);

	memset(bit_arr, 0, up_bound >> 3);
	int filter_count = 0;
	for (int i = 0; i < gen_count; ++i) {

		double factor = (double)rand() / (1 + (double)RAND_MAX);
		if (factor <= prob_factor) {

			bit_arr[i >> 3] = bit_arr[i >> 3] | (1 << (i & 7));
			filter_count++;

		}
	}

	//Now actually copy the filter count number of data but shuffeled
	char* selected = malloc(filter_count * unit_len * sizeof * selected);
	int inx = 0;
	for (int i = 0; i < filter_count; ++i) {
		//Find inx 
		while (1) {
			if (bit_arr[inx >> 3] & (1 << (inx & 7)))
				break;
			inx++;
		}


		
		int swap_inx = (int)((i + 1) * ((double)rand() / (1 + (double)RAND_MAX)));

		if (swap_inx != i) {
			strcpy(selected + i * unit_len, selected + swap_inx * unit_len);
		}

		strcpy(selected + swap_inx * unit_len, words + inx * unit_len);
		inx++;

	}

	printf("\nThe selected words for deletion are written in file \n");

	file = fopen("delete.txt", "w");

	for (int i = 0; i < filter_count; ++i) {
		fprintf(file,"%s", selected + i * unit_len);
		if (i != filter_count - 1)
			fprintf(file, "\n");
	}
	fclose(file);

	//Now do the same thing as above again, but occasionally replace the word with new generated word
	//For some uniformity, let's squareroot the prob fac
	prob_factor = sqrtf(prob_factor);
	int query_count = 0;
	for (int i = 0; i < gen_count; ++i) {

		if (bit_arr[i >> 3] & (1 << (i & 7))) {
			bit_arr[i >> 3] ^= (1 << (i & 7));
			continue;
		}

		double factor = (double)rand() / (1 + (double)RAND_MAX);
		if (factor <= prob_factor) {
			bit_arr[i >> 3] = bit_arr[i >> 3] | (1 << (i & 7));
			query_count++;
		}
	}

	prob_factor *= prob_factor;
	char* queried = malloc(query_count * unit_len * sizeof * queried);
	memset(queried, 0, query_count * unit_len * sizeof * queried);
	inx = 0;
	for (int i = 0; i < query_count; ++i) {
		//Find inx 
		while (1) {
			if (bit_arr[inx >> 3] & (1 << (inx & 7)))
				break;
			inx++;
		}

		int swap_inx = (int)((i + 1) * ((double)rand() / (1 + (double)RAND_MAX)));

		if (swap_inx != i) {
			strcpy(queried + i * unit_len, queried + swap_inx * unit_len);
		}

		double factor = (double)rand() / (1 + (double)RAND_MAX);
		if (factor <= prob_factor) {

			int len = min_len + rand() % (max_len + 1 - min_len);

			for (int j = 0; j < len; ++j) {

				const int nums = 0 + '9' - '0' + 1;
				const int lows = nums + 'z' - 'a' + 1;

				int rnd = rand() % lows;
				if (rnd < nums)
					queried[j + unit_len * swap_inx] = (char)('0' + rnd);
				else
					queried[j + unit_len * swap_inx] = (char)('a' + rnd - nums);
			}
		
		}
		else
			strcpy(queried + swap_inx * unit_len, words + inx * unit_len);
		inx++;

	}

	printf("\nThe strings to be queried are written in file \n");

	file = fopen("search.txt", "w");

	for (int i = 0; i < query_count; ++i) {
		fprintf(file,"%s", queried + i * unit_len);
		if (i != query_count - 1)
			fprintf(file, "\n");
	}
	fclose(file);

	
	free(queried);
	free(selected);
	free(words);
	return 0;
}

int main() {
	return main1();
}