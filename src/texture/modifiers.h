/**
 * This header declares uv modifiers, which are a modular
 * way to augment the uv coordinates to allow things like:
 * - offsetting
 * - flipping
 *
 * These modifiers can be stacked on top of each other in
 * any way you like.
 */
#pragma once

#include "texture.h"

#include <cmath>
#include <memory>


class uv_modifier : public Texture
{
public:
    // Just for convenience...
    using texture_t = std::shared_ptr<Texture>;

public:
    uv_modifier(texture_t t) : t(t) {}

    Color Value(double u,
                double v,
                const Point3& p) const override
    {
        this->Modify(u, v);
        return t->Value(u, v, p);
    }

    /**
     * The core of each modifier - performing some
     * manipulation on the uv coordinates.
     */
    virtual void Modify(double& u, double& v) const = 0;

private:
    texture_t t;
};

#define MOD_NAME(x) x##_modifier

/**
 * Declare a new uv modifier. You must declare a struct with
 * the parameters you require, and pass it to this macro in
 * this fashion (inspired by gtest):
 *
 *   struct mod { int number; };
 *
 *   UV_MODIFIER(mod)
 *   {
 *       u = f(u, n);
 *       v = f(v, n)
 *   }
 *
 * You then use it like so:
 *   
 *   const auto texture = std::make_shared<SomeTexture>(...)
 *      | mod{10}
 *      | mod{20}        // Can be chained to itself
 *      | strech_u{2.0}  // Or with any other modifier
 */
#define UV_MODIFIER(x)                                      \
    class MOD_NAME(x) : public uv_modifier                  \
    {                                                       \
    public:                                                 \
        MOD_NAME(x)(texture_t t, x params)                  \
            : uv_modifier(t),                               \
              params(params)                                \
        {}                                                  \
                                                            \
        void Modify(double& u, double& v) const override;   \
                                                            \
    private:                                                \
        x params;                                           \
    };                                                      \
                                                            \
    uv_modifier::texture_t operator|(                       \
        uv_modifier::texture_t t, x m)                      \
    {                                                       \
        return std::make_shared<MOD_NAME(x)>(t, m);         \
    }                                                       \
                                                            \
    void MOD_NAME(x)::Modify(double& u, double& v) const


static double offset_uv_component(double c, double o)
{
    return fmod(c + o, 1.0);

}

struct offset_v
{
    double offset;
};

UV_MODIFIER(offset_v)
{
    v = offset_uv_component(v, params.offset);
}

struct offset_u
{
    double offset;
};

UV_MODIFIER(offset_u)
{
    u = offset_uv_component(u, params.offset);
}

struct flip_u {};

UV_MODIFIER(flip_u)
{
    u = 1.0 - u;
}

struct flip_v {};

UV_MODIFIER(flip_v)
{
    v = 1.0 - v;
}
