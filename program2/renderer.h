#ifndef _CSCI441_RENDERER_H_
#define _CSCI441_RENDERER_H_

#include <csci441/matrix3.h>

class Renderer {
    Matrix3 itModel_tmp;
public:

    Vector look;

    void render(const Camera& camera, Model& m, const Vector& light, const Matrix cameraLook) {
        itModel_tmp.inverse_transpose(m.model);

        m.shader.use();
        Uniform::set(m.shader.id(), "model", m.model);
        Uniform::set(m.shader.id(), "projection", camera.projection);
        Uniform::set(m.shader.id(), "camera", look);
        Uniform::set(m.shader.id(), "eye", cameraLook);
        Uniform::set(m.shader.id(), "lightPos", light);
        Uniform::set(m.shader.id(), "itModel", itModel_tmp);

        // render the cube
        glBindVertexArray(m.vao);
        glDrawArrays(GL_TRIANGLES, 0, m.size);
    }
};

#endif
