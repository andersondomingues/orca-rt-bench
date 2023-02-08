from random import randint
from rtbench.modeling.graph import Graph, GraphNode


def test_graph_ctor():
    graph = Graph()
    assert len(graph._edges) == 0
    assert len(graph._nodes) == 0


def test_graph_get_set_nodes():
    graph = Graph()
    assert len(graph.get_nodes()) == len(graph._nodes)
    assert len(graph.get_nodes()) == 0
    graph.add_node(GraphNode(""))
    assert len(graph.get_nodes()) == len(graph._nodes)
    assert len(graph.get_nodes()) == 1
    graph.remove_node(GraphNode(""))
    assert len(graph.get_nodes()) == len(graph._nodes)
    assert len(graph.get_nodes()) == 0


def test_graph_get_edges():
    graph = Graph()
    assert len(graph.get_edges()) == len(graph._edges)
    assert len(graph.get_edges()) == 0
    graph.add_edge(GraphNode(randint(0, 10)), GraphNode(randint(0, 10)))
    assert len(graph.get_edges()) == len(graph._edges)
    assert len(graph.get_edges()) == 1
    graph.remove_edge(GraphNode(randint(0, 10)), GraphNode(randint(0, 10)))
    assert len(graph.get_edges()) == len(graph._edges)
    assert len(graph.get_edges()) == 0


def test_graph_node():
    node = GraphNode(randint(0, 10))
    assert node._data == node.get_data()
