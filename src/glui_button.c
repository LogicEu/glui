#include <glui.h>
#include <string.h>

wxButton wxButtonCreate(const char* text, Rect rect)
{
    wxButton w;
    w.state = WIDGET_UNSELECTED;
    strcpy(w.text, text);
    w.rect = rect;
    w.text_offset = vec3_new(0.0f, 0.0f, 0.7f);
    return w;
}

void wxButtonUpdate(wxButton* w, vec2 mouse, bool pressed)
{
    w->state = rect_point_overlap(mouse, w->rect);
    if (w->state && pressed) w->state = WIDGET_SELECTED;
}

void wxButtonDraw(wxButton* w)
{
    vec4 box = globalTheme.primary[w->state];
    vec4 font = globalTheme.secondary[w->state];
    
    wxRect rect = {w->rect, box};
    wxRectDraw(rect);

    vec2 fontPos = {w->rect.x - w->rect.w * 0.5f + w->text_offset.x, w->rect.y - w->rect.h * 0.5f + w->text_offset.y};
    fontDrawText(globalFont, w->text, fontPos.x, fontPos.y, (w->rect.h / 32.0f) * w->text_offset.z , vec3_new(font.x, font.y, font.z));
}