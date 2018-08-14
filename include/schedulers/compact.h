#pragma once

#include <abstractions/scheduler.h>
#include <policies/compact.h>

BEGIN_NAMESPACE(Scheduler)

/**
 * @brief Class that represents a scheduler which utilizes the compact policy to output a task map.
 **/
template<typename ... _Concepts>
class Compact : public Abstraction::Scheduler<Abstraction::SchedulerEnum::compact> {
public:

  using Concepts = typename MOGSLib::SchedulerTraits<SchedulerType>::Dependencies<_Concepts...>;
  std::unique_ptr<Concepts> concepts;

  /**
   * @brief The method that will initialize the references to the concrete concepts used by the scheduler.
   */
  void init(_Concepts *... ref) {
    concepts = std::make_unique<Concepts>(std::make_tuple(ref...));
  }

  /**
   * @brief The method to obtain a task map based on a compact policy.
   **/
  TaskMap work() override {
    auto ntasks = concepts->task_data->ntasks();
    auto nPEs = concepts->PE_data->nPEs();

    auto map = new Index[ntasks]();
    Policy::Compact::map(map, ntasks, nPEs);
    return map;
  }

};

END_NAMESPACE