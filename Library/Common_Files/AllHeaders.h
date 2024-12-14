// MIT License
//
// Copyright( c ) 2017 Packt
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files( the "Software" ), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions :
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// Vulkan Cookbook
// ISBN: 9781786468154
// © Packt Publishing Limited
//
// Author:   Pawel Lapinski
// LinkedIn: https://www.linkedin.com/in/pawel-lapinski-84522329
//
// Common

#ifndef ALL_HEADERS
#define ALL_HEADERS

#include "01_Instance_and_Devices/03_Connecting_with_a_Vulkan_Loader_library.h"
#include "01_Instance_and_Devices/05_Loading_function_exported_from_a_Vulkan_Loader_library.h"
#include "01_Instance_and_Devices/06_Loading_global-level_functions.h"
#include "01_Instance_and_Devices/07_Checking_available_Instance_extensions.h"
#include "01_Instance_and_Devices/08_Creating_a_Vulkan_Instance.h"
#include "01_Instance_and_Devices/09_Loading_instance-level_functions.h"
#include "01_Instance_and_Devices/10_Enumerating_available_physical_devices.h"
#include "01_Instance_and_Devices/11_Checking_available_device_extensions.h"
#include "01_Instance_and_Devices/12_Getting_features_and_properties_of_a_physical_device.h"
#include "01_Instance_and_Devices/13_Checking_available_queue_families_and_their_properties.h"
#include "01_Instance_and_Devices/14_Selecting_index_of_a_queue_family_with_desired_capabilities.h"
#include "01_Instance_and_Devices/15_Creating_a_logical_device.h"
#include "01_Instance_and_Devices/16_Loading_device-level_functions.h"
#include "01_Instance_and_Devices/17_Getting_a_device_queue.h"
#include "01_Instance_and_Devices/18_Creating_a_logical_device_with_geometry_shaders_and_graphics_queue.h"
#include "01_Instance_and_Devices/19_Destroying_a_logical_device.h"
#include "01_Instance_and_Devices/20_Destroying_a_Vulkan_Instance.h"
#include "01_Instance_and_Devices/21_Releasing_a_Vulkan_Loader_library.h"

#include "02_Image_Presentation/01_Creating_a_Vulkan_Instance_with_WSI_extensions_enabled.h"
#include "02_Image_Presentation/02_Creating_a_presentation_surface.h"
#include "02_Image_Presentation/03_Selecting_a_queue_family_that_supports_presentation_to_a_given_surface.h"
#include "02_Image_Presentation/04_Creating_a_logical_device_with_WSI_extensions_enabled.h"
#include "02_Image_Presentation/05_Selecting_a_desired_presentation_mode.h"
#include "02_Image_Presentation/06_Getting_capabilities_of_a_presentation_surface.h"
#include "02_Image_Presentation/07_Selecting_a_number_of_swapchain_images.h"
#include "02_Image_Presentation/08_Choosing_a_size_of_swapchain_images.h"
#include "02_Image_Presentation/09_Selecting_desired_usage_scenarios_of_swapchain_images.h"
#include "02_Image_Presentation/10_Selecting_a_transformation_of_swapchain_images.h"
#include "02_Image_Presentation/11_Selecting_a_format_of_swapchain_images.h"
#include "02_Image_Presentation/12_Creating_a_swapchain.h"
#include "02_Image_Presentation/13_Getting_handles_of_swapchain_images.h"
#include "02_Image_Presentation/14_Creating_a_swapchain_with_R8G8B8A8_format_and_a_MAILBOX_present_mode.h"
#include "02_Image_Presentation/15_Acquiring_a_swapchain_image.h"
#include "02_Image_Presentation/16_Presenting_an_image.h"
#include "02_Image_Presentation/17_Destroying_a_swapchain.h"
#include "02_Image_Presentation/18_Destroying_a_presentation_surface.h"

#include "03_Command_Buffers_and_Synchronization/01_Creating_a_command_pool.h"
#include "03_Command_Buffers_and_Synchronization/02_Allocating_command_buffers.h"
#include "03_Command_Buffers_and_Synchronization/03_Beginning_a_command_buffer_recording_operation.h"
#include "03_Command_Buffers_and_Synchronization/04_Ending_a_command_buffer_recording_operation.h"
#include "03_Command_Buffers_and_Synchronization/05_Resetting_a_command_buffer.h"
#include "03_Command_Buffers_and_Synchronization/06_Resetting_a_command_pool.h"
#include "03_Command_Buffers_and_Synchronization/07_Creating_a_semaphore.h"
#include "03_Command_Buffers_and_Synchronization/08_Creating_a_fence.h"
#include "03_Command_Buffers_and_Synchronization/09_Waiting_for_fences.h"
#include "03_Command_Buffers_and_Synchronization/10_Resetting_fences.h"
#include "03_Command_Buffers_and_Synchronization/11_Submitting_command_buffers_to_the_queue.h"
#include "03_Command_Buffers_and_Synchronization/12_Synchronizing_two_command_buffers.h"
#include "03_Command_Buffers_and_Synchronization/13_Checking_if_processing_of_a_submitted_command_buffer_has_finished.h"
#include "03_Command_Buffers_and_Synchronization/14_Waiting_until_all_commands_submitted_to_a_queue_are_finished.h"
#include "03_Command_Buffers_and_Synchronization/15_Waiting_for_all_submitted_commands_to_be_finished.h"
#include "03_Command_Buffers_and_Synchronization/16_Destroying_a_fence.h"
#include "03_Command_Buffers_and_Synchronization/17_Destroying_a_semaphore.h"
#include "03_Command_Buffers_and_Synchronization/18_Freeing_command_buffers.h"
#include "03_Command_Buffers_and_Synchronization/19_Destroying_a_command_pool.h"

#include "04_Resources_and_Memory/01_Creating_a_buffer.h"
#include "04_Resources_and_Memory/02_Allocating_and_binding_memory_object_to_a_buffer.h"
#include "04_Resources_and_Memory/03_Setting_a_buffer_memory_barrier.h"
#include "04_Resources_and_Memory/04_Creating_a_buffer_view.h"
#include "04_Resources_and_Memory/05_Creating_an_image.h"
#include "04_Resources_and_Memory/06_Allocating_and_binding_memory_object_to_an_image.h"
#include "04_Resources_and_Memory/07_Setting_an_image_memory_barrier.h"
#include "04_Resources_and_Memory/08_Creating_an_image_view.h"
#include "04_Resources_and_Memory/09_Creating_a_2D_image_and_view.h"
#include "04_Resources_and_Memory/10_Creating_a_layered_2D_image_with_a_CUBEMAP_view.h"
#include "04_Resources_and_Memory/11_Mapping,_updating_and_unmapping_host-visible_memory.h"
#include "04_Resources_and_Memory/12_Copying_data_between_buffers.h"
#include "04_Resources_and_Memory/13_Copying_data_from_a_buffer_to_an_image.h"
#include "04_Resources_and_Memory/14_Copying_data_from_an_image_to_a_buffer.h"
#include "04_Resources_and_Memory/15_Using_staging_buffer_to_update_a_buffer_with_a_device-local_memory_bound.h"
#include "04_Resources_and_Memory/16_Using_staging_buffer_to_update_an_image_with_a_device-local_memory_bound.h"
#include "04_Resources_and_Memory/17_Destroying_an_image_view.h"
#include "04_Resources_and_Memory/18_Destroying_an_image.h"
#include "04_Resources_and_Memory/19_Destroying_a_buffer_view.h"
#include "04_Resources_and_Memory/20_Freeing_a_memory_object.h"
#include "04_Resources_and_Memory/21_Destroying_a_buffer.h"

#include "05_Descriptor_Sets/01_Creating_a_sampler.h"
#include "05_Descriptor_Sets/02_Creating_a_sampled_image.h"
#include "05_Descriptor_Sets/03_Creating_a_combined_image_sampler.h"
#include "05_Descriptor_Sets/04_Creating_a_storage_image.h"
#include "05_Descriptor_Sets/05_Creating_a_uniform_texel_buffer.h"
#include "05_Descriptor_Sets/06_Creating_a_storage_texel_buffer.h"
#include "05_Descriptor_Sets/07_Creating_a_uniform_buffer.h"
#include "05_Descriptor_Sets/08_Creating_a_storage_buffer.h"
#include "05_Descriptor_Sets/09_Creating_an_input_attachment.h"
#include "05_Descriptor_Sets/10_Creating_a_descriptor_set_layout.h"
#include "05_Descriptor_Sets/11_Creating_a_descriptor_pool.h"
#include "05_Descriptor_Sets/12_Allocating_descriptor_sets.h"
#include "05_Descriptor_Sets/13_Updating_descriptor_sets.h"
#include "05_Descriptor_Sets/14_Binding_descriptor_sets.h"
#include "05_Descriptor_Sets/15_Creating_descriptors_with_a_texture_and_a_uniform_buffer.h"
#include "05_Descriptor_Sets/16_Freeing_descriptor_sets.h"
#include "05_Descriptor_Sets/17_Resetting_a_descriptor_pool.h"
#include "05_Descriptor_Sets/18_Destroying_a_descriptor_pool.h"
#include "05_Descriptor_Sets/19_Destroying_a_descriptor_set_layout.h"
#include "05_Descriptor_Sets/20_Destroying_a_sampler.h"

#include "06_Render_Passes_and_Framebuffers/01_Specifying_attachments_descriptions.h"
#include "06_Render_Passes_and_Framebuffers/02_Specifying_subpass_descriptions.h"
#include "06_Render_Passes_and_Framebuffers/03_Specifying_dependencies_between_subpasses.h"
#include "06_Render_Passes_and_Framebuffers/04_Creating_a_render_pass.h"
#include "06_Render_Passes_and_Framebuffers/05_Creating_a_framebuffer.h"
#include "06_Render_Passes_and_Framebuffers/06_Preparing_a_render_pass_for_geometry_rendering_and_postprocess_subpasses.h"
#include "06_Render_Passes_and_Framebuffers/07_Preparing_a_render_pass_and_a_framebuffer_with_color_and_depth_attachments.h"
#include "06_Render_Passes_and_Framebuffers/08_Beginning_a_render_pass.h"
#include "06_Render_Passes_and_Framebuffers/09_Progressing_to_the_next_subpass.h"
#include "06_Render_Passes_and_Framebuffers/10_Ending_a_render_pass.h"
#include "06_Render_Passes_and_Framebuffers/11_Destroying_a_framebuffer.h"
#include "06_Render_Passes_and_Framebuffers/12_Destroying_a_render_pass.h"

#include "08_Graphics_and_Compute_Pipelines/01_Creating_a_shader_module.h"
#include "08_Graphics_and_Compute_Pipelines/02_Specifying_pipeline_shader_stages.h"
#include "08_Graphics_and_Compute_Pipelines/03_Specifying_pipeline_vertex_input_state.h"
#include "08_Graphics_and_Compute_Pipelines/04_Specifying_pipeline_input_assembly_state.h"
#include "08_Graphics_and_Compute_Pipelines/05_Specifying_pipeline_tessellation_state.h"
#include "08_Graphics_and_Compute_Pipelines/06_Specifying_pipeline_viewport_and_scissor_test_state.h"
#include "08_Graphics_and_Compute_Pipelines/07_Specifying_pipeline_rasterization_state.h"
#include "08_Graphics_and_Compute_Pipelines/08_Specifying_pipeline_multisample_state.h"
#include "08_Graphics_and_Compute_Pipelines/09_Specifying_pipeline_depth_and_stencil_state.h"
#include "08_Graphics_and_Compute_Pipelines/10_Specifying_pipeline_blend_state.h"
#include "08_Graphics_and_Compute_Pipelines/11_Specifying_pipeline_dynamic_states.h"
#include "08_Graphics_and_Compute_Pipelines/12_Creating_a_pipeline_layout.h"
#include "08_Graphics_and_Compute_Pipelines/13_Specifying_graphics_pipeline_creation_parameters.h"
#include "08_Graphics_and_Compute_Pipelines/14_Creating_a_pipeline_cache_object.h"
#include "08_Graphics_and_Compute_Pipelines/15_Retrieving_data_from_a_pipeline_cache.h"
#include "08_Graphics_and_Compute_Pipelines/16_Merging_multiple_pipeline_cache_objects.h"
#include "08_Graphics_and_Compute_Pipelines/17_Creating_graphics_pipelines.h"
#include "08_Graphics_and_Compute_Pipelines/18_Creating_a_compute_pipeline.h"
#include "08_Graphics_and_Compute_Pipelines/19_Binding_a_pipeline_object.h"
#include "08_Graphics_and_Compute_Pipelines/20_Creating_a_pipeline_layout_with_a_combined_image_sampler,_a_buffer_and_push_constant_ranges.h"
#include "08_Graphics_and_Compute_Pipelines/21_Creating_a_graphics_pipeline_with_vertex_and_fragment_shaders,_depth_test_enabled,_and_with_dynamic_viewport_and_scissor_tests.h"
#include "08_Graphics_and_Compute_Pipelines/22_Creating_multiple_graphics_pipelines_on_multiple_threads.h"
#include "08_Graphics_and_Compute_Pipelines/23_Destroying_a_pipeline.h"
#include "08_Graphics_and_Compute_Pipelines/24_Destroying_a_pipeline_cache.h"
#include "08_Graphics_and_Compute_Pipelines/25_Destroying_a_pipeline_layout.h"
#include "08_Graphics_and_Compute_Pipelines/26_Destroying_a_shader_module.h"

#include "09_Command_Recording_and_Drawing/01_Clearing_a_color_image.h"
#include "09_Command_Recording_and_Drawing/02_Clearing_a_depth-stencil_image.h"
#include "09_Command_Recording_and_Drawing/03_Clearing_render_pass_attachments.h"
#include "09_Command_Recording_and_Drawing/04_Binding_vertex_buffers.h"
#include "09_Command_Recording_and_Drawing/05_Binding_an_index_buffer.h"
#include "09_Command_Recording_and_Drawing/06_Providing_data_to_shaders_through_push_constants.h"
#include "09_Command_Recording_and_Drawing/07_Setting_viewport_state_dynamically.h"
#include "09_Command_Recording_and_Drawing/08_Setting_scissor_state_dynamically.h"
#include "09_Command_Recording_and_Drawing/09_Setting_line_width_state_dynamically.h"
#include "09_Command_Recording_and_Drawing/10_Setting_depth_bias_state_dynamically.h"
#include "09_Command_Recording_and_Drawing/11_Setting_blend_constants_state_dynamically.h"
#include "09_Command_Recording_and_Drawing/12_Drawing_a_geometry.h"
#include "09_Command_Recording_and_Drawing/13_Drawing_an_indexed_geometry.h"
#include "09_Command_Recording_and_Drawing/14_Dispatching_compute_work.h"
#include "09_Command_Recording_and_Drawing/15_Executing_secondary_command_buffer_inside_a_primary_command_buffer.h"
#include "09_Command_Recording_and_Drawing/16_Recording_a_command_buffer_that_draws_a_geometry_with_dynamic_viewport_and_scissor_states.h"
#include "09_Command_Recording_and_Drawing/17_Recording_command_buffers_on_multiple_threads.h"
#include "09_Command_Recording_and_Drawing/18_Preparing_a_single_frame_of_animation.h"
#include "09_Command_Recording_and_Drawing/19_Increasing_the_performance_through_increasing_the_number_of_separately_rendered_frames.h"

#include "10_Helper_Recipes/01_Preparing_a_translation_matrix.h"
#include "10_Helper_Recipes/02_Preparing_a_rotation_matrix.h"
#include "10_Helper_Recipes/03_Preparing_a_scaling_matrix.h"
#include "10_Helper_Recipes/04_Preparing_a_perspective_projection_matrix.h"
#include "10_Helper_Recipes/05_Preparing_an_orthographic_projection_matrix.h"
#include "10_Helper_Recipes/06_Loading_texture_data_from_a_file.h"
#include "10_Helper_Recipes/07_Loading_a_3D_model_from_an_OBJ_file.h"


#endif // ALL_HEADERS
