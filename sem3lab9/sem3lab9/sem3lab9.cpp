#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <random>
#include <locale.h>
#include <chrono>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

int getPositiveInt(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите положительное число: ";
        }
        else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}

int getPercent(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < 0 || value > 100) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите число от 0 до 100: ";
        }
        else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}

int getVertexNumber(const string& prompt, int maxVertex) {
    int value;
    while (true) {
        cout << prompt;
        cin >> value;
        if (cin.fail() || value < 1 || value > maxVertex) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите номер вершины от 1 до " << maxVertex << ": ";
        }
        else {
            cin.ignore(10000, '\n');
            return value - 1;
        }
    }
}

int getTestCount() {
    int value;
    while (true) {
        cout << "Введите количество тестовых размеров: ";
        cin >> value;
        if (cin.fail() || value <= 0) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите положительное число: ";
        }
        else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}

int getFillChoice() {
    int value;
    while (true) {
        cout << "Выберите способ заполнения:" << endl;
        cout << "1. Ручной ввод" << endl;
        cout << "2. Автозаполнение" << endl;
        cout << "Ваш выбор: ";
        cin >> value;
        if (cin.fail() || (value != 1 && value != 2)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Ошибка! Введите 1 или 2: ";
        }
        else {
            cin.ignore(10000, '\n');
            return value;
        }
    }
}

vector<vector<int>> generateAdjacencyMatrix(int n, double density) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 1.0);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (dis(gen) < density) {
                matrix[i][j] = 1;
                matrix[j][i] = 1;
            }
        }
    }
    return matrix;
}

vector<vector<int>> convertToAdjacencyList(const vector<vector<int>>& matrix) {
    int n = matrix.size();
    vector<vector<int>> list(n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (matrix[i][j] == 1) {
                list[i].push_back(j);
            }
        }
    }
    return list;
}

void printMatrix(const vector<vector<int>>& matrix) {
    int n = matrix.size();

    int maxIndexWidth = to_string(n).length();

    cout << "Матрица смежности:" << endl;
    cout << setw(maxIndexWidth + 2) << " ";
    for (int i = 1; i <= n; i++) {
        cout << setw(2) << i;
    }
    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << setw(maxIndexWidth) << (i + 1) << ": ";
        for (int j = 0; j < n; j++) {
            cout << setw(2) << matrix[i][j];
        }
        cout << endl;
    }
}

void printAdjacencyList(const vector<vector<int>>& adjList) {
    cout << "Списки смежности:" << endl;
    for (int i = 0; i < adjList.size(); i++) {
        cout << (i + 1) << ": ";
        for (int neighbor : adjList[i]) {
            cout << (neighbor + 1) << " ";
        }
        cout << endl;
    }
}

void printDistances(const vector<int>& dist) {
    cout << "Вектор расстояний: ";
    for (int i = 0; i < dist.size(); i++) {
        cout << "[" << (i + 1) << "]=" << dist[i] << " ";
    }
    cout << endl;
}

vector<int> BFSD_matrix(const vector<vector<int>>& G, int v) {
    int n = G.size();
    vector<int> DIST(n, -1);
    queue<int> Q;

    Q.push(v);
    DIST[v] = 0;

    while (!Q.empty()) {
        int current = Q.front();
        Q.pop();

        for (int i = 0; i < n; i++) {
            if (G[current][i] == 1 && DIST[i] == -1) {
                Q.push(i);
                DIST[i] = DIST[current] + 1;
            }
        }
    }
    return DIST;
}

vector<int> BFSD_list(const vector<vector<int>>& adjList, int v) {
    int n = adjList.size();
    vector<int> DIST(n, -1);
    queue<int> Q;

    Q.push(v);
    DIST[v] = 0;

    while (!Q.empty()) {
        int current = Q.front();
        Q.pop();

        for (int neighbor : adjList[current]) {
            if (DIST[neighbor] == -1) {
                Q.push(neighbor);
                DIST[neighbor] = DIST[current] + 1;
            }
        }
    }
    return DIST;
}

vector<int> DFSD_iterative_matrix(const vector<vector<int>>& G, int v) {
    int n = G.size();
    vector<int> DIST(n, -1);
    stack<int> S;

    S.push(v);
    DIST[v] = 0;

    while (!S.empty()) {
        int current = S.top();
        S.pop();

        for (int i = 0; i < n; i++) {
            if (G[current][i] == 1 && DIST[i] == -1) {
                DIST[i] = DIST[current] + 1;
                S.push(i);
            }
        }
    }
    return DIST;
}

vector<int> DFSD_iterative_list(const vector<vector<int>>& adjList, int v) {
    int n = adjList.size();
    vector<int> DIST(n, -1);
    stack<int> S;

    S.push(v);
    DIST[v] = 0;

    while (!S.empty()) {
        int current = S.top();
        S.pop();

        for (int neighbor : adjList[current]) {
            if (DIST[neighbor] == -1) {
                DIST[neighbor] = DIST[current] + 1;
                S.push(neighbor);
            }
        }
    }
    return DIST;
}

string measurePerformance(int n, double density, int startVertex) {
    auto matrix = generateAdjacencyMatrix(n, density);
    auto adjList = convertToAdjacencyList(matrix);

    auto start = chrono::high_resolution_clock::now();
    auto dist1 = BFSD_matrix(matrix, startVertex);
    auto end = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration_cast<chrono::microseconds>(end - start);

    start = chrono::high_resolution_clock::now();
    auto dist2 = BFSD_list(adjList, startVertex);
    end = chrono::high_resolution_clock::now();
    auto duration2 = chrono::duration_cast<chrono::microseconds>(end - start);

    start = chrono::high_resolution_clock::now();
    auto dist3 = DFSD_iterative_matrix(matrix, startVertex);
    end = chrono::high_resolution_clock::now();
    auto duration3 = chrono::duration_cast<chrono::microseconds>(end - start);

    start = chrono::high_resolution_clock::now();
    auto dist4 = DFSD_iterative_list(adjList, startVertex);
    end = chrono::high_resolution_clock::now();
    auto duration4 = chrono::duration_cast<chrono::microseconds>(end - start);

    long long min_time = min(min(duration1.count(), duration2.count()),
        min(duration3.count(), duration4.count()));

    cout << "Граф из " << n << " вершин (" << (int)(density * 100) << "% рёбер), стартовая вершина " << (startVertex + 1) << ":" << endl;

    cout << "BFS матрица: " << duration1.count() << " мкс";
    if (min_time > 0 && duration1.count() > min_time) {
        cout << " (медленнее на " << (duration1.count() - min_time) << " мкс)";
    }
    cout << endl;

    cout << "BFS списки:  " << duration2.count() << " мкс";
    if (min_time > 0 && duration2.count() > min_time) {
        cout << " (медленнее на " << (duration2.count() - min_time) << " мкс)";
    }
    cout << endl;

    cout << "DFS матрица: " << duration3.count() << " мкс";
    if (min_time > 0 && duration3.count() > min_time) {
        cout << " (медленнее на " << (duration3.count() - min_time) << " мкс)";
    }
    cout << endl;

    cout << "DFS списки:  " << duration4.count() << " мкс";
    if (min_time > 0 && duration4.count() > min_time) {
        cout << " (медленнее на " << (duration4.count() - min_time) << " мкс)";
    }
    cout << endl;

    string fastest;
    if (min_time == duration1.count()) fastest = "BFS матрица";
    else if (min_time == duration2.count()) fastest = "BFS списки";
    else if (min_time == duration3.count()) fastest = "DFS матрица";
    else fastest = "DFS списки";

    cout << "✓ Самый быстрый: " << fastest << endl;
    cout << "----------------------------------------" << endl;

    return fastest;
}

int main() {
    setlocale(LC_ALL, "Russian");

    int n;
    int densityPercent;
    int startVertex;

    cout << "=== ЛАБОРАТОРНАЯ РАБОТА №9 ===" << endl;
    cout << "=== ПОИСК РАССТОЯНИЙ В ГРАФЕ ===" << endl;

    n = getPositiveInt("Введите количество вершин графа: ");
    densityPercent = getPercent("Введите процент рёбер между вершинами (0-100%): ");
    startVertex = getVertexNumber("Введите стартовую вершину для поиска расстояний: ", n);

    double density = densityPercent / 100.0;

    cout << "\n=== ЗАДАНИЕ 1 ===" << endl;

    auto matrix = generateAdjacencyMatrix(n, density);
    printMatrix(matrix);

    auto adjList = convertToAdjacencyList(matrix);
    printAdjacencyList(adjList);

    cout << "\nПоиск расстояний BFS (матрица смежности) из вершины " << (startVertex + 1) << ":" << endl;
    auto dist_bfs_matrix = BFSD_matrix(matrix, startVertex);
    printDistances(dist_bfs_matrix);

    cout << "\nПоиск расстояний BFS (списки смежности) из вершины " << (startVertex + 1) << ":" << endl;
    auto dist_bfs_list = BFSD_list(adjList, startVertex);
    printDistances(dist_bfs_list);

    cout << "\n=== ЗАДАНИЕ 2* ===" << endl;

    cout << "\nПоиск расстояний DFS (матрица смежности) из вершины " << (startVertex + 1) << ":" << endl;
    auto dist_dfs_matrix = DFSD_iterative_matrix(matrix, startVertex);
    printDistances(dist_dfs_matrix);

    cout << "\nПоиск расстояний DFS (списки смежности) из вершины " << (startVertex + 1) << ":" << endl;
    auto dist_dfs_list = DFSD_iterative_list(adjList, startVertex);
    printDistances(dist_dfs_list);

    cout << "\n=== СРАВНЕНИЕ ПРОИЗВОДИТЕЛЬНОСТИ ===" << endl;

    int testCount = getTestCount();
    int fillChoice = getFillChoice();

    vector<int> sizes;
    vector<double> densities;
    vector<int> startVertices;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> size_dis(100, 1000);
    uniform_int_distribution<> percent_dis(10, 60);

    if (fillChoice == 1) {
        for (int i = 0; i < testCount; i++) {
            int size = getPositiveInt("Тест " + to_string(i + 1) + " - введите количество вершин: ");
            int percent = getPercent("Тест " + to_string(i + 1) + " - введите процент рёбер: ");
            int startVert = getVertexNumber("Тест " + to_string(i + 1) + " - введите стартовую вершину: ", size);

            sizes.push_back(size);
            densities.push_back(percent / 100.0);
            startVertices.push_back(startVert);
        }
    }
    else {
        cout << "Автозаполнение " << testCount << " тестов случайными значениями..." << endl;
        for (int i = 0; i < testCount; i++) {
            int size = size_dis(gen);
            sizes.push_back(size);
            densities.push_back(percent_dis(gen) / 100.0);
            uniform_int_distribution<> vertex_dis(0, size - 1);
            startVertices.push_back(vertex_dis(gen));
        }

        cout << "Случайные значения:" << endl;
        for (int i = 0; i < testCount; i++) {
            cout << "Тест " << i + 1 << ": " << sizes[i] << " вершин, "
                << (int)(densities[i] * 100) << "% рёбер, стартовая вершина " << (startVertices[i] + 1) << endl;
        }
    }

    cout << "\n=== РЕЗУЛЬТАТЫ ТЕСТИРОВАНИЯ ===" << endl;

    vector<string> fastestMethods;
    for (int i = 0; i < testCount; i++) {
        string fastest = measurePerformance(sizes[i], densities[i], startVertices[i]);
        fastestMethods.push_back(fastest);
    }

    cout << "=== ТОП САМЫХ БЫСТРЫХ МЕТОДОВ ===" << endl;

    int bfs_matrix_count = 0;
    int bfs_list_count = 0;
    int dfs_matrix_count = 0;
    int dfs_list_count = 0;

    for (const string& method : fastestMethods) {
        if (method == "BFS матрица") bfs_matrix_count++;
        else if (method == "BFS списки") bfs_list_count++;
        else if (method == "DFS матрица") dfs_matrix_count++;
        else if (method == "DFS списки") dfs_list_count++;
    }

    cout << "BFS матрица: " << bfs_matrix_count << " раз" << endl;
    cout << "BFS списки:  " << bfs_list_count << " раз" << endl;
    cout << "DFS матрица: " << dfs_matrix_count << " раз" << endl;
    cout << "DFS списки:  " << dfs_list_count << " раз" << endl;

    return 0;
}