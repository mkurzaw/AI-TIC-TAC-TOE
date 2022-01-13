#pragma once
#include <iostream>
#include <vector>
#include "Point.h"
// zabezpieczenie przed wpisaniem niprawidlowego punktu.. czysci bufor
#define CLEAR_CIN { cin.clear(); cin.ignore(INT_MAX, '\n'); }

using namespace std;

bool tie(vector<vector<char>>& v);
void get_input(const string&, size_t&);
void fill_vector(vector<vector<char>>&, size_t, char);
void print_map(size_t size, const vector<vector<char>>& vec, size_t field_size);
void print_line(size_t, size_t);
void bot(char sign, vector<vector<char>>& initial_state, unsigned int depth);
bool win(const vector<vector<char>>& symbols);
bool check_connection(const vector<vector<char>>& symbols, const Point& p0, const Point& p1, const Point& p2,
                      const bool& condition);
