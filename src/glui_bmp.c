#include <glui.h>

#define _utof(u) ((float)(u) / 255.0f)
#define _px_at(bmp, x, y) (bmp->pixels + (bmp->width * (y) + (x)) * bmp->channels)

void bmpDraw(bmp_t* bmp, float xPos, float yPos, float scale)
{
    glUseProgram(widgetShader);
    glBindVertexArray(widgetVAO);

    float wPos = xPos - (float)bmp->width * scale * 0.5f;
    float hPos = yPos - (float)bmp->height * scale * 0.5f;

    for (unsigned int y = 0; y < bmp->width; y++) {
        for (unsigned int x = 0; x < bmp->height; x++) {
            uint8_t* px = _px_at(bmp, x, y);
            vec4 c = {
                _utof(px[0]),
                _utof(px[1]),
                _utof(px[2]),
                _utof(px[3])
            };

            float dx = wPos + (float)x * scale;
            float dy = hPos + (float)y * scale;

            float rect[] = {
                dx, dy,
                dx + scale, dy + scale
            };

            float vertices[] = {
                rect[0], rect[1],
                rect[0], rect[3],
                rect[2], rect[3],
                rect[0], rect[1],
                rect[2], rect[3],
                rect[2], rect[1]
            };

            glUniform4f(glGetUniformLocation(widgetShader, "color"), c.x, c.y, c.z, c.w);
            glBindBuffer(GL_ARRAY_BUFFER, widgetVBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }
    }
    glBindVertexArray(0);
}