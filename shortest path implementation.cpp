#include "the7.h"



int nextNode(bool *finalized, int *shortest, int n)
{
    int min = 100000;
    int nextN;
    for(int i = 0; i < n; i++)
    {
        if (finalized[i] == false && shortest[i] <= min)
        {
            min = shortest[i];
            nextN = i;
        }
    }
    return nextN;
}

std::vector<int> dijkstra(int n, std::vector<Road> roads, int s, int d)
{
    int houseMatrix[n][n];
    int roadMap[n];
    int shortest[n];
    bool finalized[n];
    long unsigned int k; 
    int i, initialNode;
    int a, b, value;
    int temp;
    std::vector<int> path;
  
    for (i = 0; i < n; i++)
    {
        finalized[i] = false;
        shortest[i] = 100000;
        for (int l = 0; l < n; l++)
        {
            houseMatrix[i][l] = 100000;
            if (i == l)
            {
                houseMatrix[i][i] = 0;
            }
        }
    }
    
    for (k = 0; k < roads.size(); k++)
    {
        a = roads[k].endpoints.first;
        b = roads[k].endpoints.second;
        value = roads[k].time;
        houseMatrix[a][b] = value;
        houseMatrix[b][a] = value;
        
    }
  
    shortest[s] = 0;
  
    for (i = 0; i < n-1; i++)
    {
        initialNode = nextNode(finalized, shortest, n);
        finalized[initialNode] = true;
        for (int j = 0; j < n; j++)
        {
            if (!finalized[j] && houseMatrix[initialNode][j] 
                    && shortest[initialNode] != 100000
                    && shortest[initialNode] + houseMatrix[initialNode][j] < shortest[j])
                {
                    shortest[j] = shortest[initialNode] + houseMatrix[initialNode][j];
                    roadMap[j] = initialNode;
                }
        }
    }
    
    temp = d;
    path.push_back(s);
    while (roadMap[temp] != s)
    {
        path.push_back(roadMap[temp]);
        temp = roadMap[temp];
    }
    path.push_back(shortest[d]);

    return path;
  
}

void FindRoute(int n, std::vector<Road> roads, int s, int d, int x, int y) {
  // You can change these variables. These are here for demo only.
  
    std::vector<int> path;
    int cost = INT_MAX;
  
    std::vector<int> fromStoY;
    std::vector<int> fromYtoX;
    std::vector<int> fromXtoD;
    std::vector<int> fromStoX;
    std::vector<int> fromXtoY;
    std::vector<int> fromYtoD;
    
    fromStoY = dijkstra(n, roads, s, y);
    fromYtoX = dijkstra(n, roads, y, x);
    fromXtoD = dijkstra(n, roads, x, d);
    fromStoX = dijkstra(n, roads, s, x);
    fromXtoY = dijkstra(n, roads, x, y);
    fromYtoD = dijkstra(n, roads, y, d);
    if (fromStoY.back() + fromYtoX.back() + fromXtoD.back() <= fromStoX.back() + fromXtoY.back() + fromYtoD.back())
    {
        cost = fromStoY.back() + fromYtoX.back() + fromXtoD.back();
        for(long unsigned int i = 0; i < fromStoY.size()-1; i++)
        {
            path.push_back(fromStoY[i]);
        }
        for(long unsigned int i = 0; i < fromYtoX.size()-1;i++)
        {
            path.push_back(fromYtoX[i]);
        }
        for(long unsigned int i = 0; i < fromXtoD.size()-1;i++)
        {
            path.push_back(fromXtoD[i]);
        }
    }
    else
    {
        cost = fromStoX.back() + fromXtoY.back() + fromYtoD.back();
        for(long unsigned int i = 0; i < fromStoX.size()-1; i++)
        {
            path.push_back(fromStoX[i]);
        }
        for(long unsigned int i = 0; i < fromXtoY.size()-1;i++)
        {
            path.push_back(fromXtoY[i]);
        }
        for(long unsigned int i = 0; i < fromYtoD.size()-1;i++)
        {
            path.push_back(fromYtoD[i]);
        }
    }
    path.push_back(d);
    


  std::cout << cost << " ";
  PrintRange(path.begin(), path.end());
  std::cout << std::endl;
}