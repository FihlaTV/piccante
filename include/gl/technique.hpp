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

#ifndef PIC_GL_TECHNIQUE_HPP
#define PIC_GL_TECHNIQUE_HPP

#include <string>

#include "GL/program.hpp"

namespace pic {

/**
 * @brief The TechniqueGL class
 */
class TechniqueGL{
protected:
    std::vector<ProgramGL*> shaders;
    ProgramGL main;

    /**
     * @brief getLocation
     * @param name
     * @return
     */
    GLuint getLocation(const char *name)
    {
        return glGetUniformLocation(main.getObject(), name);
    }

public:
    TechniqueGL()
    {

    }

    bool init( std::string version_number,
               std::string vertex_shader_source,
               std::string fragment_shader_source)
    {
        ProgramGL *vss = new ProgramGL(version_number, "", vertex_shader_source, GL_VERTEX_SHADER);
        ProgramGL *fss = new ProgramGL(version_number, "", fragment_shader_source, GL_FRAGMENT_SHADER);
        shaders.push_back(vss);
        shaders.push_back(fss);

        bool bCheck = main.setupProgram(shaders);

        for(unsigned int i = 0; i < shaders.size(); i++) {
            printf("%s", shaders[i]->log.c_str());
        }

        printf("%s", main.log.c_str());

        return bCheck;
    }

    /**
     * @brief bind
     */
    void bind()
    {
        glUseProgram(main.getObject());
    }

    /**
     * @brief unbind
     */
    void unbind()
    {
        glUseProgram(0);
    }

    /**
     * @brief link
     */
    void link()
    {
        glLinkProgram(main.getObject());
    }

    /**
     * @brief setOutputFragmentShaderIndex
     * @param fragment_output_color_name
     * @param index
     */
    void setOutputFragmentShaderIndex(const char *fragment_output_color_name, unsigned int index)
    {
        glBindFragDataLocation(main.getObject(), GLuint(index), fragment_output_color_name);
    }

    /**
     * @brief setAttributeIndex
     * @param attribute_name
     * @param index
     */
    void setAttributeIndex(const char *attribute_name, unsigned int index)
    {
        glBindAttribLocation(main.getObject(), GLuint(index), attribute_name);
    }


    /**
     * @brief SetUniform
     * @param name_uniform
     * @param value0
     */
    void SetUniform(const char *name_uniform, int value0)
    {
        glUniform1i(getLocation(name_uniform), GLint(value0));
    }

    /**
     * @brief SetUniform
     * @param name_uniform
     * @param value0
     */
    void SetUniform(const char *name_uniform, float value0)
    {
        glUniform1f(getLocation(name_uniform), GLfloat(value0));
    }
};

} // end namespace pic

#endif /* PIC_GL_TECHNIQUE_HPP */

