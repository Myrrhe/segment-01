#ifndef STATICOBJECT_HPP
#define STATICOBJECT_HPP

namespace segment01
{
////////////////////////////////////////////////////////////
/// \brief Mother class for static classes
///
////////////////////////////////////////////////////////////
class StaticObject
{
public:
    StaticObject() = delete;
    StaticObject(const StaticObject &rhs) = delete;
    StaticObject(StaticObject &&rhs) = delete;
    StaticObject &operator=(const StaticObject &rhs) = delete;
    StaticObject &operator=(StaticObject &&rhs) = delete;
    ~StaticObject() = delete;
};

} // namespace segment01

#endif // STATICOBJECT_HPP
