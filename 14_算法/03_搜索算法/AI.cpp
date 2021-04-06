#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <ctime>
using namespace std;

typedef pair<string, int> neighbor;  //当前城市的相邻城市的城市名和对应的路径代价
struct state            //罗马尼亚问题中的每一个城市的城市信息
{
    string name;        //该城市的城市名
    int neighbor_num;   //与该城市相邻的有几个城市
    map<int, neighbor> nextstate;    //记录每个相邻的城市和对应的路径代价
    int h;              //该城市到目标城市的最小代价路径的估计值
};

struct Treenode         //搜索树中的树结点定义
{
    int child_num;      //该树结点有几个孩子结点
    int value;          //该树结点的代价估计值（启发式）
    int depth;          //该树结点的深度
    state theState;     //该树结点对应在哪个城市
    Treenode* father;  //保存该树结点的父亲结点（指针）
    map<int, Treenode*> child;  //保存该树结点的所有孩子结点（指针）
};

int state_num = 0;          //罗马尼亚问题中的每一个城市
map<string, state> graph;    //邻接表保存罗马尼亚问题的图：<城市名，城市信息>
map<string, int> explored;   //罗马尼亚问题中的城市是否被拓展过

Treenode* Create_node()    //创建一个树结点，返回该树结点的指针
{
    Treenode* node = new Treenode; //申请一个新的树结点
    node->child_num = 0;    //初始化树结点的孩子结点数目为 0
    node->value = 0;        //初始化树结点的代价估计值（启发式）为 0
    node->depth = 0;        //初始化树结点的深度为 0
    node->father = NULL;    //初始化树结点的父亲结点（指针）为空
    node->child.clear();    //初始化树结点不存在孩子结点（指针）
    return node;            //返回该树结点的指针
}

void File_Input(string s)
{
    ifstream f(s);      //导入描述罗马尼亚问题详细信息的文件
    f >> state_num;      //输入罗马尼亚问题的总城市数目
    for (int i = 0; i < state_num; i++) {   //初始化每一个城市的城市信息
        state t;
        f >> t.name;            //当前城市的城市名
        f >> t.h;               //当前城市到目标城市的最小代价路径的估计值
        f >> t.neighbor_num;    //当前城市有几个相邻的城市
        for (int j = 0; j < t.neighbor_num; j++) {  //保存每一个相邻的城市
            f >> t.nextstate[j].first;       //保存相邻城市的城市名
            f >> t.nextstate[j].second;      //保存到相邻城市的路径代价
        }
        graph[t.name] = t;      //在罗马尼亚问题的图中添加当前城市
        explored[t.name] = 0;   //初始化当前城市未被拓展过
    }
}

void Show_Graph()
{
    cout << " State number : " << state_num << endl;
    map<string, state>::iterator mit;
    for (mit = graph.begin(); mit != graph.end(); mit++) {
        cout << "State : " << " name : " << mit->second.name << endl;
        cout << "        " << " h : " << mit->second.h << endl;
        for (int j = 0; j < mit->second.neighbor_num; j++) {
            cout << "        " << " naighbor " << j << " : name :" << mit->second.nextstate[j].first
                << "\tg : " << mit->second.nextstate[j].second << endl;
        }
    }
}

queue<Treenode*> sort(queue<Treenode*> q)
{
    queue<Treenode*> s;
    map<float, Treenode*> m;
    int i = 0;
    while (!q.empty()) {
        i++;
        Treenode* t = q.front();
        q.pop();
        if (m[t->value] == NULL)
            m[t->value] = t;
        else {
            m[t->value + i * 0.01] = t;
        }
    }
    map<float, Treenode*>::iterator mit;
    for (mit = m.begin(); mit != m.end(); mit++)
        s.push(mit->second);
    return s;
}

void Route(Treenode* c, string s)   //递归得到搜索路径
{
    if (c->theState.name == s) {      //当前城市为目标城市
        //输出当前城市和代价估计值（启发式）
        cout << c->theState.name << " v : " << c->value << " -> ";
        return;
    }
    Route(c->father, s);     //当前城市还不是目标城市，继续递归
    //输出当前城市和代价估计值（启发式）
    cout << c->theState.name << " v : " << c->value << " -> ";
    return;
}

void Breadth_First_Search(string start, string goal) //宽度优先搜索算法
{
    state start_state = graph[start];   //获取开始城市的城市信息
    Treenode* root = Create_node();     //创建搜索树一个根结点
    queue<Treenode*> Q;                //记录保存待拓展的城市集合
    root->theState = start_state;       //根结点的城市为开始城市
    Q.push(root);                       //将开始城市加入待拓展的城市集合（根结点）
    while (!Q.empty()) {                  //还存在待拓展的城市
        Treenode* current = Q.front();             //取出当前需要拓展的城市
        Q.pop();
        state current_state = current->theState;    //获取当前城市的城市信息
        cout << "State name : " << current_state.name << "\tValue : " << current->value << endl;
        explored[current_state.name] = 1;           //将当前城市设置为已经拓展过

        if (current_state.name == goal) {             //判断当前城市是不是目标城市
            cout << endl << endl << "Breadth_First_Search Route : ";
            Route(current, start);               //输出搜索的路径
            return;                             //搜索结束，返回
        }
        for (int i = 0; i < current_state.neighbor_num; i++) {                  //拓展当前城市的所有相邻城市
            string nextstate_name = current_state.nextstate[i].first;   //获取相邻城市的城市名
            Treenode* current_child = Create_node();                   //创建一个新的子结点
            current_child->theState = graph[nextstate_name];            //子结点的城市信息
            current_child->value = current->value + current_state.nextstate[i].second;  //子结点的代价估计值
            current_child->father = current;                            //子结点的父亲结点是当前正在拓展的结点
            current->child[current->child_num] = current_child;         //在当前正在拓展的结点中加入该子结点
            current->child_num++;                   //当前正在拓展的结点中孩子结点数加一

            cout << "\tChild State : " << nextstate_name << "\tValue : " << current_child->value;
            if (explored[nextstate_name] == 0) {      //判断该相邻城市是否已经被拓展过
                Q.push(current_child);              //没被拓展过，加入待拓展的城市集合（树结点）
            }
        }
        cout << endl << endl;
    }
    cout << "Failure" << endl;        //找不到可以到目标城市的路径，搜索失败
    return;
}

void Uniform_Cost_Search(string start, string goal)  //一致代价搜索算法
{
    state start_state = graph[start];   //获取开始城市的城市信息
    Treenode* root = Create_node();     //创建搜索树一个根结点
    queue<Treenode*> Q;                //记录保存待拓展的城市集合
    root->theState = start_state;       //根结点的城市为开始城市
    Q.push(root);                       //将开始城市加入待拓展的城市集合（根结点）
    while (!Q.empty()) {                  //还存在待拓展的城市
        Treenode* current = Q.front();             //取出当前需要拓展的城市
        Q.pop();
        state current_state = current->theState;    //获取当前城市的城市信息
        cout << "State name : " << current_state.name << "\tValue : " << current->value << endl;
        explored[current_state.name] = 1;           //将当前城市设置为已经拓展过

        if (current_state.name == goal) {             //判断当前城市是不是目标城市
            cout << endl << endl << "Uniform_Cost_Search Route : ";
            Route(current, start);               //输出搜索的路径
            return;                             //搜索结束，返回
        }
        for (int i = 0; i < current_state.neighbor_num; i++) {                  //拓展当前城市的所有相邻城市
            string nextstate_name = current_state.nextstate[i].first;   //获取相邻城市的城市名
            Treenode* current_child = Create_node();                   //创建一个新的子结点
            current_child->theState = graph[nextstate_name];            //子结点的城市信息
            current_child->value = current->value + current_state.nextstate[i].second;  //子结点的代价估计值
            current_child->father = current;                            //子结点的父亲结点是当前正在拓展的结点
            current->child[current->child_num] = current_child;         //在当前正在拓展的结点中加入该子结点
            current->child_num++;                   //当前正在拓展的结点中孩子结点数加一

            cout << "\tChild State : " << nextstate_name << "\tValue : " << current_child->value;
            if (explored[nextstate_name] == 0) {      //判断该相邻城市是否已经被拓展过
                Q.push(current_child);              //没被拓展过，加入待拓展的城市集合（树结点）
            }
        }
        Q = sort(Q);            //进行优先队列的排序，实现优先队列的功能
        cout << endl << endl;
    }
    cout << "Failure" << endl;    //找不到可以到目标城市的路径，搜索失败
    return;
}

void Depth_First_Search(string start, string goal) //深度优先搜索算法
{
    state start_state = graph[start];   //获取开始城市的城市信息
    Treenode* root = Create_node();     //创建搜索树一个根结点
    stack<Treenode*> Q;                //记录保存待拓展的城市集合
    root->theState = start_state;       //根结点的城市为开始城市
    Q.push(root);                       //将开始城市加入待拓展的城市集合（根结点）
    while (!Q.empty()) {                  //还存在待拓展的城市
        Treenode* current = Q.top();   //取出当前需要拓展的城市
        Q.pop();
        state current_state = current->theState;    //获取当前城市的城市信息
        cout << "State name : " << current_state.name << "\tValue : " << current->value << "\tDepth : " << current->depth << endl;
        explored[current_state.name] = 1;           //将当前城市设置为已经拓展过

        if (current_state.name == goal) {             //判断当前城市是不是目标城市
            cout << endl << endl << "Depth_First_Search Route : ";
            Route(current, start);               //输出搜索的路径
            return;                             //搜索结束，返回
        }
        for (int i = 0; i < current_state.neighbor_num; i++) {                  //拓展当前城市的所有相邻城市
            string nextstate_name = current_state.nextstate[i].first;   //获取相邻城市的城市名
            Treenode* current_child = Create_node();                   //创建一个新的子结点
            current_child->theState = graph[nextstate_name];            //子结点的城市信息
            current_child->value = current->value + current_state.nextstate[i].second;  //子结点的代价估计值
            current_child->father = current;                            //子结点的父亲结点是当前正在拓展的结点
            current->child[current->child_num] = current_child;         //在当前正在拓展的结点中加入该子结点
            current->child_num++;                   //当前正在拓展的结点中孩子结点数加一

            cout << "\tChild State : " << nextstate_name << "\tValue : " << current_child->value;
            if (explored[nextstate_name] == 0) {      //判断该相邻城市是否已经被拓展过
                Q.push(current_child);              //没被拓展过，加入待拓展的城市集合（树结点）
            }
        }
        cout << endl << endl;
    }
    cout << "Failure" << endl;        //找不到可以到目标城市的路径，搜索失败
    return;
}

int Iterative_Deepening_Depth_First_Search(string start, string goal, int D)  //迭代加深的深度优先搜索算法
{
    state start_state = graph[start];   //获取开始城市的城市信息
    Treenode* root = Create_node();     //创建搜索树一个根结点
    stack<Treenode*> Q;                //记录保存待拓展的城市集合
    root->theState = start_state;       //根结点的城市为开始城市
    Q.push(root);                       //将开始城市加入待拓展的城市集合（根结点）
    while (!Q.empty()) {                  //还存在待拓展的城市
        Treenode* current = Q.top();   //取出当前需要拓展的城市
        Q.pop();
        if (current->depth > D)          //判断当前结点的深度是否超过限界
            continue;                   //超过限界，跳过该结点，不进行讨论
        state current_state = current->theState;    //获取当前城市的城市信息
        cout << "State name : " << current_state.name << "\tValue : " << current->value << "\tDepth : " << current->depth << endl;
        explored[current_state.name] = 1;           //将当前城市设置为已经拓展过

        if (current_state.name == goal) {             //判断当前城市是不是目标城市
            cout << endl << endl << "Iterative_Deepening_Depth_First_Search Route : ";
            Route(current, start);                   //输出搜索的路径
            return 1;                               //搜索结束，返回 1 表示搜索成功
        }
        for (int i = 0; i < current_state.neighbor_num; i++) {                  //拓展当前城市的所有相邻城市
            string nextstate_name = current_state.nextstate[i].first;   //获取相邻城市的城市名
            Treenode* current_child = Create_node();                   //创建一个新的子结点
            current_child->theState = graph[nextstate_name];            //子结点的城市信息
            current_child->value = current->value + current_state.nextstate[i].second;  //子结点的代价估计值
            current_child->depth = current->depth + 1;                  //子结点的深度为父亲结点的深度加一
            current_child->father = current;                            //子结点的父亲结点是当前正在拓展的结点
            current->child[current->child_num] = current_child;         //在当前正在拓展的结点中加入该子结点
            current->child_num++;                   //当前正在拓展的结点中孩子结点数加一

            cout << "\tChild State : " << nextstate_name << "\tValue : " << current_child->value;
            if (explored[nextstate_name] == 0) {      //判断该相邻城市是否已经被拓展过
                Q.push(current_child);              //没被拓展过，加入待拓展的城市集合（树结点）
            }
        }
        cout << endl << endl;
    }
    cout << "Failure" << endl;    //找不到可以到目标城市的路径，搜索失败
    return 0;                   //返回 0 表示搜索失败，需要继续加深
}

void Greedy_Best_First_Search(string start, string goal) //贪婪最佳优先搜索算法
{
    state start_state = graph[start];   //获取开始城市的城市信息
    Treenode* root = Create_node();     //创建搜索树一个根结点
    queue<Treenode*> Q;                //记录保存待拓展的城市集合
    root->theState = start_state;       //根结点的城市为开始城市
    root->value = start_state.h;        //根结点的启发函数估计值
    Q.push(root);                       //将开始城市加入待拓展的城市集合（根结点）
    while (!Q.empty()) {                  //还存在待拓展的城市
        Treenode* current = Q.front();             //取出当前需要拓展的城市
        Q.pop();
        state current_state = current->theState;    //获取当前城市的城市信息
        cout << "State name : " << current_state.name << "\tValue : " << current->value << endl;
        explored[current_state.name] = 1;           //将当前城市设置为已经拓展过

        if (current_state.name == goal) {             //判断当前城市是不是目标城市
            cout << endl << endl << "Greedy_Best_First_Search Route : ";
            Route(current, start);               //输出搜索的路径
            return;                             //搜索结束，返回
        }
        for (int i = 0; i < current_state.neighbor_num; i++) {                  //拓展当前城市的所有相邻城市
            string nextstate_name = current_state.nextstate[i].first;   //获取相邻城市的城市名
            Treenode* current_child = Create_node();                   //创建一个新的子结点
            current_child->theState = graph[nextstate_name];            //子结点的城市信息
            current_child->value = graph[nextstate_name].h;             //子结点的启发函数估计值
            current_child->father = current;                            //子结点的父亲结点是当前正在拓展的结点
            current->child[current->child_num] = current_child;         //在当前正在拓展的结点中加入该子结点
            current->child_num++;                   //当前正在拓展的结点中孩子结点数加一

            cout << "\tChild State : " << nextstate_name << "\tValue : " << current_child->value;
            if (explored[nextstate_name] == 0) {      //判断该相邻城市是否已经被拓展过
                Q.push(current_child);              //没被拓展过，加入待拓展的城市集合（树结点）
            }
        }
        Q = sort(Q);            //进行优先队列的排序，实现优先队列的功能
        cout << endl << endl;
    }
    cout << "Failure" << endl;    //找不到可以到目标城市的路径，搜索失败
    return;
}

void A_Star_Search(string start, string goal)
{
    state start_state = graph[start];   //获取开始城市的城市信息
    Treenode* root = Create_node();     //创建搜索树一个根结点
    queue<Treenode*> Q;                //记录保存待拓展的城市集合
    root->theState = start_state;       //根结点的城市为开始城市
    root->value = start_state.h;        //根结点的启发函数估计值
    Q.push(root);                       //将开始城市加入待拓展的城市集合（根结点）
    while (!Q.empty()) {                  //还存在待拓展的城市
        Treenode* current = Q.front();             //取出当前需要拓展的城市
        Q.pop();
        state current_state = current->theState;    //获取当前城市的城市信息
        cout << "State name : " << current_state.name << "\tValue : " << current->value << endl;
        explored[current_state.name] = 1;           //将当前城市设置为已经拓展过
        if (current_state.name == goal) {             //判断当前城市是不是目标城市
            cout << endl << endl << "A_Star_Search Route : ";
            Route(current, start);               //输出搜索的路径
            return;                             //搜索结束，返回
        }

        for (int i = 0; i < current_state.neighbor_num; i++) {                  //拓展当前城市的所有相邻城市
            string nextstate_name = current_state.nextstate[i].first;   //获取相邻城市的城市名
            Treenode* current_child = Create_node();                   //创建一个新的子结点
            current_child->theState = graph[nextstate_name];            //子结点的城市信息
            //子结点的启发函数估计值
            current_child->value = current->value - current_state.h + current_state.nextstate[i].second + graph[nextstate_name].h;
            current_child->father = current;                            //子结点的父亲结点是当前正在拓展的结点
            current->child[current->child_num] = current_child;         //在当前正在拓展的结点中加入该子结点
            current->child_num++;                   //当前正在拓展的结点中孩子结点数加一

            cout << "\tChild State : " << nextstate_name << "\tValue : " << current_child->value;
            if (explored[nextstate_name] == 0) {      //判断该相邻城市是否已经被拓展过
                Q.push(current_child);              //没被拓展过，加入待拓展的城市集合（树结点）
            }
        }
        Q = sort(Q);            //进行优先队列的排序，实现优先队列的功能
        cout << endl << endl;
    }
    cout << "Failure" << endl;    //找不到可以到目标城市的路径，搜索失败
    return;
}

int main()
{
    // 记录程序运行时间 
    clock_t start, end, over;
    start = clock();
    end = clock();
    over = end - start;

    ifstream file("Select_Search.txt");
    string select_Search;
    while (cout << endl << endl << "Choose How to Search : " && file >> select_Search) {
        File_Input("Romania.txt");
        // Show_Graph();

        start = clock();
        if (select_Search == "BFS") {
            cout << endl << "Breadth_First_Search" << endl;
            Breadth_First_Search("Arad", "Bucharest");
        }
        else if (select_Search == "UCS") {
            cout << endl << "Uniform_Cost_Search" << endl;
            Uniform_Cost_Search("Arad", "Bucharest");
        }
        else if (select_Search == "DFS") {
            cout << endl << "Depth_First_Search" << endl;
            Depth_First_Search("Arad", "Bucharest");
        }
        else if (select_Search == "IDDFS") {
            for (int i = 0; ; i++) {
                File_Input("Romania.txt");
                cout << endl << "Iterative_Deepening_Depth_First_Search : Limit : " << i << endl;
                int ans = Iterative_Deepening_Depth_First_Search("Arad", "Bucharest", i);
                if (ans == 1)
                    break;
            }
        }
        else if (select_Search == "GBFS") {
            cout << endl << "Greedy_Best_First_Search" << endl;
            Greedy_Best_First_Search("Arad", "Bucharest");
        }
        else if (select_Search == "ASS") {
            cout << endl << "A_Star_Search" << endl;
            A_Star_Search("Arad", "Bucharest");
        }
        else {
            cout << "unknown select search:" << select_Search << endl;
            continue;
        }
        end = clock();
        printf("\nRun Time : %6.3f ms\n", (double)(end - start - over) / CLOCKS_PER_SEC * 1000);
    }
}
