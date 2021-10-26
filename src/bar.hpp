// somebar - dwl bar
// See LICENSE file for copyright and license details.

#pragma once
#include <optional>
#include <vector>
#include <wayland-client.h>
#include <QString>
#include <QFontMetrics>
#include <QPainter>
#include "wlr-layer-shell-unstable-v1-client-protocol.h"
#include "common.hpp"
#include "shm_buffer.hpp"

struct Tag {
    znet_tapesoftware_dwl_wm_monitor_v1_tag_state state;
    int numClients;
    int focusedClient;
    int x;
};

struct Monitor;
class Bar {
    static const zwlr_layer_surface_v1_listener _layerSurfaceListener;
    static const wl_callback_listener _frameListener;

    wl_unique_ptr<wl_surface> _surface;
    wl_unique_ptr<zwlr_layer_surface_v1> _layerSurface;
    Monitor *_mon;
    QPainter *_painter {nullptr};
    std::optional<ShmBuffer> _bufs;
    int _textY, _x;
    int _statusX, _titleX, _layoutX;
    bool _invalid {false};

    std::vector<Tag> _tags;
    int _layout;
    bool _selected;
    QString _title;
    QString _status;

    void layerSurfaceConfigure(uint32_t serial, uint32_t width, uint32_t height);
    void render();
    void renderTags();
    void renderStatus();
    void renderText(const QString &text);
    int textWidth(const QString &text);
    void setColorScheme(const ColorScheme &scheme);
public:
    Bar(Monitor *mon);
    const wl_surface* surface() const;
    void create(wl_output *output);
    void setSelected(bool selected);
    void setTag(int tag, znet_tapesoftware_dwl_wm_monitor_v1_tag_state state, int numClients, int focusedClient);
    void setLayout(int layout);
    void setTitle(const char *title);
    void setStatus(const QString &status);
    void invalidate();
    void click(int x, int y, int btn, unsigned int modifiers);
};
