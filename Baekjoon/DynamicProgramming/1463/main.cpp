#include <iostream>
#include <deque>

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
            cerr << "Input number (" << num_in << ") is out of range!" << endl;
        }
        
        _count_operated = 0;
    }
    ~finder() { }
    int find();
    int get_count();
};

int finder::find()
{
    int result;
    
    return result;
}

int finder::get_count()
{
    return _count_operated;
}

int main(int argc, char const *argv[])
{
    finder a(10);
    a.find();
    cout << a.get_count() << endl;
    return 0;
}
