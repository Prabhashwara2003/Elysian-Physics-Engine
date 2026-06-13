#pragma once

#ifndef PHYSICSENGINE_STATIC
  #ifdef PHYSICSENGINE_EXPORTS
    #define PHYSICSENGINE_API __declspec(dllexport)
  #else
    #define PHYSICSENGINE_API __declspec(dllimport)
  #endif
#else
  #define PHYSICSENGINE_API
#endif
