// Test.cpp 
// Guanglei Wang 
// Thu Oct 10 15:37:36 CST 2019


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ClpSimplex.hpp"

TEST_CASE("test clp"){
    ClpSimplex  model;
    int status;
    // Keep names
    status = model.readMps(string(prj_dir)+"hello.mps", true);
    if (status)
        exit(10);
    
    int numberColumns = model.numberColumns();
    int numberRows = model.numberRows();
    
    if (numberColumns > 80 || numberRows > 80) {
        printf("model too large\n");
        exit(11);
    }
    printf("This prints x wherever a non-zero element exists in the matrix.\n\n\n");
    
    char x[81];
    
    int iRow;
    // get row copy
    CoinPackedMatrix rowCopy = *model.matrix();
    rowCopy.reverseOrdering();
    const int * column = rowCopy.getIndices();
    const int * rowLength = rowCopy.getVectorLengths();
    const CoinBigIndex * rowStart = rowCopy.getVectorStarts();
    
    x[numberColumns] = '\0';
    for (iRow = 0; iRow < numberRows; iRow++) {
        memset(x, ' ', numberColumns);
        for (CoinBigIndex k = rowStart[iRow]; k < rowStart[iRow] + rowLength[iRow]; k++) {
            int iColumn = column[k];
            x[iColumn] = 'x';
        }
        printf("%s\n", x);
    }
    printf("\n\n");
}
