#include "graph.h"

/*!
    \brief Вспомогательный класс Set непересекающихся множеств для эффективной реализации алгоритма Краскала.
    \details Каждый объект класса  Set хранит в себе следующую информацию:
    * root - указатель на Set, который является корневым для поддерева
    * rank - высота поддерева
*/
class Set {
public:
    /*!
     * Создает объект класса Set для одной вершины
     * @param ind номер вершины
     */
    void MakeSet(const size_t& ind) {
        this->root = this;
        this->rank = 0;
    }

    /*!
     * Объединяет множество с другим
     * @param other указатель на другой объект класса Set
     */
    void Union(Set* other) {
        this->FindSet()->Link(other->FindSet());
    }

    /*!
     * Определяет к какому множеству относится поддерево
     * @return Возвращает указатель на объект класса Set, который является корневым для поддерева
     */
    Set* FindSet() {
        if (this != this->root) {
            this->root = this->root->FindSet();
        }
        return this->root;
    }
private:
    void Link(Set* other) {
        if (this->rank > other->rank) {
            other->root = this;
        } else {
            this->root = other;
            if (this->rank == other->rank) {
                other->rank += 1;
            }
        }
    }

    Set* root;
    size_t rank;
};


Graph Graph::FindMST() { // поиск минимального остовного дерева, вернет его в виде графа
    // внутри функции связка индекса и номера вершины не изменяется, поэтому создадим map, чтобы узнавать индекс вершины за O(1)
    std::map<int,size_t> ind_num;
    for (size_t i = 0; i < this->vertex.size(); i++) {
        ind_num[this->vertex[i]] = i;
    }

    // сначала сделаем общий массив ребер, чтобы иметь возможность его отсортировать по весу ребер
    int edge_cnt = 0;
    for (size_t i = 0; i < this->edge.size(); i++) {
        edge_cnt += this->edge[i].size();
    }
    edge_cnt /= 2;

    std::vector<Edge> all_edges(edge_cnt);
    int k = 0;
    std::sort(this->vertex.begin(), this->vertex.end());
    for (size_t i = 0; i < this->vertex.size(); i++) {
        for (size_t j = 0; j < this->edge[i].size(); j++) {
            if (this->vertex[i] < this->edge[i][j].other_vertex) {
                this->edge[i][j].from_vertex = this->vertex[i];
                all_edges[k++] = this->edge[i][j];
            }
        }
    }

    // теперь отсортируем полученный массив по весам ребер
    std::sort(all_edges.begin(), all_edges.end(), [](Edge a, Edge b) {
        return a.weight < b.weight;
    });

    // далее выполняем алгоритм
    std::vector<Set> sets(this->Size());

    // для каждой вершины создаем отдельный граф
    for (size_t i = 0; i < this->Size(); i++) {
        sets[i].MakeSet(i);
    }

    // по возрастанию веса ребер начинаем объединять графы
    std::vector<Edge> mstEdge;
    for (auto& edge : all_edges) {
        int ind1 = ind_num[edge.from_vertex];
        int ind2 = ind_num[edge.other_vertex];

        if (sets[ind1].FindSet() != sets[ind2].FindSet()) {
            mstEdge.push_back(edge);
            sets[ind1].Union(&sets[ind2]);
        }
    }
    Graph result(mstEdge);

    return result;
}

