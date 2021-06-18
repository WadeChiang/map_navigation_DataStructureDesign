#include "graph.h"

int index(int i, int j) {
    return 5 * i + j;
}

void initgraph(Loca *loc) {
    int x, i, j, p;
    for (i = 0; i < 8; i++)
    {
        if (i % 2 == 0)
        {
            for (j = 0; j < 5; j++)
            {
                x = index(i, j);
                loc[x].path_num = 0;
                if (i - 1 >= 0)
                    loc[x].path[loc[x].path_num++].to_loca = index(i - 1, j);
                if (j + 1 < 5)
                    loc[x].path[loc[x].path_num++].to_loca = index(i, j + 1);
                if (i + 1 < 8)
                    loc[x].path[loc[x].path_num++].to_loca = index(i + 1, j);
                if (j - 1 >= 0)
                    loc[x].path[loc[x].path_num++].to_loca = index(i, j - 1);
                if (i - 1 >= 0 && j + 1 < 5)
                    loc[x].path[loc[x].path_num++].to_loca = index(i - 1, j + 1);
                if (i + 1 < 8 && j + 1 < 5)
                    loc[x].path[loc[x].path_num++].to_loca = index(i + 1, j + 1);
            }
        }
        else
        {
            for (j = 0; j < 5; j++)
            {
                x = index(i, j);
                if (i - 1 >= 0)
                    loc[x].path[loc[x].path_num++].to_loca = index(i - 1, j);
                if (j + 1 < 5)
                    loc[x].path[loc[x].path_num++].to_loca = index(i, j + 1);
                if (i + 1 < 8)
                    loc[x].path[loc[x].path_num++].to_loca = index(i + 1, j);
                if (j - 1 >= 0)
                    loc[x].path[loc[x].path_num++].to_loca = index(i, j - 1);
                if (i - 1 >= 0 && j - 1 >= 0)
                    loc[x].path[loc[x].path_num++].to_loca = index(i - 1, j - 1);
                if (i + 1 < 8 && j - 1 >= 0)
                    loc[x].path[loc[x].path_num++].to_loca = index(i + 1, j - 1);
            }
        }
    }
    for (x = 0; x < LOCANUM; x++)
    {
        for (p = 0; p < loc[x].path_num; p++)
        {
            loc[x].path[p].crowding = (double) (rand() % 91) / 100 + 0.1;
        }
    }
}


void init_name_info(Loca *loc,int which) {
    string s_file;
    if(which==1)
    {
        s_file="./name_info.txt";
    }
    else if(which==2)
    {
        s_file="./name_info2.txt";
    }
    ifstream f1(s_file);

    int i, num;
    string s1;
    string s2;
    if (!f1)
    {
        lprint("Error opening name_info"+std::to_string(which)+".txt");

        exit(1);
    }
    else
    {
        lprint("Succeed in opening name_info"+std::to_string(which)+".txt");
    }
    f1 >> num;

    for (i = 0; i < num; i++)
    {
        f1 >> s1;
        loc[i].name = s1;
        f1 >> s2;
        loc[i].info = s2;
    }
    f1.close();
}

void init_distance(Loca *loc,int which) {
    string s_file;
    if(which==1)
    {
        s_file="./dis_cyc.txt";
    }
    else if(which==2)
    {
        s_file="./dis_cyc2.txt";
    }
    ifstream f1(s_file);
    if (!f1)
    {
        lprint("Error opening dis_cyc"+std::to_string(which)+".txt");
        exit(1);
    }
    else
    {
        lprint("Succeed in opening dis_cyc"+std::to_string(which)+".txt");
    }
    int i, j, num;
    f1 >> num;
    for (i = 0;i < num;i++)
    {
        //		cout << loc[i].path_num << endl;
        for (j = 0; j < loc[i].path_num; j++)
        {
            f1 >> loc[i].path[j].distance;
            //			cout << loc[i].path[j].distance << " ";
        }
        for (j = 0; j < loc[i].path_num; j++)
        {
            f1 >> loc[i].path[j].cycle;
            //			cout << loc[i].path[j].cycle << " ";
        }
    }
    f1.close();
}

vector<int> Dj(Loca *loc,int x, int y)//#求最短路径
{
    double dist[LOCANUM],min;
        string dist_path[LOCANUM];
        bool final[LOCANUM];
        int v, i, j, nv, w;
        vector< vector<int> > path_inds(LOCANUM, vector<int>());
        for (v = 0; v < LOCANUM; v++)
        {
            dist[v] = MAXC;
            final[v] = false;
            dist_path[v] = "";
        }
        dist[x] = 0;
        final[x] = true;
        path_inds[x].push_back(x);
        for (i = 0; i < loc[x].path_num; i++)
        {
            v = loc[x].path[i].to_loca;
            dist[v] = loc[x].path[i].distance;
            dist_path[v] = loc[x].name + "->" + loc[v].name;
            path_inds[v].push_back(x);
        }
        for (i = 0; i < LOCANUM - 1; i++)
        {
            min = MAXC;
            nv = -1;
            for (j = 0; j < 40; j++)
            {
                if (dist[j] < min && final[j] == false)
                {
                    min = dist[j];
                    nv = j;
                }
            }
            final[nv] = true;
            path_inds[nv].push_back(nv);
            if (nv == y)
                break;
            for (j = 0; j < loc[nv].path_num; j++)
            {
                w = loc[nv].path[j].to_loca;
                if (loc[nv].path[j].distance + dist[nv] < dist[w])
                {
                    dist[w] = loc[nv].path[j].distance + dist[nv];
                    dist_path[w] = dist_path[nv] + "->" + loc[w].name;
                    path_inds[w] = path_inds[nv];
                }
            }
        }
    //	cout << dist_path[y]<<endl;
        return path_inds[y];
}

vector<int> Dj_crowd(Loca *loc,int x, int y)//#求(拥挤度）最短路径
{
    double dist[LOCANUM],min;
        string dist_path[LOCANUM];
        bool final[LOCANUM];
        int v, i, j, nv, w;
        vector< vector<int> > path_inds(LOCANUM, vector<int>());

        for (v = 0; v < LOCANUM; v++)
        {
            dist[v] = MAXC;
            final[v] = false;
            dist_path[v] = "";
        }
        dist[x] = 0;
        final[x] = true;
        path_inds[x].push_back(x);
        for (i = 0; i < loc[x].path_num; i++)
        {
            v = loc[x].path[i].to_loca;
            dist[v] = loc[x].path[i].distance / loc[x].path[i].crowding;
//            cout << dist[v] << endl;
            dist_path[v] = loc[x].name + "->" + loc[v].name;
            path_inds[v].push_back(x);
        }
        for (i = 0; i < LOCANUM - 1; i++)
        {
            min = MAXC;
            nv = -1;
            for (j = 0; j < 40; j++)
            {
                if (dist[j] < min && final[j] == false)
                {
                    min = dist[j];
                    nv = j;
                }
            }
            final[nv] = true;
            path_inds[nv].push_back(nv);
            if (nv == y)
                break;
            for (j = 0; j < loc[nv].path_num; j++)
            {
                w = loc[nv].path[j].to_loca;
                if (loc[nv].path[j].distance / loc[x].path[j].crowding + dist[nv] < dist[w])
                {
                    dist[w] = loc[nv].path[j].distance / loc[x].path[j].crowding + dist[nv];
                    dist_path[w] = dist_path[nv] + "->" + loc[w].name;
                    path_inds[w] = path_inds[nv];
                }
            }
        }
//        cout << dist_path[y]<<endl;
        return path_inds[y];
}

vector<int> Dj_muti(Loca *loc,int* mid, int min_num, int x, int y)//途径点最短路径
{
    int i;
    string path;
    vector<int> path_inds;
    vector<int> np;
    path_inds = Dj(loc,x, mid[0]);
    x = mid[0];
    vector<int>::iterator t;

    for (i = 1; i < min_num; i++)
    {
        np = Dj(loc,x, mid[i]);
        for (t = np.begin()+1; t != np.end(); t++)
            path_inds.push_back(*t);
        x = mid[i];
    }
    np = Dj(loc,x, y);
    for (t = np.begin()+1; t != np.end(); t++)
        path_inds.push_back(*t);
    return path_inds;
}

vector<int> Dj_cyc(Loca *loc,int x, int y, int speed)//#求(考虑自行车和拥挤度）最短路径
{
    double dist[LOCANUM], min;
        string dist_path[LOCANUM];
        bool final[LOCANUM];
        int v, i, j, nv, w;
        vector< vector<int> > path_inds(LOCANUM, vector<int>());
        for (v = 0; v < LOCANUM; v++)
        {
            dist[v] = MAXC;
            final[v] = false;
            dist_path[v] = "";
        }
        dist[x] = 0;
        final[x] = true;
        path_inds[x].push_back(x);
        for (i = 0; i < loc[x].path_num; i++)
        {
            v = loc[x].path[i].to_loca;
            dist[v] = loc[x].path[i].cycle ? (loc[x].path[i].distance / (loc[x].path[i].crowding * speed)) : (loc[x].path[i].distance / loc[x].path[i].crowding);
//            cout << dist[v] << endl;
            dist_path[v] = loc[x].name + "->" + loc[v].name;
            path_inds[v].push_back(x);
        }
        for (i = 0; i < LOCANUM - 1; i++)
        {
            min = MAXC;
            nv = -1;
            for (j = 0; j < 40; j++)
            {
                if (dist[j] < min && final[j] == false)
                {
                    min = dist[j];
                    nv = j;
                }
            }
            final[nv] = true;
            path_inds[nv].push_back(nv);
            if (nv == y)
                break;
            for (j = 0; j < loc[nv].path_num; j++)
            {
                w = loc[nv].path[j].to_loca;
                if ((loc[x].path[j].cycle ? (loc[x].path[j].distance / (loc[x].path[j].crowding * speed)) : (loc[x].path[j].distance / loc[x].path[j].crowding)) + dist[nv] < dist[w])
                {
                    dist[w] = (loc[x].path[j].cycle ? (loc[x].path[j].distance / (loc[x].path[j].crowding * speed)) : (loc[x].path[j].distance / loc[x].path[j].crowding)) + dist[nv];
                    dist_path[w] = dist_path[nv] + "->" + loc[w].name;
                    path_inds[w] = path_inds[nv];
                }
            }
        }
//        cout << dist_path[y]<<endl;
        return path_inds[y];
}
vector<int> search(Loca *loc,int x)//查周边
{
    double dist[LOCANUM], min;
    string dist_path[LOCANUM];
    bool final[LOCANUM];
    int v, i, j, nv, w;
    vector<int> note_inds;
    for (v = 0; v < LOCANUM; v++)
    {
        dist[v] = MAXC;
        final[v] = false;
        dist_path[v] = "";
    }
    dist[x] = 0;
    final[x] = false;
    for (i = 0; i < loc[x].path_num; i++)
    {
        v = loc[x].path[i].to_loca;
        dist[v] = loc[x].path[i].distance;
        dist_path[v] = loc[x].name + "->" + loc[v].name;
    }
    for (i = 0; i < LOCANUM - 1; i++)
    {
        min = MAXC;
        nv = -1;
        for (j = 0; j < 40; j++)
        {
            if (dist[j] < min && final[j] == false)
            {
                min = dist[j];
                nv = j;
            }
        }
        final[nv] = true;
        for (j = 0; j < loc[nv].path_num; j++)
        {
            w = loc[nv].path[j].to_loca;
            if (loc[nv].path[j].distance + dist[nv] < dist[w])
            {
                dist[w] = loc[nv].path[j].distance + dist[nv];
                dist_path[w] = dist_path[nv] + "->" + loc[w].name;
            }
        }
    }
    for (v = 0; v < LOCANUM; v++)
    {
        if (dist[v] < SEARCH_DIS && x != v)
        {
            note_inds.push_back(v);
        }
    }
    return note_inds;
}
