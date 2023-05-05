#include <string.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct Node Node;
struct Node {
	Node* left;
	Node* right;
	//This Node struct will be of variable size
	//The pointer next to right will start having chars, specified by maxsize + 1

	//Warning : Donot ever try to store this Node as a array, more so access it's pointer like array
};

//Helper fxn to get char * for a Node
char* char_of(Node* node) {
	return (char*)node + sizeof(*node);
}

int g_max_len = 0;
int g_min_len = 0;

//No alignments for now
int size_of_node() {
	return sizeof(Node) + g_max_len + 1;
}

//A helper fxn
void swap_nodes(Node** a, Node** b) {
	if (a && b) {
		Node* tmp = *a;
		*a = *b;
		*b = tmp;
	}
}

void insert_node(Node** proot, Node* ins_node) {
	if (!proot || !ins_node)
		return;
	if (!(*proot)) {
		*proot = ins_node;
		return;
	}

	if (strcmp(char_of(*proot), char_of(ins_node)) > 0) {
		insert_node(&(*proot)->left, ins_node);
	}
	else {
		insert_node(&(*proot)->right, ins_node);
	}
}



Node* remove_node(Node** proot, char* data) {
	if (!proot || !data || !(*proot))
		return NULL;
	Node* tmp = *proot;
	int res = strcmp(data, char_of(tmp));
	if (res == 0) {
		//Proceed to remove this node
		if (!(*proot)->left && !(*proot)->right){
			*proot = NULL;
			return tmp;
		}
		if (!(*proot)->left) {
			*proot = tmp->right;
			tmp->right = NULL;
			return tmp;
		}
		if (!(*proot)->right) {
			*proot = tmp->left;
			tmp->left = NULL;
			return tmp;
		}
		//Find in order successor

		Node** succ = &(tmp->right);
		while ((*succ)->left) {
			succ = &(*succ)->left;
		}

		swap_nodes(proot, succ);
		swap_nodes(&(*proot)->left, &(*succ)->left);
		swap_nodes(&(*proot)->right, &(*succ)->right);

		//This will guarentee trigger either first or second case of this branch in next step
		return remove_node(succ, data);

	}
	else if (res < 0)
		return remove_node(&(*proot)->left, data);
	else
		return remove_node(&(*proot)->right, data);

}

Node** find_node(Node** proot, char* data) {
	if (!(proot) || !data) {
		return NULL;
	}
	if (!(*proot))
		return NULL;
	int res = strcmp(data, char_of(*proot));
	if (res == 0)
		return proot;
	if (res < 0)
		return find_node(&(*proot)->left, data);
	return find_node(&(*proot)->right, data);

}

void in_order_print(Node* root, FILE * file) {
	if (!root)
		return;
	in_order_print(root->left,file);

	fprintf(file,"%s\n", char_of(root));

	in_order_print(root->right,file);
}

Node* create_node(const char* data) {

	Node* node = (Node*)malloc(size_of_node());
	if (!node)
		return NULL;
	strcpy(char_of(node), data);
	node->left = node->right = NULL;
	return node;

}

void free_node(Node** pnode) {
	if (pnode) {
		if (*pnode) {
			free(*pnode);
			*pnode = NULL;
		}
	}
}

void free_tree(Node** proot) {
	if (!proot || !(*proot))
		return;

	free_tree(&(*proot)->left);
	free_tree(&(*proot)->right);
	free_node(proot);
}

