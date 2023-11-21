#pragma once

#include <windows.h>

// 4DModLoader-Core hooking stuff for multihooking yea

__stdcall void Hook(LPVOID target, LPVOID detour, LPVOID* original) {
	reinterpret_cast<decltype(Hook)*>(GetProcAddress(GetModuleHandleA("4DModLoader-Core.dll"),"Hook"))(target, detour, original);
}
template<typename FuncPtr> void Hook( unsigned long long target, FuncPtr detour, FuncPtr* original ) {
	static_assert(
		std::is_function<typename std::remove_pointer<FuncPtr>::type>::value,
		"Hook must be called with a function and a pointer to a function of identical signature"
	);
	Hook( reinterpret_cast<LPVOID>(target), reinterpret_cast<LPVOID>(detour), reinterpret_cast<LPVOID*>(original) );
}
template<typename FuncPtr> void Hook( unsigned long long target, FuncPtr detour) {
	Hook( reinterpret_cast<LPVOID>(target), reinterpret_cast<LPVOID>(detour), nullptr );
}

__stdcall void EnableHook(LPVOID target){ // enables specific hook.
	reinterpret_cast<decltype(EnableHook)*>(GetProcAddress(GetModuleHandleA("4DModLoader-Core.dll"),"EnableHook"))(target);
}
void EnableHook(){ // enables every hook.
	EnableHook(nullptr);
}
