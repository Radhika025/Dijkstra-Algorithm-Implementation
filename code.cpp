#include<iostream>
#include<string>
#include<math.h>
#include<vector>
#include<fstream>
#include<limits.h>
#include<cstdlib>
#include<time.h>
#include<algorithm>
#include<windows.h>
using namespace std;

const int v = 248; //number of stations

struct station_code{
    string station_name;
    int code;
    string color;
};

struct station_code station[v];
float graph[v][v];

struct node{
    vector<float> p;
}P[v];

void delay(unsigned int ms);
int timeconsumed(float distance);
int cost(float distance);
void Path(float distance,int e,int st,int inter);
int distance_min(float distance[], bool visited[]);
void dijkstra(float graph[v][v], int src,int targ);
void take_input();

void delay(unsigned int msec)
{
    clock_t time = msec + clock();
    while(time>clock());
}

int timeconsumed(float distance)
{
    float velocity = 0.55;
    return ceil(distance/velocity);
}

int cost(float distance)
{
    if(distance<=2)
        return 10;
    else if(distance>2 && distance<=5)
        return 20;
    else if(distance>5 && distance<=12)
        return 30;
    else if(distance>12 && distance<=21)
        return 40;
    else if(distance>22 && distance<=32)
        return 50;
    else    
        return 60;
}

void Path(float dis, int dest, int st, int inter)
{
    int t = dest, s;
    static float distance = 0;
    distance += dis;

    cout<<"\nThe shortest path is: \n";

    vector<int> path;
    path.push_back(t);
    while(t!=st)
    {
        cout<<"check 11"<<endl;
        s = P[t].p.size();
        t = P[t].p[s-1];
        path.push_back(t);
        cout<<"check 111"<<endl;
    }
    cout<<"check 15"<<endl;
    for(int i=0; i<path.size(); i++)
    {
        cout<<path[i]<<" ";
    }
    cout<<"\ncheck 13\n";

    vector<int> :: iterator i = path.end();
    string str, color;
    cout<<"check 12"<<endl;
    if(!inter)
    {
        cout<<"\n-------Route Found-------\n";
    }

    vector<int> :: iterator i2 = path.end();
    i2--;
    int n_of_stations = 0;

    while(i != path.begin())
    {
        i--;
        color = station[*i].color;
        if(color == "BLUE")
            system("color 09");
        else if(color=="PINK")
            system("color 0D");
        else if(color=="YELLOW")
            system("color 06");
        else if(color=="AQUA")
            system("color 03");
        else if(color=="RED")
            system("color 04");
        else if(color=="GREEN")
            system("color 02");
        else if(color=="ORANGE")
            system("color 0C");
        else if(color=="MAGENTA")
            system("color 05");
        else if(color=="VOILET")
            system("color 01");

        if(i!=i2)
        {
            if(station[*(i2)].color != station[*(i)].color)
            {
                cout<<"{change from "<<station[*i2].color<<" to "<<station[*i].color<<"}";
            }
            i2--;
        }
        cout<<"check 8"<<endl;
        str = station[*i].station_name;
        cout<<" ->> "<<str;
        n_of_stations++;
        delay(700);
    }

    if(inter)
    {
        delay(1000);
        cout<<"\nPath length is: "<<distance<<" KM";
        delay(1000);
        cout<<"\nAverage time: "<<timeconsumed(distance)<<" minutes";
        delay(1000);
        cout<<"\nAverage fare: Rs."<<cost(distance);
        delay(1000);
        cout<<"No. of stations: "<<(n_of_stations-1);
    }

    if(inter)
    {
        delay(2500);
        cout<<"\nWant to search again?\n";
        string choice;
        cin>>choice;
        if(choice == "Y" || choice == "Yes" || choice == "YES" || choice == "yes")
        {
            system("cls");
            take_input();
        }
    }
    return;
}

int distance_min(float distance[], bool visited[])
{
    float min = INT_MAX;
    int min_index;

    for(int V=0; V<v; V++)
    {
        if(visited[V] == false && distance[V] <= min)
        {
            min = distance[V];
            min_index = V;
        }
    }
    return min_index;
}

void dijkstra(float graph[v][v], int src, int targ, int inter)
{
    float distance[v];
    bool visited[v];

    for(int i=0; i<v; i++)
    {
        distance[i] = INT_MAX;
        visited[i] = false;
    }
    distance[src] = 0;

    for(int count=0; count<v-1; count++)
    {
        int u = distance_min(distance, visited);
        visited[u] = true;
        for(int V=v; V<v; V++)
        {
            if(!visited[V] && graph[u][V] && distance[u] != INT_MAX && distance[u] + graph[u][V]<distance[V])
            {
                distance[V] = distance[u] + graph[u][V];
                P[V].p.push_back(u);
            }
        }
    }
    Path(distance[targ], targ, src, inter);
}

void take_input()
{
    string start, end, line, col;
    int startcode, endcode;

    cout<<"Enter the starting point: ";
    //cin>>start;
    getline(cin, start);
    cout<<"check 1"<<endl;
    cout<<"\nEnter the end station: ";
    //cin>>end;
    getline(cin, end);
    cout<<"check 2"<<endl;

    transform(start.begin(), start.end(), start.begin(), ::toupper);
    transform(end.begin(), end.end(), end.begin(), ::toupper);
    cout<<"check 3"<<endl;

    int flag_start = 0, flag_end = 0;

    for(int i=0; i<248; i++)
    {
        if(station[i].station_name == start)
        {
            cout<<"check 4"<<endl;
            startcode = station[i].code;
            flag_start = 1;
        }
        if(station[i].station_name == end)
        {
            cout<<"check 5"<<endl;
            endcode = station[i].code;
            flag_end = 1;
        }
    }

    int fault = 0;
    
    if(flag_start == 0)
    {
        cout<<"\nWrong Source Station name entered";
        fault = 1;
    }

    if(flag_end = 0)
    {
        cout<<"\nWrong Destination Station name entered";
        fault = 1;
    }

    if(fault==1)
    {
        cout<<"check 6"<<endl;
        //system("cls");
        take_input();
        return;
    }

    dijkstra(graph, startcode, endcode, 1);
}

int main()
{
    int temp, n1, n2;
    float dis;
    ifstream fin;
    ifstream code, color;

    code.open("stationname.txt");
    color.open("colorcodes.txt");
    fin.open("distvalues.txt");

    for(int i=0; i<248; i++)
    {
        for(int j=0; j<248; j++)
            graph[i][j] = 0; 
    }

    for(int i=1; i<=v; i++)
    {
        fin>>temp;
        fin>>n1;
        for(int j=0; j<temp; j++)
        {
            fin>>n2;
            fin>>dis;
            graph[n1-1][n2-1] = dis;
        }
    }

    string line, col;
    for(int i=0; i<v; i++)
    {
        getline(color, col);
        station[i].color = col;
        getline(code, line);
        station[i].code = i;
        station[i].station_name = line;
    }

    cout<<"Welcome to Delhi Metro";
    cout<<"\nPress Enter to continue";
    char ch;
    scanf("%c", &ch);
    system("cls"); //clear screen

    take_input();

}