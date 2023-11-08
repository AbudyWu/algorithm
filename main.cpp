#include <iostream>
#include <cstdlib>
#include <fstream>
#include <cstring>
#include <vector>

using namespace std;

// parser set
vector<vector<int>> load;

int findline(int f)
{
    int key = 0;
    for (size_t i = 0; i < load.size(); i++)
    {
        for (size_t j = 0; j < load[i].size(); j++)
        {
            if (f == load[i][j])
            {
                if (j == 0)
                {
                    key = load[i][1];
                    break;
                }
                else if (j == 1)
                {
                    key = load[i][0];
                    break;
                }
            }
        }
    }
    return key;
}

void mis(int numChord, vector<vector<int>> &m, vector<vector<int>> &checkcase)
{
    int i, j, k, diff;
    for (diff = 1; diff < numChord; ++diff)
    {
        i = 0;
        j = i + diff;
        while (j != numChord)
        {
            k = findline(j);
            // case1
            if (k < i || k > j)
            {
                m[i][j] = m[i][j - 1];
            }

            // case2: i<k<j
            else if (k > i && k < j)
            {
                // case2-1
                if (m[i][j - 1] >= (m[i][k - 1] + m[k + 1][j - 1] + 1))
                {
                    m[i][j] = m[i][j - 1];
                }
                // case2-2
                else
                {
                    m[i][j] = m[i][k - 1] + m[k + 1][j - 1] + 1;
                    checkcase[i][j] = 2;
                }
            }

            else if (k == i)
            {
                if (diff == 1)
                {
                    m[i][j] = 1;
                    checkcase[i][j] = 3;
                }

                else
                {
                    m[i][j] = m[i + 1][j - 1] + 1;
                    checkcase[i][j] = 3;
                }
            }

            i++;
            j++;
        }
    }
}

void findChord(int i, int j, vector<vector<int>> &checkCase, vector<vector<int>> &line)
{
    while (j - i > 1)
    {
        if (checkCase[i][j] == 2)
        {
            int k = findline(j);
            line.push_back({k, j});
            findChord(k, j - 1, checkCase, line);
            j = k - 1;
        }
        else if (checkCase[i][j] == 3)
        {
            int k = findline(j);
            line.push_back({k, j});
            findChord(i + 1, j - 1, checkCase, line);
            j = i - 1;
        }
        else
        {
            j--;
        }
    }
}

int main(int argc, char **argv)
{
    char buffer[100];

    if (argc != 3)
    {
        cout << "Usage: ./[exe] [input file] [output file]" << endl;
        exit(1);
    }

    // open the input file
    fstream fin;
    fin.open(argv[1], fstream::in);
    if (!fin.is_open())
    {
        cout << "Error: the input file is not opened!!" << endl;
        exit(1);
    }

    // load point num
    fin >> buffer;
    int numChord = atoi(buffer);
    cout << "#Chords:" << numChord << endl;

    // MIS store
    vector<vector<int>> mis_store;
    mis_store.resize(numChord);
    for (size_t i = 0; i < numChord; ++i)
    {
        mis_store[i].resize(numChord);
    }

    // check
    vector<vector<int>> check;
    check.resize(numChord);
    for (size_t i = 0; i < numChord; ++i)
    {
        check[i].resize(numChord);
    }

    // line
    vector<vector<int>> line;

    for (int i = 0; i < numChord / 2; ++i)
    {
        int n1, n2;
        while (fin >> n1 >> n2)
        {
            if (n1 < n2)
            {
                load.push_back({n1, n2});
                // cout << "Chord(" << n1 << "," << n2 << ")" << endl;
            }
            else
            {
                load.push_back({n2, n1});
                // cout << "Chord(" << n2 << "," << n1 << ")" << endl;
            }
        }
    }

    mis(numChord, mis_store, check);
    findChord(0, numChord - 1, check, line);

    // open the output file
    fstream fout;
    fout.open(argv[2], fstream::out);
    if (!fout.is_open())
    {
        cout << "Error: the output file is not opened!!" << endl;
        exit(1);
    }

    cout << "ans : " << mis_store[0][numChord - 1] << endl;

    for (size_t i = 0; i < mis_store[0][numChord - 1]; i++)
    {
        for (size_t j = 0; j < 2; j++)
        {
            cout << line[i][j] << " ";
        }
        cout << endl;
    }

    // // print mis stage
    // for (int i = 0; i < mis_store.size(); ++i)
    // {
    //     for (int j = 0; j < mis_store[i].size(); ++j)
    //     {
    //         fout << mis_store[i][j] << " ";
    //     }
    //     fout << endl;
    // }

    return 0;
}
