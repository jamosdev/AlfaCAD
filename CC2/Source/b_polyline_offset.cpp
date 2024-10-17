/*   ______   ___       ___         ____     ______  ____
*   /\  _  \ /\_ \    /'___\       /\  _`\  /\  _  \/\  _`\
*   \ \ \L\ \\//\ \  /\ \__/   __  \ \ \/\_\\ \ \L\ \ \ \/\ \
*    \ \  __ \ \ \ \ \ \ ,__\/'__`\ \ \ \/_/_\ \  __ \ \ \ \ \
*     \ \ \/\ \ \_\ \_\ \ \_/\ \L\.\_\ \ \L\ \\ \ \/\ \ \ \_\ \
*      \ \_\ \_\/\____\\ \_\\ \__/.\_\\ \____/ \ \_\ \_\ \____/
*       \/_/\/_/\/____/ \/_/ \/__/\/_/ \/___/   \/_/\/_/\/___/
*
*   A CAD
*
*   By Marek Ratajczak 2024
*
*   See readme_alfacad.txt for copyright information.
*
*/

#include "cavc/polylineoffset.hpp"
#include "b_polyline_offset.h"

extern "C" {
	void get_polyline_offset_data(int size, VERTEX *vertex, int *capacity, int* sizes, int *closes, bool closed, double distance, bool smooth_vertex);
}

void get_polyline_offset_data(int size, VERTEX *vertex,int *capacity, int *sizes, int *closes, bool closed, double distance, bool smooth_vertex)
{
	int i,n,j;
	cavc::Polyline<double> input;
	bool isClosed;
	int vsize;

	for (i = 0; i < size; i++)
	{
	   input.addVertex(vertex[i].x, vertex[i].y, vertex[i].bulge);
	}

	input.isClosed() = closed;

	// compute the resulting offset polylines, offset = 3
	std::vector<cavc::Polyline<double>> results = cavc::parallelOffset(input, distance, false, smooth_vertex);

	*capacity = (int)results.capacity();
	n = 0;
	for (j = 0; j < (*capacity); j++)
	{
		isClosed = results[j].isClosed();
		closes[j] = isClosed;
		vsize= (int)results[j].size();
		sizes[j] = vsize;
		for (i = 0; i < (sizes[j]); i++)
		{
			vertex[n].x = (float)results[j].vertexes().at(i).x();
			vertex[n].y = (float)results[j].vertexes().at(i).y();
			vertex[n].bulge = (double)results[j].vertexes().at(i).bulge();

			n++;
		}
	}

	//return of the structrue

}