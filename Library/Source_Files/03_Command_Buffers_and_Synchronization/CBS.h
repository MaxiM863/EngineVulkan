#include "Common.h"

#ifndef CREATING_A_COMMAND_POOL
#define CREATING_A_COMMAND_POOL

namespace VulkanCookbook {

  bool CreateCommandPool( VkDevice                   logical_device,
                          VkCommandPoolCreateFlags   command_pool_flags,
                          uint32_t                   queue_family,
                          VkCommandPool            & command_pool );

} // namespace VulkanCookbook

#endif // CREATING_A_COMMAND_POOL


#ifndef ALLOCATING_COMMAND_BUFFERS
#define ALLOCATING_COMMAND_BUFFERS

namespace VulkanCookbook {

  bool AllocateCommandBuffers( VkDevice                       logical_device,
                               VkCommandPool                  command_pool,
                               VkCommandBufferLevel           level,
                               uint32_t                       count,
                               std::vector<VkCommandBuffer> & command_buffers );

} // namespace VulkanCookbook

#endif // ALLOCATING_COMMAND_BUFFERS


#ifndef BEGINNING_A_COMMAND_BUFFER_RECORDING_OPERATION
#define BEGINNING_A_COMMAND_BUFFER_RECORDING_OPERATION

namespace VulkanCookbook {

  bool BeginCommandBufferRecordingOperation( VkCommandBuffer                  command_buffer,
                                             VkCommandBufferUsageFlags        usage,
                                             VkCommandBufferInheritanceInfo * secondary_command_buffer_info );

} // namespace VulkanCookbook

#endif // BEGINNING_A_COMMAND_BUFFER_RECORDING_OPERATION


#ifndef ENDING_A_COMMAND_BUFFER_RECORDING_OPERATION
#define ENDING_A_COMMAND_BUFFER_RECORDING_OPERATION

namespace VulkanCookbook {

  bool EndCommandBufferRecordingOperation( VkCommandBuffer command_buffer );

} // namespace VulkanCookbook

#endif // ENDING_A_COMMAND_BUFFER_RECORDING_OPERATION


#ifndef RESETTING_A_COMMAND_BUFFER
#define RESETTING_A_COMMAND_BUFFER

namespace VulkanCookbook {

  bool ResetCommandBuffer( VkCommandBuffer command_buffer,
                           bool            release_resources );

} // namespace VulkanCookbook

#endif // RESETTING_A_COMMAND_BUFFER


#ifndef RESETTING_A_COMMAND_POOL
#define RESETTING_A_COMMAND_POOL

namespace VulkanCookbook {

  bool ResetCommandPool( VkDevice      logical_device,
                         VkCommandPool command_pool,
                         bool          release_resources );

} // namespace VulkanCookbook

#endif // RESETTING_A_COMMAND_POOL


#ifndef CREATING_A_SEMAPHORE
#define CREATING_A_SEMAPHORE

namespace VulkanCookbook {

  bool CreateSemaphore( VkDevice      logical_device,
                        VkSemaphore & semaphore );

} // namespace VulkanCookbook

#endif // CREATING_A_SEMAPHORE


#ifndef CREATING_A_FENCE
#define CREATING_A_FENCE

namespace VulkanCookbook {

  bool CreateFence( VkDevice   logical_device,
                    bool       signaled,
                    VkFence  & fence );

} // namespace VulkanCookbook

#endif // CREATING_A_FENCE


#ifndef WAITING_FOR_FENCES
#define WAITING_FOR_FENCES

namespace VulkanCookbook {

  bool WaitForFences( VkDevice                     logical_device,
                      std::vector<VkFence> const & fences,
                      VkBool32                     wait_for_all,
                      uint64_t                     timeout );

} // namespace VulkanCookbook

#endif // WAITING_FOR_FENCES


#ifndef RESETTING_FENCES
#define RESETTING_FENCES

namespace VulkanCookbook {

  bool ResetFences( VkDevice                     logical_device,
                    std::vector<VkFence> const & fences );

} // namespace VulkanCookbook

#endif // RESETTING_FENCES


#ifndef SUBMITTING_A_COMMAND_BUFFER_TO_THE_QUEUE
#define SUBMITTING_A_COMMAND_BUFFER_TO_THE_QUEUE

namespace VulkanCookbook {

  struct WaitSemaphoreInfo {
    VkSemaphore           Semaphore;
    VkPipelineStageFlags  WaitingStage;
  };

  bool SubmitCommandBuffersToQueue( VkQueue                         queue,
                                    std::vector<WaitSemaphoreInfo>  wait_semaphore_infos,
                                    std::vector<VkCommandBuffer>    command_buffers,
                                    std::vector<VkSemaphore>        signal_semaphores,
                                    VkFence                         fence );

} // namespace VulkanCookbook

#endif // SUBMITTING_A_COMMAND_BUFFER_TO_THE_QUEUE


#ifndef SYNCHRONIZING_TWO_COMMAND_BUFFERS
#define SYNCHRONIZING_TWO_COMMAND_BUFFERS

namespace VulkanCookbook {

  bool SynchronizeTwoCommandBuffers( VkQueue                         first_queue,
                                     std::vector<WaitSemaphoreInfo>  first_wait_semaphore_infos,
                                     std::vector<VkCommandBuffer>    first_command_buffers,
                                     std::vector<WaitSemaphoreInfo>  synchronizing_semaphores,
                                     VkQueue                         second_queue,
                                     std::vector<VkCommandBuffer>    second_command_buffers,
                                     std::vector<VkSemaphore>        second_signal_semaphores,
                                     VkFence                         second_fence );

} // namespace VulkanCookbook

#endif // SYNCHRONIZING_TWO_COMMAND_BUFFERS


#ifndef CHECKING_IF_PROCESSING_OF_A_SUBMITTED_COMMAND_BUFFER_HAS_FINISHED
#define CHECKING_IF_PROCESSING_OF_A_SUBMITTED_COMMAND_BUFFER_HAS_FINISHED

namespace VulkanCookbook {

  bool CheckIfProcessingOfSubmittedCommandBufferHasFinished( VkDevice                         logical_device,
                                                             VkQueue                          queue,
                                                             std::vector<WaitSemaphoreInfo>   wait_semaphore_infos,
                                                             std::vector<VkCommandBuffer>     command_buffers,
                                                             std::vector<VkSemaphore>         signal_semaphores,
                                                             VkFence                          fence,
                                                             uint64_t                         timeout,
                                                             VkResult                       & wait_status );

} // namespace VulkanCookbook

#endif // CHECKING_IF_PROCESSING_OF_A_SUBMITTED_COMMAND_BUFFER_HAS_FINISHED


#ifndef WAITING_UNTIL_ALL_COMMANDS_SUBMITTED_TO_A_QUEUE_ARE_FINISHED
#define WAITING_UNTIL_ALL_COMMANDS_SUBMITTED_TO_A_QUEUE_ARE_FINISHED

namespace VulkanCookbook {

  bool WaitUntilAllCommandsSubmittedToQueueAreFinished( VkQueue queue );

} // namespace VulkanCookbook

#endif // WAITING_UNTIL_ALL_COMMANDS_SUBMITTED_TO_A_QUEUE_ARE_FINISHED


#ifndef WAITING_FOR_ALL_SUBMITTED_COMMANDS_TO_BE_FINISHED
#define WAITING_FOR_ALL_SUBMITTED_COMMANDS_TO_BE_FINISHED

namespace VulkanCookbook {

  bool WaitForAllSubmittedCommandsToBeFinished( VkDevice logical_device );

} // namespace VulkanCookbook

#endif // WAITING_FOR_ALL_SUBMITTED_COMMANDS_TO_BE_FINISHED


#ifndef DESTROYING_A_FENCE
#define DESTROYING_A_FENCE

namespace VulkanCookbook {

  void DestroyFence( VkDevice   logical_device,
                     VkFence  & fence );

} // namespace VulkanCookbook

#endif // DESTROYING_A_FENCE


#ifndef DESTROYING_A_SEMAPHORE
#define DESTROYING_A_SEMAPHORE

namespace VulkanCookbook {

  void DestroySemaphore( VkDevice      logical_device,
                         VkSemaphore & semaphore );

} // namespace VulkanCookbook

#endif // DESTROYING_A_SEMAPHORE


#ifndef FREEING_COMMAND_BUFFERS
#define FREEING_COMMAND_BUFFERS

namespace VulkanCookbook {

  void FreeCommandBuffers( VkDevice                       logical_device,
                           VkCommandPool                  command_pool,
                           std::vector<VkCommandBuffer> & command_buffers );

} // namespace VulkanCookbook

#endif // FREEING_COMMAND_BUFFERS


#ifndef DESTROYING_A_COMMAND_POOL
#define DESTROYING_A_COMMAND_POOL

namespace VulkanCookbook {

  void DestroyCommandPool( VkDevice        logical_device,
                           VkCommandPool & command_pool );

} // namespace VulkanCookbook

#endif // DESTROYING_A_COMMAND_POOL