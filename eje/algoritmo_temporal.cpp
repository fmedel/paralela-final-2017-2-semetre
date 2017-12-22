// A C++ Program to implement A* Search Algorithm
#include<bits/stdc++.h>
using namespace std;

#define ROW 10240
#define COL 10240

typedef pair<int, int> Pair;

typedef pair<double, pair<int, int> >pPair;

struct cell{
    int parent_i, parent_j;
    double f, g, h;
};

bool isValid(int row, int col){
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}
bool isUnBlocked(std::vector< std::vector<int> > grid, int row, int col){
    if (grid[row][col] == 1){return true;}
    else{return false;}
}
bool isDestination(int row, int col, Pair dest){
    if (row == dest.first && col == dest.second){return true;}
    else{return false;}

}
double calculateHValue(int row, int col, Pair dest){
    return ((double)sqrt ((row-dest.first)*(row-dest.first) + (col-dest.second)*(col-dest.second)));
}
void tracePath(std::vector< std::vector<cell> > cellDetails, Pair dest,char resultado_camino[8000]){
    //printf ("\nThe Path is ");
    int row = dest.first;
    int col = dest.second;
    char temporal[7];
    char gigante[8000];
    stack<Pair> Path;

    while (!(cellDetails[row][col].parent_i == row
             && cellDetails[row][col].parent_j == col ))
    {
        Path.push (make_pair (row, col));
        int temp_row = cellDetails[row][col].parent_i;
        int temp_col = cellDetails[row][col].parent_j;
        row = temp_row;
        col = temp_col;
    }

    Path.push (make_pair (row, col));
    while (!Path.empty())
    {
        pair<int,int> p = Path.top();
        Path.pop();
        //sprintf(temporal, "(%d,%d)-",p.first,p.second);
        printf("(%d,%d)-",p.first,p.second);
        strcat(gigante,temporal);
        temporal[0]=NULL;
    }
    //printf("holiwi\n");
    //printf("%s\n",gigante );
    strcpy(resultado_camino,gigante);
    gigante[0]=NULL;
    return;
}
int funcion_main(std::vector< std::vector<int> > grid,int inicio_fila,int inicio_columna,int fin_fila,int fin_columna,char resultado_camino[8000]){
  //printf("entrp en funcion_main\n");
    /* Description of the Grid-
     1--> The cell is not blocked
     0--> The cell is blocked    */
/*    int grid[ROW][COL] =
    {
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 1 },
        { 1, 1, 1, 0, 1, 1, 0, 1, 0, 1 },
        { 0, 0, 1, 0, 1, 0, 0, 0, 0, 1 },
        { 1, 1, 1, 0, 1, 1, 1, 0, 1, 0 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 0, 0 },
        { 1, 0, 0, 0, 0, 1, 0, 0, 0, 1 },
        { 1, 0, 1, 1, 1, 1, 0, 1, 1, 1 },
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 },
        { 1, 1, 1, 0, 0, 0, 1, 0, 0, 1 }
    };*/
    // Source is the left-most bottom-most corner
    printf("a1\n");
    Pair src = make_pair(inicio_fila, inicio_columna);
    // Destination is the left-most top-most corner
    printf("a2\n");
    Pair dest = make_pair(fin_fila, fin_columna);
    printf("a3\n");

    printf("a4\n");
    if (isValid (src.first, src.second) == false){
        return 0;
    }
    printf("a5\n");
    if (isValid (dest.first, dest.second) == false){
        return 0;
    }
    printf("a6\n");
    // Either the source or the destination is blocked
    if (isUnBlocked(grid, src.first, src.second) == false || isUnBlocked(grid, dest.first, dest.second) == false){
        return 0;
    }
    printf("a7\n");
    // If the destination cell is the same as source cell
    if (isDestination(src.first, src.second, dest) == true){
          return 0;
    }
    printf("a8\n");
    std::vector< std::vector<bool> > closedList;
    vector<bool> vectorAux;
    for ( int i = 0; i < ROW; i++) {
      for (int  c = 0; c < COL; c++) {
          vectorAux.push_back(false);
      }
      closedList.push_back(vectorAux);
      vectorAux.clear(); // limpia vector auxiliar para cargar nuevos datos sin que esten los anteriores
    }
    printf("a9\n");
     cell auxiliar_cell;
    printf("a10\n");
    auxiliar_cell.f = FLT_MAX;
    auxiliar_cell.g = FLT_MAX;
    auxiliar_cell.h = FLT_MAX;
    auxiliar_cell.parent_i = -1;
    auxiliar_cell.parent_j = -1;
    std::vector<cell> vectorAuxCell(ROW, auxiliar_cell);
    std::vector<std::vector<cell> > cellDetails(COL, vectorAuxCell);
    int i, j;
    printf("27\n");
    i = src.first, j = src.second;
    cellDetails[i][j].f = 0.0;
    cellDetails[i][j].g = 0.0;
    cellDetails[i][j].h = 0.0;
    cellDetails[i][j].parent_i = i;
    cellDetails[i][j].parent_j = j;
    printf("28\n");
    set<pPair> openList;
    printf("29\n");
    openList.insert(make_pair (0.0, make_pair (i, j)));
    printf("30\n");
    bool foundDest = false;
    printf("31\n");
    while (!openList.empty()){
          pPair p = *openList.begin();
          openList.erase(openList.begin());
          i = p.second.first;
          j = p.second.second;
          closedList[i][j] = true;
          double gNew, hNew, fNew;
          //----------- 1st Successor (North) ------------
          if (isValid(i-1, j) == true){
              if (isDestination(i-1, j, dest) == true){
                  cellDetails[i-1][j].parent_i = i;
                  cellDetails[i-1][j].parent_j = j;
                  printf ("The destination cell is found\n");
                  tracePath (cellDetails, dest,resultado_camino);
                  foundDest = true;
                  return 1;
              }
              else if (closedList[i-1][j] == false && isUnBlocked(grid, i-1, j) == true){
                  gNew = cellDetails[i][j].g + 1.0;
                  hNew = calculateHValue (i-1, j, dest);
                  fNew = gNew + hNew;
                  if (cellDetails[i-1][j].f == FLT_MAX || cellDetails[i-1][j].f > fNew){
                      openList.insert( make_pair(fNew,make_pair(i-1, j)));
                      cellDetails[i-1][j].f = fNew;
                      cellDetails[i-1][j].g = gNew;
                      cellDetails[i-1][j].h = hNew;
                      cellDetails[i-1][j].parent_i = i;
                      cellDetails[i-1][j].parent_j = j;
                  }
              }
          }

          //----------- 2nd Successor (South) ------------
          if (isValid(i+1, j) == true){
              if (isDestination(i+1, j, dest) == true){
                  cellDetails[i+1][j].parent_i = i;
                  cellDetails[i+1][j].parent_j = j;
                  printf("The destination cell is found\n");
                  tracePath(cellDetails, dest,resultado_camino);
                  foundDest = true;
                  return 1;
              }
              else if (closedList[i+1][j] == false && isUnBlocked(grid, i+1, j) == true){
                  gNew = cellDetails[i][j].g + 1.0;
                  hNew = calculateHValue(i+1, j, dest);
                  fNew = gNew + hNew;
                  if (cellDetails[i+1][j].f == FLT_MAX || cellDetails[i+1][j].f > fNew){
                      openList.insert( make_pair (fNew, make_pair (i+1, j)));
                      cellDetails[i+1][j].f = fNew;
                      cellDetails[i+1][j].g = gNew;
                      cellDetails[i+1][j].h = hNew;
                      cellDetails[i+1][j].parent_i = i;
                      cellDetails[i+1][j].parent_j = j;
                  }
              }
          }

          //----------- 3rd Successor (East) ------------

          if (isValid (i, j+1) == true){
              if (isDestination(i, j+1, dest) == true){
                  cellDetails[i][j+1].parent_i = i;
                  cellDetails[i][j+1].parent_j = j;
                  printf("The destination cell is found\n");
                  tracePath(cellDetails, dest,resultado_camino);
                  foundDest = true;
                  return 1;
              }

              else if (closedList[i][j+1] == false && isUnBlocked (grid, i, j+1) == true)
              {
                  gNew = cellDetails[i][j].g + 1.0;
                  hNew = calculateHValue (i, j+1, dest);
                  fNew = gNew + hNew;
                  if (cellDetails[i][j+1].f == FLT_MAX ||cellDetails[i][j+1].f > fNew){
                      openList.insert( make_pair(fNew,make_pair (i, j+1)));
                      cellDetails[i][j+1].f = fNew;
                      cellDetails[i][j+1].g = gNew;
                      cellDetails[i][j+1].h = hNew;
                      cellDetails[i][j+1].parent_i = i;
                      cellDetails[i][j+1].parent_j = j;
                  }
              }
          }

          //----------- 4th Successor (West) ------------
          if (isValid(i, j-1) == true){
              if (isDestination(i, j-1, dest) == true){
                  cellDetails[i][j-1].parent_i = i;
                  cellDetails[i][j-1].parent_j = j;
                  printf("The destination cell is found\n");
                  tracePath(cellDetails, dest,resultado_camino);
                  foundDest = true;
                  return 1;
              }
              else if (closedList[i][j-1] == false && isUnBlocked(grid, i, j-1) == true) {
                  gNew = cellDetails[i][j].g + 1.0;
                  hNew = calculateHValue(i, j-1, dest);
                  fNew = gNew + hNew;
                  if (cellDetails[i][j-1].f == FLT_MAX || cellDetails[i][j-1].f > fNew) {
                      openList.insert( make_pair (fNew, make_pair (i, j-1)));
                      cellDetails[i][j-1].f = fNew;
                      cellDetails[i][j-1].g = gNew;
                      cellDetails[i][j-1].h = hNew;
                      cellDetails[i][j-1].parent_i = i;
                      cellDetails[i][j-1].parent_j = j;
                  }
              }
          }

          //----------- 5th Successor (North-East) ------------
          if (isValid(i-1, j+1) == true){
              if (isDestination(i-1, j+1, dest) == true){
                  cellDetails[i-1][j+1].parent_i = i;
                  cellDetails[i-1][j+1].parent_j = j;
                  printf ("The destination cell is found\n");
                  tracePath (cellDetails, dest,resultado_camino);
                  foundDest = true;
                  return 1;
              }
              else if (closedList[i-1][j+1] == false && isUnBlocked(grid, i-1, j+1) == true){
                  gNew = cellDetails[i][j].g + 1.414;
                  hNew = calculateHValue(i-1, j+1, dest);
                  fNew = gNew + hNew;
                  if (cellDetails[i-1][j+1].f == FLT_MAX || cellDetails[i-1][j+1].f > fNew){
                      openList.insert( make_pair (fNew,make_pair(i-1, j+1)));
                      cellDetails[i-1][j+1].f = fNew;
                      cellDetails[i-1][j+1].g = gNew;
                      cellDetails[i-1][j+1].h = hNew;
                      cellDetails[i-1][j+1].parent_i = i;
                      cellDetails[i-1][j+1].parent_j = j;
                  }
              }
          }

          //----------- 6th Successor (North-West) ------------

          if (isValid (i-1, j-1) == true){
              if (isDestination (i-1, j-1, dest) == true){
                  cellDetails[i-1][j-1].parent_i = i;
                  cellDetails[i-1][j-1].parent_j = j;
                  printf ("The destination cell is found\n");
                  tracePath (cellDetails, dest,resultado_camino);
                  foundDest = true;
                  return 1;
              }
              else if (closedList[i-1][j-1] == false && isUnBlocked(grid, i-1, j-1) == true) {
                  gNew = cellDetails[i][j].g + 1.414;
                  hNew = calculateHValue(i-1, j-1, dest);
                  fNew = gNew + hNew;

                  if (cellDetails[i-1][j-1].f == FLT_MAX || cellDetails[i-1][j-1].f > fNew) {
                      openList.insert( make_pair (fNew, make_pair (i-1, j-1)));
                      cellDetails[i-1][j-1].f = fNew;
                      cellDetails[i-1][j-1].g = gNew;
                      cellDetails[i-1][j-1].h = hNew;
                      cellDetails[i-1][j-1].parent_i = i;
                      cellDetails[i-1][j-1].parent_j = j;
                  }
              }
          }
          //----------- 7th Successor (South-East) ------------
          if (isValid(i+1, j+1) == true){
              if (isDestination(i+1, j+1, dest) == true){
                  cellDetails[i+1][j+1].parent_i = i;
                  cellDetails[i+1][j+1].parent_j = j;
                  printf ("The destination cell is found\n");
                  tracePath (cellDetails, dest,resultado_camino);
                  foundDest = true;
                  return 1;
              }
              else if (closedList[i+1][j+1] == false && isUnBlocked(grid, i+1, j+1) == true) {
                  gNew = cellDetails[i][j].g + 1.414;
                  hNew = calculateHValue(i+1, j+1, dest);
                  fNew = gNew + hNew;
                  if (cellDetails[i+1][j+1].f == FLT_MAX || cellDetails[i+1][j+1].f > fNew) {
                      openList.insert(make_pair(fNew,make_pair (i+1, j+1)));
                      cellDetails[i+1][j+1].f = fNew;
                      cellDetails[i+1][j+1].g = gNew;
                      cellDetails[i+1][j+1].h = hNew;
                      cellDetails[i+1][j+1].parent_i = i;
                      cellDetails[i+1][j+1].parent_j = j;
                  }
              }
          }
          //----------- 8th Successor (South-West) ------------
          if (isValid (i+1, j-1) == true){
              if (isDestination(i+1, j-1, dest) == true){
                  cellDetails[i+1][j-1].parent_i = i;
                  cellDetails[i+1][j-1].parent_j = j;
                  printf("The destination cell is found\n");
                  tracePath(cellDetails, dest,resultado_camino);
                  foundDest = true;
                  return 1;
              }
              else if (closedList[i+1][j-1] == false && isUnBlocked(grid, i+1, j-1) == true) {
                  gNew = cellDetails[i][j].g + 1.414;
                  hNew = calculateHValue(i+1, j-1, dest);
                  fNew = gNew + hNew;
                  if (cellDetails[i+1][j-1].f == FLT_MAX || cellDetails[i+1][j-1].f > fNew){
                      openList.insert(make_pair(fNew,make_pair(i+1, j-1)));
                      cellDetails[i+1][j-1].f = fNew;
                      cellDetails[i+1][j-1].g = gNew;
                      cellDetails[i+1][j-1].h = hNew;
                      cellDetails[i+1][j-1].parent_i = i;
                      cellDetails[i+1][j-1].parent_j = j;
                  }
              }
          }
        }


    int contador =1; //aStarSearch(grid, src, dest,resultado_camino);
    printf("aaaa\n");
    if (foundDest == false) {return 0;}
    return 0;
}
