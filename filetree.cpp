
#include <iostream>
#include <filesystem>
using namespace std;

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

    for (auto &entry : filesystem::directory_iterator(root))
    {
        cout << entry.path().filename() << endl;
    }

        return 0;
}