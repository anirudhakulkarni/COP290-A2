//Purpy Pupple's amazing maze generator.
//Released under the CC-BY-SA 3.0 License and the GFDL
#include "mazegenerator.hpp"
long numinn = 1; //Number of cells in the maze.
const int xxsize = 20;
const int yysize = 20;
// net size will be (2*xsize-3),(2*ysize-3)
struct cell
{
	bool in;		  //Is this cell in the maze?
	bool up;		  //Does the wall above this cell exist?
	bool left;		  //Does the wall to the left of this cell exist?
	int prevx, prevy; //The coordinates of the previous cell, used for backtracking.
};

cell MAZE[xxsize][yysize];

int maze_generate()
{
	srand((unsigned int)time(NULL)); //seed random number generator with system time
	initialize();					 //initialize the maze
	generate();						 //generate the maze
#ifdef movie
	for (int i = 1; i < 10; i++)
	{
		numinn++;
		savebmp(0, 0); //output the bitmap
	}
#else movie
	savebmp(0, 0);
#endif
	return 0;
}

void initialize()
{
	//Initialize the maze!
	for (int x = 0; x < xxsize; x++)
	{
		for (int y = 0; y < yysize; y++)
		{
			//The maze cells on the edges of the maze are "in" to provide padding. Otherwise, all maze cells are not in.
			MAZE[x][y].in = (x == 0 || x == xxsize - 1 || y == 0 || y == yysize - 1) ? 1 : 0;
			//All maze cells have all walls existing by default, except the perimeter cells.
			MAZE[x][y].up = (x == 0 || x == xxsize - 1 || y == 0) ? 0 : 1;
			MAZE[x][y].left = (x == 0 || y == 0 || y == yysize - 1) ? 0 : 1;
		}
	}
	return;
}

void generate()
{
	int xcur = 1, ycur = 1; //start growing from the corner. It could theoretically start growing from anywhere, doesn't matter.
	MAZE[xcur][ycur].in = 1;
	int whichway;
	bool success;
	do
	{
#ifdef movie
		savebmp(xcur, ycur);
#endif
#ifdef nodeadend
		if (MAZE[xcur][ycur - 1].in && MAZE[xcur][ycur + 1].in &&
			MAZE[xcur - 1][ycur].in && MAZE[xcur + 1][ycur].in)
		{
			//If at a dead end, randomly destroy a wall to make it not a dead end!
			do
			{
				success = 0;
				whichway = rand() % 4;
				switch (whichway)
				{
				case UP:
					if (MAZE[xcur][ycur].up && ycur != 1)
					{
						success = 1;
						MAZE[xcur][ycur].up = 0;
					}
					break;
				case DOWN:
					if (MAZE[xcur][ycur + 1].up && ycur != yysize - 2)
					{
						success = 1;
						MAZE[xcur][ycur + 1].up = 0;
					}
					break;
				case LEFT:
					if (MAZE[xcur][ycur].left && xcur != 1)
					{
						success = 1;
						MAZE[xcur][ycur].left = 0;
					}
					break;
				case RIGHT:
					if (MAZE[xcur + 1][ycur].left && xcur != xxsize - 2)
					{
						success = 1;
						MAZE[xcur + 1][ycur].left = 0;
					}
					break;
				}
			} while (!success);
		}
#endif
#ifdef backtrack
		while (MAZE[xcur][ycur - 1].in && MAZE[xcur][ycur + 1].in &&
			   MAZE[xcur - 1][ycur].in && MAZE[xcur + 1][ycur].in)
		{
			//If all the neighbourhood cells are in, backtrack.
			int xcur2 = MAZE[xcur][ycur].prevx;
			ycur = MAZE[xcur][ycur].prevy;
			xcur = xcur2;
		}
#endif
#ifdef prim
		do
		{
			//randomly find a cell that's in the maze
			xcur = rand() % (xxsize - 2) + 1;
			ycur = rand() % (yysize - 2) + 1;
		} while (!MAZE[xcur][ycur].in ||
				 MAZE[xcur][ycur - 1].in && MAZE[xcur][ycur + 1].in &&
					 MAZE[xcur - 1][ycur].in && MAZE[xcur + 1][ycur].in);
#endif
		do
		{
			//Randomly grow the maze if possible.
			success = 0;
			whichway = rand() % 4;
			switch (whichway)
			{
			case UP:
				if (!MAZE[xcur][ycur - 1].in)
				{
					success = 1;
					MAZE[xcur][ycur].up = 0;
					MAZE[xcur][ycur - 1].prevx = xcur;
					MAZE[xcur][ycur - 1].prevy = ycur;
					ycur--;
				}
				break;
			case DOWN:
				if (!MAZE[xcur][ycur + 1].in)
				{
					success = 1;
					MAZE[xcur][ycur + 1].up = 0;
					MAZE[xcur][ycur + 1].prevx = xcur;
					MAZE[xcur][ycur + 1].prevy = ycur;
					ycur++;
				}
				break;
			case LEFT:
				if (!MAZE[xcur - 1][ycur].in)
				{
					success = 1;
					MAZE[xcur][ycur].left = 0;
					MAZE[xcur - 1][ycur].prevx = xcur;
					MAZE[xcur - 1][ycur].prevy = ycur;
					xcur--;
				}
				break;
			case RIGHT:
				if (!MAZE[xcur + 1][ycur].in)
				{
					success = 1;
					MAZE[xcur + 1][ycur].left = 0;
					MAZE[xcur + 1][ycur].prevx = xcur;
					MAZE[xcur + 1][ycur].prevy = ycur;
					xcur++;
				}
				break;
			}
		} while (!success);
		MAZE[xcur][ycur].in = 1;
		numinn++; //Every iteration of this loop, one maze cell is added to the maze.
	} while (numinn < (xxsize - 2) * (yysize - 2));
#ifdef movie
	savebmp(xcur, ycur);
#endif
	return;
}

void savebmp(int xspecial, int yspecial)
{
	//save a bitmap file! the xspecial, yspecial pixel is coloured red.
	FILE *outfile;
	int extrabytes, paddedsize;
	int x, y, n;
	int width = (xxsize - 1) * 2 - 1;
	int height = (yysize - 1) * 2 - 1;
	int arr[height][width] = {0};
	extrabytes = (4 - ((width * 3) % 4)) % 4;

	char filename[200];

	sprintf(filename, "../outputs/%s_%dx%d_n%d.bmp", OUTFILE, xxsize, yysize, numinn);
	paddedsize = ((width * 3) + extrabytes) * height;

	unsigned int headers[13] = {paddedsize + 54, 0, 54, 40, width, height, 0, 0, paddedsize, 0, 0, 0, 0};

	outfile = fopen(filename, "wb");
	fprintf(outfile, "BM");

	for (n = 0; n <= 5; n++)
	{
		fprintf(outfile, "%c", headers[n] & 0x000000FF);
		fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
		fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
		fprintf(outfile, "%c", (headers[n] & (unsigned int)0xFF000000) >> 24);
	}

	fprintf(outfile, "%c", 1);
	fprintf(outfile, "%c", 0);
	fprintf(outfile, "%c", 24);
	fprintf(outfile, "%c", 0);

	for (n = 7; n <= 12; n++)
	{
		fprintf(outfile, "%c", headers[n] & 0x000000FF);
		fprintf(outfile, "%c", (headers[n] & 0x0000FF00) >> 8);
		fprintf(outfile, "%c", (headers[n] & 0x00FF0000) >> 16);
		fprintf(outfile, "%c", (headers[n] & (unsigned int)0xFF000000) >> 24);
	}

	//Actual writing of data begins here:
	for (y = 0; y <= height - 1; y++)
	{
		for (x = 0; x <= width - 1; x++)
		{
			if (x % 2 == 1 && y % 2 == 1)
			{
				if (x / 2 + 1 == xspecial && y / 2 + 1 == yspecial)
				{
					RED;
				}
				else
				{
					if (MAZE[x / 2 + 1][y / 2 + 1].in)
					{
						BLACK;
						arr[y][x] = 1;
					}
					else
					{
						WHITE;
						arr[y][x] = 0;
					}
				}
			}
			else if (x % 2 == 0 && y % 2 == 0)
			{
				{
					WHITE;
					arr[y][x] = 0;
				}
			}
			else if (x % 2 == 0 && y % 2 == 1)
			{
				if (MAZE[x / 2 + 1][y / 2 + 1].left)
				{
					WHITE;
					arr[y][x] = 0;
				}
				else
				{
					BLACK;
					arr[y][x] = 1;
				}
			}
			else if (x % 2 == 1 && y % 2 == 0)
			{
				if (MAZE[x / 2 + 1][y / 2 + 1].up)
				{
					WHITE;
					arr[y][x] = 0;
				}
				else
				{
					BLACK;
					arr[y][x] = 1;
				}
			}
		}
		if (extrabytes)
		{ // See above - BMP lines must be of lengths divisible by 4.
			for (n = 1; n <= extrabytes; n++)
			{
				fprintf(outfile, "%c", 0);
			}
		}
	}
	printf("file printed: %s\n", filename);
	fclose(outfile);
	freopen("../outputs/matrix.out", "w", stdout);

	for (y = 0; y <= height - 1; y++)
	{
		for (x = 0; x <= width - 1; x++)
		{
			cout << arr[height - 1 - y][x] << " "; // Height is reversed as bmp saves image from bottom
		}
		cout << endl;
	}
	return;
}
