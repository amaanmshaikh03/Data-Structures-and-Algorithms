#include "wall.h"
#include "maze.h"
/********************************************************************/
/*                                                                  */
/*  A1 Part 3: runMaze                                  */
/*                                                                  */
/*  Author1 Name: Mohammedamaan Shaikh                              */
/*      - cellavail and runMaze                                     */
/*  Author2 Name: Marc Nicolas Oliva                                */
/*      - cellavail and runMaze                                     */
/*                                                                  */
/********************************************************************/

bool cellavail(Maze& maze, int cellStart, int& next) {
    int anv[4] = {-1, 1, -maze.numCols(), maze.numCols()};
    for (int i = 0; i < 4; i++) {
        next = anv[i] + cellStart;
        if (maze.canGo(cellStart, next) && !maze.isMarked(next)) { 
            return true;
        }
    }
    return false;
}
int runMaze(Maze& maze, int path[1], int cellStart, int endCell) {
    int next{};
    static int count{};
    maze.mark(cellStart);
    path[count] = cellStart;
    if (cellStart == endCell) {
        int len = count + 1;
        count = 0;
        return len;
    } 
    if (cellavail(maze, cellStart, next)) {
        count++;
        return runMaze(maze, path, next, endCell);
    }
    if (count != 0) {
        count--;
        return runMaze(maze, path, path[count], endCell);
    }
    return 0;
}
