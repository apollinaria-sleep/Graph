/*!
 * @mainpage Класс Graph
 *
 * @section intro_sec Введение
 *
 * Класс Graph предназначен для работы с неориентированными, связными графами.
 *
 * <a href="https://github.com/apollinaria-sleep/Graph/Graph.pdf"> Ссылка на документацию</a>
 */
#ifndef GRAPH_GRAPH_H
#define GRAPH_GRAPH_H

#include <vector>
#include <iosfwd>
#include <iostream>
#include <exception>
#include <string>
#include <string_view>
#include <algorithm>
#include <map>
#include <fstream>


/*!
    \brief Класс Edge реализует ребра графа.
    \details Каждый объект класса Edge хранит в себе следующую информацию:
    * from_vertex - одна из вершин ребра
    * other_vertex - другая вершина ребра
    * weight - вес ребра
*/
class Edge {
public:
    int from_vertex;
    int other_vertex;
    int weight = 1;

    Edge() = default;
    Edge(int from_v, int to_v) : from_vertex(from_v), other_vertex(to_v) {}
    Edge(int from_v, int to_v, int weight) : from_vertex(from_v), other_vertex(to_v), weight(weight) {}
};

/*!
    \brief Класс Graph основной класс реализующий граф, поддерживающий добавление и удаление вершин и ребер, то есть способный динамически изменяться.
    \details Каждый объект класса Graph хранит в себе следующую информацию:
    * vertex - std::vector<int> с вершинами графа
    * edge - std::vector<std::vector<Edge>> матрица смежности графа, то есть множество ребер графа
*/
class Graph {
public:
    // конструкторы
    Graph() = default;
    /*!
     * Создает объект класса Graph
     * @param edge список ребер, которые задают граф
     */
    Graph(const std::vector<Edge>& edge);
    // копирование
    Graph(const Graph& other);
    Graph& operator=(const Graph& other);
    // move конструктор
    Graph(Graph&& other) noexcept;
    // move оператор присваивания
    Graph& operator=(Graph&& other) noexcept;
    // деструктор
    ~Graph();


    // добавление/удаление вершины
    /*!
     * Добавляет одну вершину в граф, обычно используется при добавлении первой вершины
     * @param v_num номер вершины
     */
    void AddVertex(int v_num);
    /*!
     * Добавляет в граф вершину и её ребра. Необходимо, чтобы все вершины в списке уже находились в графе
     * @param v_num номер вершины
     * @param edges список смежных вершин
     */
    void AddVertex(int v_num, std::vector<int> &edges);
    /*!
     * Добавляет в граф вершину и её ребра с весами. Необходимо, чтобы все вершины в списке уже находились в графе
     * @param v_num номер вершины
     * @param edges список смежных вершин
     * @param weights список весов ребер
     */
    void AddVertex(int v_num, const std::vector<int>&edges, const std::vector<int> &weights);
    /*!
     * Удаляет вершину из графа вместе со всеми её ребрами
     * @param v_num номер вершины
     */
    void RemoveVertex(int v_num);


    // добавление/удаление ребра
    /*!
     * Добавляет указанное ребро в граф
     * @param new_edge ребро, которое нужно добавить в граф
     */
    void AddEdge(Edge new_edge);
    /*!
     * Добавляет в граф ребро между вершинами
     * @param from_v одна из вершин ребра
     * @param to_v другая вершина ребра
     */
    void AddEdge(int from_v, int to_v);
    /*!
     * Добавляет в граф ребро с указанным весом между вершинами
     * @param from_v одна из вершин ребра
     * @param to_v другая вершина ребра
     * @param weight вес ребра
     */
    void AddEdge(int from_v, int to_v, int weight);
    /*!
     * Удаляет ребро между двумя вершинами
     * @param from_v одна из вершин ребра
     * @param to_v другая вершина ребра
     */
    void RemoveEdge(int from_v, int to_v);


    /*!
     * Функция поиска минимального остовного дерева в связном, взвешенном графе
     * @return Объект класса Graph, являющийся минимальным остовным деревом исходного графа
     */
    Graph FindMST();

    // функции, описывающие свойства графа
    /*!
     * Функция определения размера графа
     * @return Количество вершин в графе
     */
    int Size();
    /*!
     * Функция, показывающая ребра графа
     * @return Список всех ребер графа
     */
    std::vector<Edge> AllEdges();
    /*!
     * Функция, показывающая вершины графа
     * @return Список всех вершин графа
     */
    std::vector<int> AllVertex();


    /*!
     * Визуализирует граф
     * @param file_name имя .md файла, в которое будет записано описание графа
     * @note После компиляции .md файла будет получено визуальное представление графа
     */
    void ShowGraph(std::string file_name) const;

    std::istream& ReadFrom(std::istream&);
    std::ostream& WriteTo(std::ostream&) const;
private:
    // класс ошибок
    class Exceptions : public std::exception {
    public:
        explicit Exceptions(std::string_view error) : m_error{error} {}
        const char* what() const noexcept override {
            return m_error.c_str();//;
        }
    private:
        std::string m_error;
    };

    std::vector<int> vertex;
    std::vector<std::vector<Edge>> edge;

    int findEdge(int from_ind, int to_num) const;
    int findVertex(int v_num) const;
};

/*!
    * Ввод графа через поток
    * @param in поток на чтение
    * @param graph объект класса Graph
    * @return поток на чтение
    * @note Формат ввода: "vertex:\n<кол-во вершин>\n<вершины через пробел>\n<NotWeight/Weight>\nedge:\n<кол-во ребер>\n<ребра: первая вторая вес(в зависимости от параметра NotWeight/Weight>"
*/
std::istream& operator>>(std::istream& in, Graph& graph);
/*!
    * Вывод графа через поток
    * @param in поток на запись
    * @param graph объект класса Graph
    * @return поток на запись
    * @note Формат ввода: "vertex:\n<кол-во вершин>\n<вершины через пробел>\nedge:\n<ребра: первая вторая вес(в зависимости от параметра NotWeight/Weight>"
*/
std::ostream& operator<<(std::ostream& out, Graph& graph);

#endif