#pragma once

#ifdef DEBUG_MODE_ENABLED
#define IF_DEBUG_MODE_ENABLED(expr) expr;
#else
#define IF_DEBUG_MODE_ENABLED()
#endif
