#include "Graphics.h"

using namespace VulkanCookbook;

class Graphics : public VulkanCookbook::VulkanCookbookSample
{

  sdlTextEngine*                      aas;
 
  vessel** vess;
  std::vector<Mesh> Models;

  bool UpdateUniformBuffer;

public:

  HWND* hWnd;


virtual bool Initialize( WindowParameters window_parameters, HWND hWnd ) override {

  if( !InitializeVulkan( window_parameters, nullptr, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, false ) ) {

    return false;
  }

  float pos_x0 = -0.15f;
  float pos_x1 = 0.15f;
  float pos_y0 = 0.80f;
  float pos_y1 = 0.86f;

  
  aas = new sdlTextEngine();

  aas->Initialize("Hello you !!!", 200, 0x00FF0000, 0x00FFFFFF, pos_x0, pos_x1, pos_y0, pos_y1, 1000, 200, LogicalDevice.Object.Handle, PhysicalDevice, GraphicsQueue, FramesResources.front().CommandBuffer[0], Swapchain);

  Load L;  
  
  // Vertex data
  if( !L.Load3DModelFromTxtFile( "Data/Models/vessel_0.txt", Models ) ) {
    
    return false;
  }

  vess = new vessel*[Models.size()];

  for(int i = 0 ; i < Models.size(); i++)
  {
    
    vess[i] = new vessel();
 
    vess[i]->Initialize(LogicalDevice.Object.Handle, PhysicalDevice, GraphicsQueue, FramesResources.front().CommandBuffer[0], Swapchain, Models[i]);
  }

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
    //BeginRenderPass( command_buffer[0], *RenderPass2, framebuffer, { { 0, 0 }, Swapchain.Size }, { { 0.1f, 0.2f, 0.3f, 1.0f } }, VK_SUBPASS_CONTENTS_INLINE );


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

    

    ///////////////////////////////////////////////////////

    if( UpdateUniformBuffer ) {
      
      for(int i = 0 ; i < Models.size(); i++)
      {

        BufferTransition pre_transfer_transition = {
          vess[i]->getUniformBuffer(),               // VkBuffer         Buffer
          VK_ACCESS_UNIFORM_READ_BIT,   // VkAccessFlags    CurrentAccess
          VK_ACCESS_TRANSFER_WRITE_BIT, // VkAccessFlags    NewAccess
          VK_QUEUE_FAMILY_IGNORED,      // uint32_t         CurrentQueueFamily
          VK_QUEUE_FAMILY_IGNORED       // uint32_t         NewQueueFamily
        };
        SetBufferMemoryBarrier( command_buffer[0], VK_PIPELINE_STAGE_VERTEX_SHADER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, { pre_transfer_transition } );

        std::vector<VkBufferCopy> regions = {
          {
            0,                        // VkDeviceSize     srcOffset
            0,                        // VkDeviceSize     dstOffset
            3 * 16 * sizeof( float )  // VkDeviceSize     size
          }
        };
        CopyDataBetweenBuffers( command_buffer[0], vess[i]->getStagingBuffer(), vess[i]->getUniformBuffer(), regions );

        BufferTransition post_transfer_transition = {
          vess[i]->getUniformBuffer(),               // VkBuffer         Buffer
          VK_ACCESS_TRANSFER_WRITE_BIT, // VkAccessFlags    CurrentAccess
          VK_ACCESS_UNIFORM_READ_BIT,   // VkAccessFlags    NewAccess
          VK_QUEUE_FAMILY_IGNORED,      // uint32_t         CurrentQueueFamily
          VK_QUEUE_FAMILY_IGNORED       // uint32_t         NewQueueFamily
        };
        SetBufferMemoryBarrier( command_buffer[0], VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT, { post_transfer_transition } );
      }
    }

    if( PresentQueue.FamilyIndex != GraphicsQueue.FamilyIndex ) {
      ImageTransition image_transition_before_drawing = {
        Swapchain.Images[swapchain_image_index],  // VkImage              Image
        VK_ACCESS_MEMORY_READ_BIT,                // VkAccessFlags        CurrentAccess
        VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT,     // VkAccessFlags        NewAccess
        VK_IMAGE_LAYOUT_UNDEFINED,                // VkImageLayout        CurrentLayout
        VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, // VkImageLayout        NewLayout
        PresentQueue.FamilyIndex,                 // uint32_t             CurrentQueueFamily
        GraphicsQueue.FamilyIndex,                // uint32_t             NewQueueFamily
        VK_IMAGE_ASPECT_COLOR_BIT                 // VkImageAspectFlags   Aspect
      };
      SetImageMemoryBarrier( command_buffer[0], VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, { image_transition_before_drawing } );
    }

    // Drawing
    BeginRenderPass( command_buffer[0], vess[0]->getRenderPass(), framebuffer, { { 0, 0 }, Swapchain.Size }, { { 0.4f, 0.4f, 0.3f, 1.0f }, { 1.0f, 0 } }, VK_SUBPASS_CONTENTS_INLINE );

    

    //BeginRenderPass( command_buffer[0], *RenderPass, framebuffer, { { 0, 0 }, Swapchain.Size }, { { 0.1f, 0.2f, 0.3f, 1.0f }, { 1.0f, 0 } }, VK_SUBPASS_CONTENTS_INLINE );

    BindPipelineObject( command_buffer[0], VK_PIPELINE_BIND_POINT_GRAPHICS, vess[0]->getGraphicsPipeline() );
    
    for(int i = 0; i < 1; i++)
    {

      BindVertexBuffers( command_buffer[0], 0, { { vess[i]->getVertexBuffer(), 0 } } );

      BindDescriptorSets( command_buffer[0], VK_PIPELINE_BIND_POINT_GRAPHICS, vess[i]->getPipelineLayout(), 0, vess[i]->getDescriptorSet(), {} );


      BindPipelineObject( command_buffer[0], VK_PIPELINE_BIND_POINT_GRAPHICS, vess[i]->getGraphicsPipeline() );

      for( size_t ii = 0; ii < vess[i]->getMesh().Parts.size(); ++ii ) {
        
        DrawGeometry( command_buffer[0], vess[i]->getMesh().Parts.at(0).VertexCount, 1, 0, 0 );
      }
    }

    BindPipelineObject( command_buffer[0], VK_PIPELINE_BIND_POINT_GRAPHICS, aas->getGraphicsPipeline() );

    BindDescriptorSets( command_buffer[0], VK_PIPELINE_BIND_POINT_GRAPHICS, aas->getPipelineLayout(), 0, aas->getDescriptorSet(), {} );

    BindVertexBuffers( command_buffer[0], 0, { { aas->getVertexBuffer(), 0 } } );

    DrawGeometry( command_buffer[0], 4, 1, 0, 0 );



    

    ///////////////////////////////////////////////////////
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
    *Swapchain.Handle, Swapchain.Size, Swapchain.ImageViewsRaw, vess[0]->getRenderPass(), {}, prepare_frame, FramesResources );
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

  void OnMouseEvent() {

    static float horizontal_angle = 0.0f;
    static float vertical_angle = 0.0f;

    if( MouseState.Buttons[0].IsPressed)
    {
      
      horizontal_angle += 0.5f * MouseState.Position.Delta.X;
      vertical_angle -= 0.5f * MouseState.Position.Delta.Y;

      if( vertical_angle > 90.0f ) {
        vertical_angle = 90.0f;
      }

      if( vertical_angle < -90.0f ) {
        vertical_angle = -90.0f;
      }

      for(int i = 0; i < Models.size(); i++) vess[i]->UpdateStagingBuffer( false, LogicalDevice.Object.Handle, static_cast<float>(Swapchain.Size.width) / static_cast<float>(Swapchain.Size.height), vertical_angle, horizontal_angle);
    }
  }

  

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