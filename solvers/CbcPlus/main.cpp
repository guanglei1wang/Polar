//
//  main.cpp
//  greatCbc
//
//  Created by 王光磊 on 2019/6/13.
//  Copyright © 2019 王光磊. All rights reserved.
//

#include <iostream>
#include <cassert>
#include <iomanip>

// For Branch and bound

#include <polar/Config.h>
#include <CoinPragma.hpp>
#include "OsiClpSolverInterface.hpp"
#include <CbcModel.hpp>
#include "CbcStrategy.hpp"
// Preprocessing
#include "CglPreProcess.hpp"

#include "CoinTime.hpp"

//#############################################################################
/************************************************************************
 This main program reads in an integer model from an mps file.
 It then uses default strategy - just cuts at root node
 ************************************************************************/

int main (int argc, const char *argv[])
{
    if ((64&63) ==0 ){
        printf("yes");
    }
  OsiClpSolverInterface solver1;

  // Read in model using argv[1]
  // and assert that it is a clean model
 std::string mpsfile=prj_dir"/data/Sample/p0033.mps";

  int numMpsReadErrors = solver1.readMps(mpsfile.c_str(),"");
  if( numMpsReadErrors != 0 )
  {
    printf("%d errors reading MPS file\n", numMpsReadErrors);
    return numMpsReadErrors;
  }
 
  printf("The solver has %d variables and %d constraints",  solver1.getNumCols(), solver1.getNumRows());

 //
 // /* Options are:
 //  preprocess to do preprocessing time in minutes
 //  if 2 parameters and numeric taken as time
 //  */
  bool preProcess=false;
  double minutes=-1.0;
  int nGoodParam=0;
  for (int iParam=2; iParam<argc;iParam++) {
    if (!strcmp(argv[iParam],"preprocess")) {
      preProcess=true;
      nGoodParam++;
    } else if (!strcmp(argv[iParam],"time")) {
      if (iParam+1<argc&&isdigit(argv[iParam+1][0])) {
        minutes=atof(argv[iParam+1]);
        if (minutes>=0.0) {
          nGoodParam+=2;
          iParam++; // skip time
        }
      }
    }
  }
  if (nGoodParam==0&&argc==3&&isdigit(argv[2][0])) {
    // If time is given then stop after that number of minutes
    minutes = atof(argv[2]);
    if (minutes>=0.0)
      nGoodParam=1;
  }
  if (nGoodParam!=argc-2&&argc>=2) {
    printf("Usage <file> [preprocess] [time <minutes>] or <file> <minutes>\n");
    exit(1);
  }
  // See if we want preprocessing
  OsiSolverInterface * solver2=&solver1;
  CglPreProcess process;
  if (preProcess) {
    /* Do not try and produce equality cliques and
     do up to 5 passes */
    solver2 = process.preProcess(solver1,false,5);
    if (!solver2) {
      printf("Pre-processing says infeasible\n");
      exit(2);
    }
    solver2->resolve();
  }
  CbcModel model(*solver2);

 // // If time is given then stop after that number of minutes
  if (minutes>=0.0) {
    std::cout<<"Stopping after "<<minutes<<" minutes"<<std::endl;
    model.setDblParam(CbcModel::CbcMaximumSeconds,60.0*minutes);
  }
  // Set strategy - below is == CbcStrategyDefault()
  CbcStrategyDefault strategy(true,5,8);
  model.setStrategy(strategy);

 
    // be safe: we add "-quit" at end.
  const char *arg2[]={"test","-solve", "-quit"};
  CbcMain1(3, arg2, model);
  return 0;
}

