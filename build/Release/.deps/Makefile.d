cmd_Makefile := cd ..; /home/bruce/tmp/node-cc-api/node_modules/node-gyp/gyp/gyp_main.py -fmake --ignore-environment "--toplevel-dir=." -I/home/bruce/tmp/node-cc-api/build/config.gypi -I/home/bruce/tmp/node-cc-api/node_modules/node-gyp/addon.gypi -I/home/bruce/.node-gyp/8.11.3/include/node/common.gypi "--depth=." "-Goutput_dir=." "--generator-output=build" "-Dlibrary=shared_library" "-Dvisibility=default" "-Dnode_root_dir=/home/bruce/.node-gyp/8.11.3" "-Dnode_gyp_dir=/home/bruce/tmp/node-cc-api/node_modules/node-gyp" "-Dnode_lib_file=/home/bruce/.node-gyp/8.11.3/<(target_arch)/node.lib" "-Dmodule_root_dir=/home/bruce/tmp/node-cc-api" "-Dnode_engine=v8" binding.gyp