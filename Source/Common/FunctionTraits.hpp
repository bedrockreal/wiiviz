#pragma once

template <typename ReturnType, typename ClassType, typename... Args>
struct MethodTraits<ReturnType(ClassType::*)(Args)>
