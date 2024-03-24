#ifndef _FOUNDATION_DESKTOP_SURFACE_H
#define _FOUNDATION_DESKTOP_SURFACE_H

#include <foundation/event.h>

typedef struct ft_size_i_t ft_size_i_t;
typedef struct ft_rect_i_t ft_rect_i_t;
typedef struct ft_surface_t ft_surface_t;

typedef enum ft_desktop_surface_role {
    FT_DESKTOP_SURFACE_ROLE_TOPLEVEL,
    FT_DESKTOP_SURFACE_ROLE_POPUP,
} ft_desktop_surface_role;

typedef enum ft_desktop_surface_toplevel_resize_edge {
    FT_DESKTOP_SURFACE_TOPLEVEL_RESIZE_EDGE_NONE            = 0,
    FT_DESKTOP_SURFACE_TOPLEVEL_RESIZE_EDGE_TOP             = 1,
    FT_DESKTOP_SURFACE_TOPLEVEL_RESIZE_EDGE_BOTTOM          = 2,
    FT_DESKTOP_SURFACE_TOPLEVEL_RESIZE_EDGE_LEFT            = 4,
    FT_DESKTOP_SURFACE_TOPLEVEL_RESIZE_EDGE_TOP_LEFT        = 5,
    FT_DESKTOP_SURFACE_TOPLEVEL_RESIZE_EDGE_BOTTOM_LEFT     = 6,
    FT_DESKTOP_SURFACE_TOPLEVEL_RESIZE_EDGE_RIGHT           = 8,
    FT_DESKTOP_SURFACE_TOPLEVEL_RESIZE_EDGE_TOP_RIGHT       = 9,
    FT_DESKTOP_SURFACE_TOPLEVEL_RESIZE_EDGE_BOTTOM_RIGHT    = 10,
} ft_desktop_surface_toplevel_resize_edge;

enum ft_desktop_surface_toplevel_state {
    FT_DESKTOP_SURFACE_TOPLEVEL_STATE_NORMAL            = 0,
    FT_DESKTOP_SURFACE_TOPLEVEL_STATE_MAXIMIZED         = 1,
    FT_DESKTOP_SURFACE_TOPLEVEL_STATE_FULLSCREEN        = 2,
    FT_DESKTOP_SURFACE_TOPLEVEL_STATE_RESIZING          = 3,
    FT_DESKTOP_SURFACE_TOPLEVEL_STATE_ACTIVATED         = 4,
    FT_DESKTOP_SURFACE_TOPLEVEL_STATE_TILED_LEFT        = 5,
    FT_DESKTOP_SURFACE_TOPLEVEL_STATE_TILED_RIGHT       = 6,
    FT_DESKTOP_SURFACE_TOPLEVEL_STATE_TILED_TOP         = 7,
    FT_DESKTOP_SURFACE_TOPLEVEL_STATE_TILED_BOTTOM      = 8,
    FT_DESKTOP_SURFACE_TOPLEVEL_STATE_SUSPENDED         = 9,
};

typedef struct ft_desktop_surface_t ft_desktop_surface_t;

ft_desktop_surface_t* ft_desktop_surface_new(ft_desktop_surface_role role);

/// \brief Get the surface object of the desktop surface.
ft_surface_t*
ft_desktop_surface_surface(ft_desktop_surface_t *desktop_surface);

void ft_desktop_surface_show(ft_desktop_surface_t *desktop_surface);

void ft_desktop_surface_hide(ft_desktop_surface_t *desktop_surface);

/// \brief Tell the geometry is the actual window area to the compositor.
///
/// A Wayland client is CSD (client side decoration). It means the window
/// should draw it's own decorations such as shadow.
/// The shadow may not clickable.
///
/// This method tells to the compositor (window manager) to ignore the events
/// which is out of the given geometry.
void ft_desktop_surface_set_wm_geometry(ft_desktop_surface_t *desktop_surface,
                                        const ft_rect_i_t *geometry);

const ft_size_i_t*
ft_desktop_surface_toplevel_minimum_size(ft_desktop_surface_t *desktop_surface);

/// \brief Set minimum size of the toplevel desktop surface.
///
/// This changes the field and call `_set_min_size` method in XDG toplevel.
void ft_desktop_surface_toplevel_set_minimum_size(
    ft_desktop_surface_t *desktop_surface, const ft_size_i_t *size);

void ft_desktop_surface_toplevel_close(ft_desktop_surface_t *desktop_surface);

void ft_desktop_surface_toplevel_move(ft_desktop_surface_t *desktop_surface);

void ft_desktop_surface_toplevel_resize(ft_desktop_surface_t *desktop_surface,
    ft_desktop_surface_toplevel_resize_edge edge);

void ft_desktop_surface_add_event_listener(
    ft_desktop_surface_t *desktop_surface,
    enum ft_event_type event_type,
    void (*listener)(ft_event_t*));

void ft_desktop_surface_on_resize(ft_desktop_surface_t *desktop_surface,
                                  ft_event_t *event);

void ft_desktop_surface_on_toplevel_state_change(
    ft_desktop_surface_t *desktop_surface,
    ft_event_t *event);

#endif /* _FOUNDATION_DESKTOP_SURFACE_H */
