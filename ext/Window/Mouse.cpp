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

#define WINDOW_MOUSE_CPP
#include "Mouse.hpp"

void rbMouse::Init(VALUE SFML)
{
    Mouse = rb_define_module_under(SFML, "Mouse");
    
    rb_define_const(Mouse, "Left",        INT2FIX(sf::Mouse::Left    ));
    rb_define_const(Mouse, "Right",       INT2FIX(sf::Mouse::Right   ));
    rb_define_const(Mouse, "Middle",      INT2FIX(sf::Mouse::Middle  ));
    rb_define_const(Mouse, "XButton1",    INT2FIX(sf::Mouse::XButton1));
    rb_define_const(Mouse, "XButton2",    INT2FIX(sf::Mouse::XButton2));
    
    // Singleton methods
    rb_define_singleton_method(Mouse, "button_pressed?", IsButtonPressed,  1);
    rb_define_singleton_method(Mouse, "position",        Position,        -1);
    rb_define_singleton_method(Mouse, "GetPosition",     GetPosition,     -1);
    rb_define_singleton_method(Mouse, "SetPosition",     SetPosition,     -1);
    
    // Singleton aliasses
    VALUE sMouse = rb_singleton_class(Mouse);
    rb_define_alias(sMouse, "IsButtonPressed", "button_pressed?");
    rb_define_alias(sMouse, "pressed?",        "button_pressed?");
    rb_define_alias(sMouse, "position=",       "position"       );
}

// Mouse::button_pressed?(button)
// Mouse::IsButtonPressed(button)
// Mouse::pressed?(button)
VALUE rbMouse::IsButtonPressed(VALUE self, VALUE button)
{
    sf::Mouse::Button btn = static_cast<sf::Mouse::Button>(NUM2INT(button));
    return RBOOL(sf::Mouse::IsButtonPressed(btn));
}

// Mouse::position
// Mouse::position(relative_to)
// Mouse::position(position)
// Mouse::position=(position)
// Mouse::position(position, relative_to)
VALUE rbMouse::Position(int argc, VALUE argv[], VALUE self)
{
    switch (argc)
    {
        case 0:
            return GetPosition(argc, argv, self);
        case 1:
            if (rb_obj_is_kind_of(argv[0], rbWindow::Window))
                return GetPosition(argc, argv, self);
            else
                return SetPosition(argc, argv, self);
        case 2:
            return SetPosition(argc, argv, self);
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0..2)", argc);
    }
    return Qnil;
}

// Mouse::GetPosition
// Mouse::GetPosition(relative_to)
VALUE rbMouse::GetPosition(int argc, VALUE argv[], VALUE self)
{
    sf::Vector2i pos;
    switch (argc)
    {
        case 0:
            pos = sf::Mouse::GetPosition();
        case 1:
            pos = sf::Mouse::GetPosition(*rbWindow::ToSFML(argv[0]));
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 0..1)", argc);
    }
    return rbVector2::ToRuby(pos);
}

// Mouse::SetPosition(position)
// Mouse::SetPosition(position, relative_to)
VALUE rbMouse::SetPosition(int argc, VALUE argv[], VALUE self)
{
    switch (argc)
    {
        case 1:
        {
            sf::Vector2i pos = rbVector2::ToSFMLi(argv[0]);
            sf::Mouse::SetPosition(pos);
            break;
        }
        case 2:
        {
            sf::Vector2i pos = rbVector2::ToSFMLi(argv[0]);
            sf::Window* window = rbWindow::ToSFML(argv[1]);
            sf::Mouse::SetPosition(pos, *window);
            break;
        }
        default:
            rb_raise(rb_eArgError,
                     "wrong number of arguments(%i for 1..2)", argc);
    }
    return Qnil;
}
