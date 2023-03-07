
#ifndef _MY_TRIE_H
#define _MY_TRIE_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


class Trie {

protected:
    // private/protected stuff goes here!
    //  - protected allows this class to be inherited
    //    and adapted to the problem at hand (if needed)
    //   typedefs
    //   data members
    //   definition of trie node structure
    //   private helper functions
    //   etc.

    struct node {
        char curr;
        bool is_word;

        vector<node*> next;

        node() {
            curr = '!'; // nothing
            is_word = false;

            next = vector<node*>(26 , NULL);
        }

        node(bool w): curr('!') , is_word(w) {
            next = vector<node*>(26 , NULL);
        }

        node(char c): curr(c) , is_word(false) {
            next = vector<node*>(26 , NULL);
        }

        node(char c , bool w): curr(c) , is_word(w) {
            next = vector<node*>(26 , NULL);
        }
    };

    node* head;
    int num_words;


    //------ protected functions -----------------
    node* gethead() {
        return head;
    }

    void lower(string &word) {
        for (char &c: word) {
            c = tolower(c);
        }
    }

    bool proper(string &word) const {
        if (word == "") return false;

        for (char &c: word) {
            if (!isalpha(c)) return false;
        }

        return true;
    }

    void rec_clear(node* curr) {
        if (curr == NULL) return;

        for (node* n : curr->next) {
            rec_clear(n);
        }

        if (curr->is_word) num_words--;
        delete curr;
    }

    bool help_insert(const string &word) {
        node* curr = head;
        int n = word.size();
        int i = 0;

        while (curr != NULL && i < n && curr->next[word[i]-'a'] != NULL) {
            curr = curr->next[word[i]-'a'];
            i++;
        }

        if (curr != NULL && i == n && curr->is_word) return false;
        else if (curr != NULL && i == n) {
            curr->is_word = true;
        } else if (curr != NULL) {
            while (i < n) {
                curr->next[word[i]-'a'] = new node(word[i], false);

                curr = curr->next[word[i]-'a'];
                i++;
            }

            curr->is_word = true;
        }

        num_words++;
        return true;
    }

    void rec_add(vector<string> *ans, node* curr, string so_far) const {
        if (curr == NULL) return;

        if (curr->is_word) {
            (*ans).push_back(so_far);
        }

        for (node* c: curr->next) {
            if (c != NULL) {
                rec_add(ans, c, so_far + c->curr);
            }
        }
    }

    bool check_all_null(node* curr) {
        if (curr == NULL) return false;

        for (node* n: curr->next) {
            if (n != NULL) return false;
        }

        return true;
    }

    bool rec_remove(string &word, int i, node* curr) {
        if (curr == NULL) return false;

        if (i == word.size() && curr->is_word) {
            curr->is_word = false;
            num_words--;

            return true;
        } else if (i != word.size()) {
            node* move_to = curr->next[word[i]-'a'];
            if (rec_remove(word, i+1, move_to)) {
                if (check_all_null(move_to) && !move_to->is_word) {
                    delete move_to;

                    curr->next[word[i]-'a'] = NULL;
                }

                return true;
            }
        }

        return false;
    }


public:
    /**
    * constructor and destructor
    */
    Trie() {
        head = new node();
        num_words = 0;
    }
    ~Trie() {
        // your destructor code here.
        rec_clear(head);
        head = NULL;
    }

    /*
     * function: getFromFile
     * description:  extract all of the words from the file
     *   specified by the filename given in the parameter.
     *   Words are separated by whitespace characters and
     *   must only contain letters.
     *
     * return:  indicates success/failure (file not readable...)
     */
    bool getFromFile(string filename) {
        ifstream file(filename);
        string word;

        if (!file.is_open()) {
            return false;
        }

        while (file >> word) {
            insert(word);
        }

        return file.eof();
    }

    /*
     * function: insert
     * description:  inserts the word given by the parameter
     *   into the trie data structure.
     *
     *   fails if word already exists or contains non-letters
     *
     * return:  indicates success/failure
     */
    bool insert(string word) {
        if (!proper(word)) return false;
        lower(word);

        return help_insert(word);
    }

    /*
     * function: search
     * description:  determines if the word given by the parameter
     *   is stored in the trie data structure.
     *
     *   fails if word already does not exist
     *
     * return:  indicates success/failure
     */
    bool search(string word) const {
        int n = word.size();
        node* curr = head;
        int i = 0;

        while (i < n) {
            if (curr->next[word[i]-'a'] == NULL) return false;
            
            curr = curr->next[word[i]-'a'];
            i++;
        }

        return curr->is_word;
    }

    /*
     * function: remove
     * description:  removes the word given by the parameter
     *   from the trie data structure.  Only deallocate nodes
     *   in subtrees that do not contain any words.
     *
     *   succeed if word exists and is properly removed
     *
     * return:  indicates success/failure
     */
    bool remove(string word) {
        return rec_remove(word, 0, head);
    }

    /*
     * function: clear
     * description:  remove all words from the trie and deallocate
     *   all nodes.
     *
     * return:  indicates success/failure
     */
    bool clear() {
        rec_clear(head);
        head = new node();
        return num_words == 0;
    }



    /*
     * function: wordCount
     * description:  return the number of words currently stored in the trie
     *
     * return:  an integer containing the number of words stored
     *
     * comment/note:  this should have an O(1) runtime.
     */
    int wordCount() const {
        return num_words;
    }


    /*
     * function: words
     * description:  build a vector of all words in the dictionary and return that
     *   vector.  The words are to be in sorted ascending order.
     *
     * return:  a pointer to a vector of strings
     *
     */
    std::vector<string>* words() const {
        vector<string> *ans = new vector<string>();
        string temp = "";

        rec_add(ans, head, temp);

        return ans;
    }
};

#endif
