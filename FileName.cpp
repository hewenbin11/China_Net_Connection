//#include <iostream>
//#include <climits>
//using namespace std;
//
//// 定义最大点数
//const int MAX = 34;
//
//// Prim 算法函数
//void prim_algorithm(int Max, int Distance_Matrix[MAX][MAX])
//{
//    int parent[MAX]; // 记录最小生成树中每个点的父节点
//    int key[MAX];    // 记录每个点到最小生成树的最小距离
//    bool visited[MAX]; // 记录每个点是否已经在最小生成树中
//
//    // 初始化
//    for (int i = 0; i < Max; ++i) 
//{
//        key[i] = INT_MAX;
//        visited[i] = false;
//    }
//
//    // 选择起始点为点0
//    key[0] = 0;
//    parent[0] = -1;
//
//    // 构建最小生成树
//    for (int count = 0; count < Max - 1; ++count) 
//    {
//        // 找到当前距离最小的点
//        int u = -1;
//        for (int v = 0; v < Max; ++v) 
//        {
//            if (!visited[v] && (u == -1 || key[v] < key[u])) 
//            {
//                u = v;
//            }
//        }
//
//        visited[u] = true;
//
//        // 更新与该点相邻的点的距离
//        for (int v = 0; v < Max; ++v) {
//            if (Distance_Matrix[u][v] != 0 && !visited[v] && Distance_Matrix[u][v] < key[v]) {
//                parent[v] = u;
//                key[v] = Distance_Matrix[u][v];
//            }
//        }
//    }
//
//    // 输出最小生成树的边
//    cout << "生成的最小生成树边列表：" << endl;
//    for (int i = 1; i < Max; ++i) {
//        cout << parent[i] << "->" << i << endl;
//    }
//}
//
//// 示例用法
//int main() {
//    int Max = 4;
//    int Distance_Matrix[MAX][MAX] = {
//        {0, 10, 20, 0},
//        {10, 0, 30, 5},
//        {20, 30, 0, 15},
//        {0, 5, 15, 0}
//    };
//
//    prim_algorithm(Max, Distance_Matrix);
//
//    return 0;
//}
