#include <iostream>
#include <conio.h>
#include <fstream>
#include <cstring>
#include <vector>
#include <algorithm>
#include "quotaAvl.h"
#include "enrAvl.h"
#include "enrHeap.h"
using namespace std;

struct student_Status
{
    int rut;
    char verDig;
    vector<int> nrc;
};

int strisDig(string str)
{
    int dig = 1;
    for (int i = 0; i < str.length(); i++)
    {
        if (!isdigit(str[i]))
        {
            dig = 0;
        }
    }
    return dig;
}

int searchStatus(student_Status *arr, string rut, int pos, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i].rut == stoi(rut.substr(0, pos)))
        {
            rut.erase(0, pos + 1);
            if (arr[i].verDig == rut[0])
            {
                return 1;
            }
        }
    }
    return 0;
}

int searchNRC(vector<int> nrc, int val)
{
    for (int i = 0; i < nrc.size(); i++)
    {
        if (nrc[i] == val)
        {
            return 1;
        }
    }
    return 0;
}

int deleteStudent(int rut, quotaAVL *quoataavl, student_Status *arr, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (arr[i].rut == rut)
        {
            arr[i].rut = -1;
            for (int j = 0; j < arr[i].nrc.size(); j++)
            {
                quoataavl->updateQuota(arr[i].nrc[j], 1);
            }
            arr[i].nrc.clear();
            return 1;
        }
    }
    return 0;
}

void processReg(enrAVLNode *node, student_Status *arr, int size)
{
    if (node != NULL)
    {
        for (int i = 0; i < size; i++)
        {
            if (arr[i].rut == node->getInfo())
            {
                vector<int> temp = node->getNRC();
                for (int j = 0; j < temp.size(); j++)
                {
                    if (!searchNRC(arr[i].nrc, temp[j]))
                    {
                        arr[i].nrc.push_back(temp[j]);
                    }
                }
            }
        }
    }
}

int main()
{
    quotaAVL avl;//avl tree to store quota details
    enrAVL enravl;//avl tree to store enrollment attempts details
    MinHeap<int> mh1;//min heap to store time of an attempt made

    //code to store quotas into the avl tree
    string temp = "";
    ifstream quotafile("C:\\Users\\Abdul Ahad\\Desktop\\test\\quotas.txt");
    while (quotafile.good())
    {
        size_t pos = 0;
        string word;
        AVLNode *searchedNode;
        getline(quotafile, temp);
        // cout << temp << endl;
        while ((pos = temp.find(",")) != std::string::npos)
        {
            word = temp.substr(0, pos); // store the substring
            // cout << word << endl;
            searchedNode = avl.search(stoi(word));
            temp.erase(0, pos + 1); /* erase() function store the current positon and move to next token. */
            if (searchedNode == NULL && stoi(word) > 0 && stoi(temp) >= 0)
            {
                avl.insert(stoi(word), stoi(temp));
            }
        }
        // cout << temp << endl; // it print last token of the string.
    }
    quotafile.close();

    // avl.inorder(avl.root);
    // if(avl.updateQuota(21212,-1)){
    //     cout<<"value updated";
    // }
    // else{
    //     cout<<"cannot update";
    // }
    // avl.inorder(avl.root);

    //code to get the number of records in student status file
    int statusSize = 0;
    ifstream statusfile("C:\\Users\\Abdul Ahad\\Desktop\\test\\student_enrollment_status.txt");
    while (statusfile.good())
    {
        string temp;
        getline(statusfile, temp);
        statusSize++;
    }
    statusfile.close();

    //code to store the details of student status in an array of struct
    student_Status *studentStatus = new student_Status[statusSize];
    statusfile.open("C:\\Users\\Abdul Ahad\\Desktop\\test\\student_enrollment_status.txt");
    size_t pos = 0;
    string word;

    for (int i = 0; i < statusSize; i++)
    {
        getline(statusfile, temp);
        pos = temp.find(",");
        word = temp.substr(0, pos); // store the substring
        temp.erase(0, pos + 1);     /* erase() function store the current positon and move to next token. */
        pos = word.find("-");
        if (strisDig(word.substr(0, pos)) && !searchStatus(studentStatus, word, pos, i))
        {
            studentStatus[i].rut = stoi(word.substr(0, pos));
            word.erase(0, pos + 1);
            studentStatus[i].verDig = word[0];
        }
        else
        {
            continue;
        }
        // cout << temp << endl;

        while ((pos = temp.find(",")) != std::string::npos)
        {
            word = temp.substr(0, pos); // store the substring
            // cout << word << endl;
            if (!searchNRC(studentStatus[i].nrc, stoi(word)) && avl.search(stoi(word)))
            {
                studentStatus[i].nrc.push_back(stoi(word));
            }
            temp.erase(0, pos + 1); /* erase() function store the current positon and move to next token. */
        }
        if (!searchNRC(studentStatus[i].nrc, stoi(temp)) && avl.search(stoi(temp)))
        {
            studentStatus[i].nrc.push_back(stoi(temp));
        }
    }
    statusfile.close();
    // for (int i = 0; i < statusSize; i++)
    // {
    //     cout << studentStatus[i].rut << "-" << studentStatus[i].verDig << " ";
    //     for (int j = 0; j < studentStatus[i].nrc.size(); j++)
    //     {
    //         cout << studentStatus[i].nrc[j] << " ";
    //     }
    //     cout << endl;
    // }

    //code to store the details of attempts in avl and heap
    ifstream attemptfile("C:\\Users\\Abdul Ahad\\Desktop\\test\\enrollment_attempts.txt");
    while (attemptfile.good())
    {
        size_t pos = 0;
        string word;
        // AVLNode *searchedNode;
        enrAVLNode *searchedNode;
        getline(attemptfile, temp);
        // cout << temp << endl;
        pos = temp.find(",");
        word = temp.substr(0, pos); // store the substring
        // cout << word << endl;
        temp.erase(0, pos + 1); /* erase() function store the current positon and move to next token. */
        pos = word.find("-");
        int info;
        searchedNode = enravl.search(stoi(word.substr(0, pos)));
        info = stoi(word.substr(0, pos));
        if (searchedNode == NULL && searchStatus(studentStatus, word, pos, statusSize))
        {

            enravl.insert(info, word[word.length()]);
        }
        else
        {
            // if RUT already exists then to consider the later NRC's
            if (searchedNode != NULL)
            {
                pos = temp.find(",");
                temp.erase(0, pos + 1);
                enravl.clearNRC(info);
                while ((pos = temp.find(",")) != std::string::npos)
                {
                    word = temp.substr(0, pos); // store the substring
                    // cout << word << endl;
                    temp.erase(0, pos + 1);
                    enravl.addNRC(info, stoi(word));
                }
                enravl.addNRC(info, stoi(temp));
            }
            continue;
        }
        //storing time in both avl and heap
        pos = temp.find(",");
        word = temp.substr(0, pos);
        temp.erase(0, pos + 1);
        mh1.add(stoi(word));
        enravl.setTime(info, stoi(word));

        while ((pos = temp.find(",")) != std::string::npos)
        {
            word = temp.substr(0, pos); // store the substring
            // cout << word << endl;
            temp.erase(0, pos + 1);
            enravl.addNRC(info, stoi(word));
        }
        enravl.addNRC(info, stoi(temp));
        // cout << temp << endl; // it print last token of the string.
    }
    attemptfile.close();
    // cout << mh1.get_min();
    // avl.inorder(avl.root);
    // enravl.inorder(enravl.root);
    // for (int i = 0; i < statusSize; i++)
    // {

    //     if (studentStatus[i].rut != -1)
    //     {
    //         cout << studentStatus[i].rut << "-" << studentStatus[i].verDig << " ";
    //         for (int j = 0; j < studentStatus[i].nrc.size(); j++)
    //         {
    //             cout << studentStatus[i].nrc[j] << " ";
    //         }
    //         cout << endl;
    //     }
    // }


    //main menu
    int loop = 1;
    while (loop)
    {
        int input;
        cout << "\n1. Display subjects without quotas\n"
             << "2. Add quotas to subject\n"
             << "3. Delete student\n"
             << "4. Process registration of the day\n"
             << "5. Quit\n";
        cout << "Select one of (1-5) :";
        cin >> input;
        string fileline="";
        ofstream writestatus("C:\\Users\\Abdul Ahad\\Desktop\\test\\student_enrollment_status.txt");
        ofstream writequotas("C:\\Users\\Abdul Ahad\\Desktop\\test\\quotas.txt");
        switch (input)
        {
        case 1://diplay subjects without quota
            cout << "\nSubjects unavailable for registration :";
            avl.inorder(avl.root);
            cout << endl;
            break;
        case 2://adding quota
            int tempinfo, tempnum;
            cout << "\nEnter the subject NRC :";
            cin >> tempinfo;
            cout << "\nEnter number of quotas :";
            cin >> tempnum;
            if (tempnum <= 0)
            {
                cout << "\nGiven quota cannot be added....";
                break;
            }
            // if already in the system then update else add
            if (!avl.updateQuota(tempinfo, tempnum))
            {
                avl.insert(tempinfo, tempnum);
            }
            cout << "\nQuota added successfully";
            break;
        case 3://delete a student
            int temprut;
            cout << "\nEnter the student RUT without verification digit :";
            cin >> temprut;
            if (deleteStudent(temprut, &avl, studentStatus, statusSize))
            {
                cout << "\nStudent deleted successfully...";
            }
            else
            {
                cout << "\nStudent record doesn't exist...";
            }
            break;
        case 4://processing registration of the day
            while (mh1.get_min() != -1)
            {
                processReg(enravl.searchTime(mh1.get_min()), studentStatus, statusSize);
                mh1.rem_min();
            }
            break;
        case 5://storing the processed data in the files and freeing memory
            for (int i = 0; i < statusSize; i++)
            {

                if (studentStatus[i].rut != -1)
                {
                    fileline += to_string(studentStatus[i].rut) + "-" + studentStatus[i].verDig ;
                    for (int j = 0; j < studentStatus[i].nrc.size(); j++)
                    {
                        fileline+=","+ to_string(studentStatus[i].nrc[j]);
                    }
                    fileline+="\n";
                }
            }
            writestatus<<fileline;
            writequotas<<avl.writeTofile(avl.root);
            writestatus.close();
            writequotas.close();
            free(studentStatus);
            loop = 0;
            break;
        default:
            break;
        }
    }

    // avl.inorder(avl.root);
    return 1;
}