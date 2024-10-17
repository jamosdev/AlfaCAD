/*         ______   ___    ___
 *        /\  _  \ /\_ \  /\_ \ 
 *        \ \ \L\ \\//\ \ \//\ \      __     __   _ __   ___ 
 *         \ \  __ \ \ \ \  \ \ \   /'__`\ /'_ `\/\`'__\/ __`\
 *          \ \ \/\ \ \_\ \_ \_\ \_/\  __//\ \L\ \ \ \//\ \L\ \
 *           \ \_\ \_\/\____\/\____\ \____\ \____ \ \_\\ \____/
 *            \/_/\/_/\/____/\/____/\/____/\/___L\ \/_/ \/___/
 *                                           /\____/
 *                                           \_/__/
 *
 *      The 2d polygon rasteriser.
 *
 *      By Shawn Hargreaves
 *      Altered by Marek Ratajczak 2024 for AlfaCAD
 *
 *      See readme.txt for copyright information.
 */


#include <limits.h>

#include "allegro.h"
#include "allegro/internal/aintern.h"

extern void set_mode_trans();

typedef struct
{
	int x1;
	int x2;
	int y;
} LAST_EDGE;

#define EDGE_LOG_NO 4

static LAST_EDGE last_edge[EDGE_LOG_NO] = {0};


typedef struct
{
	int borderm;
	int paperm;
	int inkm;

	int cur;
	int blok;
	int border;
	int paper;
	int ink;
	int paperk;
	int inkk;
	int paperk_ini;
	int inkk_ini;

	int dlg_border;
	int dlg_paper;
	int dlg_label;
	int dlg_in_line_border;
	int dlg_in_line_ink;
	int dlg_in_line_paper;
	int dlg_button_ink;
	/*   int dlg_button_paper;
	   int dlg_button_border;
	*/
} KOLORY;

extern KOLORY kolory;

extern unsigned char _dac_normal[256][3];

typedef int64_t myfixed;

/* information for polygon scanline fillers */
typedef struct MY_POLYGON_SEGMENT
{
	myfixed u, v, du, dv;              /* fixed point u/v coordinates */
	myfixed c, dc;                     /* single color gouraud shade values */
	myfixed r, g, b, dr, dg, db;       /* RGB gouraud shade values */
	float z, dz;                     /* polygon depth (1/z) */
	float fu, fv, dfu, dfv;          /* floating point u/v coordinates */
	unsigned char* texture;          /* the texture map */
	int umask, vmask, vshift;        /* texture map size information */
	int seg;                         /* destination bitmap selector */
	uintptr_t zbuf_addr;		    /* Z-buffer address */
	uintptr_t read_addr;		    /* reading address for transparency modes */
} MY_POLYGON_SEGMENT;

typedef struct MY_POLYGON_EDGE
{
	int top;                         /* top y position */
	int bottom;                      /* bottom y position */
	myfixed x, dx;                     /* fixed point x position and gradient */
	myfixed w;                         /* width of line segment */
	MY_POLYGON_SEGMENT dat;             /* texture/gouraud information */
	struct MY_POLYGON_EDGE* prev;       /* doubly linked list */
	struct MY_POLYGON_EDGE* next;
	struct MY_POLYGON_INFO* poly;	    /* father polygon */
} MY_POLYGON_EDGE;

typedef struct MY_POLYGON_INFO         /* a polygon waiting rendering */
{
	struct MY_POLYGON_INFO* next, * prev;/* double linked list */
	int inside;                      /* flag for "scanlining" */
	int flags;                       /* INTERP_* flags */
	int color;                       /* vtx[0]->c */
	float a, b, c;                   /* plane's coefficients -a/d, -b/d, -c/d */
	int dmode;                       /* drawing mode */
	BITMAP* dpat;                    /* drawing pattern */
	int xanchor, yanchor;            /* for dpat */
	int alpha;                       /* blender alpha */
	int b15, b16, b24, b32;          /* blender colors */
	COLOR_MAP* cmap;                 /* trans color map */
	SCANLINE_FILLER drawer;	    /* scanline drawing functions */
	SCANLINE_FILLER alt_drawer;
	MY_POLYGON_EDGE* left_edge;	    /* true edges used in interpolation */
	MY_POLYGON_EDGE* right_edge;
	MY_POLYGON_SEGMENT info;            /* base information for scanline functions */
} MY_POLYGON_INFO;

/* fill_edge_structure:
 *  Polygon helper function: initialises an edge structure for the 2d
 *  rasteriser.
 */
static void fill_edge_structure__(POLYGON_EDGE *edge, AL_CONST int *i1, AL_CONST int *i2)
{
   if (i2[1] < i1[1]) {
      AL_CONST int *it;

      it = i1;
      i1 = i2;
      i2 = it;
   }

   edge->top = i1[1];
   edge->bottom = i2[1];
   edge->x = (i1[0] << POLYGON_FIX_SHIFT) + (1 << (POLYGON_FIX_SHIFT-1));
   if (i2[1] != i1[1]) {
      edge->dx = ((i2[0] - i1[0]) << POLYGON_FIX_SHIFT) / (i2[1] - i1[1]);
   }
   else {
      edge->dx = ((i2[0] - i1[0]) << POLYGON_FIX_SHIFT) << 1;
   }     
   edge->w = MAX(ABS(edge->dx)-1, 0);
   edge->prev = NULL;
   edge->next = NULL;
   if (edge->dx < 0)
      edge->x += edge->dx/2 ;
}



/* _add_edge:
 *  Adds an edge structure to a linked list, returning the new head pointer.
 */
MY_POLYGON_EDGE *my_add_edge(MY_POLYGON_EDGE *list, MY_POLYGON_EDGE *edge, int sort_by_x)
{
   MY_POLYGON_EDGE *pos = list;
   MY_POLYGON_EDGE *prev = NULL;

   if (sort_by_x) {
      while ((pos) && (pos->x < edge->x)) {  //<
	 prev = pos;
	 pos = pos->next;
      }
   }
   else {
      while ((pos) && (pos->top < edge->top)) { // <
	 prev = pos;
	 pos = pos->next;
      }
   }

   edge->next = pos;
   edge->prev = prev;

   if (pos)
      pos->prev = edge;

   if (prev) {
      prev->next = edge;
      return list;
   }
   else
      return edge;
}



/* _remove_edge:
 *  Removes an edge structure from a list, returning the new head pointer.
 */
MY_POLYGON_EDGE *my_remove_edge(MY_POLYGON_EDGE *list, MY_POLYGON_EDGE *edge)
{
   if (edge->next) 
      edge->next->prev = edge->prev;

   if (edge->prev) {
      edge->prev->next = edge->next;
      return list;
   }
   else
      return edge->next;
}


void my_grow_scratch_mem(int size)
	{
	   if (size > _scratch_mem_size) {
		  size = (size + 1023) & 0xFFFFFC00;
		  _scratch_mem = _AL_REALLOC(_scratch_mem, size);
		  _scratch_mem_size = size;
	   }
	}

/* fill_edge_structure:
 *  Polygon helper function: initialises an edge structure for the 2d
 *  rasteriser.
 */
static void my_fill_edge_structure(MY_POLYGON_EDGE* edge, AL_CONST int* i1, AL_CONST int* i2)
{
	if (i2[1] < i1[1]) {
		AL_CONST int* it;

		it = i1;
		i1 = i2;
		i2 = it;
	}

	edge->top = i1[1];
	edge->bottom = i2[1];
	edge->x = ((myfixed)i1[0] << POLYGON_FIX_SHIFT) + (1 << (POLYGON_FIX_SHIFT - 1));
	if (i2[1] != i1[1]) {
		edge->dx = ((myfixed)(i2[0] - i1[0]) << POLYGON_FIX_SHIFT) / (myfixed)(i2[1] - i1[1]);
	}
	else {
		edge->dx = ((myfixed)(i2[0] - i1[0]) << POLYGON_FIX_SHIFT) << 1;
	}
	edge->w = MAX(ABS(edge->dx) - 1, 0);
	edge->prev = NULL;
	edge->next = NULL;
	if (edge->dx < 0)
		edge->x += edge->dx / 2;
}

void update_edge(int x1, int y, int x2)
{
	int i;
	for (i = EDGE_LOG_NO; i > 0; i--)
		memmove(&last_edge[i], &last_edge[i - 1], sizeof(LAST_EDGE));
	last_edge[0].x1 = x1;
	last_edge[0].y = y;
	last_edge[0].x2 = x2;
}

int compare_edges(int x1, int y, int x2)
{
	int i;
	int count = 0;
	for (i = 0; i < EDGE_LOG_NO; i++)
	{
		if ((x1 != last_edge[i].x1) || (y != last_edge[i].y) || (x2 != last_edge[i].x2))
			count++;
		if ((x2 != last_edge[i].x1) || (y != last_edge[i].y) || (x1 != last_edge[i].x2))
			count++;
	}
	if (count == 2*EDGE_LOG_NO) return 1;
	else return 0;
}



/* polygon:
 *  Draws a filled polygon with an arbitrary number of corners. Pass the 
 *  number of vertices, then an array containing a series of x, y points 
 *  (a total of vertices*2 values).
 */

void my_soft_polygon(BITMAP* bmp, int vertices, AL_CONST int* points, int color, int translucency, int colorB)
{
	int c;
	int top = INT_MAX;
	int bottom = INT_MIN;
	AL_CONST int* i1, * i2;
	MY_POLYGON_EDGE* edge, * next_edge;
	MY_POLYGON_EDGE* active_edges = NULL;
	MY_POLYGON_EDGE* inactive_edges = NULL;
	ASSERT(bmp);
	//int kolor256, color1;
	int r, g, b; // , r1, g1, b1;
	int edging;
	int translucency_;
    int color1;

    //return;

  	r = getr32(color);
	g = getg32(color);
	b = getb32(color);


	//kolor256 = GetColorAC(colorB);

	//r1 = _dac_normal[kolor256][0] << 2;
	//g1 = _dac_normal[kolor256][1] << 2;
	//b1 = _dac_normal[kolor256][2] << 2;

	//color1 = makeacol32(r1, g1, b1, 255);

	/* allocate some space and fill the edge table */
	my_grow_scratch_mem(sizeof(MY_POLYGON_EDGE) * vertices);

	edge = (MY_POLYGON_EDGE*)_scratch_mem;
	i1 = points;
	i2 = points + (vertices - 1) * 2;

	for (c = 0; c < vertices; c++) {
		my_fill_edge_structure(edge, i1, i2);

		if (edge->bottom >= edge->top) {

			if (edge->top < top)
				top = edge->top;

			if (edge->bottom > bottom)
				bottom = edge->bottom;

			inactive_edges = my_add_edge(inactive_edges, edge, FALSE);
			edge++;
		}

		i2 = i1;
		i1 += 2;
	}

	if (bottom >= bmp->cb)
		bottom = bmp->cb - 1;

	acquire_bitmap(bmp);

	/* for each scanline in the polygon... */
	for (c = top; c < bottom; c++) {    //<=
		int hid = 0;
		int b1 = 0;
		int e1 = 0;
		int up = 0;
		int draw = 0;
		int e;

		int diff_edge;


		/* check for newly active edges */
		edge = inactive_edges;
		while ((edge) && (edge->top == c)) {
			next_edge = edge->next;
			inactive_edges = my_remove_edge(inactive_edges, edge);
			active_edges = my_add_edge(active_edges, edge, TRUE);
			edge = next_edge;
		}

		/* draw horizontal line segments */
		edge = active_edges;
		while (edge) {
			e = edge->w;
			if (edge->bottom != c) {
				up = 1 - up;
			}
			else {
				e = edge->w >> 1;
			}

			if (edge->top == c) {
				e = edge->w >> 1;
			}

			if ((draw < 1) && (up >= 1)) {
				b1 = (edge->x + e) >> POLYGON_FIX_SHIFT;
			}
			else if (draw >= 1) {
				/* filling the polygon */
				e1 = edge->x >> POLYGON_FIX_SHIFT;
				hid = MAX(hid, b1 + 1);

				//if (hid <= e1 - 1) 
				if (hid <= e1)
				{
					color1 = color;
					if (translucency < 255)
					{
						////set_difference_blender(r, g, b, translucency);
						//set_mode_trans();

						//bmp->vtable->hfill(bmp, hid, c, e1 - 1, colorB);
						////bmp->vtable->hfill(bmp, hid-1, c, e1, colorB);

						///set_trans_blender(r, g, b, (int)translucency);
						//set_mode_trans();

						if (bmp->vtable->color_depth > 8) {

							set_trans_blender(0, 0, 0, (int)translucency);
							color1 = color;
							set_mode_trans();

						}
						else
						{
							color1 = color & 0x0000FF;
							double tf = translucency;
							tf /= 255.0;
							color1 = (color1 + tf * (255 - color1));
							if (color1 > 255) color1 = 255;
							solid_mode();
						}
					}
			

                    //bmp->vtable->hfill(bmp, hid, c, e1 - 1, color1);
                    bmp->vtable->hfill(bmp, hid, c, e1, color1);

					////set_trans_blender(0, 0, 0, (int)translucency);
					//set_mode_trans();

				}

				b1 = (edge->x + e) >> POLYGON_FIX_SHIFT;
			}

			/* drawing the edge */
			hid = MAX(hid, edge->x >> POLYGON_FIX_SHIFT);
			if (hid < ((edge->x + e) >> POLYGON_FIX_SHIFT)) {  //<=

				if (translucency == 255) diff_edge = 1;
				else
				{
					if ((c == edge->top) || (c == edge->bottom)) diff_edge = 1;
					else
					{
						//if (hid != ((edge->x + e) >> POLYGON_FIX_SHIFT))
						//	diff_edge = 0;
						//else diff_edge = 1;
						//edging=(edge->x >> POLYGON_FIX_SHIFT);
						//if (hid != (edge->x >> POLYGON_FIX_SHIFT)) diff_edge = 1;
						if ((hid!=e1)) diff_edge = 2;
						else diff_edge = 0;
					}
				}

				//diff_edge = compare_edges(hid, c, ((edge->x + e) >> POLYGON_FIX_SHIFT));

				if (diff_edge)
				{
					color1 = color;
					if (translucency < 255)
					{
						////set_difference_blender(r, g, b, translucency);
						//set_mode_trans();

						////bmp->vtable->hfill(bmp, hid, c, (edge->x + e) >> POLYGON_FIX_SHIFT, colorB);

						////set_trans_blender(r, g, b, (int)translucency);
						//set_trans_blender(0, 0, 0, (int)translucency);
						//set_mode_trans();


						if (diff_edge == 2) translucency_ = translucency * 3 / 4;
						else translucency_ = translucency;

						if (bmp->vtable->color_depth > 8) {
							set_trans_blender(0, 0, 0, (int)translucency_);
							color1 = color;
							set_mode_trans();
						}
						else {
							color1 = color & 0x0000FF;
							double tf = translucency;
							tf /= 255.0;
							color1 = (color1 + tf * (255 - color1));
							if (color1 > 255) color1 = 255;
							solid_mode();
						}
					}
					bmp->vtable->hfill(bmp, hid, c, (edge->x + e) >> POLYGON_FIX_SHIFT, color1);

					//bmp->vtable->hfill(bmp, hid, c, (edge->x + e) >> POLYGON_FIX_SHIFT, color);
					//bmp->vtable->hfill(bmp, hid, c, (edge->x + e) >> POLYGON_FIX_SHIFT, color);
					//bmp->vtable->hfill(bmp, hid, c, (edge->x + e) >> POLYGON_FIX_SHIFT, color);

					////set_trans_blender(0, 0, 0, (int)translucency);
					//set_mode_trans();
				}

				hid = 1 + ((edge->x + e) >> POLYGON_FIX_SHIFT);
				//hid = ((edge->x + e) >> POLYGON_FIX_SHIFT);
			}

			edge = edge->next;
			draw = up;
		}

		/* update edges, sorting and removing dead ones */
		edge = active_edges;
		while (edge) {
			next_edge = edge->next;
			if (c >= edge->bottom) {
				active_edges = my_remove_edge(active_edges, edge);
			}
			else {
				edge->x += edge->dx;
				if ((edge->top == c) && (edge->dx > 0)) {
					edge->x -= edge->dx / 2;
				}
				if ((edge->bottom == c + 1) && (edge->dx < 0)) {
					edge->x -= edge->dx / 2;
				}
				while ((edge->prev) && (edge->x < edge->prev->x)) {
					if (edge->next)
						edge->next->prev = edge->prev;
					edge->prev->next = edge->next;
					edge->next = edge->prev;
					edge->prev = edge->prev->prev;
					edge->next->prev = edge;
					if (edge->prev)
						edge->prev->next = edge;
					else
						active_edges = edge;
				}
			}
			edge = next_edge;
		}
	}

	release_bitmap(bmp);
}


/* triangle:
 *  Draws a filled triangle between the three points.
 */
void my_soft_triangle(BITMAP *bmp, int x1, int y1, int x2, int y2, int x3, int y3, int color)
{
   ASSERT(bmp);

   #if (defined ALLEGRO_GCC) && (defined ALLEGRO_I386)

      /* note: this depends on a dodgy assumption about parameter passing 
       * conventions. I assume that the point coordinates are all on the 
       * stack in consecutive locations, so I can pass that block of stack 
       * memory as the array for polygon() without bothering to copy the 
       * data to a temporary location. 
       */
      polygon(bmp, 3, &x1, color);

   #else
   {
      /* portable version for other platforms */
      int point[6];

      point[0] = x1; point[1] = y1;
      point[2] = x2; point[3] = y2;
      point[4] = x3; point[5] = y3;

      polygon(bmp, 3, point, color);
   }
   #endif
}

