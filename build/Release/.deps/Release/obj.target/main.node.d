cmd_Release/obj.target/main.node := g++ -shared -pthread -rdynamic -m64  -Wl,-soname=main.node -o Release/obj.target/main.node -Wl,--start-group Release/obj.target/main/src/main.o Release/obj.target/main/src/object-wrap.o Release/obj.target/main/src/object-factory.o Release/obj.target/main/src/addable.o Release/obj.target/node_modules/node-addon-api/src/nothing.a -Wl,--end-group 
