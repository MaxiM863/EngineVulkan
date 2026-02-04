#include "Graphics.h"

using namespace VulkanCookbook;

class Graphics : public VulkanCookbook::VulkanCookbookSample
{

  sdlTextEngine*                      aas;
 
  bool UpdateUniformBuffer;

  std::vector<ALuint> playlist;

  Client client;
  
public:

  char playerNbr = '0';

  float horizontal_angle = 0.0f;
  float vertical_angle = 0.0f;

  float horizontal_angle2 = 0.0f;
  float vertical_angle2 = 0.0f;

  HWND* hWnd;

  OrbitingCamera Camera;

  Matrix4x4 additiveRotation;

  std::vector<char> loadWAV(const std::string& filename, ALenum& format, ALsizei& freq) {
    // Simplified WAV loading logic (use a library like dr_wav for production)
    std::ifstream file(filename, std::ios::binary);
    std::vector<char> buffer((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
    format = AL_FORMAT_MONO16; // Example format
    freq = 44100; // Example frequency
    return buffer;
  }
  ALuint* buffer;
  ALuint* source;
  ALCdevice* device = alcOpenDevice(nullptr);
  ALCcontext* context = alcCreateContext(device, nullptr);

  ALfloat* state = new float;
        
  MAP map1;

  ~Graphics() {

    alDeleteSources(20, &source[0]);
    alDeleteBuffers(1, &buffer[0]);
    alcDestroyContext(context);
    alcCloseDevice(device);
  }

virtual bool Initialize( WindowParameters window_parameters, HWND hWnd ) override {
 
  
  alcMakeContextCurrent(context);

  source = new ALuint[21];
  buffer = new ALuint[2];
  
  alGenBuffers(2, buffer);
  alGenSources(21, source);

  ALenum format;
  ALsizei freq;
  auto data = loadWAV("Data/Sounds/engineRockets.wav", format, freq);
  alBufferData(buffer[0], format, data.data(), data.size(), freq);

  auto data2 = loadWAV("Data/Sounds/test.wav", format, freq);
  alBufferData(buffer[1], format, data2.data(), data2.size(), freq);

  alSourcei(source[20], AL_BUFFER, buffer[1]);
  alSourcePlay(source[20]);
  
  *state = 0.6f;
  
  if( !InitializeVulkan( window_parameters, nullptr, VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT, false ) ) {

    return false;
  }
  
  //client.connectServer(hWnd);

  float pos_x0 = -0.15f;
  float pos_x1 = 0.15f;
  float pos_y0 = 0.80f;
  float pos_y1 = 0.86f;
  
  aas = new sdlTextEngine();

  aas->Initialize("Demo-1", 150, 0x00FF0000, 0x00FFFFFF, pos_x0, pos_x1, pos_y0, pos_y1, 1000, 200, LogicalDevice.Object.Handle, PhysicalDevice, GraphicsQueue, FramesResources.front().CommandBuffer[0], Swapchain);

  Camera = OrbitingCamera( Vector3{ 0.0f, 0.0f, 0.0f }, 5.0f );

  map1.Initialize( LogicalDevice.Object.Handle, PhysicalDevice, GraphicsQueue, FramesResources.front().CommandBuffer[0], Swapchain, Mesh(), Camera, Vector3{0.0f,10.0f,0.0f} );

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

    

    /////////////////////////////////////////////////////// DRAW-1 OBJECTS HERE

    map1.Draw_1(command_buffer[0], TimerState, source, buffer, swapchain_image_index);

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

    

    // Drawing
    BeginRenderPass( command_buffer[0], map1.getRenderPass(), framebuffer, { { 0, 0 }, Swapchain.Size }, { { 0.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 0 } }, VK_SUBPASS_CONTENTS_INLINE );

    // Draw-2 OBJECTS HERE

    map1.Draw_2( *LogicalDevice, command_buffer[0], Swapchain, swapchain_image_index, vertical_angle, horizontal_angle, Camera, MouseState );

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
    *Swapchain.Handle, Swapchain.Size, Swapchain.ImageViewsRaw, aas->getRenderPass(), {}, prepare_frame, FramesResources );
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

    

    if( MouseState.Buttons[0].IsPressed)
    {
      float horizontal_angle = 0.0f;
      float vertical_angle = 0.0f;
      
      horizontal_angle += 0.5f * MouseState.Position.Delta.X;
      vertical_angle -= 0.5f * MouseState.Position.Delta.Y;

      if( vertical_angle > 180.0f ) {
        vertical_angle = 180.0f;
      }

      if( vertical_angle < -180.0f ) {
        vertical_angle = -180.0f;
      }

      Camera.RotateHorizontally(horizontal_angle);
      Camera.RotateVertically(vertical_angle);
    }
  }

  void OnKeyEvent() {

    char* dddf = new char[200];

    char destination = '0';
    if(playerNbr == '0') destination = '1';

    dddf[0] = destination;

    dddf[1] = '0';
    dddf[2] = '0';
    dddf[3] = '0';
    dddf[4] = '0';
    dddf[5] = '0';
    dddf[6] = '\0';

    

    float angleS = 1.0f;

    

    if(KeyState.dturn == true)
    {
      dddf[2] = '1';
      horizontal_angle += angleS;
    }
    if(KeyState.uturn == true)
    {
      dddf[3] = '1';
      horizontal_angle -= angleS;
    }
    if(KeyState.lturn == true)
    {
      dddf[4] = '1';
      vertical_angle += angleS;
    }
    if(KeyState.rturn == true)
    {
      dddf[5] = '1';
      vertical_angle -= angleS;
    }   
    

    client.sendMsg(dddf);
  }

  void OnServerEvent() {

    char* data = ServerState.data;

    if(data[0] == playerNbr)
    {
      float angleS = 1.0f;

      
      if(data[2] == '1')
      {
        horizontal_angle2 -= angleS;
      }
      if(data[3] == '1')
      {
        horizontal_angle2 += angleS;
      }
      if(data[4] == '1')
      {
        vertical_angle2 -= angleS;
      }
      if(data[5] == '1')
      {
        vertical_angle2 += angleS;
      }
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