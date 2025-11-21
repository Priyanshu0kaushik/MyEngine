//
//  ECS.h
//  MyEngine
//
//  Created by Priyanshu Kaushik on 16/11/2025.
//

#pragma once
#include <cstdint>
#include <bitset>

const size_t MAX_COMPONENTS = 50;

using Entity = uint32_t;
using Signature = std::bitset<MAX_COMPONENTS>;
using ComponentType = uint32_t;

const Entity MAX_ENTITIES = 5000;
constexpr Entity INVALID_ENTITY = 0;
