/*
 * Copyright (c) 2015, Frederic Dubouchet
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the Calodox nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY Frederic Dubouchet ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL Frederic DUBOUCHET BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdexcept>
#include <string>
#include <vector>

#ifdef __linux__
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif // __linux__

#ifdef __APPLE__
#include <glut/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif // __APPLE__

#define __CL_ENABLE_EXCEPTIONS
#include "../thirdparty/CL/cl.hpp"

#include "glut_win.hpp"
#include "win_3d_engine.hpp"

win_3d_engine::win_3d_engine(
	callback_next_t callback_next,
    const std::pair<unsigned int, unsigned int>& size,
    bool gpu,
    unsigned int device) :
callback_next_(callback_next),
range_(size),
gpu_(gpu),
device_(device),
texture_id_(0)
{}

win_3d_engine::~win_3d_engine() {}

void win_3d_engine::init()
{
    glClearColor(0, 0, 0, 0);
    gluOrtho2D(-1, 1, -1, 1);
    glGenTextures(1, &texture_id_);
}

void win_3d_engine::display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    {
        glPushMatrix();
        glBegin(GL_QUADS);
        {
            glTexCoord2f(0, 1);
			glVertex2f(-1, 1);
			glTexCoord2f(1, 1);
			glVertex2f(1, 1);
			glTexCoord2f(1, 0);
			glVertex2f(1, -1);
			glTexCoord2f(0, 0);
			glVertex2f(-1, -1);
        }
        glEnd();
        glPopMatrix();
    }
    glDisable(GL_TEXTURE_2D);
    glFlush();
    glutPostRedisplay();
}

void win_3d_engine::idle()
{
	callback_next_(current_image_);
    glFinish();
    glBindTexture(GL_TEXTURE_2D, texture_id_);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA,
        range_.first,
        range_.second,
        0,
        GL_BGRA,
        GL_UNSIGNED_BYTE,
        &current_image_[0]);
    glFinish();
}

void win_3d_engine::reshape(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, w, h);
	glMatrixMode(GL_MODELVIEW);
	glFinish();
}

void win_3d_engine::mouse_event(int button, int state, int x, int y) {}

void win_3d_engine::mouse_move(int x, int y) {}

void win_3d_engine::keyboard(unsigned char key, int x, int y) {}

void win_3d_engine::finish() {}
