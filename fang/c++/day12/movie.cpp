#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;
class Movie {
public:
    friend istream& operator>> (istream& is, 
            Movie& movie) {
        return is >> movie.m_title >> movie.m_comp
            >>movie.m_gross;
    }
    friend ostream& operator<< (ostream& os,
            const Movie& movie){
        return os << movie.m_title << ' '
            << movie.m_comp << ' ' << movie.m_gross;
    }
    bool operator< (const Movie& movie) const {
        return gross () > movie.gross ();
    }
private:
    double gross (void) const {
        string str (m_gross);
        size_t pos = 0;
        while ((pos = str.find_first_of ("$.", pos)) !=
                string::npos)
            str.erase (pos, 1);
        return atof (str.c_str ());
    }
    string m_title;
    string m_comp;
    string m_gross;
};
bool read (const char* file, vector<Movie>& vm) {
    ifstream ifs (file);
    if (! ifs){
        perror("打开票房文件失败");
        return false;
    }
    Movie movie;
    while(ifs >> movie)
        vm.push_back (movie);
    ifs.close ();
    return true;
}
bool write (const char* file, const vector<Movie>& vm) {
    ofstream ofs (file);
    if(! ofs){
        perror("打开排行文件失败");
        return false;
    }
    for(vector<Movie>::const_iterator it = vm.begin();
            it != vm.end(); ++it)
        ofs << *it << endl;
    ofs.close ();
    return true;
}
int main(int argc, char* argv[]) {
    if (argc < 3){
        cerr << "用法:" << argv[0]
            << "<票房文件><排行文件>" << endl;
        return -1;
    }
    vector<Movie> vm;
    if (! read(argv[1], vm))
        return -1;
    sort(vm.begin(), vm.end());
    if(vm.size() > 10)
        vm.resize(10);
    if (! write (argv[2], vm))
        return -1;
    return 0;

