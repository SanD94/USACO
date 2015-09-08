#include <stdio.h>

/* maximum number of segments */
#define MAXS 100

/* an edge is a fence segment */
/* a place is a side of a fence segment */
/* there are two places for each edge */

/* conn is the index of the incident edge */
/* alist is the index of the incident place */

int conn[2*MAXS][8]; /* one edge list for each side of each segment */
int ccnt[2*MAXS]; /* number of incident edges */
int length[MAXS]; /* length of the segments */

int alist[2*MAXS][8]; /* adjacency list for each end of each segment */

int nfence; /* numbor of fences */
int npl; /* number of places */

int dist[2*MAXS]; /* distance to each place */

/* heap data structure */
int heap[2*MAXS]; 
int hsize;
int hloc[2*MAXS]; /* location within heap of each place */

/* debugging routine */
/* ensure heap order has been maintained */
void check_heap(void) {
    int lv;

    for (lv = 1; lv < hsize; lv++) {
        if (dist[heap[lv]] < dist[heap[(lv-1)/2]]) {
            fprintf (stderr, "HEAP ERROR!\n");
            return;
        }
    }
}

/* delete the minimum item from the heap */
void delete_min(void) {
    int loc, val;
    int p, t;

    /* remove last item in the heap array */
    loc = heap[--hsize];
    val = dist[loc];
    p = 0;

    while (2*p+1 < hsize) {
        /* find smaller child */
        t = 2*p+1;
        if (t+1 < hsize && dist[heap[t+1]] < dist[heap[t]]) t++;

        /* if child less than the removed item, move child up */
        if (dist[heap[t]] < val) {
            heap[p] = heap[t];
            hloc[heap[p]] = p;
            p = t;
        } else break; /* otherwise, put removed item here */
    }

    /* put removed item back into the heap */
    heap[p] = loc;
    hloc[loc] = p;
    check_heap(); /* sanity check */
}

void update(int loc) { /* we've decreased the value of dist[loc] */
    /* change heap to maintain heap order */
    int val;
    int p, t;

    val = dist[loc];
    p = hloc[loc];
    while (p > 0) { /* while the element's not the root of the heap */

        /* check to see if it's less than it's parent */
        t = (p-1)/2;
        if (dist[heap[t]] > val) { /* if so, move parent down */
            heap[p] = heap[t];
            hloc[heap[p]] = p;

            /* consider as if updated element is now in parent's prev location */
            p = t;
        } else break; /* otherwise, stop */
    }

    /* put element in proper location in heap */
    heap[p] = loc;
    hloc[loc] = p;
    check_heap(); /* sanity check */
}

void add_heap(int loc) { /* add an element to the heap */

     if (hloc[loc] == -1) { /* if it's not in the heap, add to the end (eff value = infinity) */
         heap[hsize++] = loc;
         hloc[loc] = hsize-1;
     }


     /* change the value to the real value */
     update(loc);
}


void fill_dist(int s) {
    int lv;
    int p;
    int t;
    int l;

    /* initialize hloc & dist */
    for (lv = 0; lv < npl; lv++) { hloc[lv] = -1; dist[lv] = 255*MAXS + 1; }
    dist[s] = 0;
    hsize = 0;
    add_heap(s);

    while (hsize) { /* heap is not empty */

        /* take minimum distance location */
        p = heap[0];
        delete_min();
        t = dist[p];

        /* try all possible endpoints of other edges at the same location */
        for (lv = 0; lv < ccnt[p]; lv++) {
            l = alist[p][lv];
            if (dist[l] > t) { /* found better distance */
                dist[l] = t;
                add_heap(l); /* add, if necessary, update otherwise */
            }
        }

        /* consider moving across this edge */
        t = dist[p] + length[p/2]; 
        p = p ^ 0x1; /* go to the other endpoint */
        if (dist[p] > t) { /* found a better way to get to the location */
            dist[p] = t;
            add_heap(p);
        }
    }
}

int main(int argc, char **argv) {
    FILE *fout, *fin;
    int lv, lv2, lv3;
    int c1, c2;
    int segid, len;
    int p;
    int min;

    if ((fin = fopen("fence6.in", "r")) == NULL) {
        perror ("fopen fin");
        exit(1);
    }
    if ((fout = fopen("fence6.out", "w")) == NULL) {
        perror ("fopen fout");
        exit(1);
    }

    fscanf (fin, "%d\n", &nfence);
    npl = nfence*2;

    for (lv = 0; lv < nfence; lv++) { /* read in edges */
        fscanf (fin, "%d %d %d %d", &segid, &len, &c1, &c2);
        segid--;
        length[segid] = len;
        ccnt[2*segid] = c1;
        ccnt[2*segid+1] = c2;
        while (c1--) {
            fscanf (fin, "%d", &p);
            conn[2*segid][c1] = p-1;
        }
        while (c2--) {
            fscanf (fin, "%d", &p);
            conn[2*segid+1][c2] = p-1;
        }
    }

    for (lv = 0; lv < npl; lv++)
        for (lv2 = 0; lv2 < ccnt[lv]; lv2++) { /* for all edges */
            c1 = lv/2;
            c2 = conn[lv][lv2]*2;

            /* find other occurance of edge */
            for (lv3 = 0; lv3 < ccnt[c2]; lv3++)
                if (conn[c2][lv3] == c1)
                    break;

            /* if no match was found, must be on 'other' side of edge */
            if (lv3 >= ccnt[c2]) c2++;

            /* update adjaceny list */
            alist[lv][lv2] = c2;
        }

    min = 255*MAXS+1; /* higher than we could ever see */

    for (lv = 0; lv < nfence; lv++) { /* for each fence */

        /* make edge infinite length, to ensure it's not used */
        len = length[lv];
        length[lv] = 255*MAXS+1; 

        /* find distance from one end-point of edge to the other */
        fill_dist(2*lv);

        /* if the cycle (the path plus the edge deleted) is better
           than the best found so far, update min */
        if (dist[2*lv+1] + len < min)
            min = dist[2*lv+1] + len; 

        /* put edge back in */
        /* actually, not necessary, since we've already found the
           best cycle which uses this edge */
        length[lv] = len;
    }

    fprintf (fout, "%i\n", min);
    return 0;
}

