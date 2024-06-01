/**
 * @file main.cpp
 * @author Krisna Pranav
 * @brief main
 * @version 1.0
 * @date 2024-06-01
 *
 * @copyright Copyright (c) 2024 Krisna Pranav
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include "video_reader.hpp"

int main(int argc, const char **argv)
{
    GLFWwindow *window;

    if (!glfwInit())
    {
        printf("Couldn't init GLFW\n");
        return 1;
    }

    VideoReaderState vr_state;

    if (!video_reader_open(&vr_state, "video_path"))
    {
        printf("Couldn't open video file make sure it exists");
        return 1;
    }

    window = glfwCreateWindow(vr_state.width, vr_state.height, "Video", NULL, NULL);

    if (!window)
    {
        printf("Couldn't open window\n");
        return 1;
    }

    glfwMakeContextCurrent(window);

    glfwMakeContextCurrent(window);

    GLuint tex_handle;
    glGenTextures(1, &tex_handle);
    glBindTexture(GL_TEXTURE_2D, tex_handle);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}