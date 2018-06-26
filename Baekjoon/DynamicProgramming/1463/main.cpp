#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class finder
{
private:
    const unsigned int _num_input;
    int _count_operated;
public:
    finder *next[3];
public:
    finder(const int num_in) : _num_input(num_in)
    {
        if (num_in < 1 && num_in > 1000000) {
            cout << "Input number (" << num_in << ") is out of range!" << endl;
        }
        
        _count_operated = 0;
    }
    ~finder() { }
    void cal();
    int get_count();
};

void finder::cal()
{
    _count_operated = 0;

    vector<int> list_searched;
    list_searched.push_back(1);

    int ii_start = 0;
    int ii_last = 1;
    bool is_found = false;

    while(ii_start < list_searched.size()){
        int size_of_level = 0;
                
        for(int ii = ii_start; ii < ii_last; ii++)
        {
            if (list_searched[ii] == _num_input)
            {
                is_found = true;
                break;
            }
            else
            {
                int value = list_searched[ii] + 1;
                auto it = find(list_searched.begin(), list_searched.end(), value);
                if (it == list_searched.end() && value <= _num_input)
                {
                    list_searched.push_back(value);
                    size_of_level++;
                }
                value = list_searched[ii] * 2;
                it = find(list_searched.begin(), list_searched.end(), value);
                if (it == list_searched.end() && value <= _num_input)
                {
                    list_searched.push_back(value);
                    size_of_level++;
                }
                value = list_searched[ii] * 3;
                it = find(list_searched.begin(), list_searched.end(), value);
                if (it == list_searched.end() && value <= _num_input)
                {
                    list_searched.push_back(value);
                    size_of_level++;
                }
            }
        }

        if (is_found)
        {
            break;
        }
        else
        {
            ii_start = ii_last;
            ii_last += size_of_level;
            _count_operated++;
        }
    }
}

int finder::get_count()
{
    return _count_operated;
}

int main(int argc, char const *argv[])
{
    int in;
    cin >> in;
    finder a(in);
    a.cal();
    cout << a.get_count() << endl;
    return 0;
}
