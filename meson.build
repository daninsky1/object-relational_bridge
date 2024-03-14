project(
    'object-relational_bridge',
    'cpp',
    default_options : ['c_std=c11', 'cpp_std=c++20']
)
sqlite3_dep = subproject('sqlite3')
sqlite3 = dependency('sqlite3', version : '>=3.45.1')
exe = executable(
    'main',
    'src/main.cpp',
    dependencies : sqlite3
)
