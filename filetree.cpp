#define BOLDYELLOW "\033[1m\033[33m" /* Bold Yellow */
#define BOLDBLUE "\033[1m\033[34m"   /* Bold Blue */
#define RESET "\033[0m"
#define MAGENTA "\033[35m" /* Magenta */
#include <iostream>
#include <vector>
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

    for (const auto &entry : filesystem::directory_iterator(path))
    {
        entries.push_back(entry);
    }

    for (long long i = 0; i < entries.size(); ++i)
    {
        auto &entry = entries[i];

        int lastfile = 0;
        string name = entry.path().filename().string();

        if (i == entries.size() - 1)
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
        if (entry.is_directory())
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

        if (entry.is_directory())
        {
            string folder_name = entry.path().filename().string();
            if (!folder_name.empty() && folder_name[0] != '.')
            {
                print_file_tree(entry.path(), start);
            }
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
