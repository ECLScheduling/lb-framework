#pragma once

#include <iostream>
#include <strategies/impl/greedyPG/greedyPGStrategy.h>
#include <strategies/input/minimalParallelInput.h>

typedef Traits<void>::Load Weight;

namespace GreedyPGModule {

const Weight squarePenality(unsigned int size) {
  return size * size;
}

}

/**
 * This struct is used by the StrategyAnalyzer to analyze the GreedyPenalizedGraphStrategy with the NaiveBasicOutput as input.
 */
struct GreedyPGStrategyPerfModule {

  typedef IMinimalParallelInputTraits::Task Task;
  typedef IMinimalParallelInputTraits::PE PE;

  MinimalParallelInput* createInput(int argc, char *argv[]) {
    Task *tasks;
    PE *PEs;
    unsigned int taskCount;
    unsigned int PECount;

    if(argc < 2) {
      std::cout << "Correct execution of program: ./" << argv[0] << " {PE count} {Task Count}" << std::endl;
      exit(0);
    }

    PECount = atoi(argv[1]);
    taskCount = atoi(argv[2]);
    
    PEs = new PE[PECount];
    tasks = new Task[taskCount];

    for(unsigned int i = 0; i < PECount; ++i) {
      PEs[i] = PE(i);
    }

    for(unsigned int i = 0; i < taskCount; ++i) {
      tasks[i] = Task(i, i*2);
    }

    return new MinimalParallelInput(PEs, tasks, PECount, taskCount);
  }

  GreedyPenalizedGraphStrategy* createStrategy(int argc, char *argv[]) {
    return new GreedyPenalizedGraphStrategy(GreedyPGModule::squarePenality);
  }
};