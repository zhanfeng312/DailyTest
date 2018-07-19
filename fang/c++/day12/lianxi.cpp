#include <iostream>
#include <cstdio>
#include <vector>
#include <fstream>
#include <algorithm>
using namespace std;
class Movie{
    public:
        //输入流
        friend istream& operator >> (istream& is,
                Movie& movie){
            return is >> movie.m_title >> movie.m_comp
                >> movie.m_gross;
        }
        //输出流
        friend ostream& operator<< (ostream& os,
                const Movie& movie){
            return os << movie.m_title << ' '
                << movie.m_comp << ' '<<movie.m_gross;
        }
        bool operator < (const Movie& movie) const{
            return gross() > movie.gross();
        }
    private:
        double gross(void) const {
            string str(m_gross);
            size_t pos = 0;
            while ((pos = str.find_first_of ("$,", pos)) != 
                    string::npos)
                str.erase(pos, 1);
            return atof(str.c_str());//字符串转换为浮点数
        }
        string m_title;
        string m_comp;
        string m_gross;
};
bool read(const char* file, vector<Movie>& vm){
    ifstream ifs(file);
    if (! ifs){
        perror("打开票房文件失败!");
        return false;
    }
    Movie movie;
    while (ifs >> movie)
        vm.push_back(movie);
    ifs.close();
    return true;
}
bool write(const char*file, vector<Movie>& vm){
    ofstream ofs(file);
    if (! ofs){
        perror("打开文件失败");
        return false;
    }
    for (vector<Movie>::const_iterator it = vm.begin();
            it != vm.end(); ++it)
        ofs << *it << endl;
    ofs.close();
    return true;
}
int main(int argc, char *argv[]){
    if (argc < 3){
        fprintf(stderr, "%s<票房文件><排行文件>\n", argv[0]);
        return -1;
    }
    vector<Movie> vm;
    if (! read(argv[1], vm))
        return -1;
    sort(vm.begin(), vm.end());
    if (vm.size() > 5)
        vm.resize(5);
    if (! write(argv[2], vm))
        return -1;
    return 0;
}
