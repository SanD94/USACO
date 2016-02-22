#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define NAME "starry"
/* MAXSTAR is the largest a cluster can be */
#define MAXSTAR 160

/* the board */
char board[100][100];
int w, h;

/* clusters already lettered */
int stars[26][MAXSTAR]; /* stars are stored as xval + yval*1000 */
int count[26]; /* number of stars */
int size[26][2]; /* the x & y dimensions */
int nstart; /* number of clusters */

/* the current cluster */
int current[MAXSTAR][2]; /* y, x */
int ncurrent; /* number of stars in current cluster */

/* int_comp is integer comparison, used for bsearch and qsort */
int int_comp(const void *pa, const void *pb) {
    int a = *(int*)pa;
    int b = *(int*)pb;
    if (a > b) return 1;
    else if (a < b) return -1;
    else return 0;
}

/* check boundaries */
bool is_good(int x, int y){
    if(x < 0 || x >= w || y < 0 || y >= h) return 0;
    return 1;
}
/* find the boundary (in my,mx,My, and Mx.. m is minimum, M is maximum */
/* also fills in current */
int find_boundary(int y, int x, int *my, int *mx, int *My, int *Mx) {
    int rv = 0;
    if (board[y][x] != '1') return 0; /* not a star or already visited */
    rv++; /* one more star */
    board[y][x] = '2'; /* mark as visited */
    /* put in current cluster */
    current[ncurrent][0] = y;
    current[ncurrent][1] = x;
    ncurrent++;
    /* update boundary */
    if (y < *my) *my = y;
    if (y > *My) *My = y;
    if (x < *mx) *mx = x;
    if (x > *Mx) *Mx = x;
    /* check all adjacent stars */
    for(int i=-1;i<2;i++)
	for(int j=-1;j<2;j++){
	    int nx = x+i;
	    int ny = y+j;
	    if(is_good(nx,ny))
		rv += find_boundary(ny, nx, my, mx, My, Mx);
	}
    return rv;
}

/* this is a very basic flood fill...fill ch everywhere there's not a '0' */
void mark_shape(int y, int x, char ch) {
    if (board[y][x] == ch) return; /* done already */
    if (board[y][x] == '0') return; /* nothing to do */
    board[y][x] = ch;
    /* recurse on all boundary stars */
    for(int i=-1;i<2;i++)
	for(int j=-1;j<2;j++){
	    int nx = x+i;
	    int ny = y+j;
	    if(is_good(nx,ny))
		mark_shape(ny, nx, ch);
	}
}

/* is shape id the same as the current shape */
/* specify the orientation with dy/dx and by/bx */
/* dy/dx is the difference value to associate with y and x changes */
/* by/bx is the upper right corner of the bounding box with respect
   to the current orientation */
/* NOTE: assumes that the number of stars are the same */
int check_shape(int id, int dy, int dx, int by, int bx) {
    int lv;
    int pval;
    for (lv = 0; lv < ncurrent; lv++) {
	pval = (current[lv][0]-by)*dy + (current[lv][1]-bx)*dx;
	if (!bsearch(&pval, stars[id], count[id], sizeof(stars[id][0]), int_comp))
	    return 0; /* found a star that didn't match */
    }
    return 1;
}

/* we found a star here, make it a cluster */
void fix_board(int y, int x) {
    int mx, my, Mx, My;
    int cnt;
    int lv;
    int pw, ph;
    int f;
    /* gather the cluster information */
    mx = Mx = x;
    my = My = y;
    ncurrent = 0;
    cnt = find_boundary(y, x, &my, &mx, &My, &Mx);
    pw = Mx - mx + 1;
    ph = My - my + 1;
    f = 0;
    int cs[][2] = {{1000,1}, {1000, -1}, {-1000,1}, {-1000, -1},
	{1, 1000}, {1, -1000}, {-1, 1000}, {-1, -1000}};
    int ps[][2] = {{my, mx}, {my, Mx}, {My, mx}, {My,Mx},
	{my,mx}, {my,Mx}, {My,mx}, {My,Mx}};
    /* check each cluster */
    for (lv = 0; lv < nstart; lv++)
	if (cnt == count[lv]) /* the cluster must have the same # of stars */ {
	    if ((pw == size[lv][1] && ph == size[lv][0]) ||
		    (pw == size[lv][0] && ph == size[lv][1]))  /* the bounding box sizes match */
		for(int i=0;i<8 && !f;i++)
		    f+= check_shape(lv, cs[i][0], cs[i][1], ps[i][0], ps[i][1]);
	    if (f) break;
	}
    if (f) mark_shape(y, x, 'a' + lv); /* found match */
    else { /* new cluster! */
	count[nstart] = 0;
	mark_shape(y, x, 'a' + nstart);
	for (lv = 0; lv < ncurrent; lv++)
	    stars[nstart][lv] = (current[lv][0]-my)*1000 + (current[lv][1]-mx);
	count[nstart] = ncurrent;
	/* we need the stars in increasing order */
	qsort(stars[nstart], count[nstart], sizeof(stars[nstart][0]), int_comp);
	size[nstart][0] = ph;
	size[nstart][1] = pw;
	nstart++;
    }
}


int main(int argc, char **argv) {
    FILE *fin, *fout;
    int lv, lv2;
    fin = fopen(NAME ".in", "r");
    fout = fopen(NAME ".out", "w");
    /* read in the data */
    fscanf (fin, "%d %d", &w, &h);
    for (lv = 0; lv < h; lv++) fscanf (fin, "%s", board[lv]);
    fclose(fin);
    /* everywhere there's a star not in a cluster, make it into one */
    for (lv = 0; lv < h; lv++)
	for (lv2 = 0; lv2 < w; lv2++)
	    if (board[lv][lv2] == '1')
		fix_board(lv, lv2);
    /* output data */
    for (lv = 0; lv < h; lv++) {
	for(lv2 = 0; lv2 < w; lv2++)
	    fprintf (fout, "%c", board[lv][lv2]);
	fprintf (fout, "\n");
    }
    fclose(fout);
    return 0;
}


