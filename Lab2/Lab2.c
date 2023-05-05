#include <stdio.h>
#include <string.h>
#include <stdlib.h>



//Don't attempt to think making refrence variables inside these two
//They should be easily surfce copyable
typedef struct {
	char str[8];
} Key;
typedef struct {
	long long score;
} Value;
typedef struct {
	Key key;
	Value value;
} Data;

struct ListNode;

struct ListNode{
	struct ListNode* next;
	Data data;
};

typedef struct ListNode ListNode;

int ScoreDataKeyEqual(Key d1, Key d2) {
	return strcmp(d1.str, d2.str) == 0;
}

unsigned long ScoreDataKeyHash(Key d) {
	unsigned long val = 0;
	for (int i = 0; i < 7; ++i) {
		if (!(d.str[i]))
			break;
		val += (unsigned long)d.str[i];
	}
	return val;
}

ListNode* find( ListNode * node,Key key) {
	while (node != NULL) {
		if (ScoreDataKeyEqual(key,node->data.key)) {
			return node;
		}
		node = node->next;
	}
	return NULL;
}

ListNode* insert(ListNode* node, Data data) {
	ListNode* newNode = malloc(sizeof * node);
	if (!newNode)
		return NULL;
	newNode->data = data;
	newNode->next = NULL;
	if (node) {
		newNode->next = node->next;
		node->next = newNode;
	}
	return newNode;
}

ListNode* insertEnd(ListNode* node, Data data) {
	if (!node)
		return insert(node, data);
	while (node->next)
		node = node->next;
	return insert(node, data);
}

ListNode* erase(ListNode* start, Key key) {
	if (!start )
		return NULL;
	if (ScoreDataKeyEqual(start->data.key, key)) {
		ListNode* next = start->next;
		free(start);
		return next;
	}
	ListNode* curr = start;
	ListNode* next = start->next;
	while (next != NULL) {
		if (ScoreDataKeyEqual(next->data.key, key)) {
			curr->next = next->next;
			free(next);
			next = curr->next;
			return start;
		}
		else {
			curr = next;
			next = next->next;
		}
	}
	return start;
}

void traverse(ListNode* start, void(*trav_func)(Key , Value ) ) {
	while (start) {
		trav_func(start->data.key,start->data.value);
		start = start->next;
	}
}

void printNode(Key key, Value value) {
	printf_s("Name : %s, Score : %lli\n", key.str, value.score);
}

void clear(ListNode* node) {
	if (!node)
		return;
	ListNode* next = node->next;
	while (node) {
		next = node->next;
		free(node);
		node = next;
	}
}

typedef struct {
	ListNode** main_table;
	size_t num_elem;
	unsigned long (*hashFunc)(Key);
	int (*is_same_key)(Key, Key);
}HashTable_list;

HashTable_list initHash_list(size_t approx_num
	, int (*check_euality)(Key, Key)
	, unsigned long (*hashFunc)(Key)) 
{
	HashTable_list table = { 0 };
	size_t tble_size = 1;
	while (approx_num) {
		tble_size = tble_size << 1;
		approx_num = approx_num >> 1;
	}
	table.main_table = malloc(tble_size * sizeof(ListNode*));
	if (!table.main_table)
		return table;
	table.num_elem = tble_size;
	memset(table.main_table, 0, tble_size * sizeof(ListNode*));
	
	table.is_same_key = check_euality;
	table.hashFunc = hashFunc;
	return table;
}

HashTable_list freeHash_list(HashTable_list table) {
	if (table.main_table) {

		for (size_t i = 0; i < table.num_elem; ++i) {
			if (table.main_table[i]) {
				clear(table.main_table[i]);
				table.main_table[i] = NULL;
			}
		}
		free(table.main_table);
	}
	table.is_same_key = NULL;
	table.main_table = NULL;
	table.hashFunc = NULL;
	table.num_elem = 0;
	return table;	
}

HashTable_list hashInsert_list(HashTable_list table, Data data) {
	unsigned long hash = table.hashFunc(data.key);
	size_t index = (size_t)(hash % table.num_elem);
	ListNode* node = insert(table.main_table[index], data);
	if (!table.main_table[index])
		table.main_table[index] = node;
	return table;
}

Data* hashFind_list(HashTable_list table, Key key) {
	unsigned long hash = table.hashFunc(key);
	size_t index = (size_t)(hash % table.num_elem);
	ListNode* node = find( table.main_table[index], key);
	if (node)
		return &(node->data);
	return NULL;

}

void hashTraverse_list(HashTable_list table, void(*trav_func)(Key key, Value value)) {
	for (size_t i = 0; i < table.num_elem; ++i) {
		if (table.main_table[i])
			traverse(table.main_table[i], trav_func);
	}
}

typedef struct {
	Data* main_table;
	size_t num_elem;
	unsigned long (*hashFunc)(Key);
	int (*is_same_key)(Key, Key);
}HashTable_line;


HashTable_line initHash_line(size_t approx_num
	, int (*check_euality)(Key, Key)
	, unsigned long (*hashFunc)(Key))
{

	HashTable_list table = { 0 };
	size_t tble_size = 1;
	while (approx_num) {
		tble_size = tble_size << 1;
		approx_num = approx_num >> 1;
	}
	table.main_table = malloc(tble_size * sizeof(ListNode*));
	if (!table.main_table)
		return table;
	table.num_elem = tble_size;
	memset(table.main_table, 0, tble_size * sizeof(ListNode*));

	table.is_same_key = check_euality;
	table.hashFunc = hashFunc;
	return table;
}
typedef enum {
	FIND  ='f',
	LIST  ='l',
	INSERT='i',
	REMOVE='r',
	CLEAR ='c',
	EXIT  ='e'
} Choice;

int main(void) {

	Choice ch = INSERT;
	ListNode* head = NULL;
	Data data;
	HashTable_list h_table = { 0 };

	while (ch != EXIT) {

		switch (ch) {
		case INSERT:
		{
			printf_s("Enter name :");
			scanf_s("%s", data.key.str,7);
			printf_s("Enter score : ");
			scanf_s("%lli", &(data.value.score));
			if (!h_table.main_table)
				h_table = initHash_list(3, ScoreDataKeyEqual, ScoreDataKeyHash);
			hashInsert_list(h_table,data);
			break;

		}
		break;
		case FIND:
		{
			printf_s("Enter name :");
			scanf_s("%s", data.key.str,7);
			Data* p_data = hashFind_list(h_table, data.key);


			if (p_data)
				printNode(p_data->key,p_data->value);
			else
				printf_s("Not Found!\n");
			

		}
		break;
		case LIST:
		{
			hashTraverse_list(h_table, printNode);
			break;
		}
		break;
		case CLEAR:
		{
			h_table = freeHash_list(h_table);
			printf_s("Data Cleared\n");
		}
		break;
		case REMOVE:
		{
			break;
			//printf_s("Enter name :");
			//scanf_s("%s", temp_score.str,7);
			//head = erase(info,head, &temp_score);
			//printf_s("All occurences of %s removes\n", temp_score.str);
		}
		break;
		case EXIT:
		{

		}
			break;
		default:
			system("cls");
		}

		printf_s("Enter choice from following :\nFind : f, Insert : i, List : l, Remove : r, Clear : c, Exit :e\n");
		scanf_s("%s", data.key.str, 2);
		ch = (Choice)(data.key.str)[0];
	}
	h_table = freeHash_list(h_table);
	clear(head);
	head = NULL;

	return 0;
}