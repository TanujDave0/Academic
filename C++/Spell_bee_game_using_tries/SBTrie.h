
#ifndef _MY_SB_TRIE_H
#define _MY_SB_TRIE_H

#include <iostream>
#include <string>
#include <vector>
#include "Trie.h"


class SBTrie: public Trie {

    // the main reason for inheriting the Trie class is that the words() method in Tries
    // is quite inefficient for the use of the Spelling Bee game.
    //
    // This allows us to customize a better method to get the desired words by "adding an
    // addtional method" on the the Trie class at the cost of using inheritance.

    protected:
    // private/protected stuff goes here!
    //  - protected allows this class to be inherited
    //    and adapted to the problem at hand (if needed)
    //   typedefs
    //   data members
    //   definition of trie node structure
    //   private helper functions
    //   etc.
    char central;
    vector<int> valid_chars;
    Trie *found_words;

    int score = 0;
    bool panagram_found = false;
    bool bingo_found = false;

    int diff_starts = 0;


    //--------------- functions -------------------------------
    bool valid_letters(string &letters) {
        lower(letters);
        string ans = "";
        vector<int> temp(26, 0);

        for (int i = 0; i < letters.size(); i++) {
            if (temp[letters[i]-'a'] != 0) return false;
            if (isalpha(letters[i])) {
                ans += letters[i];
                temp[letters[i]-'a']++;
            }
        }

        if (ans.size() < 7) return false;

        letters = ans;
        return true;
    }

    bool is_bingo(string &word) {
        int diff_starts = 0;
        for (int i = 0; i < valid_chars.size(); i++) {
            if (valid_chars[i] > 1 && i != (word[0] - 'a')) {
                diff_starts++;
            }
        }

        valid_chars[(word[0]-'a')]++;

        return diff_starts == 6 && (valid_chars[(word[0]-'a')] == 2);
    }

    bool valid_spellb_word(string &word, string &info) {
        lower(word);
        string ans = "";
        vector<int> temp(26, 0);
        bool invalid_letter_found = false;
        bool no_central = true;

        for (int i = 0; i < word.size(); i++) {
            if (isalpha(word[i])) {
                if (valid_chars[word[i]-'a'] != 0) {
                    if (word[i] == central) {
                        no_central = false;
                    }

                    ans += word[i];
                } else {
                    ans += word[i];
                    invalid_letter_found = true;
                }
            } else {
                invalid_letter_found = true;
            }
        }
        
        if (ans.size() == 0) {
            info = "word contains invalid letter";
        } else if (ans.size() < 4) {
            info = "word is too short";
        } else if (no_central) {
            info = "word is missing central letter";
        } else if (invalid_letter_found) {
            info = "word contains invalid letter";
        } else if (!search(ans)) {
            info = "word is not in the dictionary";
        } else if (found_words->search(ans)) {
            info = "word has already been found";
        } else {
            info += "found " + ans + " ";

            int points = ans.size()==4?1:ans.size();

            score += points;

            info += to_string(points);
            
            if (points != 1) info += " points, ";
            else info += " point, ";

            info += "total " + to_string(score);

            if (score != 1) info += " points";
            else info += " point";

            if (is_panagram(ans)) {
                panagram_found = true;

                info += ", Panagram found";
            }

            if (is_bingo(ans)) {
                bingo_found = true;

                info += ", Bingo scored";
            }

            found_words->insert(ans);
        }

        return false;
    }

    void build_sbwords(vector<string> *ans, node* curr, char cl, vector<bool> allowed_chars, bool cl_found, string so_far) const {
        if (curr == NULL) return;

        if (curr->is_word && so_far.size() >= 4 && cl_found) {
            ans->push_back(so_far);
        }

        for (node* n: curr->next) {
            if (n != NULL &&
                allowed_chars[n->curr - 'a']) {
                build_sbwords(ans, n, cl, allowed_chars,
                                ((n->curr == cl)?true:cl_found),
                                so_far + n->curr);
            }
        }
    }

    public:
    /**
    * constructor and destructor
    */
    SBTrie() {
        central = '!'; // safe case to generate error
        valid_chars = vector<int>(26, 0);
        found_words = new Trie();
        score = 0;
        diff_starts = 0;
        panagram_found = false;
        bingo_found = false;
    }
    ~SBTrie() {
        // your destructor code here.
        delete found_words;
    }

    bool is_panagram(string &word) const {
        int diff_words = 0;
        vector<bool> alphabets(26, false);

        for (char &c: word) {
            if (!alphabets[c-'a']) {
                diff_words++;
                alphabets[c-'a'] = true;
            }
        }

        return diff_words == 7;
    }

    bool new_set(string letters) {
        if (letters.size() < 7) return false;

        if (valid_letters(letters)) {
            found_words->clear();
            
            central = letters[0];

            for (int &i: valid_chars) {
                i = 0;
            }

            for (int i = 0; i < 7; i++) {
                valid_chars[letters[i]-'a']++;
            }

            score = 0;
            panagram_found = false;
            bingo_found = false;
            diff_starts = 0;

            return true;
        }

        return false;
    }

    string current_set() {
        string ans = "";
        ans += central;

        for (int i = 0; i < 26; i++) {
            if (valid_chars[i] && (i+'a' != central)) {
                ans += (i + 'a');
            }
        }

        return ans;
    }

    bool guess(string word, string &info) {
        return valid_spellb_word(word, info);
    }



    /*
     * function: sbWords
     * description:  build a vector of all words in the dictionary that
     *   are valid words for the spelling bee problem and return that
     *   vector.  The words are to be in sorted ascending order.
     *   The words included must have a length of 4 or greater,
     *                      must contain the central letter, and
     *                      may contain the allowed letters
     *
     * parameter: char centralLetter - the letter that MUST be contained in the words
     *            string letters - the other letters that are allowed to be in words
     *
     * return:  a pointer to a vector of strings
     *
     */
    std::vector<string>* sbWords(char centralLetter , string letters) const {
        vector<string> *ans = new vector<string>();
        vector<bool> allowed_chars(26, false);

        allowed_chars[centralLetter - 'a'] = true;

        for (char &c: letters) {
            allowed_chars[c - 'a'] = true;
        }

        build_sbwords(ans, head, centralLetter, allowed_chars, false, "");

        return ans;
    }

    vector<string>* words_guessed() {
        return found_words->words();
    }

    int total_words_found() {
        return found_words->wordCount();
    }

    int get_score() {
        return score;
    }

    bool get_panagram() {
        return panagram_found;
    }

    bool get_bingo() {
        return bingo_found;
    }


};

#endif
