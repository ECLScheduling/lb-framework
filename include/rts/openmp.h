#pragma once

#include <abstractions/rts.h>

namespace MOGSLib { namespace Abstraction {

/**
 * @brief The declaration of a specific data structure to represent the OpenMP runtime system.
 * @details This structure must contain solely static data in order to be acessed globally by Binders, Initializers, Concepts and Adaptors.
 */
template<>
struct RTS<MOGSLib::RuntimeSystemEnum::OpenMP> : RTS<MOGSLib::RuntimeSystemEnum::OpenMP, false> {
  using Index = typename MOGSLib::RuntimeTraits<id>::Index;
  using Load = typename MOGSLib::RuntimeTraits<id>::Load;

  static Index chunk_size;
  static Index nPEs;
  static Index ntasks;

  static Load* (*get_task_loads)();
  static Load* (*get_PE_loads)();

  /**
   * @brief Define the amount of chunks that are generated by OpenMP.
   * @param nchunks The amount of chunks that are generated by OpenMP.
   */
  static inline void set_chunk_size(decltype(chunk_size) nchunks) { chunk_size = nchunks; }

  /**
   * @brief Define the amount of PEs perceived by the OpenMP runtime.
   * @param _nPEs The amount of PEs detected by OpenMP.
   */
  static inline void set_nPEs(decltype(nPEs) _nPEs) { nPEs = _nPEs; }

  /**
   * @brief Define the amount of tasks perceived by the OpenMP runtime.
   * @param _ntasks The amount of tasks detected by OpenMP.
   */
  static inline void set_ntasks(decltype(ntasks) _ntasks) { ntasks = _ntasks; }

  /**
   * @brief Define the user function that will inform the load for the schedulers.
   * @param function A user-defined function that returns an array of Loads corresponding to each task workload.
   */
  static inline void set_task_load_function(decltype(get_task_loads) function) { get_task_loads = function; }

  /**
   * @brief Define the user function that will inform the load for the processing elements.
   * @param function A user-defined function that returns an array of Loads corresponding to each processing element workload.
   */
  static inline void set_PE_load_function(decltype(get_PE_loads) function) { get_PE_loads = function; }

};

}}