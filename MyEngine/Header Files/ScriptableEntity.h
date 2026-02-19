//
//  ScriptableEntity.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 16/02/2026.
//

#pragma once
#include "ECS/Coordinator.h" // Tera ECS head

class ScriptableEntity {
public:
    virtual ~ScriptableEntity() {}

    // --- EVENTS (Virtual functions jo user override karega) ---
    virtual void OnCreate() {}      // Unity's Start / Unreal's BeginPlay
    virtual void OnUpdate(float dt) {} // Unity's Update / Unreal's Tick
    virtual void OnCollision(Entity other) {} // Collision event

    // --- HELPERS (Taki script ke andar se kaam asaan ho) ---
    template<typename T>
    T* GetComponent() {
        return m_Coordinator->GetComponent<T>(m_Entity);
    }

protected:
    Entity m_Entity;
    Coordinator* m_Coordinator;

    // Sirf ScriptSystem hi in variables ko set kar paye
    friend class ScriptSystem;
};
