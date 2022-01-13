#include <iostream>
#include <vector>
#include <random>
#include "Point.h"
#include "Utility.h"

#define DEPTH 4 // Ilosc przewidywanych rychow do przodu

using namespace std;

int main()
{
    //podaje wielkosc pola
    size_t field_size;
    get_input("Podaj rozmiar pola: ", field_size);
    // wprowadza ilosc znakow w rzêdzie
    size_t fields_count = 0;
    while (fields_count < 3)
    {
        get_input("Podaj ilosc znakow w rzedzie: ", fields_count);
    }
//tworze dwuwymiarowa tablice wektorów i wypelnia j¹ spacjami
    vector<vector<char>> symbols;
    fill_vector(symbols, fields_count, ' ');
//losowanie czy jeestes x czy o
    random_device rd;
    mt19937 mt(rd());
    uniform_int_distribution<int> dist(0, 1);

    auto player = (int) dist(mt);
    //wypisywanie symbolu ktorym gramy
    cout << "Gracz: " << (player == 1 ? 'x' : 'o') << endl << "Komputer: " << (player == 1 ? 'o' : 'x') << endl;
    if (player == 1)
    {
        bot('o', symbols, 4);
    }

    while (true)
    {
        //wywietlanie pola do gry
        print_map(fields_count, symbols, field_size);
        cout << "#### RUCH GRACZA ####" << endl;
        //wczyranie puntu wybranego gdy jest wolny
        Point p;
        do
        {
            p = Point::get_point("Podaj x y: ");
        }
        while (p.getX() >= fields_count || p.getY() >= fields_count || symbols.at(p.getY()).at(p.getX()) != ' ');
        //wpisuje x lub o w zaleznosci od gracza na plansze
        symbols.at(p.getY()).at(p.getX()) = player == 1 ? 'x' : 'o';
        print_map(fields_count, symbols, field_size);
        if (win(symbols))
        {
            cout << "Wygral gracz!" << endl;
            break;
        }
        else if (tie(symbols))
        {
            cout << "Remis!";
            break;
        }

        cout << "#### RUCH BOTA ####" << endl;
        //zostahe wykonany ruch bota
        bot(player == 1 ? 'o' : 'x', symbols, DEPTH);
        if (win(symbols))
        {
            print_map(fields_count, symbols, field_size);
            cout << "Wygral bot!" << endl;
            break;
        }
        else if (tie(symbols))
        {
            print_map(fields_count, symbols, field_size);
            cout << "Remis!";
            break;
        }
    }
}

