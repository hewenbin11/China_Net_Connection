#define CRT_SECURE_NO_WARNINGS 1
#define Max_V 34
#include <easyx.h>
#include <graphics.h>
#include <string>
#include <mmsystem.h>
#include <time.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string.h>
#include <vector>
#include <algorithm>
#pragma comment(lib,"winmm.lib")
using namespace std;

typedef struct procince
{
	 int num=-1;
	 string Province_Name="";
	 string Provincial_Capital_Name="";
	 int position_x=0;
	 int position_y=0;
     bool Is_Work=true;

}Provincial_Capital;

Provincial_Capital capitals[Max_V];//capitals[]记录全部省会

float Distance_Matrix[Max_V][Max_V];//任意两城市距离矩阵

void Start();//读入文件初始化函数
void Create_Window();//新建窗口，初始化背景
void Init_Matrix();//初始化Distance_Matrix[][]
void Import_Bg();//导入背景图
void GreenPoint(Provincial_Capital);//绘制省会绿点
void RedPoint(Provincial_Capital);//绘制故障省会红点
void Init_All_GreenPoint(Provincial_Capital capital);
void Draw_Line(Provincial_Capital, Provincial_Capital);//绘制两点间绿线
void Draw_Red_Line(Provincial_Capital, Provincial_Capital);//绘制两点红线

float Calculate_Distance(Provincial_Capital capital1, Provincial_Capital capital2);//计算capital1和capital2的直线距离
void Clear();//清屏并且重置所有为绿
void Destroy_Point(int num);//摧毁城市节点
void Destroy_Line(int m, int n);

//void Prim(int Max_num, float Distance_Matrix_x[][Max_V],int start);
void Prim( float Distance_Matrix_x[][Max_V]);

int main()
{
    Start();//读入文件，初始化省会信息数组capitals[Max_V]
    Init_Matrix();//初始化城市距离矩阵
    Create_Window();
    Init_All_GreenPoint(capitals[0]);
    
    Destroy_Point(6);
    //Destroy_Point(8); 
    //Destroy_Point(9);
    //Destroy_Point(17);

    Destroy_Line(28, 30);

    Prim(Distance_Matrix);
    
	getchar();
}

void Start()
{
	
	ifstream file("./Src/TXT_Sources/Provinces_Data.txt");
	if (!file.is_open()) 
	{
		cerr << "无法打开文件" << endl;
		return ;
	}
    string line;
    int index = 0;

    // 读取文件内容
    while (getline(file, line) && index < Max_V) 
    {
        istringstream iss(line);
        Provincial_Capital capital;
        if (!(iss >> capital.num >> capital.Province_Name >> capital.Provincial_Capital_Name >> capital.position_x >> capital.position_y))
        {
            cerr << "解析错误，跳过当前行：" << line << endl;
            continue; // 如果解析失败，跳过当前行
        }
        capitals[index++] = capital; // 将解析的数据存入数组
    }


    
    // 关闭文件
    file.close();
    //// 打印数组内容以验证
    //for (int i = 0; i < index; ++i) {
    //    cout << "编号: " << capitals[i].num
    //        << ", 省份名称: " << capitals[i].Province_Name
    //        << ", 省会名称: " << capitals[i].Provincial_Capital_Name
    //        << ", X坐标: " << capitals[i].position_x
    //        << ", Y坐标: " << capitals[i].position_y << endl;
    //}

  
    return ;
}

void Create_Window()
{
    initgraph(1920, 1080);//
    Import_Bg();
}

void Init_Matrix()
{
    for (int i = 0; i < Max_V; i++)
    {
        for (int j = 0; j < Max_V ; j++)
        {
            Distance_Matrix[i][j] = Calculate_Distance(capitals[i], capitals[j]);
        }
    }
}

void Import_Bg()
{
    IMAGE pic;
    loadimage(&pic, L"./Src/PNG_Sources/China_Map.png");
    putimage(0, 0, &pic);
}

void GreenPoint(Provincial_Capital capital)
{
    setlinestyle(PS_SOLID);
    setlinecolor(COLORREF(RGB(102, 255, 51)));
    setfillcolor(COLORREF(RGB(102, 255, 51)));
    fillcircle(
        capital.position_x,
        capital.position_y,
        8
    );

}

void RedPoint(Provincial_Capital capital)
{
    setlinestyle(PS_SOLID);
    setlinecolor(COLORREF(RGB(255, 77, 77)));
    setfillcolor(COLORREF(RGB(255, 77, 77)));
    fillcircle(
        capital.position_x,
        capital.position_y,
        8
    );
}

void Init_All_GreenPoint(Provincial_Capital capital)
{
    for (int i = 0; i < Max_V; i++)
    {
        GreenPoint(capitals[i]);
    }
}

void Draw_Line(Provincial_Capital capital1, Provincial_Capital capital2)

{
    setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);
    setlinecolor(COLORREF(RGB(102, 255, 51)));
    setfillcolor(COLORREF(RGB(102, 255, 51)));
    line(capital1.position_x, capital1.position_y, capital2.position_x, capital2.position_y);
}

void Draw_Red_Line(Provincial_Capital capital1, Provincial_Capital capital2)

{
    setlinestyle(PS_DASH | PS_ENDCAP_FLAT, 3);
    setlinecolor(COLORREF(RGB(255, 77, 77)));
    setfillcolor(COLORREF(RGB(255, 77, 77)));
    line(capital1.position_x, capital1.position_y, capital2.position_x, capital2.position_y);
}

void Destroy_Point(int num)
{
    if (num >= 0 && num < 34)
    {
        capitals[num].Is_Work = false;
        RedPoint(capitals[num]);
        for (int i = 0; i < Max_V; i++)
        {
            Distance_Matrix[i][num] = INT_MAX;
            Distance_Matrix[num][i] = INT_MAX;
        }
        
    }
    else
    {
        return;
    }
}

void Destroy_Line(int m, int n) 
{
    Draw_Red_Line(capitals[m], capitals[n]);
    Distance_Matrix[m][n] = INT_MAX;
    Distance_Matrix[n][m] = INT_MAX;

}
        
void Clear()
{
    clearrectangle(
        0,
        0,
        1920,
        1080
    );

    Import_Bg();

    Init_All_GreenPoint(capitals[0]);
}

float Calculate_Distance(Provincial_Capital capital1, Provincial_Capital capital2)
{
    return sqrt(fabs((capital2.position_x - capital1.position_x) * (capital2.position_x - capital1.position_x) + (capital2.position_y - capital1.position_y) * (capital2.position_y - capital1.position_y)));
}

void Prim( float Distance_Matrix_x[][Max_V]) 
{
    int parent[Max_V]; // 记录最小生成树中每个点的父节点
    int key[Max_V];    // 记录每个点到最小生成树的最小距离
    bool visited[Max_V]; // 记录每个点是否已经在最小生成树中
    // 初始化
    for (int i = 0; i < Max_V; ++i)
    {
        key[i] = INT_MAX;
        visited[i] = false;
    }
    // 选择起始点为点0
    key[0] = 0;
    parent[0] = -1;

    // 构建最小生成树
    for (int count = 0; count < Max_V - 1; ++count)
    {
        // 找到当前距离最小的点
        int u = -1;
        for (int v = 0; v < Max_V; ++v)
        {
            if (!visited[v] && (u == -1 || key[v] < key[u]))
            {
                u = v;
            }
        }

        visited[u] = true;

        // 更新与该点相邻的点的距离
        for (int v = 0; v < Max_V; ++v) 
        {
            if (Distance_Matrix[u][v] != 0 && !visited[v] && Distance_Matrix[u][v] < key[v]) 
            {
                parent[v] = u;
                key[v] = Distance_Matrix[u][v];
            }
        }
    }

    // 输出最小生成树的边
    cout << "生成的最小生成树边列表：" << endl;
    for (int i = 1; i < Max_V; ++i) 
    {
        cout << parent[i] << "->" << i << endl;
        if (capitals[i].Is_Work)
        {
            Draw_Line(capitals[parent[i]], capitals[i]);
        }
       
        Sleep(100);
    }
}

/*
{
    GreenPoint(capitals[0]);
    GreenPoint(capitals[1]);
    RedPoint(capitals[5]);
    Draw_Line(capitals[1], capitals[0]);
}
*/ 
/*for (int i = 0; i < Max_V; i++)
{
    for (int j = 0; j < Max_V; j++)
    {
        cout << i <<"," << j << endl;
        cout << Distance_Matrix[i][j] << endl;
    }
}*/