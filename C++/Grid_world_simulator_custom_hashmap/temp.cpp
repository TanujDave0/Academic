


void helper(bstnode* root, bstnode* &curr_answer, int param) {
    if (!root) return NULL;

    if (root->data <= param) {
        helper(root->right, curr_answer, param);
    }
    if (root->data > param && (!curr_answer || root->val < curr_answer->data)) {
        curr_answer = root;

        helper(root->left, curr_answer, param);
        return;
    }
}

bstnode* main() {
    bstnode* root;
    bstnode* curr_answer = NULL;
    int param;

    helper(root, curr_answer, param);

    if (curr_answer) return curr_answer;
    else return NULL;
}