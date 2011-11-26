/* rbSFML
 * Copyright (c) 2010 Henrik Valter Vogelius Hansson - groogy@groogy.se
 * This software is provided 'as-is', without any express or implied warranty.
 * In no event will the authors be held liable for any damages arising from
 * the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software in
 *    a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
 */

#ifndef WINDOW_WINDOW_HPP
#define WINDOW_WINDOW_HPP

#include <ruby.h>
#include <rbSFML.hpp>
#include <System/SFML.hpp>
#include <System/Vector2.hpp>
#include <Window/ContextSettings.hpp>
#include <Window/Event.hpp>
#include <Window/VideoMode.hpp>

#include <SFML/Window/Window.hpp>

namespace rbWindow
{
    
    static inline void Free(void* window);
    
    static inline VALUE ToRuby(VALUE other);
    static inline VALUE ToRuby(sf::Window* window);
    static inline VALUE ToRuby(sf::Window& window);
    static inline sf::Window* ToSFML(VALUE window);
    
    static inline VALUE Allocate(VALUE);
    
#if defined(WINDOW_WINDOW_CPP)
    VALUE Window;
#else
    extern VALUE Window;
#endif
    
#if defined(RBSFML_WINDOW)
    
    void Init(VALUE SFML);
    
    // Window#initialize(...)
    static VALUE Initialize(int argc, VALUE args[], VALUE self);
    
    // Window#clone
    static VALUE Clone(VALUE self);
    
    // Window#dup
    static VALUE Dup(VALUE self);
    
    // Window#create(...)
    // Window#Create(...)
    static VALUE Create(int argc, VALUE args[], VALUE self);
    
    // Window#close
    // Window#Close
    static VALUE Close(VALUE self);
    
    // Window#opened?
    // Window#IsOpened
    // Window#open?
    static VALUE IsOpened(VALUE self);
    
    // Window#width
    // Window#GetWidth
    static VALUE GetWidth(VALUE self);
    
    // Window#height
    // Window#GetHeight
    static VALUE GetHeight(VALUE self);
    
    // Window#settings
    // Window#GetSettings
    static VALUE GetSettings(VALUE self);
    
    // Window#poll_event
    // Window#PollEvent
    // Window#poll_event(event)
    // Window#PollEvent(event)
    static VALUE PollEvent(int argc, VALUE argv[], VALUE self);
    
    // Window#wait_event
    // Window#WaitEvent
    // Window#wait_event(event)
    // Window#WaitEvent(event)
    static VALUE WaitEvent(int argc, VALUE argv[], VALUE self);
    
    // Window#each_event
    static VALUE EachEvent(VALUE self);
    
    // Window#vertical_sync=(enabled)
    // Window#EnableVerticalSync(enabled)
    // Window#vertical_sync(enabled)
    static VALUE EnableVerticalSync(VALUE self, VALUE enabled);
    
    // Window#mouse_cursor=(show)
    // Window#ShowMouseCursor(show)
    // Window#mouse_cursor(show)
    static VALUE ShowMouseCursor(VALUE self, VALUE show);
    
    // Window#position(x, y)
    // Window#Position(x, y)
    static VALUE SetPosition(VALUE self, VALUE x, VALUE y);
    
    // Window#position=(vector2)
    static VALUE SetPosition2(VALUE self, VALUE vector2);
    
    // Window#size(width, height)
    // Window#Size(width, height)
    static VALUE SetSize(VALUE self, VALUE width, VALUE height);
    
    // Window#size=(vector2)
    static VALUE SetSize2(VALUE self, VALUE vector2);
    
    // Window#title=(title)
    // Window#SetTitle(title)
    // Window#title(title)
    static VALUE SetTitle(VALUE self, VALUE title);
    
    // Window#show=(show)
    // Window#Show(show)
    // Window#show(show)
    static VALUE Show(VALUE self, VALUE show);
    
    // Window#key_repeat=(enabled)
    // Window#EnableKeyRepeat(enabled)
    // Window#key_repeat(enabled)
    static VALUE EnableKeyRepeat(VALUE self, VALUE enabled);
    
    // Window#icon(width, height, pixels)
    // Window#SetIcon(width, height, pixels)
    static VALUE SetIcon(VALUE self, VALUE width, VALUE height, VALUE pixels);
    
    // Window#active(active)
    // Window#SetActive(active)
    // Window#active=(active)
    static VALUE SetActive(VALUE self, VALUE active);
    
    // Window#display(active)
    // Window#Display(active)
    static VALUE Display(VALUE self);
    
    // Window#framerate=(limit)
    // Window#SetFramerateLimit(limit)
    // Window#framerate(limit)
    // Window#framerate_limit=(limit)
    // Window#framerate_limit(limit)
    static VALUE SetFramerateLimit(VALUE self, VALUE limit);
    
    // Window#frame_time
    // Window#GetFrameTime
    // Window#time
    static VALUE GetFrameTime(VALUE self);
    
    // Window#joystick_threshold=(threshold)
    // Window#SetJoystickThreshold(threshold)
    // Window#joystick_threshold(threshold)
    static VALUE SetJoystickThreshold(VALUE self, VALUE threshold);
    
    // Window#system_handle
    // Window#GetSystemHandle
    // Window#handle
    static VALUE GetSystemHandle(VALUE self);
    
    // Window#inspect
    // Window#to_s
    static VALUE Inspect(VALUE self);

    // Window#memory_usage
    static VALUE GetMemoryUsage(VALUE self);
    
#endif
    
}

void rbWindow::Free(void* window)
{
    delete (sf::Window*)window;
}

VALUE rbWindow::Allocate(VALUE)
{
    sf::Window* window = new(std::nothrow) sf::Window;
    if (window == NULL) rb_memerror();
    return ToRuby(window);
}

VALUE rbWindow::ToRuby(VALUE other)
{
    if (rb_obj_is_instance_of(other, Window))
    {
        return other;
    }
    else
    {
        rb_raise(rb_eTypeError,
                 "can't convert %s into Window", rb_obj_classname(other));
    }
}

VALUE rbWindow::ToRuby(sf::Window* window)
{
    return rb_data_object_alloc(Window, window, NULL, Free);
}

VALUE rbWindow::ToRuby(sf::Window& window)
{
    return rb_data_object_alloc(Window, &window, NULL, NULL);
}

sf::Window* rbWindow::ToSFML(VALUE window)
{
    window = ToRuby(window);
    return (sf::Window*)DATA_PTR(window);
}

#endif // WINDOW_WINDOW_HPP
