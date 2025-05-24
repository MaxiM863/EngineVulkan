#include "Graphics.h"

using namespace VulkanCookbook;

class Graphics : public VulkanCookbook::VulkanCookbookSample
{

  sdlTextEngine*                      aas;
 
  vessel** vess;
  std::vector<Mesh> Models;

  fume* fumee;

  fume* fumee2;

  bool UpdateUniformBuffer;

public:

  HWND* hWnd;

  OrbitingCamera Camera;

  Matrix4x4 additiveRotation;


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

  Camera = OrbitingCamera( Vector3{ 0.0f, 0.0f, 0.0f }, 4.0f );

  vess = new vessel*[Models.size()];

  for(int i = 0 ; i < Models.size(); i++)
  {
    
    vess[i] = new vessel();
 
    vess[i]->Initialize(LogicalDevice.Object.Handle, PhysicalDevice, GraphicsQueue, FramesResources.front().CommandBuffer[0], Swapchain, Models[i], Camera);
  }
  
  fumee = new fume();

  fumee->Initialize(LogicalDevice.Object.Handle, PhysicalDevice, GraphicsQueue, FramesResources.front().CommandBuffer[0], Swapchain, Camera, "Data/Textures/explo.png");

  for(int i = 0; i < 20; i++)
  {

    int rx = rand() % 30;
    int ry = rand() % 30;
    int rz = rand() % 30;

    fumee->randomization.push_back(PrepareRotationMatrix(rx, Vector3{1.0f,0.0f,0.0f}) * PrepareRotationMatrix(ry, Vector3{0.0f,1.0f,0.0f}) * PrepareRotationMatrix(rz, Vector3{0.0f,0.0f,1.0f}));
    fumee->durationTime.push_back(rand()%4);
    fumee->deltaTime.push_back(0.0f);    
  }

  fumee2 = new fume();

  fumee2->Initialize(LogicalDevice.Object.Handle, PhysicalDevice, GraphicsQueue, FramesResources.front().CommandBuffer[0], Swapchain, Camera, "Data/Textures/b.png");

  for(int i = 0; i < 20; i++)
  {

    int rx = rand() % 30;
    int ry = rand() % 30;
    int rz = rand() % 30;

    fumee2->randomization.push_back(PrepareRotationMatrix(rx, Vector3{1.0f,0.0f,0.0f}) * PrepareRotationMatrix(ry, Vector3{0.0f,1.0f,0.0f}) * PrepareRotationMatrix(rz, Vector3{0.0f,0.0f,1.0f}));
    fumee2->durationTime.push_back(rand()%15);
    fumee2->deltaTime.push_back(0.0f);    
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

    if(fumee->Bilboards.Parts[0].VertexCount < 20 && rand() % 20 == 0)
    {
      int rx = rand() % 30;
      int ry = rand() % 30;
      int rz = rand() % 30;

      fumee->randomization.push_back(PrepareRotationMatrix(rx, Vector3{1.0f,0.0f,0.0f}) * PrepareRotationMatrix(ry, Vector3{0.0f,1.0f,0.0f}) * PrepareRotationMatrix(rz, Vector3{0.0f,0.0f,1.0f}));
      fumee->durationTime.push_back(2);
      fumee->deltaTime.push_back(0.0f);

      fumee->Bilboards.Data.push_back(0.0f);
      fumee->Bilboards.Data.push_back(1.1f);
      fumee->Bilboards.Data.push_back(2.5f);

      fumee->Bilboards.Parts[0].VertexCount++;
    }

    for(int i  = 0; i < fumee->Bilboards.Parts[0].VertexCount; i++)
    {
      
      fumee->deltaTime[i] += TimerState.GetDeltaTime();

      if(fumee->durationTime[i] < fumee->deltaTime[i])
      {
        fumee->randomization.erase(fumee->randomization.begin() + i);
        fumee->durationTime.erase(fumee->durationTime.begin() + i);
        fumee->deltaTime.erase(fumee->deltaTime.begin() + i);
        fumee->Bilboards.Data.erase(fumee->Bilboards.Data.begin()+3*i);
        fumee->Bilboards.Data.erase(fumee->Bilboards.Data.begin()+3*i);
        fumee->Bilboards.Data.erase(fumee->Bilboards.Data.begin()+3*i);

        fumee->Bilboards.Parts[0].VertexCount--;
      }
      else
      {
        
        Vector3 tmpPos = Vector3{0.0f, 0.75f, -1.0f};

        Vector3 asd = tmpPos + Transform(Vector3{0.0f, 0.0f, 0.0f}, fumee->randomization[i] * PrepareTranslationMatrix(0.0f, 2.8f*fumee->deltaTime[i], 0.0f));

        fumee->Bilboards.Data[3*i+0] = asd[0];
        fumee->Bilboards.Data[3*i+1] = asd[1];
        fumee->Bilboards.Data[3*i+2] = asd[2];
      }
    }

    BufferTransition pre_transfer_transition = {
      fumee->getStagingBuffer2(),               // VkBuffer         Buffer
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
        20 * 3 * sizeof( float )  // VkDeviceSize     size
      }
    };
    CopyDataBetweenBuffers( command_buffer[0], fumee->getStagingBuffer2(), *fumee->VertexBuffer, regions );

    BufferTransition post_transfer_transition = {
      *fumee->VertexBuffer,               // VkBuffer         Buffer
      VK_ACCESS_TRANSFER_WRITE_BIT, // VkAccessFlags    CurrentAccess
      VK_ACCESS_UNIFORM_READ_BIT,   // VkAccessFlags    NewAccess
      VK_QUEUE_FAMILY_IGNORED,      // uint32_t         CurrentQueueFamily
      VK_QUEUE_FAMILY_IGNORED       // uint32_t         NewQueueFamily
    };
    SetBufferMemoryBarrier( command_buffer[0], VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT, { post_transfer_transition } );
  
    ////////////////////

    if(fumee2->Bilboards.Parts[0].VertexCount < 20 && rand() % 20 == 0)
    {
      int rx = rand() % 30;
      int ry = rand() % 30;
      int rz = rand() % 30;

      fumee2->randomization.push_back(PrepareRotationMatrix(rx, Vector3{1.0f,0.0f,0.0f}) * PrepareRotationMatrix(ry, Vector3{0.0f,1.0f,0.0f}) * PrepareRotationMatrix(rz, Vector3{0.0f,0.0f,1.0f}));
      fumee2->durationTime.push_back(rand() % 15);
      fumee2->deltaTime.push_back(0.0f);

      fumee2->Bilboards.Data.push_back(0.0f);
      fumee2->Bilboards.Data.push_back(1.1f);
      fumee2->Bilboards.Data.push_back(2.5f);

      fumee2->Bilboards.Parts[0].VertexCount++;
    }

    for(int i  = 0; i < fumee2->Bilboards.Parts[0].VertexCount; i++)
    {
      
      fumee2->deltaTime[i] += TimerState.GetDeltaTime();

      if(fumee2->durationTime[i] < fumee2->deltaTime[i])
      {
        fumee2->randomization.erase(fumee2->randomization.begin() + i);
        fumee2->durationTime.erase(fumee2->durationTime.begin() + i);
        fumee2->deltaTime.erase(fumee2->deltaTime.begin() + i);
        fumee2->Bilboards.Data.erase(fumee2->Bilboards.Data.begin()+3*i);
        fumee2->Bilboards.Data.erase(fumee2->Bilboards.Data.begin()+3*i);
        fumee2->Bilboards.Data.erase(fumee2->Bilboards.Data.begin()+3*i);

        fumee2->Bilboards.Parts[0].VertexCount--;
      }
      else
      {
        
        Vector3 tmpPos = Vector3{0.0f, 0.75f, -1.0f};

        Vector3 asd = tmpPos + Transform(Vector3{0.0f, 0.0f, 0.0f}, fumee2->randomization[i] * PrepareTranslationMatrix(0.0f, 2.8f*fumee2->deltaTime[i], 0.0f));

        fumee2->Bilboards.Data[3*i+0] = asd[0];
        fumee2->Bilboards.Data[3*i+1] = asd[1];
        fumee2->Bilboards.Data[3*i+2] = asd[2];
      }
    }

    pre_transfer_transition = {
      fumee2->getStagingBuffer2(),               // VkBuffer         Buffer
      VK_ACCESS_UNIFORM_READ_BIT,   // VkAccessFlags    CurrentAccess
      VK_ACCESS_TRANSFER_WRITE_BIT, // VkAccessFlags    NewAccess
      VK_QUEUE_FAMILY_IGNORED,      // uint32_t         CurrentQueueFamily
      VK_QUEUE_FAMILY_IGNORED       // uint32_t         NewQueueFamily
    };
    SetBufferMemoryBarrier( command_buffer[0], VK_PIPELINE_STAGE_VERTEX_SHADER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, { pre_transfer_transition } );

    regions = {
      {
        0,                        // VkDeviceSize     srcOffset
        0,                        // VkDeviceSize     dstOffset
        20 * 3 * sizeof( float )  // VkDeviceSize     size
      }
    };
    CopyDataBetweenBuffers( command_buffer[0], fumee2->getStagingBuffer2(), *fumee2->VertexBuffer, regions );

    post_transfer_transition = {
      *fumee2->VertexBuffer,               // VkBuffer         Buffer
      VK_ACCESS_TRANSFER_WRITE_BIT, // VkAccessFlags    CurrentAccess
      VK_ACCESS_UNIFORM_READ_BIT,   // VkAccessFlags    NewAccess
      VK_QUEUE_FAMILY_IGNORED,      // uint32_t         CurrentQueueFamily
      VK_QUEUE_FAMILY_IGNORED       // uint32_t         NewQueueFamily
    };
    SetBufferMemoryBarrier( command_buffer[0], VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT, { post_transfer_transition } );

    ///////////////////

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

    fumee->Draw_1(command_buffer[0]);
    fumee2->Draw_1(command_buffer[0]);

    // Drawing
    BeginRenderPass( command_buffer[0], vess[0]->getRenderPass(), framebuffer, { { 0, 0 }, Swapchain.Size }, { { 0.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0 } }, VK_SUBPASS_CONTENTS_INLINE );

    fumee->draw_2(command_buffer[0], swapchain_image_index);
    fumee2->draw_2(command_buffer[0], swapchain_image_index);

    //BeginRenderPass( command_buffer[0], *RenderPass, framebuffer, { { 0, 0 }, Swapchain.Size }, { { 0.1f, 0.2f, 0.3f, 1.0f }, { 1.0f, 0 } }, VK_SUBPASS_CONTENTS_INLINE );

    BindPipelineObject( command_buffer[0], VK_PIPELINE_BIND_POINT_GRAPHICS, vess[0]->getGraphicsPipeline() );
    
    for(int i = 0; i < Models.size(); i++)
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

    additiveRotation = vess[0]->translationMatrix;

    

    fumee->UpdateStagingBuffer(true, LogicalDevice.Object.Handle, static_cast<float>(Swapchain.Size.width) / static_cast<float>(Swapchain.Size.height), MouseState.Position.Delta.X, MouseState.Position.Delta.Y, additiveRotation , Camera);
    fumee2->UpdateStagingBuffer(true, LogicalDevice.Object.Handle, static_cast<float>(Swapchain.Size.width) / static_cast<float>(Swapchain.Size.height), MouseState.Position.Delta.X, MouseState.Position.Delta.Y, additiveRotation , Camera);
    

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

      for(int i = 0; i < Models.size(); i++) vess[i]->UpdateStagingBuffer( false, LogicalDevice.Object.Handle, static_cast<float>(Swapchain.Size.width) / static_cast<float>(Swapchain.Size.height), vertical_angle, horizontal_angle, Camera);

      
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