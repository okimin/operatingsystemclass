#include <iostream>
#include <thread>
#include <vector>
#include <iterator>
#include <fstream>
#include <algorithm>
#include <mutex>

using namespace std;

mutex mtx;

void mergeFile(vector<int> source, vector<int> &destination, int thr)
{

    for (size_t i = 0; i < source.size(); i++)
    {
        mtx.lock();
        if (source.at(i) > destination.at(destination.size() - 1))
        {
            destination.push_back(source.at(i));
        }
        else
        {
            for (size_t j = 0; j < destination.size(); j++)
            {
                if (source.at(i) <= destination.at(j))
                {
                    destination.insert(destination.begin() + j, source.at(i));
                    break;
                }
            }
        }
        if (i == (source.size() - 1))
            cout << "Thread " << thr << " done. Main data currently has " << destination.size() << " numbers in it." << endl;

        mtx.unlock();
    }
}

int main(int argc, char *argv[])
{

    ifstream is(argv[1]);
    istream_iterator<int> start(is), end;
    vector<int> data(start, end);
    cout << "Main data has  " << data.size() << " numbers" << endl;

    ifstream nD1(argv[2]);
    istream_iterator<int> start1(nD1), end1;
    vector<int> newdata1(start1, end1);

    ifstream nD2(argv[3]);
    istream_iterator<int> start2(nD2), end2;
    vector<int> newdata2(start2, end2);

    ifstream nD3(argv[4]);
    istream_iterator<int> start3(nD3), end3;
    vector<int> newdata3(start3, end3);

    cout << "numbers read in:\n";
    copy(data.begin(), data.end(),
         ostream_iterator<int>(cout, " "));
    cout << endl;

    cout << "Threads 1 and 2 and 3 "
            "operating independently"
         << endl;

    thread th1(mergeFile, newdata1, ref(data), 1);

    thread th2(mergeFile, newdata2, ref(data), 2);

    thread th3(mergeFile, newdata3, ref(data), 3);

    // Wait for the threads to finish
    // Wait for thread t1 to finish
    th1.join();

    // Wait for thread t2 to finish
    th2.join();

    // Wait for thread t3 to finish
    th3.join();

    cout << "Main data now has " << data.size() << " numbers" << endl;

    /*
    cout << "numbers read in:\n";
    copy(data.begin(), data.end(),
         ostream_iterator<int>(cout, "\n"));
    cout << endl;
     */

    cout << "The full list can be found on answer.txt" << endl;

    ofstream output_file("./answer.txt");
    ostream_iterator<int> output_iterator(output_file, "\n");
    std::copy(data.begin(), data.end(), output_iterator);

    return 0;
}
