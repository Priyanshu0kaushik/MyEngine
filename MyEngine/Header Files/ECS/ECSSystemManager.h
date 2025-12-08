//
//  ECSSystemManager.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 17/11/2025.
//
#pragma once
#include "ECS.h"
#include "ECSSystem.h"
#include <map>

class ECSSystemManager
{
public:
    template<typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        const char* typeName = typeid(T).name();

        // Create a pointer to the system and return it so it can be used externally
        auto system = std::make_shared<T>();
        mSystems.insert({typeName, std::static_pointer_cast<ECSSystem>(system)});
        return system;
    }

    template<typename T>
    void SetSignature(Signature signature)
    {
        const char* typeName = typeid(T).name();

        // Set the signature for this system
        mSignatures.insert({typeName, signature});
    }

    void EntityDestroyed(Entity entity)
    {
        // Erase a destroyed entity from all system lists
        // mEntities is a set so no check needed
        for (auto const& pair : mSystems)
        {
            auto const& system = pair.second;
            auto& entities = system->mEntities;
            entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
        }
    }

    void EntitySignatureChanged(Entity entity, Signature entitySignature)
    {
        // Notify each system that an entity's signature changed
        for (auto const& pair : mSystems)
        {
            auto const& type = pair.first;
            auto const& system = pair.second;
            auto const& systemSignature = mSignatures[type];

            // Entity signature matches system signature - insert into set
            if ((entitySignature & systemSignature) == systemSignature)
            {
                system->mEntities.push_back(entity);
            }
            // Entity signature does not match system signature - erase from set
            else
            {
                auto& entities = system->mEntities;
                entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
            }
        }
    }

private:
    // Map from system type string pointer to a signature
    std::unordered_map<const char*, Signature> mSignatures{};

    // Map from system type string pointer to a system pointer
    std::unordered_map<const char*, std::shared_ptr<ECSSystem>> mSystems{};
};
