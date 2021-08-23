#include <glui.h>
#include <string.h>

wxField wxFieldCreate(Rect rect, unsigned int maxSize)
{
    wxField f;
    f.rect = rect;
    f.text_offset = vec3_new(0.0f, 0.0f, 0.7f);
    f.state = WIDGET_UNSELECTED;
    f.maxSize = maxSize;
    f.strMark = 0;
    memset(f.text, 0, 256);
    return f;
}

void wxFieldUpdate(wxField* field, vec2 mouse, bool pressed)
{
    bool hover = rect_point_overlap(mouse, field->rect);
    if (field->state == WIDGET_SELECTED) {
        if ((!hover && pressed) || glee_key_pressed(GLFW_KEY_ENTER)) {
            field->state = WIDGET_UNSELECTED;
            return;
        }

        char ch = glee_key_char();
        if (glee_key_pressed(GLFW_KEY_ENTER)) {
            field->text[field->strMark++] = '\n';
        }
        if (glee_key_pressed(GLFW_KEY_BACKSPACE) && field->strMark) {
            field->text[--field->strMark] = '\0';
        }
        if (ch != '\0' && field->strMark < field->maxSize) {
            field->text[field->strMark++] = ch;
        }
    } else if (hover) {
        field->state = WIDGET_HOVER;
        if (pressed) field->state = WIDGET_SELECTED;
    }
    else field->state = WIDGET_UNSELECTED;
}

void wxFieldDraw(wxField* field)
{   
    vec4 box = globalTheme.primary[field->state];
    vec4 font = globalTheme.secondary[field->state];
    
    wxRect rect = {field->rect, box};
    wxRectDraw(rect);

    vec2 fontPos = {field->rect.x - field->rect.w * 0.5f + field->text_offset.x, field->rect.y - field->rect.h * 0.5f + field->text_offset.y};
    fontDrawText(globalFont, field->text, fontPos.x, fontPos.y, (field->rect.h / 32.0f) * field->text_offset.z , vec3_new(font.x, font.y, font.z));
}
