#ifndef ENTITY_H
#define ENTITY_H

// PURE ABSTRACT INTERFACE
// - all entities must define the update method
class Entity
{
    public:
        virtual void Update () = 0;
};

#endif // ENTITY_H
