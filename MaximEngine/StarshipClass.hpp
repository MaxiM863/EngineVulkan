#include "fume.hpp"
#include "vessel.hpp"

#include <AL/al.h>
#include <AL/alc.h>

using namespace VulkanCookbook;

class Starship {

  std::vector<Mesh> Models;

  fume* fumee;

  fume* fumee2;

  vessel** vess;

  public:

    VkRenderPass GetRenderPass() { return vess[0]->getRenderPass(); };

    bool Initialize(VkDevice LogicalDevice, VkPhysicalDevice PhysicalDevice, QueueParameters& GraphicsQueue, VkCommandBuffer& CommandBuffer, SwapchainParameters& Swapchain, OrbitingCamera Camera, Vector3 posIni)
    {
        Load L;  
        
        // Vertex data
        if( !L.Load3DModelFromTxtFile( "Data/Models/vessel_0.txt", Models ) ) {
            
            return false;
        }

        vess = new vessel*[Models.size()];

        for(int i = 0 ; i < Models.size(); i++)
        {
            
            vess[i] = new vessel();
        
            vess[i]->Initialize(LogicalDevice, PhysicalDevice, GraphicsQueue, CommandBuffer, Swapchain, Models[i], Camera, posIni);
        }
        
        fumee = new fume();

        fumee->Initialize(LogicalDevice, PhysicalDevice, GraphicsQueue, CommandBuffer, Swapchain, Camera, "Data/Textures/explo.png");

        for(int i = 0; i < 20; i++)
        {

            int rx = 15 - rand() % 30;
            int ry = 15 - rand() % 30;
            int rz = 15 - rand() % 30;

            fumee->randomization.push_back(PrepareRotationMatrix(rx, Vector3{1.0f,0.0f,0.0f}) * PrepareRotationMatrix(ry, Vector3{0.0f,1.0f,0.0f}) * PrepareRotationMatrix(rz, Vector3{0.0f,0.0f,1.0f}));
            fumee->durationTime.push_back(rand()%10);
            fumee->deltaTime.push_back(0.0f);    
        }

        fumee2 = new fume();

        fumee2->Initialize(LogicalDevice, PhysicalDevice, GraphicsQueue, CommandBuffer, Swapchain, Camera, "Data/Textures/b.png");

        for(int i = 0; i < 20; i++)
        {

            int rx = 15 - rand() % 30;
            int ry = 15 - rand() % 30;
            int rz = 15 - rand() % 30;

            fumee2->randomization.push_back(PrepareRotationMatrix(rx, Vector3{1.0f,0.0f,0.0f}) * PrepareRotationMatrix(ry, Vector3{0.0f,1.0f,0.0f}) * PrepareRotationMatrix(rz, Vector3{0.0f,0.0f,1.0f}));
            fumee2->durationTime.push_back(rand()%20);
            fumee2->deltaTime.push_back(0.0f);    
        }  
    }

    bool Draw_1(VkCommandBuffer command_buffer, TimerStateParameters TimerState, ALuint* buffer, ALuint* source, int swapchain_image_index)
    {
        if( true ) {
      
            for(int i = 0 ; i < Models.size(); i++)
            {
      
              BufferTransition pre_transfer_transition = {
                vess[i]->getUniformBuffer(),               // VkBuffer         Buffer
                VK_ACCESS_UNIFORM_READ_BIT,   // VkAccessFlags    CurrentAccess
                VK_ACCESS_TRANSFER_WRITE_BIT, // VkAccessFlags    NewAccess
                VK_QUEUE_FAMILY_IGNORED,      // uint32_t         CurrentQueueFamily
                VK_QUEUE_FAMILY_IGNORED       // uint32_t         NewQueueFamily
              };
              SetBufferMemoryBarrier( command_buffer, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, { pre_transfer_transition } );
      
              std::vector<VkBufferCopy> regions = {
                {
                  0,                        // VkDeviceSize     srcOffset
                  0,                        // VkDeviceSize     dstOffset
                  3 * 16 * sizeof( float )  // VkDeviceSize     size
                }
              };
              CopyDataBetweenBuffers( command_buffer, vess[i]->getStagingBuffer(), vess[i]->getUniformBuffer(), regions );
      
              BufferTransition post_transfer_transition = {
                vess[i]->getUniformBuffer(),               // VkBuffer         Buffer
                VK_ACCESS_TRANSFER_WRITE_BIT, // VkAccessFlags    CurrentAccess
                VK_ACCESS_UNIFORM_READ_BIT,   // VkAccessFlags    NewAccess
                VK_QUEUE_FAMILY_IGNORED,      // uint32_t         CurrentQueueFamily
                VK_QUEUE_FAMILY_IGNORED       // uint32_t         NewQueueFamily
              };
              SetBufferMemoryBarrier( command_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT, { post_transfer_transition } );             
          }
      
          if(fumee->Bilboards.Parts[0].VertexCount < 20 && rand() % 20 == 0)
          {
            int rx = 15 - rand() % 30;
            int ry = 15 - rand() % 30;
            int rz = 15 - rand() % 30;
      
            fumee->randomization.push_back(PrepareRotationMatrix(rx, Vector3{1.0f,0.0f,0.0f}) * PrepareRotationMatrix(ry, Vector3{0.0f,1.0f,0.0f}) * PrepareRotationMatrix(rz, Vector3{0.0f,0.0f,1.0f}));
            fumee->durationTime.push_back(rand()%10);
            fumee->deltaTime.push_back(0.0f);
      
            fumee->Bilboards.Data.push_back(0.0f);
            fumee->Bilboards.Data.push_back(1.1f);
            fumee->Bilboards.Data.push_back(2.5f);
      
            int missing = 0;
            for(int i = 0; i < 20; i++)
            {
              bool test = false;
              for(int j = 0 ; j < fumee->Bilboards.Data.size(); j++)
              {
                if(fumee->Bilboards.Data[j] == i)
                {
                  test = true;
                  break;
                }
              }
      
              if(!test)
              {
                missing = i;
                break;
              }
            }
      
            fumee->Bilboards.Data.push_back(missing);
      
            fumee->autonomous[missing] = vess[0]->translationMatrix;
      
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
              fumee->Bilboards.Data.erase(fumee->Bilboards.Data.begin()+4*i);
              fumee->Bilboards.Data.erase(fumee->Bilboards.Data.begin()+4*i);
              fumee->Bilboards.Data.erase(fumee->Bilboards.Data.begin()+4*i);
              fumee->Bilboards.Data.erase(fumee->Bilboards.Data.begin()+4*i);
      
              fumee->Bilboards.Parts[0].VertexCount--;
              
              alSourcei(source[i], AL_BUFFER, buffer[0]);
              alSourcePlay(source[i]); 
            }
            else
            {
              
              Vector3 tmpPos = Vector3{0.0f, 0.75f, -1.0f};
      
              Vector3 asd = tmpPos + Transform(Vector3{0.0f, 0.0f, 0.0f}, fumee->randomization[i] * PrepareTranslationMatrix(0.0f, 2.8f*fumee->deltaTime[i], 0.0f));
      
              fumee->Bilboards.Data[4*i+0] = asd[0];
              fumee->Bilboards.Data[4*i+1] = asd[1];
              fumee->Bilboards.Data[4*i+2] = asd[2];       
            }
          }
      
          BufferTransition pre_transfer_transition = {
            fumee->getStagingBuffer2(),               // VkBuffer         Buffer
            VK_ACCESS_UNIFORM_READ_BIT,   // VkAccessFlags    CurrentAccess
            VK_ACCESS_TRANSFER_WRITE_BIT, // VkAccessFlags    NewAccess
            VK_QUEUE_FAMILY_IGNORED,      // uint32_t         CurrentQueueFamily
            VK_QUEUE_FAMILY_IGNORED       // uint32_t         NewQueueFamily
          };
          SetBufferMemoryBarrier( command_buffer, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, { pre_transfer_transition } );
      
          std::vector<VkBufferCopy> regions = {
            {
              0,                        // VkDeviceSize     srcOffset
              0,                        // VkDeviceSize     dstOffset
              20 * 4 * sizeof( float )  // VkDeviceSize     size
            }
          };
          CopyDataBetweenBuffers( command_buffer, fumee->getStagingBuffer2(), *fumee->VertexBuffer, regions );
      
          BufferTransition post_transfer_transition = {
            *fumee->VertexBuffer,               // VkBuffer         Buffer
            VK_ACCESS_TRANSFER_WRITE_BIT, // VkAccessFlags    CurrentAccess
            VK_ACCESS_UNIFORM_READ_BIT,   // VkAccessFlags    NewAccess
            VK_QUEUE_FAMILY_IGNORED,      // uint32_t         CurrentQueueFamily
            VK_QUEUE_FAMILY_IGNORED       // uint32_t         NewQueueFamily
          };
          SetBufferMemoryBarrier( command_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT, { post_transfer_transition } );
        
          ////////////////////
      
          if(fumee2->Bilboards.Parts[0].VertexCount < 20 && rand() % 20 == 0)
          {
            int rx = 15 - rand() % 30;
            int ry = 15 - rand() % 30;
            int rz = 15 - rand() % 30;
      
            fumee2->randomization.push_back(PrepareRotationMatrix(rx, Vector3{1.0f,0.0f,0.0f}) * PrepareRotationMatrix(ry, Vector3{0.0f,1.0f,0.0f}) * PrepareRotationMatrix(rz, Vector3{0.0f,0.0f,1.0f}));
            fumee2->durationTime.push_back(rand() % 20);
            fumee2->deltaTime.push_back(0.0f);
      
            fumee2->Bilboards.Data.push_back(0.0f);
            fumee2->Bilboards.Data.push_back(1.1f);
            fumee2->Bilboards.Data.push_back(2.5f);
            
            int missing = 0;
            for(int i = 0; i < 20; i++)
            {
              bool test = false;
              for(int j = 0 ; j < fumee2->Bilboards.Data.size(); j++)
              {
                if(fumee2->Bilboards.Data[j] == i)
                {
                  test = true;
                  break;
                }
              }
      
              if(!test)
              {
                missing = i;
                break;
              }
            }
      
            fumee2->Bilboards.Data.push_back(missing);
      
            fumee2->autonomous[missing] = vess[0]->translationMatrix;
      
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
              fumee2->Bilboards.Data.erase(fumee2->Bilboards.Data.begin()+4*i);
              fumee2->Bilboards.Data.erase(fumee2->Bilboards.Data.begin()+4*i);
              fumee2->Bilboards.Data.erase(fumee2->Bilboards.Data.begin()+4*i);
              fumee2->Bilboards.Data.erase(fumee2->Bilboards.Data.begin()+4*i);
      
              fumee2->Bilboards.Parts[0].VertexCount--;
            }
            else
            {
              
              Vector3 tmpPos = Vector3{0.0f, 0.75f, -1.0f};
      
              Vector3 asd = tmpPos + Transform(Vector3{0.0f, 0.0f, 0.0f}, fumee2->randomization[i] * PrepareTranslationMatrix(0.0f, 2.8f*fumee2->deltaTime[i], 0.0f));
      
              fumee2->Bilboards.Data[4*i+0] = asd[0];
              fumee2->Bilboards.Data[4*i+1] = asd[1];
              fumee2->Bilboards.Data[4*i+2] = asd[2];
            }
          }
      
          pre_transfer_transition = {
            fumee2->getStagingBuffer2(),               // VkBuffer         Buffer
            VK_ACCESS_UNIFORM_READ_BIT,   // VkAccessFlags    CurrentAccess
            VK_ACCESS_TRANSFER_WRITE_BIT, // VkAccessFlags    NewAccess
            VK_QUEUE_FAMILY_IGNORED,      // uint32_t         CurrentQueueFamily
            VK_QUEUE_FAMILY_IGNORED       // uint32_t         NewQueueFamily
          };
          SetBufferMemoryBarrier( command_buffer, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT, VK_PIPELINE_STAGE_TRANSFER_BIT, { pre_transfer_transition } );
      
          regions = {
            {
              0,                        // VkDeviceSize     srcOffset
              0,                        // VkDeviceSize     dstOffset
              20 * 4 * sizeof( float )  // VkDeviceSize     size
            }
          };
          CopyDataBetweenBuffers( command_buffer, fumee2->getStagingBuffer2(), *fumee2->VertexBuffer, regions );
      
          post_transfer_transition = {
            *fumee2->VertexBuffer,               // VkBuffer         Buffer
            VK_ACCESS_TRANSFER_WRITE_BIT, // VkAccessFlags    CurrentAccess
            VK_ACCESS_UNIFORM_READ_BIT,   // VkAccessFlags    NewAccess
            VK_QUEUE_FAMILY_IGNORED,      // uint32_t         CurrentQueueFamily
            VK_QUEUE_FAMILY_IGNORED       // uint32_t         NewQueueFamily
          };
          SetBufferMemoryBarrier( command_buffer, VK_PIPELINE_STAGE_TRANSFER_BIT, VK_PIPELINE_STAGE_VERTEX_SHADER_BIT, { post_transfer_transition } );

            fumee->Draw_1(command_buffer);
            fumee2->Draw_1(command_buffer);
        }

        return true;
    }

    bool Draw_2(VkDevice LogicalDevice, VkCommandBuffer& command_buffer, SwapchainParameters& Swapchain, int swapchain_image_index, float vertical_angle, float horizontal_angle, OrbitingCamera Camera, MouseStateParameters MouseState)
    {

        fumee->draw_2(command_buffer, swapchain_image_index);
        fumee2->draw_2(command_buffer, swapchain_image_index);

        //BeginRenderPass( command_buffer[0], *RenderPass, framebuffer, { { 0, 0 }, Swapchain.Size }, { { 0.1f, 0.2f, 0.3f, 1.0f }, { 1.0f, 0 } }, VK_SUBPASS_CONTENTS_INLINE );

        BindPipelineObject( command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vess[0]->getGraphicsPipeline() );
        
        for(int i = 0; i < Models.size(); i++)
        {

            BindVertexBuffers( command_buffer, 0, { { vess[i]->getVertexBuffer(), 0 } } );

            BindDescriptorSets( command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vess[i]->getPipelineLayout(), 0, vess[i]->getDescriptorSet(), {} );


            BindPipelineObject( command_buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, vess[i]->getGraphicsPipeline() );

            for( size_t ii = 0; ii < vess[i]->getMesh().Parts.size(); ++ii ) {
                
                DrawGeometry( command_buffer, vess[i]->getMesh().Parts.at(0).VertexCount, 1, 0, 0 );
            }
        }   
        
        for(int i = 0; i < Models.size(); i++) vess[i]->UpdateStagingBuffer( false, LogicalDevice, static_cast<float>(Swapchain.Size.width) / static_cast<float>(Swapchain.Size.height), vertical_angle, horizontal_angle, Camera); 

        
        fumee->UpdateStagingBuffer(true, LogicalDevice, static_cast<float>(Swapchain.Size.width) / static_cast<float>(Swapchain.Size.height), MouseState.Position.Delta.X, MouseState.Position.Delta.Y, Camera);
        fumee2->UpdateStagingBuffer(true, LogicalDevice, static_cast<float>(Swapchain.Size.width) / static_cast<float>(Swapchain.Size.height), MouseState.Position.Delta.X, MouseState.Position.Delta.Y, Camera);
        
        return true;        
    }

    void setThrust(bool state, char& dddf)
    {
        if(state)
        {
        for(int i = 0; i < Models.size(); i++) vess[i]->UpdateStagingBufferThrust(true);
        dddf = '1';
        }
        else
        {
        for(int i = 0; i < Models.size(); i++) vess[i]->UpdateStagingBufferThrust(false);
        }
    }
};