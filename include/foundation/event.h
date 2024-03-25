#ifndef _FOUNDATION_EVENT_H
#define _FOUNDATION_EVENT_H

#include <stdbool.h>

#include <foundation/input.h>
#include <foundation/point.h>
#include <foundation/size.h>

#ifdef __cplusplus
extern "C" {
#endif

enum ft_event_target_type {
    FT_EVENT_TARGET_TYPE_APPLICATION        = 1,
    FT_EVENT_TARGET_TYPE_DESKTOP_SURFACE    = 2,
    FT_EVENT_TARGET_TYPE_SURFACE            = 3,
    FT_EVENT_TARGET_TYPE_VIEW               = 4,
};

enum ft_event_type {
    FT_EVENT_TYPE_POINTER_ENTER             = 10,
    FT_EVENT_TYPE_POINTER_LEAVE             = 11,
    FT_EVENT_TYPE_POINTER_MOVE              = 12,
    FT_EVENT_TYPE_POINTER_PRESS             = 13,
    FT_EVENT_TYPE_POINTER_RELEASE           = 14,
    FT_EVENT_TYPE_POINTER_CLICK             = 15,
    FT_EVENT_TYPE_POINTER_DOUBLE_CLICK      = 16,
    FT_EVENT_TYPE_REQUEST_UPDATE            = 70,
    FT_EVENT_TYPE_MOVE                      = 100,
    FT_EVENT_TYPE_RESIZE                    = 101,
    FT_EVENT_TYPE_STATE_CHANGE              = 110,
};

typedef struct ft_event_t ft_event_t;

typedef struct ft_event_listener_tuple_t {
    enum ft_event_type type;
    void (*listener)(ft_event_t*);
} ft_event_listener_tuple_t;

typedef struct ft_pointer_event_t {
    ft_pointer_button button;
    ft_point_t position;
} ft_pointer_event_t;

typedef struct ft_move_event_t {
    ft_point_t old_position;
    ft_point_t position;
} ft_move_event_t;

typedef struct ft_resize_event_t {
    ft_size_t old_size;
    ft_size_t size;
} ft_resize_event_t;

/// \brief An event used when toplevel desktop surface state changed.
typedef struct ft_state_change_event_t {
    /// Must a valid value in `enum ft_desktop_surface_toplevel_state`.
    int state;
    ft_size_i_t size;
} ft_state_change_event_t;

struct ft_event_t {
    enum ft_event_target_type target_type;
    void *target;
    enum ft_event_type type;
    bool propagation;
    union {
        ft_pointer_event_t pointer;
        ft_move_event_t move;
        ft_resize_event_t resize;
        ft_state_change_event_t state_change;
    };
};

ft_event_t* ft_event_new(enum ft_event_target_type target_type,
                         void *target,
                         enum ft_event_type type);

enum ft_event_target_type ft_event_target_type(ft_event_t *event);

void* ft_event_target(ft_event_t *event);

enum ft_event_type ft_event_type(ft_event_t *event);

bool ft_event_propagation(ft_event_t *event);

void ft_event_set_propagation(ft_event_t *event, bool value);

/// \brief Returns `event->resize.old_size`.
const ft_size_t* ft_event_resize_old_size(ft_event_t *event);

/// \brief Returns `event->resize.size`.
const ft_size_t* ft_event_resize_size(ft_event_t *event);

void ft_event_free(ft_event_t *event);

//!<=================
//!< Pointer Event
//!<=================

ft_event_t* ft_pointer_event_new(enum ft_event_target_type target_type,
                                 void *target,
                                 enum ft_event_type type,
                                 ft_pointer_button button,
                                 const ft_point_t *position);

ft_pointer_button ft_pointer_event_button(ft_pointer_event_t *event);

//!<=====================
//!< Event Listener
//!<=====================

ft_event_listener_tuple_t*
ft_event_listener_tuple_new(enum ft_event_type type,
                            void (*listener)(ft_event_t*));

void ft_event_listener_tuple_free(ft_event_listener_tuple_t *tuple);

#ifdef __cplusplus
}
#endif

#endif /* _FOUNDATION_EVENT_H */
