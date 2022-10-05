#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>
#include <graph/graph.h>


TEST_CASE("init_simple") {
    Graph gr;
    CHECK(gr.Size() == 0);
}

TEST_CASE("init_simple") {
    std::vector<Edge> edges = {Edge(1, 2), Edge(1, 3)};
    Graph gr(edges);
    CHECK(gr.Size() == 3);

    std::vector<Edge> gr_edges = gr.AllEdges();
    CHECK(gr_edges.size() == edges.size());
    for (size_t i = 0; i < edges.size(); i++) {
        CHECK(gr_edges[i].from_vertex == edges[i].from_vertex);
        CHECK(gr_edges[i].other_vertex == edges[i].other_vertex);
        CHECK(gr_edges[i].weight == edges[i].weight);
    }
}

TEST_CASE("add_vertex") {
    Graph gr;
    int vertex = rand() % 100;
    gr.AddVertex(vertex);

    CHECK(gr.Size() == 1);

    std::vector<int> gr_vertex = gr.AllVertex();
    CHECK(gr_vertex[0] == vertex);
}

TEST_CASE("add_vertex_with_edges") {
    Graph gr;
    int vertex1 = rand() % 100;
    int vertex2 = rand() % 100;
    int vertex3 = rand() % 100;
    while (vertex1 >= vertex2) {
        vertex1 = rand() % 100;
    }
    while (vertex1 >= vertex3) {
        vertex1 = rand() % 100;
    }
    while (vertex3 <= vertex2) {
        vertex3 = rand() % 100;
    }

    gr.AddVertex(vertex1);
    gr.AddVertex(vertex2);
    CHECK(gr.Size() == 2);
    std::vector<int> edges_x = {vertex1, vertex2};
    gr.AddVertex(vertex3, edges_x);
    std::vector<Edge> edges = {Edge(vertex1, vertex3), Edge(vertex2, vertex3)};

    CHECK(gr.Size() == 3);

    std::vector<int> gr_vertex = gr.AllVertex();
    std::sort(gr_vertex.begin(), gr_vertex.end());
    CHECK(gr_vertex[0] == vertex1);
    CHECK(gr_vertex[1] == vertex2);
    CHECK(gr_vertex[2] == vertex3);

    std::vector<Edge> gr_edges = gr.AllEdges();
    CHECK(gr_edges.size() == edges.size());
    for (size_t i = 0; i < edges.size(); i++) {
        CHECK(gr_edges[i].from_vertex == edges[i].from_vertex);
        CHECK(gr_edges[i].other_vertex == edges[i].other_vertex);
        CHECK(gr_edges[i].weight == edges[i].weight);
    }
}

TEST_CASE("add_vertex_with_edges_and_weights") {
    Graph gr;
    int vertex1 = rand() % 100;
    int vertex2 = rand() % 100;
    int vertex3 = rand() % 100;
    while (vertex1 >= vertex2) {
        vertex1 = rand() % 100;
    }
    while (vertex1 >= vertex3) {
        vertex1 = rand() % 100;
    }
    while (vertex3 <= vertex2) {
        vertex3 = rand() % 100;
    }

    gr.AddVertex(vertex1);
    gr.AddVertex(vertex2);
    CHECK(gr.Size() == 2);
    std::vector<int> edges_x = {vertex1, vertex2};

    int weight1 = rand() % 100;
    int weight2 = rand() % 100;
    std::vector<int> edges_w = {weight1, weight2};
    gr.AddVertex(vertex3, edges_x, edges_w);
    std::vector<Edge> edges = {Edge(vertex1, vertex3, weight1), Edge(vertex2, vertex3, weight2)};

    CHECK(gr.Size() == 3);

    std::vector<int> gr_vertex = gr.AllVertex();
    std::sort(gr_vertex.begin(), gr_vertex.end());
    CHECK(gr_vertex[0] == vertex1);
    CHECK(gr_vertex[1] == vertex2);
    CHECK(gr_vertex[2] == vertex3);

    std::vector<Edge> gr_edges = gr.AllEdges();
    CHECK(gr_edges.size() == edges.size());
    for (size_t i = 0; i < edges.size(); i++) {
        CHECK(gr_edges[i].from_vertex == edges[i].from_vertex);
        CHECK(gr_edges[i].other_vertex == edges[i].other_vertex);
        CHECK(gr_edges[i].weight == edges[i].weight);
    }
}

TEST_CASE("remove_vertex") {
    Graph gr;
    int vertex1 = rand() % 100;
    int vertex2 = rand() % 100;
    int vertex3 = rand() % 100;
    while (vertex1 >= vertex2) {
        vertex1 = rand() % 100;
    }
    while (vertex1 >= vertex3) {
        vertex1 = rand() % 100;
    }
    while (vertex3 <= vertex2) {
        vertex3 = rand() % 100;
    }

    gr.AddVertex(vertex1);
    gr.AddVertex(vertex2);
    std::vector<int> edges_x = {vertex1, vertex2};

    int weight1 = rand() % 100;
    int weight2 = rand() % 100;
    std::vector<int> edges_w = {weight1, weight2};
    gr.AddVertex(vertex3, edges_x, edges_w);
    gr.RemoveVertex(vertex1);
    std::vector<Edge> edges = {Edge(vertex2, vertex3, weight2)};

    CHECK(gr.Size() == 2);

    std::vector<int> gr_vertex = gr.AllVertex();
    std::sort(gr_vertex.begin(), gr_vertex.end());
    CHECK(gr_vertex[0] == vertex2);
    CHECK(gr_vertex[1] == vertex3);

    std::vector<Edge> gr_edges = gr.AllEdges();
    CHECK(gr_edges.size() == edges.size());
    for (size_t i = 0; i < edges.size(); i++) {
        CHECK(gr_edges[i].from_vertex == edges[i].from_vertex);
        CHECK(gr_edges[i].other_vertex == edges[i].other_vertex);
        CHECK(gr_edges[i].weight == edges[i].weight);
    }
}

TEST_CASE("remove_edge") {
    Graph gr;
    int vertex1 = rand() % 100;
    int vertex2 = rand() % 100;
    int vertex3 = rand() % 100;
    while (vertex1 >= vertex2) {
        vertex1 = rand() % 100;
    }
    while (vertex1 >= vertex3) {
        vertex1 = rand() % 100;
    }
    while (vertex3 <= vertex2) {
        vertex3 = rand() % 100;
    }

    gr.AddVertex(vertex1);
    gr.AddVertex(vertex2);
    std::vector<int> edges_x = {vertex1, vertex2};

    int weight1 = rand() % 100;
    int weight2 = rand() % 100;
    std::vector<int> edges_w = {weight1, weight2};
    gr.AddVertex(vertex3, edges_x, edges_w);

    std::vector<Edge> edges1 = {Edge(vertex1, vertex3, weight1), Edge(vertex2, vertex3, weight2)};
    std::vector<Edge> gr_edges1 = gr.AllEdges();
    CHECK(gr_edges1.size() == edges1.size());
    for (size_t i = 0; i < edges1.size(); i++) {
        CHECK(gr_edges1[i].from_vertex == edges1[i].from_vertex);
        CHECK(gr_edges1[i].other_vertex == edges1[i].other_vertex);
        CHECK(gr_edges1[i].weight == edges1[i].weight);
    }

    gr.RemoveEdge(vertex3, vertex1);
    std::vector<Edge> edges = {Edge(vertex2, vertex3, weight2)};

    CHECK(gr.Size() == 3);

    std::vector<int> gr_vertex = gr.AllVertex();
    std::sort(gr_vertex.begin(), gr_vertex.end());
    CHECK(gr_vertex[0] == vertex1);
    CHECK(gr_vertex[1] == vertex2);
    CHECK(gr_vertex[2] == vertex3);

    std::vector<Edge> gr_edges = gr.AllEdges();
    CHECK(gr_edges.size() == edges.size());
    for (size_t i = 0; i < edges.size(); i++) {
        CHECK(gr_edges[i].from_vertex == edges[i].from_vertex);
        CHECK(gr_edges[i].other_vertex == edges[i].other_vertex);
        CHECK(gr_edges[i].weight == edges[i].weight);
    }
}

TEST_CASE("MST") {
    std::vector<Edge> edges = {Edge(1, 2, 1),
                               Edge(1, 3, 7),
                               Edge(1, 4, 7),
                               Edge(2, 4, 1),
                               Edge(3, 4, 1)};
    Graph gr(edges);
    CHECK(gr.Size() == 4);

    std::vector<Edge> gr_edges = gr.AllEdges();
    CHECK(gr_edges.size() == edges.size());
    for (size_t i = 0; i < edges.size(); i++) {
        CHECK(gr_edges[i].from_vertex == edges[i].from_vertex);
        CHECK(gr_edges[i].other_vertex == edges[i].other_vertex);
        CHECK(gr_edges[i].weight == edges[i].weight);
    }

    Graph mstGraph = gr.FindMST();
    std::vector<Edge> edges_MST = {Edge(1, 2, 1),
                               Edge(2, 4, 1),
                               Edge(3, 4, 1)};
    CHECK(mstGraph.Size() == 4);

    std::vector<Edge> gr_edges_mst = mstGraph.AllEdges();
    CHECK(gr_edges_mst.size() == edges_MST.size());
    for (size_t i = 0; i < edges_MST.size(); i++) {
        CHECK(gr_edges_mst[i].from_vertex == edges_MST[i].from_vertex);
        CHECK(gr_edges_mst[i].other_vertex == edges_MST[i].other_vertex);
        CHECK(gr_edges_mst[i].weight == edges_MST[i].weight);
    }
}
