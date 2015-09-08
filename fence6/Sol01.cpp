#include <fstream.h>

const int Inf = 1000 * 1000 * 1000;

ifstream in ("fence6.in");
ofstream out ("fence6.out");

/* The edges are one-way so two edges are neccesary for each fence segment. */

struct Edge {
    Edge () { }
    Edge (int _to, int _dist):to (_to), dist (_dist) { }
    int     to, dist;
}       edges[100][8];		/* edges[x][y] = edge number y of node
                               number x */
int     edgeCo[100];		/* edgeCo[x]   = number of edges that
                               connect at node x */
int     nodeCo = 0;		/* total number of nodes */

/*
 * Each node is given a signature consisting of the two largest fence
 * segment IDs of all the fence segments that connect at that node
 */

int     sigs[100][2];		/* sigs[x] = signature of node x.
                               sigs[x][0] > sigs[x][1] */

    void 
AddEdge (int from, const Edge & edge)
{
    edges[from][edgeCo[from]++] = edge;
}

/* Returns the removed edge */
    Edge 
RemoveEdge (int from, int to)
{
    int     i;
    for (i = 0; i < edgeCo[from]; ++i) {
        if (edges[from][i].to == to) {
            Edge    tmp = edges[from][i];
            edges[from][i] = edges[from][--edgeCo[from]];
            return tmp;
        }
    }
}

/*
 * The segs parameter is an array of length len that contains the IDs of the
 * fence segments that meet at the sought-for node.
 */

int 
GetNode (int *segs, int len) {
    /* The signature of the node is calculated by retriving the two largets
       fence segment IDs */
    int     i, max0 = 0, max1 = 0;
    for (i = 0; i < len; ++i) {
        if (segs[i] > max1) {
            if (segs[i] > max0) {
                max1 = max0;
                max0 = segs[i];
            }
            else
                max1 = segs[i];
        }
    }

    /* The known signatures are searched. If a matching signature is found,
       the corresponding node is returned */
    for (i = 0; i < nodeCo; ++i)
        if (max0 == sigs[i][0] && max1 == sigs[i][1])
            return i;

    /* A signature could not be made, so we will have to create a new node
       with that signature. This node is then returned */
    sigs[nodeCo][0] = max0;
    sigs[nodeCo][1] = max1;

    return nodeCo++;
}

/* This function returns length of the shortest path between the passed-in
   nodes.
   Paths of length equal to or larger than lessThan are not considered.
   It is not guaranteed that the graph is connected.
   If no suitable path is found, Infinity is returned
   */
int 
CalcShortestPath (int from, int to, int lessThan) {
    bool    visited[100];
    int     dist[100];

    int     i;
    for (i = 0; i < nodeCo; ++i)
        visited[i] = false, dist[i] = Inf;

    visited[from] = true;
    dist[from] = 0;
    int     lastVisited = from;

    for (;;) {
        int     j;
        for (j = 0; j < edgeCo[lastVisited]; ++j) {
            const   Edge & edge = edges[lastVisited][j];
            int     d = dist[lastVisited] + edge.dist;
            if (d < lessThan && dist[edge.to] > d)
                dist[edge.to] = d;
        }

        int     minDist = Inf;
        for (j = 0; j < nodeCo; ++j)
            if (!visited[j] && minDist > dist[j])
                lastVisited = j, minDist = dist[j];

        if (minDist == Inf)
            break;

        visited[lastVisited] = true;
    }

    return dist[to];
}

    void 
ReadArray (int *arr, int len, istream & in)
{
    int     i;
    for (i = 0; i < len; ++i)
        in >> arr[i];
}

int 
main () {
    int     segCo;
    in >> segCo;

    int     i;
    for (i = 0; i < segCo; ++i) {
        int     dist, co1, co2, segs[9];
        in >> segs[0] >> dist >> co1 >> co2;

        ReadArray (segs + 1, co1, in);
        int     node1 = GetNode (segs, co1 + 1);

        ReadArray (segs + 1, co2, in);
        int     node2 = GetNode (segs, co2 + 1); AddEdge (node1, Edge (node2, dist)); AddEdge (node2, Edge (node1, dist));
    }

    /*
     * For each node, the smallest perimeter that includes that node is
     * calculated. After each calculation, that node is deleted, as no smaller
     * perimeter can possibly include that node (we already got the smallest
     * one).
     */
    int     minPerim = Inf;
    while (nodeCo != 0) {
        int     node = nodeCo - 1;

        /* Nodes and therefore edges are continually removed, so there might be
           some nodes with less than 2 edges. Such nodes obviously cannot be
           part of any perimeter. */
        if (edgeCo[node] > 1) {
            /* The minimal perimeter that includes the node is calculated */
            for (i = 0; i < edgeCo[node]; ++i) {
                int     otherNode = edges[node][i].to;

                Edge    out = RemoveEdge (node, otherNode);
                Edge    in = RemoveEdge (otherNode, node);

                int     perim = out.dist + CalcShortestPath (node,
                        otherNode, minPerim - out.dist);

                if (minPerim > perim)
                    minPerim = perim;

                AddEdge (node, out);
                AddEdge (otherNode, in);
            }
        }

        /* The node is deleted by deleting all edges to it and decreasing
           nodeCo, so that the current node "falls of the edge" of the now
           smaller edges array */
        for (i = 0; i < edgeCo[node]; ++i)
            RemoveEdge (edges[node][i].to, node);
        --nodeCo;
    }

    out << minPerim << '\n';

    return 0;
}
