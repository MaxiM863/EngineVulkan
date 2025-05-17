#include "Graphics.h"

using namespace VulkanCookbook;

class Graphics : public VulkanCookbook::VulkanCookbookSample
{

    VkDestroyer(VkBuffer)               VertexBuffer;
    VkDestroyer(VkDeviceMemory)         BufferMemory;
    
    VkDestroyer(VkImage)                Image;
    //VkDestroyer(VkDeviceMemory)         ImageMemory;
    VkDestroyer(VkImageView)            ImageView;
    VkDestroyer(VkSampler)              Sampler;
    
    VkDestroyer(VkDescriptorSetLayout)  DescriptorSetLayout;
    VkDestroyer(VkDescriptorPool)       DescriptorPool;
    std::vector<VkDescriptorSet>        DescriptorSets;
    
    VkDestroyer(VkRenderPass)           RenderPass;
    VkDestroyer(VkPipelineLayout)       PipelineLayout;
    VkDestroyer(VkPipeline)             GraphicsPipeline;

    sdlTextEngine*                      aas;

public:



virtual bool Initialize( WindowParameters window_parameters ) override {

  if( !InitializeVulkan( window_parameters, nullptr, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, false ) ) {

    return false;
  }

  InitVkDestroyer( LogicalDevice, Sampler );
  InitVkDestroyer( LogicalDevice, Image );
  InitVkDestroyer( LogicalDevice, RenderPass);
  InitVkDestroyer( LogicalDevice, PipelineLayout);
  InitVkDestroyer( LogicalDevice, GraphicsPipeline);
  InitVkDestroyer( LogicalDevice, DescriptorSetLayout);
  InitVkDestroyer( LogicalDevice, DescriptorPool);
  InitVkDestroyer( LogicalDevice, Sampler );
  InitVkDestroyer( LogicalDevice, VertexBuffer );
  aas = new sdlTextEngine();

  InitVkDestroyer( LogicalDevice, ImageView );
  aas->Initialize(LogicalDevice.Object.Handle, PhysicalDevice, GraphicsQueue, FramesResources.front().CommandBuffer[0], Sampler.Object.Handle, Image.Object.Handle, 
                  ImageView.Object.Handle, Swapchain, RenderPass.Object.Handle, PipelineLayout.Object.Handle, GraphicsPipeline.Object.Handle, DescriptorSets, DescriptorSetLayout.Object.Handle, DescriptorPool.Object.Handle, VertexBuffer.Object.Handle);


  return true;
}



virtual bool Draw() override {
  auto prepare_frame = [&]( std::vector<VkCommandBuffer> command_buffer, uint32_t swapchain_image_index, VkFramebuffer framebuffer ) {
    if( !BeginCommandBufferRecordingOperation( command_buffer[0], VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT, nullptr ) ) {
      return false;
    }

    if( PresentQueue.FamilyIndex != GraphicsQueue.FamilyIndex ) {
      ImageTransition image_transition_before_drawing = {
        Swapchain.Images[swapchain_image_index],  // VkImage              Image
        VK_ACCESS_MEMORY_READ_BIT,                // VkAccessFlags        CurrentAccess
        VK_ACCESS_MEMORY_READ_BIT,                // VkAccessFlags        NewAccess
        VK_IMAGE_LAYOUT_UNDEFINED,                // VkImageLayout        CurrentLayout
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, // VkImageLayout        NewLayout
        PresentQueue.FamilyIndex,                 // uint32_t             CurrentQueueFamily
        GraphicsQueue.FamilyIndex,                // uint32_t             NewQueueFamily
        VK_IMAGE_ASPECT_COLOR_BIT                 // VkImageAspectFlags   Aspect
      };
      SetImageMemoryBarrier( command_buffer[0], VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, { image_transition_before_drawing } );
    }

    // Drawing
    BeginRenderPass( command_buffer[0], *RenderPass, framebuffer, { { 0, 0 }, Swapchain.Size }, { { 0.1f, 0.2f, 0.3f, 1.0f } }, VK_SUBPASS_CONTENTS_INLINE );

    BindPipelineObject( command_buffer[0], VK_PIPELINE_BIND_POINT_GRAPHICS, *GraphicsPipeline );
    VkViewport viewport = {
      0.0f,                                       // float    x
      0.0f,                                       // float    y
      static_cast<float>(Swapchain.Size.width),   // float    width
      static_cast<float>(Swapchain.Size.height),  // float    height
      0.0f,                                       // float    minDepth
      1.0f,                                       // float    maxDepth
    };
    SetViewportStateDynamically( command_buffer[0], 0, { viewport } );

    VkRect2D scissor = {
      {                                           // VkOffset2D     offset
        0,                                          // int32_t        x
        0                                           // int32_t        y
      },
      {                                           // VkExtent2D     extent
        Swapchain.Size.width,                       // uint32_t       width
        Swapchain.Size.height                       // uint32_t       height
      }
    };
    SetScissorStateDynamically( command_buffer[0], 0, { scissor } );

    BindDescriptorSets( command_buffer[0], VK_PIPELINE_BIND_POINT_GRAPHICS, *PipelineLayout, 0, DescriptorSets, {} );

    BindVertexBuffers( command_buffer[0], 0, { { *VertexBuffer, 0 } } );

    DrawGeometry( command_buffer[0], 4, 1, 0, 0 );

    EndRenderPass( command_buffer[0] );

    if( PresentQueue.FamilyIndex != GraphicsQueue.FamilyIndex ) {
      ImageTransition image_transition_before_present = {
        Swapchain.Images[swapchain_image_index],  // VkImage              Image
        VK_ACCESS_MEMORY_READ_BIT,                // VkAccessFlags        CurrentAccess
        VK_ACCESS_MEMORY_READ_BIT,                // VkAccessFlags        NewAccess
        VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,          // VkImageLayout        CurrentLayout
        VK_IMAGE_LAYOUT_PRESENT_SRC_KHR,          // VkImageLayout        NewLayout
        GraphicsQueue.FamilyIndex,                // uint32_t             CurrentQueueFamily
        PresentQueue.FamilyIndex,                 // uint32_t             NewQueueFamily
        VK_IMAGE_ASPECT_COLOR_BIT                 // VkImageAspectFlags   Aspect
      };
      SetImageMemoryBarrier( command_buffer[0], VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_BOTTOM_OF_PIPE_BIT, { image_transition_before_present } );
    }

    if( !EndCommandBufferRecordingOperation( command_buffer[0] ) ) {
      return false;
    }
    return true;
  };

  return IncreasePerformanceThroughIncreasingTheNumberOfSeparatelyRenderedFrames( *LogicalDevice, GraphicsQueue.Handle, PresentQueue.Handle,
    *Swapchain.Handle, Swapchain.Size, Swapchain.ImageViewsRaw, *RenderPass, {}, prepare_frame, FramesResources );
}



    Graphics()
    {
        //ModelClass max = ModelClass("MaximZepplin");
        //m_scene = new Scene();
    }

    Graphics(Scene scene)
    {
        //m_scene = &scene;
    }

private:

    

    bool Resize()
    {
        if (!CreateSwapchain()) {
            return false;
        }

        return true;
    }

    void Deinitialize() {

        if (LogicalDevice) {
            WaitForAllSubmittedCommandsToBeFinished(*LogicalDevice);
        }

    }

private:

};