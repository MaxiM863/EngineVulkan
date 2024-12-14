build: clean library remObjets
	g++ -std=c++14 -o ./build_linux/main_max ./Samples/Source_Files/11_Lighting/02-Rendering_a_geometry_with_fragment_specular_lighting/main.cpp -L. liball.a -I ./External -I ./Library/Source_Files -I . -I ./Samples/Common_Files -I ./Library/Common_Files -lX11 -D VK_USE_PLATFORM_XLIB_KHR

library: ll
	ranlib liball.a
	
ll: lo others
	ar rc liball.a *.o	
	
others:
	g++ -std=c++14 -c ./Samples/Common_Files/*.cpp -I ./Library/Common_Files -I ./External -I ./Library/Source_Files -D VK_USE_PLATFORM_XLIB_KHR

lo:
	g++ -std=c++14 -c ./Library/Common_Files/*.cpp ./Library/Source_Files/01_Instance_and_Devices/*.cpp ./Library/Source_Files/02_Image_Presentation/*.cpp ./Library/Source_Files/03_Command_Buffers_and_Synchronization/*.cpp ./Library/Source_Files/04_Resources_and_Memory/*.cpp ./Library/Source_Files/05_Descriptor_Sets/*.cpp ./Library/Source_Files/06_Render_Passes_and_Framebuffers/*.cpp ./Library/Source_Files/08_Graphics_and_Compute_Pipelines/*.cpp ./Library/Source_Files/09_Command_Recording_and_Drawing/*.cpp ./Library/Source_Files/10_Helper_Recipes/*.cpp -I ./Library/Source_Files -I ./Library/Common_Files -I ./External -D VK_USE_PLATFORM_XLIB_KHR
	
clean:
	rm *.o
	rm *.a

remObjets:
	rm *.o