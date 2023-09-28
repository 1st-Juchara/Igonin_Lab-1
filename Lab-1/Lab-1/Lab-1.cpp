// Lab-1.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Pipe { 
    string name = "";
    float length = 0;
    float diameter = 0;
    bool inRepare = false;
};

struct CS {
    string name = "";
    vector <bool> WS;
    int payoff = 0;
};

float tryInputNum(float min, float max) {
    float num;
    cout << "\n\n> ";
    while ((cin >> num).fail() || (num < min) || (num > max)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n\n> ";
    }
    cout << endl;
    return num;
}

int tryChoose(int min, int max) {
    int num;
    cout << "\n\n> ";
    while ((cin >> num).fail() || (num < min) || (num > max)) {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "\n> ";
    }
    cout << endl;
    return num;
}

int Menu() {
    std::cout << "1. Add pipe \n2. Add CS \n3. Objects \n4. Edit pipe \n5. Edit CS \n6. Save \n7. Load \n8. Exit";
    int number = tryChoose(1, 8);
    return number;
}

void View(Pipe pipe, CS Stations) {
    if (pipe.length > 0){
        cout << "Pipe" << endl;
        cout << "\t\t" << "Name: " << pipe.name << endl;
        cout << "\t\t" << "Length: " << pipe.length << endl;
        cout << "\t\t" << "Diameter: " << pipe.diameter << endl;
        if (pipe.inRepare)
            cout << "\t\t" << "Status: IN REPAIR" << endl;
        else
            cout << "\t\t" << "Status: EXPLOITED \n" << endl;
    }
    if (Stations.WS.size() > 0) {
        cout << "Stations" << endl;
        cout << "\t\t" << "Name: " << Stations.name << endl;
        cout << "\t\t" << "Number of workshops: " << Stations.WS.size() << endl;
        cout << "\t\t" << "Payoff: " << Stations.payoff << endl;
        for (int j = 0; j < Stations.WS.size(); j++)
            if (Stations.WS[j])
                cout << "\t\t WS " << j + 1 << ". ON" << endl;
            else
                cout << "\t\t WS " << j + 1 << ". OFF" << endl;
    }
    cout << endl;
}

void addPipe(Pipe& pipe) {
    int t = 0;
    cout << "Enter pipe name:\n\n> ";
    string name;
    cin.ignore(10000, '\n');
    getline(cin, name);
    cout << endl;
    cout << "Enter pipe length:";
    float length = tryInputNum(0, INT_MAX);
    cout << "Enter pipe diameter: ";
    float diameter = tryInputNum(0, INT_MAX);
    pipe = { name, length, diameter };
}

void addCS(CS& Stations) {
    int t = 0;
    int wsOn = 0;
    std::cout << "Enter CS name:\n\n> ";
    string name;
    cin.ignore(10000, '\n');
    getline(cin, name);
    cout << endl;
    std::cout << "Enter count of workshops: ";
    int workshops = tryChoose(1, 10000);
    vector <bool> wsStatus;
    for (int i = 0; i < workshops; i++) {
        cout << i+1 << ". Workshop status: \n\t1. ON\n\t2. OFF";
        int status = tryChoose(1, 2);
        switch (status)
        {
        case 1:
            wsStatus.push_back(true);
            wsOn++;
            break;
        case 2:
            wsStatus.push_back(false);
            break;
        default:
            cout << "WRONG KEY";
            break;
        }
    }
    Stations = { name, wsStatus, wsOn / workshops * 100 };
}

void editPipe(Pipe& pipe) {
    if (pipe.length > 0) {
        cout << pipe.name << endl;
        cout << "\tPipe status:" << endl;
        cout << "\t\t1. UNDER REPAIR \n\t\t2. IS FUNCTIONING";
        int status = tryChoose(1, 2);
        if (status == 1)
            pipe.inRepare = true;
        else
            pipe.inRepare = false;
    }
}

void editCS(CS& Stations) { // Добавь возможность редактировать сразу несколько WS за раз
    if (Stations.WS.size() > 0)
    {
        cout << Stations.name << endl;
        cout << "\tPayoff: " << Stations.payoff << endl;
        cout << "\tWorkshops: " << Stations.payoff << endl;
        for (int i = 0; i < Stations.WS.size(); i++)
            if (Stations.WS[i])
                cout << "\t\t" << i + 1 << ". WS is ON" << endl;
            else
                cout << "\t\t" << i + 1 << ". WS is OFF" << endl;
        cout << endl;
        cout << "Number of WS for editing:";
        int WScount = tryChoose(1, Stations.WS.size());
        for (int i = 0; i < WScount; i++)
        {
            cout << "Enter index of WS for editing:";
            int WSindex = tryChoose(1, Stations.WS.size());
            Stations.WS[WSindex-1] = !Stations.WS[WSindex-1];
        }
    }
}

void Save(Pipe& pipe, CS& Stations) 
{
    ofstream fout("Saves.txt", ios_base::out | ios_base::trunc);// out - открыте для записи, trunc - удаление содержимого, ios_base - класс для всех потоковых классов ввода-вывода
    if (fout.is_open())
    {
        if ((pipe.length > 0) || (Stations.WS.size() > 0))
        {
            if (pipe.length > 0)
            {
                fout << 1;
                fout << pipe.name << endl;
                fout << pipe.length << ' ' << pipe.diameter << ' ' << pipe.inRepare << endl;
            }
            else
                fout << 0 << endl;
            if (Stations.WS.size() > 0)
            {
                if (Stations.WS.size() > 0)
                {
                    fout << 1;
                    fout << Stations.name << endl;
                    fout << Stations.payoff;
                    fout << ' ' << Stations.WS.size();
                    for (int i = 0; i < Stations.WS.size(); i++)
                    {
                        fout << ' ' << Stations.WS[i];
                    }
                    fout << endl;
                }
                else
                    fout << 0 << endl;

            }
            else
                fout << 0 << endl;
            fout.close();
            cout << "Save completed" << endl;
        }
        else
            cout << "Nothing to save" << endl;
        cout << endl;
    }
    else
        cout << "Error: save was failed";
}

void Load(Pipe& pipe, CS& Stations)
{
    ifstream fout("Saves.txt");
    if (fout.is_open())
    {
        int pipeCnt = 0;
        fout >> pipeCnt;
        if (pipeCnt > 0)
        {
            getline(fout, pipe.name);
            fout >> pipe.length;
            fout >> pipe.diameter;
            fout >> pipe.inRepare;
        }
        int StationsCnt = 0;
        fout >> StationsCnt;
        if (StationsCnt > 0)
        {
            getline(fout, Stations.name);
            fout >> Stations.payoff;
            int WScount = 0;
            fout >> WScount;
            Stations.WS.resize(WScount);
            for (int i = 0; i < WScount; i++)
            {
                bool ws = true;
                fout >> ws;
                Stations.WS[i] = ws;
            }
        }
        fout.close();
        cout << "Load completed" << endl;
    }
    else
        cout << "Error: can't find save file" << endl;
    cout << endl;
}

int main()
{
    Pipe pipe;
    pipe.length = 0;
    CS Stations;
    while (true) {
        int number = Menu();
        switch (number)
        {
        case 1:
            addPipe(pipe);
            break;
        case 2:
            addCS(Stations);
            break;
        case 3:
            View(pipe, Stations);
            break;
        case 4:
            editPipe(pipe);
            break;
        case 5:
            editCS(Stations);
            break;
        case 6:
            Save(pipe, Stations);
            break;
        case 7:
            Load(pipe, Stations);
            break;
        case 8:
            return 0;
            break;
        default:
            break;
        }
    };
    return 1;
}