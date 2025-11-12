#pragma once
#include "core/NeonCommon.h"

class INeonPlugin {
public:
    virtual ~INeonPlugin() = default;
    virtual bool Initialize() = 0;
    virtual void Update() = 0;
    virtual void Shutdown() = 0;
    virtual const char* GetName() const = 0;
};
