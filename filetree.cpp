#define BOLDBLACK "\033[1m\033[30m"   /* Bold Black */
#define BOLDRED "\033[1m\033[31m"     /* Bold Red */
#define BOLDGREEN "\033[1m\033[32m"   /* Bold Green */
#define BOLDYELLOW "\033[1m\033[33m"  /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"    /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m" /* Bold Magenta */
#define BOLDCYAN "\033[1m\033[36m"    /* Bold Cyan */
#define BOLDWHITE "\033[1m\033[37m"   /* Bold White */
#define RESET "\033[0m"
#define BLACK "\033[30m"   /* Black */
#define RED "\033[31m"     /* Red */
#define GREEN "\033[32m"   /* Green */
#define YELLOW "\033[33m"  /* Yellow */
#define BLUE "\033[34m"    /* Blue */
#define MAGENTA "\033[35m" /* Magenta */
#define CYAN "\033[36m"    /* Cyan */
#define WHITE "\033[37m"   /* White */

#include <iostream>
#include <filesystem>
using namespace std;

bool last(string name, string ext)
{
    if (name.size() >= ext.size())
    {

        return name.compare(name.size() - ext.size(), ext.size(), ext) == 0;
    }
    return true;
}

void print_file_tree(const filesystem::path &path, string prefix = "")
{
    vector<filesystem::directory_entry> entries;

    for (auto it = filesystem::directory_iterator(path); it != filesystem::directory_iterator(); it++)
    {
        auto name = it->path().filename().string();
        int lastfile = 0;

        if (next(it) == filesystem::directory_iterator())
        {
            lastfile = 1;
        }

        string symbol1;
        if (lastfile == 1)
        {
            symbol1 = "L__ ";
        }
        else
        {
            symbol1 = "|--";
        }

        string start;
        if (lastfile == 1)
        {
            start = prefix;
        }
        else
        {
            start = prefix + "| ";
        }
        string colour;
        if (it->is_directory())
        {
            colour = BOLDBLUE;
        }
        else if (last(name, ".exe"))
        {
            colour = BOLDYELLOW;
        }
        else if (last(name, ".txt"))
        {
            colour = MAGENTA;
        }

        cout << prefix << symbol1 << colour << name << RESET << endl;

        if (it->is_directory())
        {
            print_file_tree(it->path(), start);
        }
    }
}
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Please provide a path to the directory";
        return 1;
    }
    cout << "Path: " << argv[1] << endl;

    filesystem::path root(argv[1]);

    if (filesystem::exists(root) != true)
    {
        cout << "Path doesn't exist" << endl;
        return 1;
    }

    // for (auto &entry : filesystem::recursive_directory_iterator(root))
    // {
    //     // cout << GREEN << "[DIR] " << RESET << entry.path().filename().string() << endl;
    // }

    cout << root.filename() << "/" << endl;
    print_file_tree(root);
    return 0;
}
