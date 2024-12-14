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
// Chapter: 02 Image Presentation
// Recipe:  14 Creating a swapchain with R8G8B8A8 format and a MAILBOX present mode

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

namespace VulkanCookbook {

  bool CreateSwapchainWithR8G8B8A8FormatAndMailboxPresentMode( VkPhysicalDevice       physical_device,
                                                               VkSurfaceKHR           presentation_surface,
                                                               VkDevice               logical_device,
                                                               VkImageUsageFlags      swapchain_image_usage,
                                                               VkExtent2D           & image_size,
                                                               VkFormat             & image_format,
                                                               VkSwapchainKHR       & old_swapchain,
                                                               VkSwapchainKHR       & swapchain,
                                                               std::vector<VkImage> & swapchain_images ) {
    VkPresentModeKHR desired_present_mode;
    if( !SelectDesiredPresentationMode( physical_device, presentation_surface, VK_PRESENT_MODE_MAILBOX_KHR, desired_present_mode ) ) {
      return false;
    }

    VkSurfaceCapabilitiesKHR surface_capabilities;
    if( !GetCapabilitiesOfPresentationSurface( physical_device, presentation_surface, surface_capabilities ) ) {
      return false;
    }

    uint32_t number_of_images;
    if( !SelectNumberOfSwapchainImages( surface_capabilities, number_of_images ) ) {
      return false;
    }

    if( !ChooseSizeOfSwapchainImages( surface_capabilities, image_size ) ) {
      return false;
    }
    if( (0 == image_size.width) ||
        (0 == image_size.height) ) {
      return true;
    }

    VkImageUsageFlags image_usage;
    if( !SelectDesiredUsageScenariosOfSwapchainImages( surface_capabilities, swapchain_image_usage, image_usage ) ) {
      return false;
    }

    VkSurfaceTransformFlagBitsKHR surface_transform;
    SelectTransformationOfSwapchainImages( surface_capabilities, VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR, surface_transform );

    VkColorSpaceKHR image_color_space;
    if( !SelectFormatOfSwapchainImages( physical_device, presentation_surface, { VK_FORMAT_B8G8R8A8_SRGB, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR }, image_format, image_color_space ) ) {
      return false;
    }

    if( !CreateSwapchain( logical_device, presentation_surface, number_of_images, { image_format, image_color_space }, image_size, image_usage, surface_transform, desired_present_mode, old_swapchain, swapchain ) ) {
      return false;
    }

    if( !GetHandlesOfSwapchainImages( logical_device, swapchain, swapchain_images ) ) {
      return false;
    }
    return true;
  }

} // namespace VulkanCookbook
