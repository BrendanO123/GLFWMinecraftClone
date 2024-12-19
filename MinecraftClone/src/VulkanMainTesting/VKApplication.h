#pragma once

#include <string.h>
#include <iostream>
#include <optional>

#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

#include <stdexcept>
#include <cstdlib>

using namespace std;

const vector<const char*> validationLayers = {
    "VK_LAYER_KHRONOS_validation"
};
const bool enableValidationLayers = true;

struct QueueFamilyIndices {
    optional<uint32_t> graphicsFamily;
};

class Application{
    public:
        GLFWwindow* window;
        int width = 640, height = 480;

        Application(){init();}
        int run(){
            int returnVal = mainLoop();
            if(returnVal){return returnVal;}
            return cleanUp();
        }

        bool checkValidationLayerSupport();

    private:
        VkInstance instance;
        VkPhysicalDevice physicalDevice = VK_NULL_HANDLE;

        int init();
        bool isDeviceSuitable(VkPhysicalDevice device);
        int pickPhysicalDevice();
        int createInstance();
        QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
        int mainLoop();

        int cleanUp(){
            vkDestroyInstance(instance, nullptr);
            glfwDestroyWindow(window);
            glfwTerminate();
            return EXIT_SUCCESS;
        }
};