//#include <iostream>
//#include <climits>
//using namespace std;
//
//// ����������
//const int MAX = 34;
//
//// Prim �㷨����
//void prim_algorithm(int Max, int Distance_Matrix[MAX][MAX])
//{
//    int parent[MAX]; // ��¼��С��������ÿ����ĸ��ڵ�
//    int key[MAX];    // ��¼ÿ���㵽��С����������С����
//    bool visited[MAX]; // ��¼ÿ�����Ƿ��Ѿ�����С��������
//
//    // ��ʼ��
//    for (int i = 0; i < Max; ++i) 
//{
//        key[i] = INT_MAX;
//        visited[i] = false;
//    }
//
//    // ѡ����ʼ��Ϊ��0
//    key[0] = 0;
//    parent[0] = -1;
//
//    // ������С������
//    for (int count = 0; count < Max - 1; ++count) 
//    {
//        // �ҵ���ǰ������С�ĵ�
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
//        // ������õ����ڵĵ�ľ���
//        for (int v = 0; v < Max; ++v) {
//            if (Distance_Matrix[u][v] != 0 && !visited[v] && Distance_Matrix[u][v] < key[v]) {
//                parent[v] = u;
//                key[v] = Distance_Matrix[u][v];
//            }
//        }
//    }
//
//    // �����С�������ı�
//    cout << "���ɵ���С���������б�" << endl;
//    for (int i = 1; i < Max; ++i) {
//        cout << parent[i] << "->" << i << endl;
//    }
//}
//
//// ʾ���÷�
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
