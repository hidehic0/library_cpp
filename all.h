#if __has_include(<atcoder/all>)
#include <atcoder/all>
#endif

#include <bits/stdc++.h>

#ifdef ONLINE_JUDGE
#define dump(...)
#define CPP_DUMP_SET_OPTION(...)
#define CPP_DUMP_SET_OPTION_GLOBAL(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT_GENERIC(...)
#define export_command
#elif __has_include(<cpp-dump/cpp-dump.hpp>)
#include <cpp-dump/cpp-dump.hpp>
#define dump(...) cpp_dump(__VA_ARGS__)
#else
#define dump(...)
#define CPP_DUMP_SET_OPTION(...)
#define CPP_DUMP_SET_OPTION_GLOBAL(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT(...)
#define CPP_DUMP_DEFINE_EXPORT_ENUM(...)
#define CPP_DUMP_DEFINE_EXPORT_OBJECT_GENERIC(...)
#define export_command
#endif

#include "templates/alias.hpp"
#include "templates/macro.hpp"

#include "grid/template.hpp"

#include "utils/compress.hpp"
#include "utils/factorial.hpp"

#include "data-structure/range_set.hpp"
#include "data-structure/removable_priority_queue.hpp"
#include "data-structure/unionfind.hpp"

#include "matrix/matrix.hpp"
