// Test.cpp
// Guanglei Wang 
// Thu Oct 10 15:37:36 CST 2019


#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <stdio.h>
#include <iostream>
#include <string>
#include <functional>
#include <stdio.h>
#include <cstring>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include <polar/doctest.h>
#include <polar/Config.h>

#ifdef USE_CLP
#include "ClpSimplex.hpp"
#endif

#ifdef USE_OSI
#include "OsiSolverInterface.hpp"
#include "OsiClpSolverInterface.hpp"
#endif

#ifdef USE_CGL
#include "CglRedSplit.hpp"
#include "CglRedSplit2.hpp"
#endif



#ifdef USE_CLP
TEST_CASE("test clp simplex"){
    ClpSimplex  model;
    int status;
    std::string mpsfile=prj_dir"/data/hello.mps";
    // Keep names
    status = model.readMps(mpsfile.c_str(), true);
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
#endif


#ifdef USE_OSI
TEST_CASE("test Osi"){
    // Create a problem pointer.  We use the base class here.
    OsiSolverInterface *si;
    
    // When we instantiate the object, we need a specific derived class.
    si = new OsiClpSolverInterface; 
    
    // Read in an mps file.  This one's from the MIPLIB library.
    std::string mpsfile=prj_dir"/data/Sample/p0033.mps";

    if (si->readMps(mpsfile.c_str()) <0){
        exit(1);
    }

    // Display some information about the instance
    int nrows = si->getNumRows();
    int ncols = si->getNumCols();
    int nelem = si->getNumElements();
    std::cout << "This problem has " << nrows << " rows, "
    << ncols << " columns, and " << nelem << " nonzeros."
    << std::endl;
    
    double const * upper_bounds = si->getColUpper();
    std::cout << "The upper bound on the first column is " << upper_bounds[0]
    << std::endl;
    // All information about the instance is available with similar methods
    
    
    // Before solving, indicate some parameters
    si->setIntParam( OsiMaxNumIteration, 10);
    si->setDblParam( OsiPrimalTolerance, 0.001 );
    
    // Can also read parameters
    std::string solver;
    si->getStrParam( OsiSolverName, solver );
    std::cout << "About to solve with: " << solver << std::endl;
    
    // Solve the (relaxation of the) problem
    si->initialSolve();
    
    // Check the solution
    if ( si->isProvenOptimal() ) {
        std::cout << "Found optimal solution!" << std::endl;
        std::cout << "Objective value is " << si->getObjValue() << std::endl;
        
        // Examine solution
        int n = si->getNumCols();
        const double *solution;
        solution = si->getColSolution();
        
        std::cout << "Solution: ";
        for (int i = 0; i < n; i++)
            std::cout << solution[i] << " ";
        std::cout << std::endl;
        
        std::cout << "It took " << si->getIterationCount() << " iterations"
        << " to solve." << std::endl;
    } else {
        std::cout << "Didn't find optimal solution." << std::endl;
        
        // Check other status functions.  What happened?
        if (si->isProvenPrimalInfeasible())
            std::cout << "Problem is proven to be infeasible." << std::endl;
        if (si->isProvenDualInfeasible())
            std::cout << "Problem is proven dual infeasible." << std::endl;
        if (si->isIterationLimitReached())
            std::cout << "Reached iteration limit." << std::endl;
    }
}
#endif


#ifdef USE_CGL
TEST_CASE("test cgl"){
    char *f_name_lp, f_name[256], *f_name_pos;
    int i, ncol;
    std::string mpsfile=prj_dir"/data/Sample/p0033.mps";

    f_name_lp = strdup(mpsfile.c_str());
    f_name_pos = strrchr(f_name_lp, '/');
    if(f_name_pos != NULL) {
        strcpy(f_name, &(f_name_pos[1]));
    }
    else {
        strcpy(f_name, f_name_lp);
    }
    //last_dot_pos = strrchr(f_name, '.');
    //if(last_dot_pos != NULL) {
    //    last_dot_pos = '\0';
    //}
    
    // Do for both RedSplit and RedSplit2
    {
        OsiClpSolverInterface *clp = new OsiClpSolverInterface;
        clp->messageHandler()->setLogLevel(0);
        if(strcmp(&(f_name_lp[strlen(f_name_lp)-3]), ".lp") == 0) {
            clp->readLp(f_name_lp);
        }
        else {
            if(strcmp(&(f_name_lp[strlen(f_name_lp)-4]), ".mps") == 0) {
                clp->readMps(f_name_lp);
            }
            else {
                printf("### ERROR: unrecognized file type\n");
                exit(1);
            }
        }
        ncol = clp->getNumCols();
        clp->initialSolve();
        
        printf("LP value: %12.2f\n", clp->getObjValue());
        
        OsiCuts cuts;
        
        // Define parameters for CglRedSplit generator
        CglParam cpar;
        cpar.setMAX_SUPPORT(ncol+1);
        CglRedSplitParam rspar(cpar);
        
        // Create a cut generator with the given parameters
        CglRedSplit cutGen(rspar);
        
        char *colType = new char[ncol];
        for(i=0; i<ncol; i++) {
            if(clp->isContinuous(i)) {
                colType[i] = 'C';
            }
            else {
                colType[i] = 'I';
            }
        }
        
        int round, max_rounds = 10;
        for(round=0; round<max_rounds; round++) {
            cutGen.generateCuts(*clp, cuts);
            
            int ncuts = cuts.sizeRowCuts();
            
            const OsiRowCut **newRowCuts = new const OsiRowCut * [ncuts];
            for(i=0; i<ncuts; i++) {
                newRowCuts[i] = &cuts.rowCut(i);
            }
            clp->applyRowCuts(ncuts, newRowCuts);
            delete[] newRowCuts;
            
            printf("round %4d: %4d generated cuts  new objective value: %12.2f\n",
                   round, ncuts, clp->getObjValue());
            
            clp->resolve();
            
            if(clp->isAbandoned()) {
                printf("###ERROR: Numerical difficulties in Solver\n");
                exit(1);
            }
            
            if(clp->isProvenPrimalInfeasible()) {
                printf("### WARNING: Problem is infeasible\n");
                exit(1);
            }
        }
        
        delete clp;
        delete[] colType;
    }
    {
        OsiClpSolverInterface *clp = new OsiClpSolverInterface;
        clp->messageHandler()->setLogLevel(0);
        if(strcmp(&(f_name_lp[strlen(f_name_lp)-3]), ".lp") == 0) {
            clp->readLp(f_name_lp);
        }
        else {
            if(strcmp(&(f_name_lp[strlen(f_name_lp)-4]), ".mps") == 0) {
                clp->readMps(f_name_lp);
            }
            else {
                printf("### ERROR: unrecognized file type\n");
                exit(1);
            }
        }
        ncol = clp->getNumCols();
        clp->initialSolve();
        
        printf("LP value: %12.2f\n", clp->getObjValue());
        
        OsiCuts cuts;
        
        // Define parameters for CglRedSplit2 generator
        CglParam cpar;
        cpar.setMAX_SUPPORT(ncol+1);
        CglRedSplit2Param rspar(cpar);
        
        // Create a cut generator with the given parameters
        CglRedSplit2 cutGen(rspar);
        
        char *colType = new char[ncol];
        for(i=0; i<ncol; i++) {
            if(clp->isContinuous(i)) {
                colType[i] = 'C';
            }
            else {
                colType[i] = 'I';
            }
        }
        
        int round, max_rounds = 10;
        for(round=0; round<max_rounds; round++) {
            cutGen.generateCuts(*clp, cuts);
            
            int ncuts = cuts.sizeRowCuts();
            
            const OsiRowCut **newRowCuts = new const OsiRowCut * [ncuts];
            for(i=0; i<ncuts; i++) {
                newRowCuts[i] = &cuts.rowCut(i);
            }
            clp->applyRowCuts(ncuts, newRowCuts);
            delete[] newRowCuts;
            
            printf("round %4d: %4d generated cuts  new objective value: %12.2f\n",
                   round, ncuts, clp->getObjValue());
            
            clp->resolve();
            
            if(clp->isAbandoned()) {
                printf("###ERROR: Numerical difficulties in Solver\n");
                exit(1);
            }
            
            if(clp->isProvenPrimalInfeasible()) {
                printf("### WARNING: Problem is infeasible\n");
                exit(1);
            }
        }
        
        delete clp;
        delete[] colType;
    }
    free(f_name_lp);
}
#endif

TEST_CASE(""){
}
