#include "Utility.h"
#include "Node.h"

bool tie(vector<vector<char>>& v)
{
    for (auto & i : v)
    {
        for (auto & j : i)
        {
            if (j == ' ')
            {
                return false;
            }
        }
    }
    return true;
}

void get_input(const string& text, size_t& input)
{
    while (true)
    {
        cout << text;
        cin >> input;
        if (!cin.fail() && input != 0)
        {
            break;
        }
        //
        CLEAR_CIN
    }
}

void print_map(const size_t size, const vector<vector<char>>& vec, const size_t field_size)
{
    for (int l = 0; l < size; l++)
    {
        for (int k = 0; k < field_size; k++)
        {
            for (int i = 0; i < size; i++)
            {
                for (int j = 0; j < field_size; j++)
                {
                    if (j == (field_size%2 == 0 ? field_size/2-1 : field_size/2)
                        && k == (field_size%2 == 0 ? field_size/2-1 : field_size/2))
                    {
                        cout << vec.at(l).at(i);
                    }
                    else
                    {
                        cout << ' ';
                    }
                }
                if (i+1 != size)
                {
                    cout << '|';
                }
            }
            cout << endl;
        }
        if (l+1 != size)
        {
            print_line(size, field_size);
        }
    }
}

void fill_vector(vector<vector<char>>& vec, const size_t size, const char fill)
{
    for (int i = 0; i < size; i++)
    {
        vector<char> v1;
        v1.reserve(size);
        for (int j = 0; j < size; j++)
        {
            v1.push_back(fill);
        }
        vec.push_back(v1);
    }
}

void print_line(const size_t size, const size_t field_size)
{
    for (int i = 0; i < (size*field_size) + size-1; i++)
    {
        cout << '-';
    }
    cout << endl;
}
//opis ruchu bota
void bot(const char sign, vector<vector<char>>& initial_state, const unsigned int depth)
{
    Node::computer = sign;
    Node::max_depth = depth;
    //informacja o poziomie drzewa
    //sign-gracz czy komputer
    Node root(initial_state, 1, sign);

    vector<Node*> all_nodes;
    Node::getAdresses(all_nodes, &root);
//
    for (unsigned int i = Node::depth-1; i > 1; i--)
    {
        //
        bool first = true;
        int alphaBeta;
        for (auto & node : all_nodes)
        {
            if (node->getLevel() == i)
            {
                node->calculateValue(alphaBeta, first);
                if (first)
                {
                    first = false;
                    alphaBeta = node->getValue();
                }
            }
        }
    }

    Node max = root.getChildren().at(0);
    for (int i = 1; i < root.getChildren().size(); i++)
    {
        if (root.getChildren().at(i).getValue() > max.getValue())
        {
            max = root.getChildren().at(i);
        }
    }

    initial_state = max.getState();
}
//win przelatuje po wszystkich polach i sprawdza czy nastapila ktoras z kombinacji wygranych
bool win(const vector<vector<char>>& symbols)
{
    const size_t size = symbols.size();
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            if (symbols.at(i).at(j) == ' ')
            {
                continue;
            }
            //sprawdza polaczenia miedzy symbolami
            //wszystkie mozliwosci wygranych
            const Point origin(j, i);
            if (check_connection(symbols, origin, Point(j-2, i-2), Point(j-1, i-1), i-2 >= 0 && j-2 >= 0) ||
                check_connection(symbols, origin, Point(j-2, i), Point(j-1, i), j-2 >= 0) ||
                check_connection(symbols, origin, Point(j-2, i+2), Point(j-1, i+1), j-2 >= 0 && i+2 < size) ||
                check_connection(symbols, origin, Point(j-1, i-1), Point(j+1, i+1), j-1 >= 0 && i-1 >= 0 && j+1 < size && i+1 < size) ||
                check_connection(symbols, origin, Point(j-1, i), Point(j+1, i), j-1 >= 0 && j+1 < size) ||
                check_connection(symbols, origin, Point(j-1, i+1), Point(j+1, i-1), j-1 >= 0 && i-1 >= 0 && j+1 < size && i+1 < size) ||
                check_connection(symbols, origin, Point(j, i-1), Point(j, i-2), i-2 >= 0) ||
                check_connection(symbols, origin, Point(j+1, i-1), Point(j+2, i-2), i-2 >= 0 && j+2 < size) ||
                check_connection(symbols, origin, Point(j+1, i), Point(j+2, i), j+2 < size) ||
                check_connection(symbols, origin, Point(j+1, i+1), Point(j+2, i+2), i+2 < size && j+2 < size) ||
                check_connection(symbols, origin, Point(j, i+1), Point(j ,i+2), i+2 < size))
            {
                return true;
            }
        }
    }
    return false;
}

bool check_connection(const vector<vector<char>>& symbols, const Point& p0, const Point& p1, const Point& p2,
                      const bool& condition)
{
    return condition && symbols.at(p0.getY()).at(p0.getX()) == symbols.at(p1.getY()).at(p1.getX()) &&
           symbols.at(p0.getY()).at(p0.getX()) == symbols.at(p2.getY()).at(p2.getX());
}


