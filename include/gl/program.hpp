/*

PICCANTE
The hottest HDR imaging library!
http://vcg.isti.cnr.it/piccante

Copyright (C) 2014
Visual Computing Laboratory - ISTI CNR
http://vcg.isti.cnr.it
First author: Francesco Banterle

This Source Code Form is subject to the terms of the Mozilla Public
License, v. 2.0. If a copy of the MPL was not distributed with this
file, You can obtain one at http://mozilla.org/MPL/2.0/.

*/

#ifndef PIC_GL_PROGRAM_HPP
#define PIC_GL_PROGRAM_HPP

#include <string>

namespace pic {

class ProgramGL
{
protected:
    GLint bCheckStatus;
    GLenum type;
    GLuint object;
    std::string source;

    /**
     * @brief checkShaderStatus
     * @return
     */
    bool checkShaderStatus()
    {
        log.clear();

        bCheckStatus = GL_FALSE;
        glGetShaderiv(object, GL_COMPILE_STATUS, &bCheckStatus);

        //get the log in case of failure
        if(bCheckStatus == GL_FALSE) {
            GLint max_length = -1;
            glGetShaderiv(object, GL_INFO_LOG_LENGTH, &max_length);

            std::vector<GLchar> error(max_length);
            glGetShaderInfoLog(object, max_length, &max_length, &error[0]);

            glDeleteShader(object);
            object = 0;

            log += "-----------------------------------------\n";
            log += "-- This shader was not compiled!\n";
            log += "-----------------------------------------\n";

            return false;
        } else {
            log += "-----------------------------------------\n";
            log += "-- This shader was compiled successfully!\n";
            log += "-----------------------------------------\n";

            return true;
        }
    }

    /**
     * @brief checkProgramStatus
     * @return
     */
    bool checkProgramStatus()
    {
        bCheckStatus = GL_FALSE;
        glGetProgramiv(object, GL_LINK_STATUS, &bCheckStatus);

        //get the log in case of failure
        if(bCheckStatus == GL_FALSE) {
            GLint max_length = -1;
            glGetProgramiv(object, GL_INFO_LOG_LENGTH, &max_length);

            std::vector<GLchar> error(max_length);
            glGetProgramInfoLog(object, max_length, &max_length, &error[0]);

            glDeleteProgram(object);
            object = 0;

            log += "----------------------------------------\n";
            log += "-- This program was not linked!\n";
            log += "----------------------------------------\n";

            return false;
        } else {
            log += "----------------------------------------\n";
            log += "-- This program was linked successfully!\n";
            log += "----------------------------------------\n";

            return true;
        }
    }

public:
    std::string log;

    ProgramGL()
    {
        SetNULL();
    }

    ProgramGL( std::string version,
               std::string extensions,
               std::string source,
               GLenum type)
    {
        SetNULL();
        setupShader(version, extensions, source, type);
    }

    ProgramGL(std::vector<ProgramGL*> &shaders)
    {
        setupProgram(shaders);
    }

    ~ProgramGL()
    {
        if(this->object != 0) {
            glDeleteShader(object);
            this->object = 0;
        }
    }

    /**
     * @brief SetNULL
     */
    void SetNULL()
    {
        this->type = 0;
        this->object = 0;
        this->log = "";
        this->source = "";
        this->bCheckStatus = GL_FALSE;
    }

    /**
     * @brief getObject
     * @return
     */
    GLuint getObject()
    {
        return object;
    }

    /**
     * @brief setupProgram
     * @param shaders
     * @return
     */
    bool setupProgram(std::vector<ProgramGL*> &shaders)
    {
        object = glCreateProgram();

        for(unsigned int i = 0; i < shaders.size(); i++)
        {
            GLuint tmp = shaders[i]->getObject();
            if(tmp != 0) {
                glAttachShader(object, tmp);
            }
        }

        glLinkProgram(object);

        return checkProgramStatus();
    }

    /**
     * @brief setupShader
     * @param version
     * @param extensions
     * @param source
     * @param type
     * @return
     */
    bool setupShader( std::string version_number,
                std::string extensions,
                std::string source,
                GLenum type)
    {
        this->type = type;

        object = glCreateShader(type);

        this->source.clear();

        //create full source
        if(!version.empty()) {
            this->source += "#version ";
            this->source += version_number;
            this->source += "\n";
        }

        if(!extensions.empty()) {
            this->source += extensions;
            this->source += "\n";
        }

        if(!source.empty()) {
            this->source += source;
        }

        const GLchar *tmp = (const GLchar *) this->source.c_str();
        glShaderSource(object, 1, &tmp, 0);
        glCompileShader(object);

        return checkShaderStatus();
    }

/*
    inline void program::uniform(const char *name, int v0)
    {
        glUniform1i(getLocation(name), GLint(v0));

        this->uniform(this->uniform_location(name), v0);
    }
*/
};

} // end namespace pic

#endif /* PIC_GL_PROGRAM_HPP */

