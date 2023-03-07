#ifndef _GRID_WORLD_H
#define _GRID_WORLD_H

#include <vector>
#include <iostream>
#include "helper.h"

// using std::vector;
using namespace std;

class GridWorld {

private:
    // private stuff goes here!
    //   typedefs
    //   data members
    //   private helper functions
    //   etc.
    int rows = 0;
    int cols = 0;
    int alive = 0;

    // grid
    vector<vector<District*>> grid;
    vector<Person*> all_alive;

    // next id
    Person* next_person_id;

    //private functions
    Person* get_new_id() {
        if (next_person_id == NULL) {
            Person* new_person = new Person(alive , nullptr , nullptr);

            all_alive.push_back(new_person);

            return new_person;
        } else {
            Person* temp = next_person_id;

            if (next_person_id->next != NULL) {
                if (next_person_id->next == next_person_id->prev) {
                    next_person_id->next->prev = NULL;
                    next_person_id->next->next = NULL;
                } else {
                    next_person_id->next->prev = next_person_id->prev;
                    next_person_id->prev->next = next_person_id->next;
                }
            }

            next_person_id = next_person_id->next;

            temp->next = NULL;
            temp->prev = NULL;

            all_alive[temp->id] = temp;

            return temp;
        }
    }

    Person* get_last_from_district(int row , int col) {
        if (grid[row][col] == NULL) {
            return NULL;
        }

        if (grid[row][col]->pop == 1) return grid[row][col]->first;

        return grid[row][col]->first->prev;
    }

public:
    /**
    * constructor:  initializes a "world" with nrows and
    *    ncols (nrows*ncols districtcs) in which all
    *    districtricts are empty (a wasteland!).
    */
    GridWorld(unsigned nrows , unsigned ncols) {
        rows = nrows;
        cols = ncols;
        alive = 0;
        next_person_id = NULL;

        // construct the RxC grid
        grid = vector<vector<District*>>(rows , vector<District*>(cols , nullptr));
    }

    ~GridWorld() {
        // grid
        for (auto row: grid) {
            for (District* district: row) {
                if (district == NULL) continue;

                Person* curr = district->first->next;
                Person* temp = curr;

                while (curr != district->first && curr != NULL) {
                    temp = curr;
                    curr = curr->next;

                    delete temp;
                }

                delete district->first;
                delete district;
            }
        }

        // next_person_id
        if (next_person_id != NULL) {
            Person* temp = NULL;
            Person* curr = next_person_id->next;

            while (curr != next_person_id && curr != NULL) {
                temp = curr;
                curr = curr->next;

                delete temp;
            }

            delete next_person_id;
        }
    }

    /*
     * function: birth
     * description:  if row/col is valid, a new person is created
     *   with an ID according to rules in handout.  New person is
     *   placed in district (row, col)
     *
     * return:  indicates success/failure
     */
    bool birth(int row , int col , int& id) {
        if ((row < 0 || row >= rows) ||
            (col < 0 || col >= cols)) {
            return false;
        }

        Person* new_person = get_new_id();

        new_person->r = row;
        new_person->c = col;

        // put it in the district
        Person* last = get_last_from_district(row , col);

        if (last == NULL) {
            grid[row][col] = new District(new_person);
        } else {
            new_person->prev = last;
            // for round link, to get the last person O(1)
            new_person->next = last->next;

            if (last->next != NULL) {
                last->next->prev = new_person;
            } else {
                new_person->next = last;
                last->prev = new_person;
            }

            last->next = new_person;
            grid[row][col]->pop++;
        }

        id = new_person->id;
        alive++;
        return true;
    }

    /*
     * function: death
     * description:  if given person is alive, person is killed and
     *   data structures updated to reflect this change.
     *
     * return:  indicates success/failure
     */
    bool death(int personID) {
        if (personID < 0 ||
            personID >= all_alive.size() ||
            all_alive[personID] == NULL) {
            return false;
        }
        // save pointer to the person
        Person* killed = all_alive[personID];

        // update grid (districts)
            // pop
            // round chain
            // case : if only person
        grid[killed->r][killed->c]->pop--;

        if (grid[killed->r][killed->c]->pop == 0) {
            delete grid[killed->r][killed->c];
            grid[killed->r][killed->c] = NULL;
        } else {
            // if only 2 people
            if (killed->next == killed->prev) {
                killed->next->prev = NULL;
                killed->next->next = NULL;

                grid[killed->r][killed->c]->first = killed->next;
            } else {
                if (grid[killed->r][killed->c]->first == killed) {
                    grid[killed->r][killed->c]->first = killed->next;
                }
                killed->next->prev = killed->prev;
                killed->prev->next = killed->next;
            }
        }

        //update alive (to NULL)
        all_alive[personID] = NULL;

        // add to next id avail
            // still round chain
            // change r,c to -1,-1
            // case : first person
        if (next_person_id == NULL) {
            next_person_id = killed;
            killed->next = NULL;
            killed->prev = NULL;
        } else {
            Person* last = NULL;

            if (next_person_id->prev == NULL) {
                last = next_person_id;
            } else {
                last = next_person_id->prev;
            }

            killed->prev = last;
            killed->next = next_person_id;

            if (last->next != NULL) {
                last->next->prev = killed;
            } else {
                killed->next = last;
                last->prev = killed;
            }

            last->next = killed;
        }

        killed->r = -1;
        killed->c = -1;

        alive--;
        return true;
    }

    /*
     * function: whereis
     * description:  if given person is alive, his/her current residence
     *   is reported via reference parameters row and col.
     *
     * return:  indicates success/failure
     */
    bool whereis(int id , int& row , int& col)const {
        if (id < 0 || all_alive.size() <= id ||
            all_alive[id] == NULL) return false;

        row = all_alive[id]->r;
        col = all_alive[id]->c;

        return true;
    }

    /*
     * function: move
     * description:  if given person is alive, and specified target-row
     *   and column are valid, person is moved to specified district and
     *   data structures updated accordingly.
     *
     * return:  indicates success/failure
     *
     * comment/note:  the specified person becomes the 'newest' member
     *   of target district (least seniority) --  see requirements of members().
     */
    bool move(int id , int targetRow , int targetCol) {
        if ((targetRow < 0 || targetRow >= rows) ||
            (targetCol < 0 || targetCol >= cols) ||
            id < 0 || all_alive.size() <= id ||
            all_alive[id] == NULL) {
            return false;
        }

        Person* moving = all_alive[id];

        // update grid (districts)
            // pop
            // round chain
            // case : if only person
        grid[moving->r][moving->c]->pop--;

        if (grid[moving->r][moving->c]->pop == 0) {
            delete grid[moving->r][moving->c];
            grid[moving->r][moving->c] = NULL;
        } else {
            // if only 2 people
            if (moving->next == moving->prev) {
                moving->next->prev = NULL;
                moving->next->next = NULL;

                grid[moving->r][moving->c]->first = moving->next;
            } else {
                if (grid[moving->r][moving->c]->first == moving) {
                    grid[moving->r][moving->c]->first = moving->next;
                }
                moving->next->prev = moving->prev;
                moving->prev->next = moving->next;
            }
        }

        moving->next = NULL;
        moving->prev = NULL;

        // put it in the district
        Person* last = get_last_from_district(targetRow , targetCol);

        if (last == NULL) {
            grid[targetRow][targetCol] = new District(moving);
        } else {
            moving->prev = last;
            // for round link, to get the last person O(1)
            moving->next = last->next;

            if (last->next != NULL) {
                last->next->prev = moving;
            } else {
                moving->next = last;
                last->prev = moving;
            }

            last->next = moving;
            grid[targetRow][targetCol]->pop++;
        }

        moving->r = targetRow;
        moving->c = targetCol;

        return true;
    }


    /*
     * function: members
     * description:  creates and populates an integer vector with a
     *   snapshot of the current residents of a district specified by
     *   the parameters row and col.  The vector musted by ordered in
     *   descending order of seniority (the person who has lived in the
     *   district the longest must be first).
     *
     *
     * return:  a pointer to the vector created
     *
     * comment/note:  If there is no such district (row, col), a vector is
     *   still created and returned, but it is empty.  An empty vector is
     *   also returned if there is no one living the in specified vector.
     */
    std::vector<int>* members(int row , int col)const {
        if ((row < 0 || row >= rows) ||
            (col < 0 || col >= cols) ||
            grid[row][col] == NULL) {
            vector<int>* ans = new vector<int>();
            return ans;
        }

        int pop = grid[row][col]->pop;
        vector<int>* ans = new vector<int>(pop);
        int i = 0;
        Person* curr = grid[row][col]->first;

        for (int i = 0; i < pop; i++) {
            (*ans)[i] = curr->id;
            curr = curr->next;
        }

        return ans;
    }

    /*
     * function: population
     * description:  returns the current (living) population of the world.
     */
    int population()const {
        return alive;
    }

    /*
     * function: population(int,int)
     * description:  returns the current (living) population of specified
     *   district.  If district does not exist, zero is returned
     */
    int population(int row , int col)const {
        if ((row < 0 || row >= rows) ||
            (col < 0 || col >= cols) ||
            (grid[row][col] == NULL)) {
            return 0;
        }

        return grid[row][col]->pop;
    }

    /*
     * function: num_rows
     * description:  returns number of rows in world
     */
    int num_rows()const {
        return rows;
    }

    /*
     * function: num_cols
     * description:  returns number of columns in world
     */
    int num_cols()const {
        return cols;
    }
};

#endif
