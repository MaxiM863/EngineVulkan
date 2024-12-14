// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation
// the rights to use, copy, modify, merge, publish, distribute, sublicense,
// and / or sell copies of the Software, and to permit persons to whom the
// Software is furnished to do so, subject to the following conditions:
//
// The below copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL
// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
// FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
// Vulkan Cookbook
// ISBN: 9781786468154
// © Packt Publishing Limited
//
// Author:   Pawel Lapinski
// LinkedIn: https://www.linkedin.com/in/pawel-lapinski-84522329
//
// Chapter: 04 Resources and Memory
// Recipe:  15 Using staging buffer to update buffer with a device-local memory bound

#include "03_Command_Buffers_and_Synchronization/03_Beginning_a_command_buffer_recording_operation.h"
#include "03_Command_Buffers_and_Synchronization/04_Ending_a_command_buffer_recording_operation.h"
#include "03_Command_Buffers_and_Synchronization/08_Creating_a_fence.h"
#include "03_Command_Buffers_and_Synchronization/09_Waiting_for_fences.h"
#include "03_Command_Buffers_and_Synchronization/11_Submitting_command_buffers_to_the_queue.h"
#include "04_Resources_and_Memory/01_Creating_a_buffer.h"
#include "04_Resources_and_Memory/02_Allocating_and_binding_memory_object_to_a_buffer.h"
#include "04_Resources_and_Memory/03_Setting_a_buffer_memory_barrier.h"
#include "04_Resources_and_Memory/11_Mapping,_updating_and_unmapping_host-visible_memory.h"
#include "04_Resources_and_Memory/12_Copying_data_between_buffers.h"
#include "04_Resources_and_Memory/15_Using_staging_buffer_to_update_a_buffer_with_a_device-local_memory_bound.h"
#include "04_Resources_and_Memory/20_Freeing_a_memory_object.h"
#include "04_Resources_and_Memory/21_Destroying_a_buffer.h"

namespace VulkanCookbook {

  bool UseStagingBufferToUpdateBufferWithDeviceLocalMemoryBound( VkPhysicalDevice           physical_device,
                                                                 VkDevice                   logical_device,
                                                                 VkDeviceSize               data_size,
                                                                 void                     * data,
                                                                 VkBuffer                   destination_buffer,
                                                                 VkDeviceSize               destination_offset,
                                                                 VkAccessFlags              destination_buffer_current_access,
                                                                 VkAccessFlags              destination_buffer_new_access,
                                                                 VkPipelineStageFlags       destination_buffer_generating_stages,
                                                                 VkPipelineStageFlags       destination_buffer_consuming_stages,
                                                                 VkQueue                    queue,
                                                                 VkCommandBuffer            command_buffer,
                                                                 std::vector<VkSemaphore>   signal_semaphores ) {

    VkDestroyer(VkBuffer) staging_buffer;
    InitVkDestroyer( logical_device, staging_buffer );
    if( !CreateBuffer( logical_device, data_size, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, *staging_buffer ) ) {
      return false;
    }

    VkDestroyer(VkDeviceMemory) memory_object;
    InitVkDestroyer( logical_device, memory_object );
    if( !AllocateAndBindMemoryObjectToBuffer( physical_device, logical_device, *staging_buffer, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT, *memory_object ) ) {
      return false;
    }

    if( !MapUpdateAndUnmapHostVisibleMemory( logical_device, *memory_object, 0, data_size, data, true, nullptr ) ) {
      return false;
    }

    if( !BeginCommandBufferRecordingOperation( command_buffer, VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT, nullptr ) ) {
      return false;
    }

    SetBufferMemoryBarrier( command_buffer, destination_buffer_generating_stages, VK_PIPELINE_STAGE_TRANSFER_BIT, { { destination_buffer, destination_buffer_current_access, VK_ACCESS_TRANSFER_WRITE_BIT, VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED } } );

    CopyDataBetweenBuffers( command_buffer, *staging_buffer, destination_buffer, { { 0, destination_offset, data_size } } );

    SetBufferMemoryBarrier( command_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT, destination_buffer_consuming_stages, { { destination_buffer, VK_ACCESS_TRANSFER_WRITE_BIT, destination_buffer_new_access, VK_QUEUE_FAMILY_IGNORED, VK_QUEUE_FAMILY_IGNORED } } );

    if( !EndCommandBufferRecordingOperation( command_buffer ) ) {
      return false;
    }

    VkDestroyer(VkFence) fence;
    InitVkDestroyer( logical_device, fence );
    if( !CreateFence( logical_device, false, *fence ) ) {
      return false;
    }

    if( !SubmitCommandBuffersToQueue( queue, {}, { command_buffer }, signal_semaphores, *fence ) ) {
      return false;
    }

    if( !WaitForFences( logical_device, { *fence }, VK_FALSE, 500000000 ) ) {
      return false;
    }

    return true;
  }

} // namespace VulkanCookbook
