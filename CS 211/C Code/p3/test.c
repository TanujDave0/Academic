
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

// void calculateSum(darray* d1, int* sum) {
// 	*sum = 0;
// 	for (int i =0; i < d1->inUse; i++) {
// 		if (i%2==1) {
// 			*sum += d1->darr[i];
// 		}
// 	}
// }

typedef char c;

typedef struct treeNode{
    int val;
	struct treeNode a;
    struct treeNode* left;
    struct treeNode* right;
}node;

int rightSum (node* root){
    if (root == NULL) {
        return 0;
    }
    if (root->right == NULL ) {
        if (root->left != NULL) {
            return root->val + rightSum(root->left);
        }else {
            return root->val;
        }
    }
    return root->val + rightSum(root->right);
}

// void MoveMinFront(node ** head) {
//     node* curr = *head;
//     node* tempPrev = NULL;
//     node* min = NULL;
//     node* prev = NULL;
// 	if (*head == NULL) {
// 		return;
// 	}
//     int minValue = (*head)->val;
//     while (curr != NULL) {
//         if (curr->val < minValue) {
//             minValue = curr->val;
//             min = curr;
//             prev = tempPrev;
//         }
//         tempPrev = curr;
//         curr = curr->next;
//     }
//     if (min != *head) {
//         prev->next = min->next;
//         min->next = *head;
//         *head = min;
//     }
// }

int main() {
	return 0;
}